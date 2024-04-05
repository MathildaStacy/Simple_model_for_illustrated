#include <iostream>
#include <mutex>

//如果想将单例对象放在堆上并保证线程安全，
//可以使用双重检查锁定模式（Double-Checked Locking Pattern）。
//不过需要注意，这种方式在C++11之前可能会因为内存模型的问题而不安全，
//但在C++11及以后由于内存模型得到了增强，这种方法是可行的。

/*
原因：如果只在第一个if里面检查一次，而不使用双重检查加锁模式，在多线程环境下可能会导致创建多个实例的问题。下面通过一个示例来具体说明这个问题：

     1.假设有两个线程A和B同时调用getInstance()方法：

     2.线程A进入getInstance()方法，执行到第一个if (instance == nullptr)判断，此时instance确实是nullptr，因此条件成立。

     3.在线程A还没有来得及进一步创建实例之前，调度器切换到了线程B。线程B也进入getInstance()方法，同样执行到第一个if判断，由于此时线程A还没有创建实例，instance仍然是nullptr，条件同样成立。

     4.如果这时调度器又切换回线程A，线程A继续执行，创建一个新的实例并将其地址赋给instance。

     5.线程A执行完毕，调度器再次切换到线程B，线程B由于之前已经通过了instance == nullptr的判断，会继续执行并创建另一个新的实例，这违反了单例模式的原则。
*/

/*
C++11以前就算使用双重检查锁定模式也不安全的原因：
    问题根源
            双重检查锁定模式试图只在第一次访问资源时加锁，以提高性能。其基本思想是先检查对象是否已经被创建，如果没有，
        则加锁并再次检查以确保只创建一次对象。问题在于，在C++11之前的内存模型中，编译器和处理器可能会对指令进行重排序，导致以下情况发生：

            指令重排序：编译器为了优化性能可能会重排序指令，处理器也可能因为各种原因（如流水线优化）重排序指令执行。这意味着实际执行的指令顺序可能与代码中的顺序不同。

            非原子操作：在C++11之前，没有原子操作的直接支持，也就是说，对于复杂对象的构造可能不是原子的。这意味着在对象构造过程中，对象的指针可能已经非空，但构造尚未完成。

    具体问题
            假设有两个线程A和B，它们同时检查到单例对象为nullptr，准备创建单例对象。由于指令重排序和非原子操作，可能出现以下情况：

            线程A进入锁内部，开始创建单例对象。
            在对象完全构造完成之前，对象的内存已经被分配，指针instance已经指向这块内存，但对象的构造函数还没有完全执行完毕。此时，线程A被挂起。
            线程B进入getInstance()方法，检查到instance不为nullptr（因为内存已经分配），因此返回一个指向未完全构造对象的指针。
            线程B使用这个不完全的对象可能导致未定义行为。
    C++11的改进
            C++11引入了一个明确的多线程内存模型和原子操作库，为多线程环境下的内存操作提供了清晰的规则和保证。其中，静态局部变量的初始化被明确为线程安全的，即如果多个线程同时到达初始化语句，
        只有一个线程会执行初始化，其余线程会等待初始化完成。这样，使用局部静态变量实现的单例模式自然是线程安全的，
        不再需要复杂的双重检查锁定模式。此外，C++11提供的std::atomic和std::memory_order等工具可以帮助开发者在需要的时候实现精确的内存顺序控制和原子操作，
        从而安全地处理多线程间的数据共享和同步。

    总结：在C++11以前，单例模式中的在静态区创建对象的方法和在堆上创建对象的方法，就算都使用双重检查加锁模式也不是线程安全的，
         因为静态局部变量的初始化并不是原子的。但是C++11以后，静态局部变量的初始化是原子的，因此在静态区创建对象的方法（不使用双重检查锁定模式）
         和在堆上创建方法（使用双重检查锁定模式）都是线程安全的
*/
class Singleton {
public:
    // 删除拷贝构造函数和赋值运算符，防止被复制
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

    // 提供一个全局访问点
    static Singleton* getInstance() {
        // 第一次检查，避免每次调用都加锁
        if (instance == nullptr) {
            std::lock_guard<std::mutex> lock(mutex); // 加锁
            // 第二次检查，确保只有第一个进入此区域的线程会创建实例
            if (instance == nullptr) {
                instance = new Singleton();
            }
        }
        return instance;
    }

    // 示例方法
    void doSomething() {
        std::cout << "Doing something." << std::endl;
    }

    // 提供手动删除单例的方法，注意需要处理线程安全和对象再次使用的问题
    static void destroyInstance() {
        std::lock_guard<std::mutex> lock(mutex); // 加锁
        if (instance != nullptr) {
            delete instance;
            instance = nullptr;
        }
    }

private:
    static Singleton* instance; // 静态成员变量，指向单例对象
    static std::mutex mutex;  // 用于同步的互斥锁

    // 私有构造函数，防止外部创建实例
    Singleton() {}

    // 私有析构函数，防止外部删除实例
    ~Singleton() {}
};

// 初始化静态成员变量
Singleton* Singleton::instance = nullptr;
std::mutex Singleton::mutex;

int main() {
    // 获取单例对象并使用
    Singleton::getInstance()->doSomething();

    // 清理单例对象
    Singleton::destroyInstance();

    return 0;
}
