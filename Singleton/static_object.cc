#include <iostream>

//简单地在静态区创建一个变量。C++11以后是线程安全的
/*
 Key points:

 The constructor is private, preventing any other class from creating a new instance.
 The copy constructor and assignment operator are deleted to prevent copying of the instance.
 getInstance() is a public static method that returns a reference to the static Singleton instance. The use of a static variable inside this method ensures that the instance is created only once (the first time getInstance() is called). This is guaranteed to be thread-safe by the C++11 standard.
 Any calls to Singleton::getInstance() will return a reference to the same instance.
 The Singleton instance is lazily initialized, meaning it's only created when it's needed.
 

*/
class Singleton {
public:
    // Deleted copy constructor and assignment operator to prevent copying
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

    // Static method to access class instance
    // Function is static so we can call it without an object
    static Singleton& getInstance() {
        // Static variable inside function ensures that instance is created only on the first call
        // and is destroyed automatically when the program ends. Initialization is thread-safe.
        static Singleton instance;
        return instance;
    }

    // Example function to demonstrate usage
    void doSomething() {
        std::cout << "Doing something." << std::endl;
    }

private:
    // Private constructor to prevent instantiation outside class
    Singleton() {}
};

int main() {
    // Get the singleton instance and use it
    Singleton::getInstance().doSomething();

    // Trying to get another instance will return the same instance
    Singleton& singletonInstance = Singleton::getInstance();
    singletonInstance.doSomething();

    return 0;
}
