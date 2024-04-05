#include "OO_Thread.hpp"
#include "TaskQueue.hpp"
#include <iostream>
#include <memory>
#include "OO_Thread.hpp"
#include <functional>


using std::unique_ptr;

void producer(TaskQueue& task_queue) {
    for(int i = 0; i < 20; i++)
    {
        task_queue.push(i);
        std::cout << "<< get " << i << std::endl;
    }
}

void consumer(TaskQueue& task_queue) {
    for(int i = 0; i < 20; i++)
    {
        int val = task_queue.pop();
        std::cout << ">> pop " << val << std::endl;
    }
}

void test()
{
    TaskQueue taskQue(10);

    unique_ptr<Thread>  pro(new Thread(std::bind(producer, std::ref(taskQue))));
    unique_ptr<Thread>  con(new Thread(std::bind(consumer, std::ref(taskQue))));

    pro->start();
    con->start();

    pro->stop();
    con->stop();
}

void test2()
{
    MutexLock mutex1;
    //MutexLock mutex2 = mutex1;//error

    MutexLock mutex3;
    //mutex3 = mutex1;//error
}

int main(int argc, char *argv[])
{
    test();
    return 0;
}