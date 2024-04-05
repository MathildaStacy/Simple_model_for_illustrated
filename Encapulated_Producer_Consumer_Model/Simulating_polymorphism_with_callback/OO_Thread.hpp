#ifndef __OO_THREAD_H__
#define __OO_THREAD_H__

#include <pthread.h>
#include <functional>

class Thread {
public:
    Thread();
    Thread(std::function<void()>&& arg);

    Thread(const Thread& src) = delete;
    Thread(Thread&& src) = delete;
    Thread& operator=(const Thread& src) = delete;

    
    virtual ~Thread();

    static void *ThreadFunc(void *arg);
    void start();
    void stop();

    void run();


    

private:
    std::function<void()> m_func;
    pthread_t m_thid;
    bool m_isRunning;

};

#endif