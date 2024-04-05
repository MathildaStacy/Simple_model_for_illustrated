#include "OO_Thread.hpp"
#include <cstddef>
#include <cstdio>
#include <pthread.h>
#include <iostream>

Thread::Thread(): m_thid(0), m_isRunning(false) {}

void *Thread::ThreadFunc(void *arg) {
    
    Thread* myThd = static_cast<Thread*>(arg);

    if(myThd != nullptr)
    {
        myThd->run();
    }
    else {
        std::cerr << "myThd is nullptr!" << std::endl;
    }

    pthread_exit(nullptr);

}

void Thread::start() {
    if(m_isRunning == false)
    {
        int ret = pthread_create(&m_thid, nullptr, ThreadFunc, this);
        if(ret != 0)
        {
            perror("error in pthread_create");
            return ;
        }
        else {
            m_isRunning = true;
        }
        
    }
}

void Thread::stop() {
    if(m_isRunning == true)
    {
        int ret = pthread_join(m_thid, nullptr);
        if(ret != 0)
        {
            perror("error in pthread_join");
        }
        else {
            m_isRunning = false;
        }
    }
}

Thread::~Thread() {
    
}