#include <windows.h>
#include <psapi.h>
#include <iostream>
#include <vector>

void PrintProcessMemory()
{
    PROCESS_MEMORY_COUNTERS_EX pmc;

    if (GetProcessMemoryInfo(
            GetCurrentProcess(),
            reinterpret_cast<PROCESS_MEMORY_COUNTERS*>(&pmc),
            sizeof(pmc)))
    {
        std::cout << "Working set: "
                  << pmc.WorkingSetSize / (1024 * 1024)
                  << " MB\n";

        std::cout << "Private usage: "
                  << pmc.PrivateUsage / (1024 * 1024)
                  << " MB\n";

        std::cout << "Pagefile usage: "
                  << pmc.PagefileUsage / (1024 * 1024)
                  << " MB\n";

        std::cout << "--------------------------\n";
    }
}

int main()
{
    std::cout << "Before allocation:\n";
    PrintProcessMemory();

    // Allocate 200 MB on heap
    std::vector<char> buffer(200 * 1024 * 1024);

    // Touch memory pages so Windows actually commits them
    for (size_t i = 0; i < buffer.size(); i += 4096)
    {
        buffer[i] = 1;
    }

    std::cout << "After allocation:\n";
    PrintProcessMemory();

    std::cout << "Press Enter to exit...";
    std::cin.get();

    return 0;
}