#include "H264Encoder.h"

#include <iostream>
#include <cstring>

H264Encoder::H264Encoder()
{
}

H264Encoder::~H264Encoder()
{
    shutdown();
}

bool H264Encoder::init(
    UINT32 width,
    UINT32 height,
    UINT32 fps,
    UINT32 bitrate
)
{
    m_width = width;
    m_height = height;
    m_fps = fps;
    m_bitrate = bitrate;

    if (WelsCreateSVCEncoder(&m_encoder) != 0)
    {
        std::cout << "WelsCreateSVCEncoder failed" << std::endl;
        return false;
    }

    SEncParamExt param;

    memset(&param, 0, sizeof(param));

    m_encoder->GetDefaultParams(&param);

    param.iUsageType = CAMERA_VIDEO_REAL_TIME;

    param.fMaxFrameRate =
        static_cast<float>(fps);

    param.iPicWidth =
        width;

    param.iPicHeight =
        height;

    param.iTargetBitrate =
        bitrate;

    param.iRCMode =
        RC_BITRATE_MODE;

    param.bEnableFrameSkip =
        false;

    param.uiIntraPeriod =
        fps;

    param.iSpatialLayerNum = 1;

    param.sSpatialLayers[0].iVideoWidth =
        width;

    param.sSpatialLayers[0].iVideoHeight =
        height;

    param.sSpatialLayers[0].fFrameRate =
        static_cast<float>(fps);

    param.sSpatialLayers[0].iSpatialBitrate =
        bitrate;

    if (m_encoder->InitializeExt(&param) != cmResultSuccess)
    {
        std::cout << "InitializeExt failed" << std::endl;
        return false;
    }
    m_i420.resize(
        width * height * 3 / 2
    );
    return true;
}


static void NV12ToI420(
    const uint8_t* nv12,
    uint8_t* i420,
    int width,
    int height)
{
    const int ySize = width * height;
    const int uvSize = ySize / 4;

    uint8_t* dstY = i420;
    uint8_t* dstU = dstY + ySize;
    uint8_t* dstV = dstU + uvSize;

    memcpy(dstY, nv12, ySize);

    const uint8_t* srcUV = nv12 + ySize;

    for (int y = 0; y < height / 2; ++y)
    {
        for (int x = 0; x < width / 2; ++x)
        {
            dstU[y * (width / 2) + x] =
                srcUV[y * width + x * 2];

            dstV[y * (width / 2) + x] =
                srcUV[y * width + x * 2 + 1];
        }
    }
}
bool H264Encoder::encode(
    const uint8_t* nv12Data,
    DWORD,
    LONGLONG,
    std::vector<uint8_t>& nal)
{
    nal.clear();

    if (!m_encoder)
        return false;

    NV12ToI420(
        nv12Data,
        m_i420.data(),
        m_width,
        m_height
    );

    const int ySize =
        m_width * m_height;

    const int uvSize =
        ySize / 4;

    SSourcePicture pic;

    memset(
        &pic,
        0,
        sizeof(pic)
    );

    pic.iPicWidth =
        m_width;

    pic.iPicHeight =
        m_height;

    pic.iColorFormat =
        videoFormatI420;

    pic.iStride[0] =
        m_width;

    pic.iStride[1] =
        m_width / 2;

    pic.iStride[2] =
        m_width / 2;

    pic.pData[0] =
        m_i420.data();

    pic.pData[1] =
        m_i420.data() + ySize;

    pic.pData[2] =
        m_i420.data() + ySize + uvSize;

    SFrameBSInfo info;

    memset(
        &info,
        0,
        sizeof(info)
    );

    int result =
        m_encoder->EncodeFrame(
            &pic,
            &info
        );

    if (result != cmResultSuccess)
    {
        std::cout
            << "EncodeFrame failed "
            << result
            << std::endl;

        return false;
    }

    // std::cout
    //     << "FrameType="
    //     << info.eFrameType
    //     << " Layers="
    //     << info.iLayerNum
    //     << std::endl;

    if (info.eFrameType ==
        videoFrameTypeSkip)
    {
        return false;
    }

    for (int layer = 0;
         layer < info.iLayerNum;
         ++layer)
    {
        SLayerBSInfo& layerInfo =
            info.sLayerInfo[layer];

        int offset = 0;

        for (int n = 0;
             n < layerInfo.iNalCount;
             ++n)
        {
            int nalSize =
                layerInfo.pNalLengthInByte[n];

            nal.insert(
                nal.end(),
                layerInfo.pBsBuf + offset,
                layerInfo.pBsBuf + offset + nalSize
            );

            offset += nalSize;
        }
    }

    // std::cout
    //     << "NAL bytes="
    //     << nal.size()
    //     << std::endl;

    return !nal.empty();
}

void H264Encoder::shutdown()
{
    if (m_encoder)
    {
        m_encoder->Uninitialize();

        WelsDestroySVCEncoder(
            m_encoder
        );

        m_encoder = nullptr;
    }
}