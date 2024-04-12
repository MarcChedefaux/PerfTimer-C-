/**
 * @file PerfTimer.cpp
 * @author Marc Chedefaux (chedefaux.marc@gmail.com)
 * @brief File containing all the logic behind the header
 * @version 0.1
 * @date 2024-04-11
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "PerfTimer.hpp"

// Timer class implementation
Timer::Timer()
{
    times = std::vector<stoppedTimer>();
}

void Timer::add_times(stoppedTimer new_time)
{
    times.push_back(new_time);
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(new_time.elapsed_time).count() << std::endl;
}

std::string Timer::summarize()
{
    return "WIP";
}

// PerfTimer class implementation
std::map<std::string, Timer> PerfTimer::all_timers;

runningTimer PerfTimer::start_timer(std::string timer_name)
{
    runningTimer timer;
    timer.name_timer = timer_name;
    timer.start_time = std::chrono::high_resolution_clock::now();
    return timer;
}

void PerfTimer::stop_timer(runningTimer start_timer)
{
    stoppedTimer timer;
    timer.elapsed_time = std::chrono::high_resolution_clock::now() - start_timer.start_time;
    all_timers[start_timer.name_timer].add_times(timer);
}

std::string PerfTimer::summarize()
{
    std::stringstream ss;
    for (auto &timer : all_timers)
    {
        ss << timer.first << " : " << timer.second.summarize() << std::endl;
    }
    return ss.str();
}
