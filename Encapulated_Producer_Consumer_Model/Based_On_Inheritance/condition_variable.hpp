#ifndef __CONDITION_VARIABLE_HPP__
#define __CONDITION_VARIABLE_HPP__

#include <pthread.h>
#include "MutexLock.hpp"

class Condition {
public:
    Condition(MutexLock& mutex);
    Condition() = delete;
    Condition(const Condition& src) = delete;
    Condition(Condition&& src) = delete;

    Condition& operator=(const Condition& src) = delete;

    void wait();

    void notify_one_or_more();

    void notify_all();

    virtual ~Condition();

private:
    pthread_mutex_t* m_mutex;
    pthread_cond_t m_cond;
};


#endif