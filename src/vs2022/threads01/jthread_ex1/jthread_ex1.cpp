// jthread_ex1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <chrono>
#include <iostream>
#include <thread>

void joinableThreadCallsTerminateInDestr() {
    std::cout << "joinable Thread calls std::terminate in destructor" << std::endl;
    std::cout << std::boolalpha;
    std::thread thr{ [] { std::cout << "Joinable std::thread" << std::endl; } };
    std::cout << "thr.joinable(): " << thr.joinable() << std::endl;
}

void joinableJThreadAtExit() {
    std::cout << "joinable JThread at exit" << std::endl;
    std::cout << std::boolalpha;
    std::jthread thr{ [] { std::cout << "Joinable std::jthread" << std::endl; } };
    std::cout << "thr.joinable(): " << thr.joinable() << std::endl;
}

void cooperativeInterruptOfJThread() {
    using namespace::std::literals;
    std::cout << "cooperative Interrupt of JThread" << std::endl;

    std::jthread nonInterruptible([] {
        int counter{ 0 };
        while (counter < 10) {
            std::this_thread::sleep_for(0.2s);
            std::cerr << "nonInterruptible: " << counter << std::endl;
            ++counter;
        }
    });

    std::jthread interruptible([](std::stop_token stoken) {
        int counter{ 0 };
        while (counter < 10) {
            std::this_thread::sleep_for(0.2s);
            if (stoken.stop_requested()) return;
            std::cerr << "interruptible: " << counter << std::endl;
            ++counter;
        }
    });

    std::this_thread::sleep_for(1s);

    std::cerr << std::endl;
    std::cerr << "Main thread interrupts both jthreads" << std::endl;
    nonInterruptible.request_stop();
    interruptible.request_stop();
}

int main()
{
  std::cout << "Thread tests:\n";
  //joinableThreadCallsTerminateInDestr();
  //joinableJThreadAtExit();
  cooperativeInterruptOfJThread();

}
