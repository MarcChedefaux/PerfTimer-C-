/**
 * @file PerfTimer.hpp
 * @author Marc Chedefaux (chedefaux.marc@gmail.com)
 * @brief File including the header for all the PerfTimer's needs
 * @version 0.1
 * @date 2024-04-11
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <chrono>
#include <string>
#include <sstream>
#include <map>
#include <vector>
#include <iostream>

class Timer;
class PerfTimer;

/**
 * @brief Struct encapsulating a started timer waiting to end
 *
 */
struct runningTimer
{
private:
    std::chrono::time_point<std::chrono::high_resolution_clock> start_time;
    std::string name_timer;

    friend PerfTimer;
};

/**
 * @brief Struct containing informations about a finished timer
 *
 */
struct stoppedTimer
{
private:
    std::chrono::duration<int64_t, std::nano> elapsed_time;

    friend Timer;
    friend PerfTimer;
};

/**
 * @brief Class instantiating an instance of a timer containing all the runs of a specific part of the execution
 *
 */
class Timer
{
private:
    std::vector<stoppedTimer> times;

    Timer();
    void add_times(stoppedTimer new_time);
    std::string summarize();

    friend PerfTimer;
};

/**
 * @brief Class that will be use from a static context used to start a timer, stop it and record everything to Timer.
 *
 */
class PerfTimer
{
private:
    static std::map<std::string, Timer> all_timers;

public:
    PerfTimer() = delete;

    static runningTimer start_timer(std::string timer_name);
    static void stop_timer(runningTimer start_timer);
    static std::string summarize();
};