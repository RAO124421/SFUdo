#ifndef SFU_H
#define SFU_H
#include<QObject>
#include<string>
#include<vector>
#include<WinSock2.h>
#include<WS2tcpip.h>
#include<mutex>
class SFU : public QObject{
    std::vector<sockaddr_in> clients;
    std::mutex udpMutex;
    std::mutex clientsMutex;
    Q_OBJECT
    SOCKET udpsock;
    public:
        void start();
        void sendNAL(const std::vector<uint8_t>& nal);
    
};
#endif