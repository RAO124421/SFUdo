#ifndef EVENTQUEUE_H
#define EVENTQUEUE_H
#include<queue>
#include<string>
#include<mutex>
#include"json.hpp"
struct Event{
    std::string type;
    std::string data;
};
class EventQueue{
    private:
        std::queue<Event> queue;
        std::mutex mutex;
    public:
        void push(Event event);
        bool pop(Event &event);
};
#endif