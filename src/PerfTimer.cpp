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
}

std::string Timer::summarize()
{
    double mean = 0;
    long long number_times = times.size();
    for (auto timer : times)
    {
        mean += (double)std::chrono::nanoseconds(timer.elapsed_time).count() / (double)number_times;
    }
    double var = 0;
    for (auto timer : times)
    {
        int64_t time = std::chrono::nanoseconds(timer.elapsed_time).count();
        var += ((double)time - mean) * ((double)time - mean) / (double)number_times;
    }
    double sd = sqrt(var);

    std::stringstream ss;
    if (mean < 1e3)
    {
        ss << mean << " ns (+- " << sd << " ns) ";
    }
    else if (mean < 1e6)
    {
        ss << mean / 1e3 << " µs (+- " << sd / 1e3 << " µs) ";
    }
    else
    {
        ss << mean / 1e6 << " ms (+- " << sd / 1e6 << " ms) ";
    }
    ss << "over " << number_times << " runs";
    return ss.str();
}

// PerfTimer class implementation
std::map<std::string, std::map<std::thread::id, Timer>> PerfTimer::all_timers;

runningTimer PerfTimer::start_timer(std::string timer_name)
{
    runningTimer timer;
    timer.name_timer = timer_name;
    timer.start_time = std::chrono::high_resolution_clock::now();
    return timer;
}

void PerfTimer::stop_timer(runningTimer start_timer)
{
    auto actual_time = std::chrono::high_resolution_clock::now();
    stoppedTimer timer;
    timer.elapsed_time = actual_time - start_timer.start_time;
    all_timers[start_timer.name_timer][std::this_thread::get_id()].add_times(timer);
}

std::string PerfTimer::summarize()
{
    std::stringstream ss;
    for (auto &timer : all_timers)
    {
        ss << KBLU << BOLD << timer.first << " : " << RST << std::endl;
        for (auto &t : timer.second)
        {
            ss << "\t" << KGRN << UNDL << t.first << " :" << RST << " " << t.second.summarize() << std::endl;
        }
    }
    return ss.str();
}
