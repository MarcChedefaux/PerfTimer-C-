#include <iostream>
#include <thread>
#include <unistd.h>
#include "../src/PerfTimer.hpp"

void test_thread()
{
    for (int i = 0; i < 10; i++)
    {
        auto timer = PerfTimer::start_timer("test");
        sleep(1);
        PerfTimer::stop_timer(timer);
    }
}

int main()
{
    test_thread();
    std::cout << PerfTimer::summarize() << std::endl;
}