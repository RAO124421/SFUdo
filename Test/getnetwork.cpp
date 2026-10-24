#include <iostream>
#include <windows.h>
#include <iphlpapi.h>
#include <string>
#include <thread>
#include <chrono>

#pragma comment(lib, "iphlpapi.lib")

using namespace std;

struct TrafficData {
    unsigned long long uploadBytes = 0;
    unsigned long long downloadBytes = 0;
};

string InterfaceTypeToString(DWORD type) {
    switch (type) {
    case IF_TYPE_ETHERNET_CSMACD:
        return "LAN / Ethernet";

    case IF_TYPE_IEEE80211:
        return "Wi-Fi";

    case IF_TYPE_SOFTWARE_LOOPBACK:
        return "Loopback";

    case IF_TYPE_TUNNEL:
        return "Tunnel / VPN";

    default:
        return "Other";
    }
}

TrafficData GetTotalTraffic() {
    TrafficData data;

    DWORD tableSize = 0;

    // First call gets required buffer size
    GetIfTable(NULL, &tableSize, FALSE);

    PMIB_IFTABLE ifTable = (PMIB_IFTABLE)malloc(tableSize);

    if (ifTable == NULL) {
        cout << "Memory allocation failed.\n";
        return data;
    }

    DWORD result = GetIfTable(ifTable, &tableSize, FALSE);

    if (result != NO_ERROR) {
        cout << "GetIfTable failed. Error code: " << result << endl;
        free(ifTable);
        return data;
    }

    for (DWORD i = 0; i < ifTable->dwNumEntries; i++) {
        MIB_IFROW row = ifTable->table[i];

        // Only active interfaces, skip loopback
        if (row.dwOperStatus == IF_OPER_STATUS_OPERATIONAL &&
            row.dwType != IF_TYPE_SOFTWARE_LOOPBACK) {

            data.uploadBytes += row.dwOutOctets;
            data.downloadBytes += row.dwInOctets;
        }
    }

    free(ifTable);
    return data;
}

void ShowConnectionType() {
    DWORD tableSize = 0;

    GetIfTable(NULL, &tableSize, FALSE);

    PMIB_IFTABLE ifTable = (PMIB_IFTABLE)malloc(tableSize);

    if (ifTable == NULL) {
        cout << "Memory allocation failed.\n";
        return;
    }

    DWORD result = GetIfTable(ifTable, &tableSize, FALSE);

    if (result != NO_ERROR) {
        cout << "GetIfTable failed. Error code: " << result << endl;
        free(ifTable);
        return;
    }

    cout << "\nConnected Network Interfaces:\n";
    cout << "----------------------------------------\n";

    bool found = false;

    for (DWORD i = 0; i < ifTable->dwNumEntries; i++) {
        MIB_IFROW row = ifTable->table[i];

        if (row.dwOperStatus == IF_OPER_STATUS_OPERATIONAL &&
            row.dwType != IF_TYPE_SOFTWARE_LOOPBACK) {

            found = true;

            cout << "Interface Name : " << row.bDescr << endl;
            cout << "Connection Type: " << InterfaceTypeToString(row.dwType) << endl;
            cout << "Upload Total   : " << row.dwOutOctets / 1024.0 / 1024.0 << " MB" << endl;
            cout << "Download Total : " << row.dwInOctets / 1024.0 / 1024.0 << " MB" << endl;
            cout << "----------------------------------------\n";
        }
    }

    if (!found) {
        cout << "No active Wi-Fi or LAN connection found.\n";
    }

    free(ifTable);
}

int main() {
    cout << "Network Performance Monitor\n";
    cout << "============================\n";

    ShowConnectionType();

    cout << "\nMeasuring bandwidth usage...\n";
    cout << "Please wait 1 second...\n\n";

    TrafficData first = GetTotalTraffic();

    this_thread::sleep_for(chrono::seconds(1));

    TrafficData second = GetTotalTraffic();

    unsigned long long uploadDiff = second.uploadBytes - first.uploadBytes;
    unsigned long long downloadDiff = second.downloadBytes - first.downloadBytes;

    double uploadKBps = uploadDiff / 1024.0;
    double downloadKBps = downloadDiff / 1024.0;
    double totalKBps = uploadKBps + downloadKBps;

    double uploadMbps = (uploadDiff * 8.0) / 1000000.0;
    double downloadMbps = (downloadDiff * 8.0) / 1000000.0;
    double totalMbps = uploadMbps + downloadMbps;

    cout << "Current Network Usage\n";
    cout << "----------------------------\n";

    cout << "Upload Traffic        : " << uploadKBps << " KB/s";
    cout << "  |  " << uploadMbps << " Mbps\n";

    cout << "Download Traffic      : " << downloadKBps << " KB/s";
    cout << "  |  " << downloadMbps << " Mbps\n";

    cout << "Total Bandwidth Usage : " << totalKBps << " KB/s";
    cout << "  |  " << totalMbps << " Mbps\n";

    cout << "\nProgram finished.\n";

    return 0;
}