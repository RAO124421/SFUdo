#include <windows.h>
#include <wbemidl.h>
#include <comdef.h>
#include <iostream>

#pragma comment(lib, "wbemuuid.lib")

int main()
{
    HRESULT hres;

    hres = CoInitializeEx(0, COINIT_MULTITHREADED);
    if (FAILED(hres))
    {
        std::cout << "Failed to initialize COM\n";
        return 1;
    }

    hres = CoInitializeSecurity(
        NULL,
        -1,
        NULL,
        NULL,
        RPC_C_AUTHN_LEVEL_DEFAULT,
        RPC_C_IMP_LEVEL_IMPERSONATE,
        NULL,
        EOAC_NONE,
        NULL
    );

    if (FAILED(hres))
    {
        std::cout << "Failed to initialize security\n";
        CoUninitialize();
        return 1;
    }

    IWbemLocator* pLoc = NULL;

    hres = CoCreateInstance(
        CLSID_WbemLocator,
        0,
        CLSCTX_INPROC_SERVER,
        IID_IWbemLocator,
        (LPVOID*)&pLoc
    );

    if (FAILED(hres))
    {
        std::cout << "Failed to create IWbemLocator\n";
        CoUninitialize();
        return 1;
    }

    IWbemServices* pSvc = NULL;

    hres = pLoc->ConnectServer(
    _bstr_t(L"ROOT\\WMI"),
    NULL,
    NULL,
    NULL,
    0,
    NULL,
    NULL,
    &pSvc
);

    if (FAILED(hres))
    {
        std::cout << "Could not connect to ROOT\\WMI\n";
        pLoc->Release();
        CoUninitialize();
        return 1;
    }

    hres = CoSetProxyBlanket(
        pSvc,
        RPC_C_AUTHN_WINNT,
        RPC_C_AUTHZ_NONE,
        NULL,
        RPC_C_AUTHN_LEVEL_CALL,
        RPC_C_IMP_LEVEL_IMPERSONATE,
        NULL,
        EOAC_NONE
    );

    if (FAILED(hres))
    {
        std::cout << "Could not set proxy blanket\n";
        pSvc->Release();
        pLoc->Release();
        CoUninitialize();
        return 1;
    }

    IEnumWbemClassObject* pEnumerator = NULL;

   hres = pSvc->ExecQuery(
    _bstr_t(L"WQL"),
    _bstr_t(L"SELECT * FROM MSAcpi_ThermalZoneTemperature"),
    WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
    NULL,
    &pEnumerator
);
    if (FAILED(hres))
    {
        std::cout << "WMI query failed\n";
        pSvc->Release();
        pLoc->Release();
        CoUninitialize();
        return 1;
    }

    IWbemClassObject* pclsObj = NULL;
    ULONG uReturn = 0;

    bool found = false;

    while (pEnumerator)
    {
        HRESULT hr = pEnumerator->Next(WBEM_INFINITE, 1, &pclsObj, &uReturn);

        if (uReturn == 0)
            break;

        VARIANT vtProp;
        hr = pclsObj->Get(L"CurrentTemperature", 0, &vtProp, 0, 0);

        if (SUCCEEDED(hr))
        {
            // WMI temperature is in tenths of Kelvin
            double kelvinTenths = vtProp.uintVal;
            double celsius = (kelvinTenths / 10.0) - 273.15;

            std::cout << "Temperature: "
                      << celsius
                      << " C"
                      << std::endl;

            found = true;
        }

        VariantClear(&vtProp);
        pclsObj->Release();
    }

    if (!found)
    {
        std::cout << "No temperature data found from WMI.\n";
    }

    pSvc->Release();
    pLoc->Release();
    pEnumerator->Release();
    CoUninitialize();

    return 0;
}