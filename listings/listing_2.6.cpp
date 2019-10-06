#include <thread>
#include <utility>
#include <iostream>

class scoped_thread
{
    std::thread t;
public:
    explicit scoped_thread(std::thread t_):
        t(std::move(t_))
    {
        if(!t.joinable())
            throw std::logic_error("No thread");
    }
    ~scoped_thread()
    {
        t.join();
    }
    scoped_thread(scoped_thread const&)=delete;
    scoped_thread& operator=(scoped_thread const&)=delete;
};

void do_something(int& i)
{
    ++i;
}

struct func
{
    int& i;
    // without passing `ostream`, 
    // there will be nothing to show
    std::ostream& os;
    func(int& i_, std::ostream& os):i(i_), os(os){}

    void operator()()
    {
        for(unsigned j=0;j<1000000;++j)
        {
            do_something(i);
        }
        os << "i=" << i << "\n";
    }
};

void do_something_in_current_thread()
{}

void f()
{
    // variable should be init
    int some_local_state = 0;
    // thread will hold its own context, 
    // when `f()` finished, the `int& i` is still valid.
    scoped_thread t(std::thread(func(some_local_state, std::cout)));

    do_something_in_current_thread();
}   // end of `f()`, thread is `join()`ed

int main()
{
    f();
    // thread will finish here, as it `join()`ed,
    // and "the end" will always printed after "i=1000000"
    std::cout << "the end\n";
}
