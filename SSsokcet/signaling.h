#ifndef SIGNALING_H
#define SIGNALING_H
#include"../core/eventqueue.h"
#include"../core/sfuconnections.h"
// #pragma once
class WebSocketClient{
    private:
        EventQueue *eventQueue;
        Connections *connections;
    public:
        WebSocketClient(EventQueue *queue,Connections *conns);
        void connectWebSocket();
};
#endif