// thread_ex01.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <thread>

void hello()
{
    std::cout << "Hello Concurrent World!" << std::endl;
}

int main()
{
    std::thread t(hello);
    t.join();
}
