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
    auto stats = get_statistics();
    double var = 0;
    for (auto timer : times)
    {
        int64_t time = std::chrono::nanoseconds(timer.elapsed_time).count();
        var += ((double)time - stats.mean) * ((double)time - stats.mean) / (double)stats.number;
    }
    double sd = sqrt(var);

    std::stringstream ss;
    if (stats.mean < 1e3)
    {
        ss << std::fixed << std::setprecision(4) << stats.mean << " ns (+- " << std::fixed << std::setprecision(4) << sd << " ns) ";
    }
    else if (stats.mean < 1e6)
    {
        ss << std::fixed << std::setprecision(4) << stats.mean / 1e3 << " µs (+- " << std::fixed << std::setprecision(4) << sd / 1e3 << " µs) ";
    }
    else
    {
        ss << std::fixed << std::setprecision(4) << stats.mean / 1e6 << " ms (+- " << std::fixed << std::setprecision(4) << sd / 1e6 << " ms) ";
    }
    ss << "over " << stats.number << " runs";
    return ss.str();
}

statistics Timer::get_statistics()
{
    double mean = 0;
    long long number_times = times.size();
    for (auto timer : times)
    {
        mean += (double)std::chrono::nanoseconds(timer.elapsed_time).count() / (double)number_times;
    }
    statistics stats;
    stats.mean = mean;
    stats.number = number_times;

    return stats;
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
        std::vector<statistics> all_stats;
        long long all_runs = 0;
        ss << KBLU << BOLD << timer.first << " : " << RST << std::endl;
        for (auto &t : timer.second)
        {
            ss << "\t" << KGRN << UNDL << t.first << " :" << RST << " " << t.second.summarize() << std::endl;
            auto stat = t.second.get_statistics();
            all_runs += stat.number;
            all_stats.push_back(stat);
        }
        double all_mean = 0;
        for (auto stat : all_stats)
        {
            all_mean += stat.mean * ((double)(stat.number) / (double)(all_runs));
        }
        ss << "\t" << KMAG << BOLD << "Average : ";
        if (all_mean < 1e3)
        {
            ss << std::fixed << std::setprecision(4) << all_mean << " ns";
        }
        else if (all_mean < 1e6)
        {
            ss << std::fixed << std::setprecision(4) << all_mean / 1e3 << " µs";
        }
        else
        {
            ss << std::fixed << std::setprecision(4) << all_mean / 1e6 << " ms";
        }
        ss << " over " << all_runs << " runs" << RST << std::endl;
    }
    return ss.str();
}
