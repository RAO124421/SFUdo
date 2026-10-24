#include <windows.h>
#include <iostream>

void PrintMemoryInfo()
{
    MEMORYSTATUSEX mem;
    mem.dwLength = sizeof(mem);

    if (!GlobalMemoryStatusEx(&mem))
    {
        std::cout << "GlobalMemoryStatusEx failed\n";
        return;
    }

    DWORDLONG totalPhys = mem.ullTotalPhys;
    DWORDLONG availPhys = mem.ullAvailPhys;
    DWORDLONG usedPhys = totalPhys - availPhys;

    std::cout << "RAM usage: " << mem.dwMemoryLoad << "%\n";

    std::cout << "Total physical RAM: "
              << totalPhys / (1024 * 1024)
              << " MB\n";

    std::cout << "Available physical RAM: "
              << availPhys / (1024 * 1024)
              << " MB\n";

    std::cout << "Used physical RAM: "
              << usedPhys / (1024 * 1024)
              << " MB\n";

    std::cout << "Total page file / commit limit: "
              << mem.ullTotalPageFile / (1024 * 1024)
              << " MB\n";

    std::cout << "Available page file / commit: "
              << mem.ullAvailPageFile / (1024 * 1024)
              << " MB\n";

    std::cout << "Total virtual memory: "
              << mem.ullTotalVirtual / (1024 * 1024)
              << " MB\n";

    std::cout << "Available virtual memory: "
              << mem.ullAvailVirtual / (1024 * 1024)
              << " MB\n";
}

int main()
{
    PrintMemoryInfo();
    return 0;
}