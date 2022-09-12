//
// Created by Dimitar Gueorguiev on 9/11/22.
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

void do_something_in_current_thread(int idx)
{
    for (int i = 0; i < func::N; ++i) {
        if (i == idx) {
            std::cout << "I am at line " << idx << "!" << std::endl;
        }
    }
};

void f()
{
    int some_local_state=100000;
    func my_func(some_local_state);
    std::thread t(my_func);
    thread_guard g(t);

    do_something_in_current_thread(some_local_state);
}

int main() {
    f();
}