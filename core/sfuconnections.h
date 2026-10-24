#ifndef SFUCONNECTIONS_h
#define SFUCONNECTIONS_h
#include<iostream>
#include<string>
#include<unordered_map>
#include<unordered_set>
#include<vector>
#include<mutex>
#include<memory>
struct Client{
    std::string clientId;
    std::string ip;
    uint16_t port;
    std::string room;
};
struct Room{
    std::string roomId;
    std::unordered_set<std::string> members;
};

class Connections{
    private:
        std::unordered_map<std::string, std::shared_ptr<Client>> clients;
        std::unordered_map<std::string,Room> rooms;
        mutable std::mutex clientMutex;
        mutable std::mutex roomMutex;
    public:
        std::shared_ptr<Client> createClient(const std::string& clientId);
        bool hasClient(const std::string& clientId)const;

};
#endif