#include <iostream>
#include <thread>

void hello()
{
    std::cout<<"Hello Concurrent World\n";
}

int main()
{
    std::thread t(hello);

    // 1. if `join()`, then "Hello Concurrent World" 
    // will always be printed before "end",
    // which means the `main()` continues after t (on another thread) 
    // is finished.
    t.join();

    // 2. if `detach()`, the order is unknown,
    // which means the `main()` continues and finished, 
    // while t is running on another thread, 
    // they didn't see each other.
    // t.detach();

    // 3. if none of join or detach, I got this error after 
    //     unknows order of the 2 above strings: 
    // terminate called without an active exception
    // “./a.out” terminated by signal SIGABRT (Abort)

    std::cout << "end\n";
}
