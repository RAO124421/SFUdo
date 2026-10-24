#include <windows.h>
#include <iostream>
#include <string>
#include <vector>

typedef LONG NTSTATUS;

#define SystemProcessorPerformanceInformation 8

typedef struct _SYSTEM_PROCESSOR_PERFORMANCE_INFORMATION
{
    LARGE_INTEGER IdleTime;
    LARGE_INTEGER KernelTime;
    LARGE_INTEGER UserTime;
    LARGE_INTEGER DpcTime;
    LARGE_INTEGER InterruptTime;
    ULONG InterruptCount;
} SYSTEM_PROCESSOR_PERFORMANCE_INFORMATION;

typedef NTSTATUS (WINAPI* NtQuerySystemInformation_t)(
    ULONG SystemInformationClass,
    PVOID SystemInformation,
    ULONG SystemInformationLength,
    PULONG ReturnLength
);

ULONGLONG FileTimeToULL(const FILETIME& ft)
{
    ULARGE_INTEGER uli;
    uli.LowPart = ft.dwLowDateTime;
    uli.HighPart = ft.dwHighDateTime;
    return uli.QuadPart;
}

std::wstring GetCpuName()
{
    HKEY hKey;
    wchar_t cpuName[256];
    DWORD bufferSize = sizeof(cpuName);

    LONG result = RegOpenKeyExW(
        HKEY_LOCAL_MACHINE,
        L"HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0",
        0,
        KEY_READ,
        &hKey
    );

    if (result != ERROR_SUCCESS)
        return L"Unknown CPU";

    result = RegQueryValueExW(
        hKey,
        L"ProcessorNameString",
        nullptr,
        nullptr,
        reinterpret_cast<LPBYTE>(cpuName),
        &bufferSize
    );

    RegCloseKey(hKey);

    if (result != ERROR_SUCCESS)
        return L"Unknown CPU";

    return cpuName;
}

int GetLogicalProcessorCount()
{
    SYSTEM_INFO sysInfo;
    GetSystemInfo(&sysInfo);
    return sysInfo.dwNumberOfProcessors;
}

int GetPhysicalCoreCount()
{
    DWORD length = 0;

    GetLogicalProcessorInformationEx(RelationProcessorCore, nullptr, &length);

    std::vector<char> buffer(length);

    if (!GetLogicalProcessorInformationEx(
        RelationProcessorCore,
        reinterpret_cast<PSYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX>(buffer.data()),
        &length))
    {
        return -1;
    }

    int coreCount = 0;
    char* ptr = buffer.data();

    while (ptr < buffer.data() + length)
    {
        auto info =
            reinterpret_cast<PSYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX>(ptr);

        if (info->Relationship == RelationProcessorCore)
            coreCount++;

        ptr += info->Size;
    }

    return coreCount;
}

double GetTotalCpuUsage()
{
    FILETIME idleTime1, kernelTime1, userTime1;
    FILETIME idleTime2, kernelTime2, userTime2;

    GetSystemTimes(&idleTime1, &kernelTime1, &userTime1);
    Sleep(1000);
    GetSystemTimes(&idleTime2, &kernelTime2, &userTime2);

    ULONGLONG idle1 = FileTimeToULL(idleTime1);
    ULONGLONG kernel1 = FileTimeToULL(kernelTime1);
    ULONGLONG user1 = FileTimeToULL(userTime1);

    ULONGLONG idle2 = FileTimeToULL(idleTime2);
    ULONGLONG kernel2 = FileTimeToULL(kernelTime2);
    ULONGLONG user2 = FileTimeToULL(userTime2);

    ULONGLONG idleDiff = idle2 - idle1;
    ULONGLONG kernelDiff = kernel2 - kernel1;
    ULONGLONG userDiff = user2 - user1;

    ULONGLONG totalDiff = kernelDiff + userDiff;

    if (totalDiff == 0)
        return 0.0;

    return (double)(totalDiff - idleDiff) * 100.0 / totalDiff;
}

std::vector<double> GetPerCoreCpuUsage()
{
    SYSTEM_INFO sysInfo;
    GetSystemInfo(&sysInfo);

    int cpuCount = sysInfo.dwNumberOfProcessors;

    HMODULE ntdll = GetModuleHandleW(L"ntdll.dll");

    auto NtQuerySystemInformation =
        reinterpret_cast<NtQuerySystemInformation_t>(
            GetProcAddress(ntdll, "NtQuerySystemInformation")
        );

    std::vector<SYSTEM_PROCESSOR_PERFORMANCE_INFORMATION> info1(cpuCount);
    std::vector<SYSTEM_PROCESSOR_PERFORMANCE_INFORMATION> info2(cpuCount);

    NtQuerySystemInformation(
        SystemProcessorPerformanceInformation,
        info1.data(),
        sizeof(SYSTEM_PROCESSOR_PERFORMANCE_INFORMATION) * cpuCount,
        nullptr
    );

    Sleep(1000);

    NtQuerySystemInformation(
        SystemProcessorPerformanceInformation,
        info2.data(),
        sizeof(SYSTEM_PROCESSOR_PERFORMANCE_INFORMATION) * cpuCount,
        nullptr
    );

    std::vector<double> usage(cpuCount);

    for (int i = 0; i < cpuCount; i++)
    {
        ULONGLONG idle1 = info1[i].IdleTime.QuadPart;
        ULONGLONG kernel1 = info1[i].KernelTime.QuadPart;
        ULONGLONG user1 = info1[i].UserTime.QuadPart;

        ULONGLONG idle2 = info2[i].IdleTime.QuadPart;
        ULONGLONG kernel2 = info2[i].KernelTime.QuadPart;
        ULONGLONG user2 = info2[i].UserTime.QuadPart;

        ULONGLONG idleDiff = idle2 - idle1;
        ULONGLONG kernelDiff = kernel2 - kernel1;
        ULONGLONG userDiff = user2 - user1;

        ULONGLONG totalDiff = kernelDiff + userDiff;

        if (totalDiff == 0)
            usage[i] = 0.0;
        else
            usage[i] = (double)(totalDiff - idleDiff) * 100.0 / totalDiff;
    }

    return usage;
}

int main()
{
    std::wcout << L"CPU Name: "
               << GetCpuName()
               << std::endl;

    std::cout << "Logical processors: "
              << GetLogicalProcessorCount()
              << std::endl;

    std::cout << "Physical cores: "
              << GetPhysicalCoreCount()
              << std::endl;

    std::cout << "Total CPU usage: "
              << GetTotalCpuUsage()
              << "%"
              << std::endl;

    auto perCoreUsage = GetPerCoreCpuUsage();

    for (size_t i = 0; i < perCoreUsage.size(); i++)
    {
        std::cout << "Logical core " << i
                  << " usage: "
                  << perCoreUsage[i]
                  << "%"
                  << std::endl;
    }

    return 0;
}