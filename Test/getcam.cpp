#include<Windows.h>
#include<mfapi.h>
#include<mfidl.h>
#include<mfobjects.h>
#include<iostream>
#include<mferror.h>
#include<mfreadwrite.h>
const wchar_t* GetFormatName(const GUID& guid)
{
    if (guid == MFVideoFormat_MJPG) return L"MJPG";
    if (guid == MFVideoFormat_YUY2) return L"YUY2";
    if (guid == MFVideoFormat_NV12) return L"NV12";
    if (guid == MFVideoFormat_RGB32) return L"RGB32";
    if (guid == MFVideoFormat_RGB24) return L"RGB24";

    return L"UNKNOWN";
}
HRESULT CreateVideoCaptureDevice(IMFMediaSource **ppSource){
    *ppSource=NULL;
    IMFAttributes *pConfig=NULL;
    IMFActivate **ppDevice=NULL;
    UINT32 count=0;
    HRESULT hr=MFCreateAttributes(&pConfig,1);
    if(SUCCEEDED(hr)){
        hr=pConfig->SetGUID(
            MF_DEVSOURCE_ATTRIBUTE_SOURCE_TYPE,
            MF_DEVSOURCE_ATTRIBUTE_SOURCE_TYPE_VIDCAP_GUID
        );
    }
    if(SUCCEEDED(hr)){
        std::cout<<"Added data"<<std::endl;
        hr=MFEnumDeviceSources(pConfig,&ppDevice,&count);
    }
    if(SUCCEEDED(hr)){
        // std::cout<<"Number if Devices used are : "<<count<<std::endl;
        if(count>0){
            hr=ppDevice[0]->ActivateObject(IID_PPV_ARGS(ppSource));
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

    if (SUCCEEDED(hr))
    {
        hr = pReaderAttr->SetUINT32(
            MF_READWRITE_DISABLE_CONVERTERS,
            TRUE
        );
    }

    if (SUCCEEDED(hr))
    {
        hr = MFCreateSourceReaderFromMediaSource(
            *ppSource,
            pReaderAttr,
            &pReader
        );
    }
    IMFMediaType* pType = NULL;

    hr = pReader->GetNativeMediaType(
        MF_SOURCE_READER_FIRST_VIDEO_STREAM,
        16,
        &pType
    );

    if (SUCCEEDED(hr))
    {
        hr = pReader->SetCurrentMediaType(
            MF_SOURCE_READER_FIRST_VIDEO_STREAM,
            NULL,
            pType
        );
    }

    std::cout
        << "SetCurrentMediaType hr = 0x"
        << std::hex
        << hr
        << std::endl;

    if (pType)
    {
        pType->Release();
    }
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

        std::cout << "ReadSample hr = 0x"
                << std::hex
                << hr
                << std::endl;

        if (flags & MF_SOURCE_READERF_STREAMTICK)
        {
            std::cout << "Stream tick\n";
        }

        if (pSample)
        {
            std::cout << "Got frame\n";

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
                    std::cout << "Frame size: "
                            << currentLen
                            << std::endl;

                    pBuffer->Unlock();
                }

                pBuffer->Release();
            }

            pSample->Release();

            // break;
        }

        // Sleep(10);
    }
    DWORD i = 0;

    // while (true)
    // {
    //     IMFMediaType* pType = NULL;

    //     HRESULT hr = pReader->GetNativeMediaType(
    //         MF_SOURCE_READER_FIRST_VIDEO_STREAM,
    //         i,
    //         &pType
    //     );

    //     if (FAILED(hr))
    //         break;

    //     GUID subtype = {0};

    //     UINT32 width = 0;
    //     UINT32 height = 0;

    //     UINT32 fpsNum = 0;
    //     UINT32 fpsDen = 0;

    //     pType->GetGUID(MF_MT_SUBTYPE, &subtype);

    //     MFGetAttributeSize(
    //         pType,
    //         MF_MT_FRAME_SIZE,
    //         &width,
    //         &height
    //     );

    //     MFGetAttributeRatio(
    //         pType,
    //         MF_MT_FRAME_RATE,
    //         &fpsNum,
    //         &fpsDen
    //     );

    //     std::wcout
    // << L"Format " << i
    // << L": "
    // << width
    // << L"x"
    // << height
    // << L" FPS="
    // << (fpsDen ? fpsNum / fpsDen : 0)
    // << L" "
    // << GetFormatName(subtype)
    // << std::endl;

    //     pType->Release();

    //     i++;
    // }
    CoTaskMemFree(ppDevice);
    return hr;
};
int main(){
    // IMFMediaSource *ppSource=NULL;
    // HRESULT hr=CreateVideoCaptureDevice(&ppSource);
    HRESULT hr = MFStartup(MF_VERSION);

    if (FAILED(hr))
    {
        std::cout << "MFStartup failed\n";
        return -1;
    }

    IMFMediaSource *ppSource = NULL;

    hr = CreateVideoCaptureDevice(&ppSource);

    std::cout << "hr = 0x" << std::hex << hr << std::endl;

    MFShutdown();

    return 0;
}
