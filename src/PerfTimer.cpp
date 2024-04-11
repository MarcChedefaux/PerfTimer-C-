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
    std::cout << new_time.elapsed_time << std::endl;
}

std::string Timer::summarize()
{
    return "WIP";
}

// PerfTimer class implementation
std::map<int, Timer> PerfTimer::all_timers;