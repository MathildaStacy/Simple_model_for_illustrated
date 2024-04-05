
#include "condition_variable.hpp"
#include "MutexLock.hpp"
#include <cstdio>
#include <pthread.h>

Condition::Condition(MutexLock& mutex): m_mutex(mutex.get_pthread_mutex_ptr())
{
    int ret = pthread_cond_init(&m_cond, nullptr);
    if(ret != 0)
    {
        perror("error in pthread_cond_init");
    }
}


void Condition::wait() {
    int ret = pthread_cond_wait(&m_cond, m_mutex);

    if(ret != 0)
    {
        perror("error in pthread_cond_wait");
        return ;
    }
}


void Condition::notify_one_or_more() {
    int ret = pthread_cond_signal(&m_cond);

    if(ret != 0)
    {
        perror("error in pthread_cond_signal");
    }
}

void Condition::notify_all() {
    int ret = pthread_cond_broadcast(&m_cond);

    if(ret != 0)
    {
        perror("error in pthread_cond_broadcast");
    }
}

Condition::~Condition() {
    int ret = pthread_cond_destroy(&m_cond);

    if(ret != 0)
    {
        perror("error in pthread_cond_destroy");
    }
}