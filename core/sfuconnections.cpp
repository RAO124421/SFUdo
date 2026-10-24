#include"sfuconnections.h"
#include<string>
#include<memory>
#include<iostream>

std::shared_ptr<Client> Connections::createClient(const std::string& clientId ){
    std::lock_guard<std::mutex> lock(clientMutex);
    auto it=clients.find(clientId);
    if(it!=clients.end()){
        return it->second;
    }
    auto client=std::make_shared<Client>();
    client->clientId = clientId;
    client->ip = "";
    client->port = 0;
    // client->roomId = roomId;
    clients[clientId]=client;
    std::cout<<clientId<<std::endl;
    return client;
}
bool Connections::hasClient(const std::string& clientId)const{
    std::lock_guard<std::mutex> lock(clientMutex);
    return clients.find(clientId)!=clients.end();
}