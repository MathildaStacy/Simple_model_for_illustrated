#ifndef __TASKQUEUE_HPP__
#define __TASKQUEUE_HPP__

#include "MutexLock.hpp"
#include "condition_variable.hpp"
#include <queue>
#include <cstdint>

class TaskQueue {
public:
    TaskQueue() = delete;
    TaskQueue(uint32_t size);
    

    void push(int val);
    
    int pop();

    bool empty();

    bool full();

    virtual~TaskQueue();


private:
    uint32_t m_max_size;
    std::queue<int> m_queue;
    MutexLock m_mutex;
    Condition m_notFull; //Condition的默认构造函数是delete的，因此将他初始化的顺序放到mutex后。注意：类的字段的初始化顺序
                         //按照定义的顺序进行
    Condition m_notEmpty;
};


#endif 