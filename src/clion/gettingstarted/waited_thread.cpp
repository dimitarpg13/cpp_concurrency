//
// Created by Dimitar Gueorguiev on 9/10/22.
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
    int some_local_state = 100000;
    std::cout << "before my_func declaration" << std::endl;
    func my_func(some_local_state);
    std::cout << "after my_func declaration my_func.p[999999]=" << my_func.p[999999] << std::endl;

    std::thread t(my_func);
    try
    {
        do_something_in_current_thread();
    }
    catch(...)
    {
        t.join();
        throw;
    }
    t.join();
};

int main() {
    f();
}