#include "consumer.hpp"
#include <bits/types/cookie_io_functions_t.h>
#include <cstdint>
#include <iostream>
#include <unistd.h>

Consumer::Consumer(TaskQueue& task_queue)
    :m_task_queue(task_queue)
{

}


void Consumer::run() {
    for(int i = 0; i < 20; i++)
    {
        int val = m_task_queue.pop();
        std::cout << ">> pop " << val << std::endl;
    }
}

Consumer::~Consumer() {}
