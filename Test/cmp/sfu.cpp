#include"sfu.h"
#include<thread>
#include<WinSock2.h>
#include<WS2tcpip.h>
#include<iostream>
#define LOCAL_UDP_PORT 40000
#pragma pack(push,1)

struct NALPacketHeader {

    uint32_t frameId;

    uint16_t packetIndex;

    uint16_t totalPackets;

    uint16_t payloadSize;
};

#pragma pack(pop)
void SFU::start(){
    std::thread([this](){
        
        WSADATA wsa;
        WSAStartup(MAKEWORD(2,2),&wsa);
        udpsock=socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
        if(udpsock==INVALID_SOCKET){
            std::cout<<"UDP Socket faild "<<std::endl;
            return;
        }
        sockaddr_in local{};
        local.sin_family=AF_INET;
        local.sin_addr.s_addr=INADDR_ANY;
        local.sin_port=htons(LOCAL_UDP_PORT);
        if(bind(udpsock,(sockaddr*)&local,sizeof(local))==SOCKET_ERROR){
            std::cout<<"Socket Bind faild"<<std::endl;
            closesocket(udpsock);
            WSACleanup();
            return;
        }
        std::cout<<"Liesting on port 4000"<<std::endl;
        // std::thread([this,udpsock](){
        //     while(true){
        //         sockaddr_in client{};
        //         // std::lock_guard<std::mutex> lock(clientsMutex);
        //         clientsMutex.lock();
        //         if(clients.empty()){
        //             clientsMutex.unlock();
        //             Sleep(3000);
        //             continue;
        //         }
        //         client=clients[0];
        //         clientsMutex.unlock();
        //         const char* message = "hello client";
        //         int result = sendto(
        //             udpsock,
        //             message,
        //             strlen(message),
        //             0,
        //             (sockaddr*)&client,
        //             sizeof(client)
        //         );
        //         Sleep(3000);
        //     }
            
        // }).detach();
        while(true){
            char buffer[2048];
            sockaddr_in sender{};
            int senderLen=sizeof(sender);
            int len=recvfrom(
                udpsock,
                buffer,
                sizeof(buffer)-1,
                0,
                (sockaddr*)&sender,
                &senderLen
            );
            if(len==SOCKET_ERROR){
                std::cout<<"Faild to recive"<<std::endl;
                continue;
            }
            buffer[len]='\0';
            char senderIp[INET_ADDRSTRLEN];
            inet_ntop(AF_INET,&sender.sin_addr,senderIp,sizeof(senderIp));
            std::cout<<"From : "<<senderIp<<":"<<ntohs(sender.sin_port)<<"\n";
            std::lock_guard<std::mutex> lock(clientsMutex);
            clients.push_back(sender);
        }
        closesocket(udpsock);
        WSACleanup();
    }).detach();
}
void SFU::sendNAL(
        const std::vector<uint8_t>& nal
) {

    sockaddr_in client{};

    clientsMutex.lock();

    if(clients.empty()){

        clientsMutex.unlock();

        return;
    }

    client = clients[0];

    clientsMutex.unlock();

    constexpr size_t CHUNK_SIZE = 1200;

    static uint32_t frameCounter = 0;

    uint32_t frameId = frameCounter++;

    size_t totalPackets =
            (nal.size() + CHUNK_SIZE - 1)
            / CHUNK_SIZE;

    size_t offset = 0;

    uint16_t packetIndex = 0;

    while(offset < nal.size()){

        size_t remaining =
                nal.size() - offset;

        size_t payloadSize =
                std::min(
                        CHUNK_SIZE,
                        remaining
                );

        NALPacketHeader header{};

        header.frameId =
        htonl(frameId);

        header.packetIndex =
                htons(packetIndex);

        header.totalPackets =
                htons(totalPackets);

        header.payloadSize =
                htons(payloadSize);

        std::vector<uint8_t> packet;

        packet.resize(
                sizeof(NALPacketHeader)
                + payloadSize
        );

        memcpy(
                packet.data(),
                &header,
                sizeof(NALPacketHeader)
        );

        memcpy(
                packet.data()
                + sizeof(NALPacketHeader),
                nal.data() + offset,
                payloadSize
        );

        int result = sendto(
                udpsock,
                reinterpret_cast<const char*>(
                        packet.data()
                ),
                static_cast<int>(
                        packet.size()
                ),
                0,
                (sockaddr*)&client,
                sizeof(client)
        );

        if(result < 0){

            std::cout
                << "Failed to send packet"
                << std::endl;

            return;
        }

        offset += payloadSize;

        packetIndex++;
    }

    // std::cout
    //     << "NAL fragmented and sent"
    //     << std::endl;
}