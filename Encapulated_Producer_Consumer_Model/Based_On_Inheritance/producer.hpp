#ifndef __PRODUCER_HPP__
#define __PRODUCER_HPP__

#include "OO_Thread.hpp"
#include "TaskQueue.hpp"
#include <cstdint>

class Producer: public Thread {
public:
    Producer() = delete;
    Producer(TaskQueue& task_queue);

    void run() override;

    virtual ~Producer();

private:
    TaskQueue& m_task_queue;

};


#endif