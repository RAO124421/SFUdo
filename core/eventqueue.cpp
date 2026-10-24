#include"eventqueue.h"
void EventQueue::push(Event event){
    std::lock_guard<std::mutex> lock(mutex);
    queue.push(event);
}
bool EventQueue::pop(Event &event){
    std::lock_guard<std::mutex> lock(mutex);
    if(queue.empty()){
        return false;
    }
    event=queue.front();
    queue.pop();
    return true;
}
