#ifndef __OO_THREAD_H__
#define __OO_THREAD_H__

#include <pthread.h>

class Thread {
public:
    Thread();

    Thread(const Thread& src) = delete;
    Thread(Thread&& src) = delete;
    Thread& operator=(const Thread& src) = delete;
    
    virtual ~Thread();

    static void *ThreadFunc(void *arg);
    void start();
    void stop();

    virtual void run() = 0;

private:
    pthread_t m_thid;
    bool m_isRunning;

};

#endif