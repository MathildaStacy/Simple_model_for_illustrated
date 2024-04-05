#include "MutexLock.hpp"
#include <cstdio>
#include <cstdlib>
#include <pthread.h>
#include <stdlib.h>
#include <iostream>

MutexLock::MutexLock() {
    int ret = pthread_mutex_init(&m_mutex, nullptr);
    if(ret != 0)
    {
        perror("error in pthread_mutex_init");
        exit(1);
    }
}

MutexLock::~MutexLock() {
    int ret = pthread_mutex_destroy(&m_mutex);
    if(ret != 0)
    {
        perror("error in pthread_mutex_destroy");
        std::cout << "ret = " << ret << std::endl;
        exit(1);
    }
}

void MutexLock::lock() {
    int ret = pthread_mutex_lock(&m_mutex);
    
    if(ret != 0)
    {
        perror("error in pthread_mutex_lock");
        return ;
    }

}


void MutexLock::unlock() {
    int ret = pthread_mutex_unlock(&m_mutex);
    if(ret != 0)
    {
        perror("error in pthread_mutex_unlock");
        return ;
    }
}

pthread_mutex_t* MutexLock::get_pthread_mutex_ptr()
{
    return &m_mutex;
}

MyLockGuard::MyLockGuard(MutexLock& mutex)
    :m_mutex(mutex)
{
    m_mutex.lock();
}

MyLockGuard::~MyLockGuard() {
    m_mutex.unlock();
}



//TODO
int MutexLock::trylock() {
    return 0;
}

