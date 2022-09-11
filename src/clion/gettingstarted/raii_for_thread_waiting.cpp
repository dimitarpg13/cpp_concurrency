//
// Created by Dimitar Gueorguiev on 9/11/22.
//
#include <iostream>
#include <thread>

struct func
{
    int& i;
    char * p;
    const int N=1000000;
    func(int& i_) : i(i_)
    {
        p = new char[N];
    }

    func(const func & f) : i(f.i) {
        p = new char[N];
        for (int idx=0; idx < N; ++idx)
            p[idx] = f.p[idx];
    }

    ~func() {

        if (p) {
            std::cout << "From the destructor of func: value at func::i = " << p[i] << std::endl;
            delete[] p;
            p = nullptr;
        }

    }

    void do_something(unsigned idx) {

        p[idx] = idx % 256;
        if (idx == i) {
            std::cout << "func obj is at line " << i << std::endl;
        }
    }

    void operator()()
    {
        for (unsigned j=0; j < 1000000; ++j)
        {
            do_something(j);
        }
    }
};

class thread_guard
{
    std::thread& t;
public:
    explicit thread_guard(std::thread& t_): t(t_)
    {}
    ~thread_guard()
    {
        if (t.joinable())
        {
            t.join();
        }
    }
    thread_guard(thread_guard const&)=delete;
    thread_guard& operator=(thread_guard const&)=delete;
};

void do_something_in_current_thread()
{
    for (int i = 0; i < 1000000; ++i) {
        if (i == 100000) {
            std::cout << "I am at line 100000!" << std::endl;
        }
    }
};

void f()
{
    int some_local_state=100000;
    func my_func(some_local_state);
    std::thread t(my_func);
    thread_guard g(t);

    do_something_in_current_thread();
}

int main() {
    f();
}