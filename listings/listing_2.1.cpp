#include <thread>
#include <iostream>

void do_something(int& i)
{
    ++i;
}

struct func
{
    int& i;

    func(int& i_):i(i_){}

    void operator()()
    {
        for(unsigned j=0;j<1000000;++j)
        {
            do_something(i);
        }
    }
};


void oops()
{
    int some_local_state=0;
    func my_func(some_local_state);
    std::thread my_thread(my_func);

    // 1. if `detach()`, then `cout` result will be 0,
    // because the `main()` continues, and the increment
    // cannot be seen before finished.
    my_thread.detach();

    // 2. if `join()`, then `cout` result will be 1000000,
    // because the `main()` will wait until `my_thread` 
    // finished, and the increment can be seen.
    // my_thread.join();
    std::cout << some_local_state << "\n";
}

int main()
{
    oops();
}
