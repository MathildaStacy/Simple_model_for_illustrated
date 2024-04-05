#include "producer.hpp"
#include <cstdint>
#include <iostream>
#include <unistd.h>

Producer::Producer(TaskQueue& task_queue)
    :m_task_queue(task_queue)
{

}


void Producer::run() {
    for(int i = 0; i < 20; i++)
    {
        m_task_queue.push(i);
        std::cout << "<< get " << i << std::endl;
    }
}


Producer::~Producer() {}
