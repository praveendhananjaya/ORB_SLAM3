//
// Created by Acer on 3/19/2022.
//

#pragma once
#ifndef UNTITLED2_PROFTIME_H
#define UNTITLED2_PROFTIME_H
#include <iostream>
#include <chrono>
#include <thread>
#include "prof.h"

class profTime {

private:
    const char* m_Name;
    std::chrono::time_point<std::chrono::high_resolution_clock> m_StartTimepoint;
    bool m_Stopped;

public:
    profTime(const char* name): m_Name(name), m_Stopped(false) {
        m_StartTimepoint = std::chrono::high_resolution_clock::now();
    };
    ~profTime();
    void Stop();


};


#endif //UNTITLED2_PROFTIME_H
