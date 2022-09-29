//
// Created by Dimitar Gueorguiev on 9/11/22.
//
#include <iostream>
#include <thread>
#include <string>
#include <cstdio>

struct func
{
    std::string& s;
    char * p;
    const int N=1000000;
    func(std::string& s_) : s(s_)
    {
        p = new char[N];
    }

    func(const func & f) : s(f.s) {
        p = new char[N];
        for (int idx=0; idx < N; ++idx)
            p[idx] = f.p[idx];
    }

    ~func() {

        if (p) {
            std::cout << "From the destructor of func: value at func::i = " << p[std::stoi(s)] << std::endl;
            delete[] p;
            p = nullptr;
        }

    }

    void do_something(unsigned idx) {

        p[idx] = idx % 92 + 33;
        int i = std::stoi(s);
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

void not_oops(int some_param) {
    char buffer[1024];

}