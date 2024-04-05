#ifndef __CONSUMER_HPP__
#define __CONSUMER_HPP__

#include "OO_Thread.hpp"
#include "TaskQueue.hpp"
#include <cstdint>

class Consumer: public Thread {
public:
    Consumer() = delete;
    Consumer(TaskQueue& task_queue);

    void run() override;

    virtual ~Consumer();

private:
    TaskQueue& m_task_queue;

};


#endif