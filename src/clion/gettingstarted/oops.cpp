//
// Created by Dimitar Gueorguiev on 9/10/22.
//
#include <iostream>
#include <chrono>
#include <thread>

using namespace std::chrono_literals;

struct func
{
    int& i;
    char* p;
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
        std::cout << "From the destructor of func: value at func::i = " << p[i] << std::endl;
        delete[] p;
    }

    void do_something(int idx) {
        p[idx] = 'A';
        std::this_thread::sleep_for(100ms);
    }

    void operator()()
    {
        for (unsigned j=0; j < 1000000; ++j)
        {
            do_something(i);
        }
    }
};

void oops() {
    int some_local_state = 100000;
    func my_func(some_local_state);
    std::thread my_thread(my_func);
    my_thread.detach();
    my_func.p = nullptr;
};

int main() {
    std::cout << "Hello from oops!" << std::endl;
    oops();
    std::cout << "After oops executed a detached thread" << std::endl;
    // we are never going to see the message in the destructor on the console
}