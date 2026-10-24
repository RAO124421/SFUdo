#include <windows.h>
#include <mfapi.h>
#include <mfidl.h>
#include <mfreadwrite.h>
#include <iostream>

#ifndef MF_E_NO_MORE_TYPES
#define MF_E_NO_MORE_TYPES ((HRESULT)0xC00D36B9L)
#endif

#pragma comment(lib, "ole32.lib")
#pragma comment(lib, "mfplat.lib")
#pragma comment(lib, "mf.lib")
#pragma comment(lib, "mfuuid.lib")
#pragma comment(lib, "mfreadwrite.lib")

const wchar_t* GetSubtypeName(const GUID& subtype)
{
    if (subtype == MFVideoFormat_RGB32) return L"RGB32";
    if (subtype == MFVideoFormat_RGB24) return L"RGB24";
    if (subtype == MFVideoFormat_RGB555) return L"RGB555";
    if (subtype == MFVideoFormat_RGB565) return L"RGB565";
    if (subtype == MFVideoFormat_RGB8) return L"RGB8";

    if (subtype == MFVideoFormat_YUY2) return L"YUY2";
    if (subtype == MFVideoFormat_UYVY) return L"UYVY";
    if (subtype == MFVideoFormat_YVYU) return L"YVYU";
    if (subtype == MFVideoFormat_NV12) return L"NV12";
    if (subtype == MFVideoFormat_NV11) return L"NV11";

    if (subtype == MFVideoFormat_I420) return L"I420";
    if (subtype == MFVideoFormat_IYUV) return L"IYUV";
    if (subtype == MFVideoFormat_YV12) return L"YV12";

    if (subtype == MFVideoFormat_MJPG) return L"MJPG";
    if (subtype == MFVideoFormat_H264) return L"H264";

    return L"UNKNOWN";
}

void CleanupDevices(IMFActivate** devices, UINT32 count)
{
    if (devices)
    {
        for (UINT32 i = 0; i < count; i++)
        {
            if (devices[i])
            {
                devices[i]->Release();
            }
        }

        CoTaskMemFree(devices);
    }
}

int main()
{
    HRESULT hr;

    hr = CoInitializeEx(NULL, COINIT_MULTITHREADED);
    if (FAILED(hr))
    {
        std::cout << "COM initialization failed\n";
        return -1;
    }

    hr = MFStartup(MF_VERSION);
    if (FAILED(hr))
    {
        std::cout << "Media Foundation startup failed\n";
        CoUninitialize();
        return -1;
    }

    IMFAttributes* attributes = NULL;
    IMFActivate** devices = NULL;
    UINT32 count = 0;

    hr = MFCreateAttributes(&attributes, 1);
    if (FAILED(hr))
    {
        std::cout << "MFCreateAttributes failed\n";
        MFShutdown();
        CoUninitialize();
        return -1;
    }

    hr = attributes->SetGUID(
        MF_DEVSOURCE_ATTRIBUTE_SOURCE_TYPE,
        MF_DEVSOURCE_ATTRIBUTE_SOURCE_TYPE_VIDCAP_GUID
    );

    if (FAILED(hr))
    {
        std::cout << "SetGUID failed\n";
        attributes->Release();
        MFShutdown();
        CoUninitialize();
        return -1;
    }

    hr = MFEnumDeviceSources(attributes, &devices, &count);
    if (FAILED(hr))
    {
        std::cout << "MFEnumDeviceSources failed\n";
        attributes->Release();
        MFShutdown();
        CoUninitialize();
        return -1;
    }

    std::wcout << L"Camera count: " << count << std::endl;

    if (count == 0)
    {
        std::wcout << L"No camera found." << std::endl;

        CoTaskMemFree(devices);
        attributes->Release();
        MFShutdown();
        CoUninitialize();

        return 0;
    }

    for (UINT32 i = 0; i < count; i++)
    {
        WCHAR* name = NULL;
        UINT32 nameLength = 0;

        hr = devices[i]->GetAllocatedString(
            MF_DEVSOURCE_ATTRIBUTE_FRIENDLY_NAME,
            &name,
            &nameLength
        );

        if (SUCCEEDED(hr))
        {
            std::wcout << L"Camera " << i << L": " << name << std::endl;
            CoTaskMemFree(name);
        }
        else
        {
            std::wcout << L"Camera " << i << L": Unknown camera" << std::endl;
        }
    }

    UINT32 selectedIndex = 0;

    std::wcout << L"\nSelect camera index: ";
    std::wcin >> selectedIndex;

    if (selectedIndex >= count)
    {
        std::wcout << L"Invalid camera index." << std::endl;

        CleanupDevices(devices, count);
        attributes->Release();
        MFShutdown();
        CoUninitialize();

        return -1;
    }

    IMFMediaSource* mediaSource = NULL;

    hr = devices[selectedIndex]->ActivateObject(
        IID_PPV_ARGS(&mediaSource)
    );

    if (FAILED(hr))
    {
        std::wcout << L"Failed to activate selected camera." << std::endl;

        CleanupDevices(devices, count);
        attributes->Release();
        MFShutdown();
        CoUninitialize();

        return -1;
    }

    IMFSourceReader* reader = NULL;

    hr = MFCreateSourceReaderFromMediaSource(
        mediaSource,
        NULL,
        &reader
    );

    if (FAILED(hr))
    {
        std::wcout << L"Failed to create source reader." << std::endl;

        mediaSource->Release();
        CleanupDevices(devices, count);
        attributes->Release();
        MFShutdown();
        CoUninitialize();

        return -1;
    }

    std::wcout << L"\nSupported camera modes:" << std::endl;

    DWORD mediaTypeIndex = 0;

    while (true)
    {
        IMFMediaType* mediaType = NULL;

        hr = reader->GetNativeMediaType(
            (DWORD)MF_SOURCE_READER_FIRST_VIDEO_STREAM,
            mediaTypeIndex,
            &mediaType
        );

        if (hr == MF_E_NO_MORE_TYPES)
        {
            break;
        }

        if (FAILED(hr))
        {
            std::wcout << L"GetNativeMediaType failed. HRESULT: 0x"
                       << std::hex << hr << std::dec << std::endl;
            break;
        }

        GUID subtype = { 0 };
        UINT32 width = 0;
        UINT32 height = 0;
        UINT32 fpsNum = 0;
        UINT32 fpsDen = 0;

        HRESULT subtypeHr = mediaType->GetGUID(
            MF_MT_SUBTYPE,
            &subtype
        );

        HRESULT sizeHr = MFGetAttributeSize(
            mediaType,
            MF_MT_FRAME_SIZE,
            &width,
            &height
        );

        HRESULT fpsHr = MFGetAttributeRatio(
            mediaType,
            MF_MT_FRAME_RATE,
            &fpsNum,
            &fpsDen
        );

        std::wcout << L"Type " << mediaTypeIndex;

        if (SUCCEEDED(subtypeHr))
        {
            std::wcout << L" | Format: " << GetSubtypeName(subtype);
        }
        else
        {
            std::wcout << L" | Format: UNKNOWN";
        }

        if (SUCCEEDED(sizeHr))
        {
            std::wcout << L" | Resolution: " << width << L"x" << height;
        }
        else
        {
            std::wcout << L" | Resolution: UNKNOWN";
        }

        if (SUCCEEDED(fpsHr) && fpsDen != 0)
        {
            double fps = static_cast<double>(fpsNum) / fpsDen;

            std::wcout << L" | FPS: " << fps
                       << L" (" << fpsNum << L"/" << fpsDen << L")";
        }
        else
        {
            std::wcout << L" | FPS: UNKNOWN";
        }

        std::wcout << std::endl;

        mediaType->Release();
        mediaTypeIndex++;
    }

    reader->Release();
    mediaSource->Release();

    CleanupDevices(devices, count);
    attributes->Release();

    MFShutdown();
    CoUninitialize();

    return 0;
}