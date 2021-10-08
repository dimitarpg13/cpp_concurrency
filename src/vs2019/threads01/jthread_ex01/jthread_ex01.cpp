// jthread_ex01.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "jthread.hpp"
#include <iostream>
#include <string>
#include <chrono>
#include <cassert>
#include <atomic>
using namespace::std::literals;

void testBasicJThreadAPI() {
	assert(std::jthread::hardware_concurrency() == std::thread::hardware_concurrency());

}

int main()
{
	testBasicJThreadAPI();
	return 0;
}
