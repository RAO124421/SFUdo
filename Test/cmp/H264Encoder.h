#pragma once

#include <vector>
#include <cstdint>

#include <Windows.h>

#include <wels/codec_api.h>

class H264Encoder
{
public:
    H264Encoder();
    ~H264Encoder();

    bool init(
        UINT32 width,
        UINT32 height,
        UINT32 fps,
        UINT32 bitrate = 4000000
    );

    bool encode(
        const uint8_t* nv12Data,
        DWORD nv12Size,
        LONGLONG pts,
        std::vector<uint8_t>& nal
    );

    void shutdown();

private:
    ISVCEncoder* m_encoder = nullptr;

    UINT32 m_width = 0;
    UINT32 m_height = 0;
    UINT32 m_fps = 0;
    UINT32 m_bitrate = 0;

    std::vector<uint8_t> m_i420;
};