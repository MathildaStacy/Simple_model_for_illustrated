#include "MutexLock.hpp"
#include "TaskQueue.hpp"

#include <cstdint>

TaskQueue::TaskQueue(uint32_t size)
    :m_max_size(size), m_notFull(m_mutex), m_notEmpty(m_mutex)
{

}

bool TaskQueue::empty() {
    return (m_queue.size() == 0);
}

bool TaskQueue::full() {
    return (m_queue.size() == m_max_size);
}


void TaskQueue::push(int val) {
    {
    MyLockGuard guard{m_mutex};

    while(full())
    {
        m_notFull.wait();
    }

    m_queue.push(val);

    m_notEmpty.notify_all();

    }
}


int TaskQueue::pop() {

    int val = 0;
    {
    MyLockGuard guard{m_mutex};

    while(empty())
    {
        m_notEmpty.wait();
    }

    val = m_queue.front();
    m_queue.pop();

    m_notFull.notify_all();

    
    }

    return val;
}

TaskQueue::~TaskQueue() {}


