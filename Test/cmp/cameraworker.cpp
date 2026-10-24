#include"cameraworker.h"
#include<thread>
#include<QImage>
#include<Windows.h>
#include<mfapi.h>
#include<mfidl.h>
#include<mfobjects.h>
#include<iostream>
#include<mferror.h>
#include<mfreadwrite.h>
#include <mftransform.h>
#include <codecapi.h>
#include<vector>
#include <wmcodecdsp.h>
#include <wels/codec_api.h>

QImage NV12ToQImage(
    BYTE* nv12,
    int width,
    int height
)
{
    QImage img(
        width,
        height,
        QImage::Format_RGB888
    );

    BYTE* yPlane = nv12;
    BYTE* uvPlane = nv12 + width * height;

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            int Y = yPlane[y * width + x];

            int uvIndex =
                (y / 2) * width +
                (x & ~1);

            int U =
                uvPlane[uvIndex] - 128;

            int V =
                uvPlane[uvIndex + 1] - 128;

            int C = Y - 16;
            int D = U;
            int E = V;

            int R =
                (298 * C + 409 * E + 128) >> 8;

            int G =
                (298 * C - 100 * D - 208 * E + 128) >> 8;

            int B =
                (298 * C + 516 * D + 128) >> 8;

            R = std::clamp(R, 0, 255);
            G = std::clamp(G, 0, 255);
            B = std::clamp(B, 0, 255);

            img.setPixel(
                x,
                y,
                qRgb(R, G, B)
            );
        }
    }

    return img;
}
void CameraWorker::start(){
    std::thread([this](){
        
    CoInitializeEx(
    NULL,
    COINIT_MULTITHREADED
    );

    HRESULT hr = MFStartup(MF_VERSION);
    if (FAILED(hr)){
        // std::cout << "MFStartup failed\n";
        return;
    }
     if (!m_encoder.init(1280,720,30,4000000))
    {
        std::cout << "encoder init failed" << std::endl;
        // return;
    }
   

    IMFMediaSource *ppSource = NULL;
    // *ppSource=NULL;
    IMFAttributes *pConfig=NULL;
    IMFActivate **ppDevice=NULL;
    UINT32 count=0;
    hr=MFCreateAttributes(&pConfig,1);
    if(SUCCEEDED(hr)){
        hr=pConfig->SetGUID(
            MF_DEVSOURCE_ATTRIBUTE_SOURCE_TYPE,
            MF_DEVSOURCE_ATTRIBUTE_SOURCE_TYPE_VIDCAP_GUID
        );
    }
    if(SUCCEEDED(hr)){
        // std::cout<<"Added data"<<std::endl;
        hr=MFEnumDeviceSources(pConfig,&ppDevice,&count);
    }
    if(SUCCEEDED(hr)){
        // std::cout<<"Number if Devices used are : "<<count<<std::endl;
        if(count>0){
            hr=ppDevice[0]->ActivateObject(IID_PPV_ARGS(&ppSource));
            WCHAR *szFriendlyName = NULL;
            UINT32 cchName;
            hr = ppDevice[0]->GetAllocatedString(
                MF_DEVSOURCE_ATTRIBUTE_FRIENDLY_NAME,
                &szFriendlyName, &cchName);
            std::wcout<<szFriendlyName<<std::endl;
            CoTaskMemFree(szFriendlyName);
        }else{
            hr=MF_E_NOT_FOUND;
        }
    }
    IMFSourceReader* pReader=NULL;
    IMFAttributes* pReaderAttr = NULL;
    hr = MFCreateAttributes(
        &pReaderAttr,
        2
    );
    // if (SUCCEEDED(hr)){
    //     hr = pReaderAttr->SetUINT32(
    //         MF_READWRITE_DISABLE_CONVERTERS,
    //         TRUE
    //     );
    // }
    if (SUCCEEDED(hr)){
        hr = MFCreateSourceReaderFromMediaSource(
            ppSource,
            pReaderAttr,
            &pReader
        );
    }
    IMFMediaType* pType = NULL;

    hr = MFCreateMediaType(&pType);

    hr = pType->SetGUID(
        MF_MT_MAJOR_TYPE,
        MFMediaType_Video
    );

    hr = pType->SetGUID(
        MF_MT_SUBTYPE,
        MFVideoFormat_NV12
    );

    hr = MFSetAttributeSize(
        pType,
        MF_MT_FRAME_SIZE,
        1280,
        720
    );

    hr = MFSetAttributeRatio(
        pType,
        MF_MT_FRAME_RATE,
        30,
        1
    );

    hr = pReader->SetCurrentMediaType(
        MF_SOURCE_READER_FIRST_VIDEO_STREAM,
        NULL,
        pType
    );

    std::cout << "SetCurrentMediaType hr=0x"
            << std::hex
            << hr
            << std::endl;

    pType->Release();

    IMFMediaType* pActual = NULL;

    hr = pReader->GetCurrentMediaType(
        MF_SOURCE_READER_FIRST_VIDEO_STREAM,
        &pActual
    );
    UINT32 width = 0;
    UINT32 height = 0;

    hr = MFGetAttributeSize(
        pActual,
        MF_MT_FRAME_SIZE,
        &width,
        &height
    );

    std::cout
        << "Resolution: "
        << width
        << "x"
        << height
        << std::endl;

    UINT32 fpsNum = 0;
    UINT32 fpsDen = 0;

    hr = MFGetAttributeRatio(
        pActual,
        MF_MT_FRAME_RATE,
        &fpsNum,
        &fpsDen
    );

    std::cout
        << "FPS: "
        << fpsNum
        << "/"
        << fpsDen
        << std::endl;

    GUID subtype;

    pActual->GetGUID(
        MF_MT_SUBTYPE,
        &subtype
    );

    if (subtype == MFVideoFormat_NV12)
    {
        std::cout << "Format: NV12\n";
    }
    else if (subtype == MFVideoFormat_MJPG)
    {
        std::cout << "Format: MJPG\n";
    }
    else if (subtype == MFVideoFormat_YUY2)
    {
        std::cout << "Format: YUY2\n";
    }
    else
    {
        std::cout << "Format: UNKNOWN\n";
    }

    pActual->Release();
    

    




    while (true)
    {
        IMFSample* pSample = nullptr;

        DWORD streamIndex = 0;
        DWORD flags = 0;
        LONGLONG timestamp = 0;

        hr = pReader->ReadSample(
            MF_SOURCE_READER_FIRST_VIDEO_STREAM,
            0,
            &streamIndex,
            &flags,
            &timestamp,
            &pSample
        );

        // std::cout << "ReadSample hr = 0x"
        //         << std::hex
        //         << hr
        //         << std::endl;

        if (flags & MF_SOURCE_READERF_STREAMTICK)
        {
            // std::cout << "Stream tick\n";
        }

        if (pSample)
        {
            // std::cout << "Got frame\n";

            IMFMediaBuffer* pBuffer = nullptr;

            hr = pSample->ConvertToContiguousBuffer(&pBuffer);

            if (SUCCEEDED(hr))
            {
                BYTE* data = nullptr;
                DWORD maxLen = 0;
                DWORD currentLen = 0;
                

                hr = pBuffer->Lock(
                    &data,
                    &maxLen,
                    &currentLen
                );
                

                if (SUCCEEDED(hr))
                {
                    // std::cout << std::dec
                    // << "Buffer Size: "
                    // << currentLen
                    // << std::endl;
                // HRESULT encHr = EncodeFrame(
                //     pEncoder,
                //     data,
                //     currentLen,
                //     frameTime
                // );

                // std::cout
                //     << "EncodeFrame hr=0x"
                //     << std::hex
                //     << encHr
                //     << std::endl;
                // frameTime += frameDuration;

                    std::vector<uint8_t> h264;

                    if (m_encoder.encode(
                            data,
                            currentLen,
                            timestamp,
                            h264))
                    {
                        emit nalReady(h264);
                    }
                    QImage img =
                        NV12ToQImage(
                            data,
                            1280,
                            720
                        );
                    // std::cout
                    // << "Image "
                    // << img.width()
                    // << " "
                    // << img.height()
                    // << std::endl;
                    emit framReady(img);

                    
                        pBuffer->Unlock();
                    }

                pBuffer->Release();
            }

            pSample->Release();

            // break;
        }

        // Sleep(10);
    }
    if (pReader) pReader->Release();
    if (ppSource) ppSource->Release();
    if (pConfig) pConfig->Release();
    if (pReaderAttr) pReaderAttr->Release();

    MFShutdown();
    CoUninitialize();
    //   while(true){
    //     QImage img(
    //         640,
    //         480,
    //         QImage::Format_RGB32
    //     );

    //     img.fill(Qt::black);

    //     for (int y = 0; y < img.height(); y++)
    //     {
    //         for (int x = 0; x < img.width(); x++)
    //         {
    //             int r = (x * 255) / img.width();
    //             int g = (y * 255) / img.height();
    //             int b = 128;

    //             img.setPixel(
    //                 x,
    //                 y,
    //                 qRgb(r, g, b)
    //             );
    //         }
    //     }
        
    //     emit framReady(img);
        

    //   }
        
    //     std::this_thread::sleep_for(
    //         std::chrono::milliseconds(30)
    //     );
    }).detach();
}