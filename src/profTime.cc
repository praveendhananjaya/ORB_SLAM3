//
// Created by Acer on 3/19/2022.
//

#include "profTime.h"


profTime:: ~profTime()
{
    if (!m_Stopped)
        Stop();
}

void profTime::Stop()
{
    auto endTimepoint = std::chrono::high_resolution_clock::now();

    long long start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimepoint).time_since_epoch().count();
    long long end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch().count();

    uint32_t threadID = std::hash<std::thread::id>{}(std::this_thread::get_id());
    prof::Get().WriteProfile({ m_Name, start, end, threadID });

    m_Stopped = true;
}


