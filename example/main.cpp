#include <iostream>
#include <thread>
#include "../src/PerfTimer.hpp"

void test_thread(std::string timer_name, int usleep_count)
{
    for (int i = 0; i < 100; i++)
    {
        auto timer_above = PerfTimer::start_timer(timer_name + "_encapsulating");
        auto timer = PerfTimer::start_timer(timer_name);
        std::this_thread::sleep_for(std::chrono::microseconds(usleep_count));
        PerfTimer::stop_timer(timer);
        PerfTimer::stop_timer(timer_above);
    }
}

int main()
{
    std::thread test_1(test_thread, "timer_1ms", 1000);
    std::thread test_2(test_thread, "timer_1ms", 1000);
    std::thread test_3(test_thread, "timer_1ms", 1000);
    std::thread test_4(test_thread, "timer_1ms", 1000);
    std::thread test_5(test_thread, "timer_1ms", 1000);

    test_1.join();
    test_2.join();
    test_3.join();
    test_4.join();
    test_5.join();

    std::cout << PerfTimer::summarize() << std::endl;
}