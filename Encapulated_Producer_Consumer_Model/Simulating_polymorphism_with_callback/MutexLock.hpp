#ifndef __MUTEXLOCK_H__
#define __MUTEXLOCK_H__

#include <pthread.h>

class MutexLock {
public:

    MutexLock();

    MutexLock(const MutexLock& src) = delete;
    MutexLock(MutexLock&& src) = delete;
    MutexLock& operator=(const MutexLock& src) = delete;

    virtual ~MutexLock();
    void lock();
    void unlock();
    int trylock();

    pthread_mutex_t* get_pthread_mutex_ptr();

private:
    pthread_mutex_t m_mutex;
   
    
};


class MyLockGuard {
public:
    MyLockGuard() = delete;
    MyLockGuard(MutexLock& mutex);

    virtual ~MyLockGuard();

private:
    MutexLock& m_mutex;
};


#endif