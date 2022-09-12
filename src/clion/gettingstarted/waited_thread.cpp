//
// Created by Dimitar Gueorguiev on 9/10/22.
//
#include <iostream>
#include <thread>
#include <cstring>

struct func
{
    int& i;
    char * p;
    static const int N=1000000;
    func(int& i_) : i(i_)
    {
        p = new char[N];
    }

    func(const func & f) : i(f.i) {
        p = new char[N];
        std::memcpy(p, f.p, N);
    }

    ~func() {

        if (p) {
            std::cout << "From the destructor of func: value at func::i = " << p[i] << std::endl;
            delete[] p;
            p = nullptr;
        }

    }

    void do_something(unsigned idx) {

        p[idx] = idx % 92 + 33;
        if (idx == i) {
            std::cout << "func obj is at line: " << p[i] << std::endl;
        }

    }

    void operator()()
    {
        for (unsigned j=0; j < N; ++j)
        {
            do_something(j);
        }
    }
};

void do_something_in_current_thread(int idx)
{
    for (int i = 0; i < func::N; ++i) {
        if (i == idx) {
            std::cout << "I am at line 100000!" << std::endl;
        }
    }
};

void f()
{
    int some_local_state = 100000;
    std::cout << "before my_func declaration" << std::endl;
    func my_func(some_local_state);
    std::cout << "after my_func declaration my_func.p[N-1]=" << my_func.p[func::N-1] << std::endl;

    std::thread t(my_func);
    try
    {
        do_something_in_current_thread(some_local_state);
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