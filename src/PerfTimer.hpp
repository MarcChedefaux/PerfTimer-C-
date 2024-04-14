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

#ifndef _COLORS_
#define _COLORS_

/* FOREGROUND */
#define RST "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"
#define KYEL "\x1B[33m"
#define KBLU "\x1B[34m"
#define KMAG "\x1B[35m"
#define KCYN "\x1B[36m"
#define KWHT "\x1B[37m"

#define BOLD "\x1B[1m"
#define UNDL "\x1B[4m"

#endif /* _COLORS_ */

#ifndef PERF_TIMER
#define PERF_TIMER

#include <chrono>
#include <string>
#include <sstream>
#include <map>
#include <vector>
#include <iostream>
#include <iomanip>
#include <math.h>
#include <thread>

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

    void add_times(stoppedTimer new_time);
    std::string summarize();

    friend PerfTimer;

public:
    Timer();
};

/**
 * @brief Class that will be use from a static context used to start a timer, stop it and record everything to Timer.
 *
 */
class PerfTimer
{
private:
    static std::map<std::string, std::map<std::thread::id, Timer>> all_timers;

public:
    PerfTimer() = delete;

    static runningTimer start_timer(std::string timer_name);
    static void stop_timer(runningTimer start_timer);
    static std::string summarize();
};

#endif