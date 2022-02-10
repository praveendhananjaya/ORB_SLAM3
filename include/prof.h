//
// Created by Acer on 3/19/2022.
//

#pragma once
#ifndef UNTITLED2_PROF_H
#define UNTITLED2_PROF_H
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <cmath>
#include <semaphore.h>
#include "profTime.h"

#ifdef PROFILING
#define PROFILING 1
#if PROFILING
#define START prof::Get().BeginSession("Profile")
#define PROFILE_SCOPE(name) profTime time##__LINE__(name)
#define PROFILE_FUNCTION() PROFILE_SCOPE(__FUNCTION__)
#else
#defile PROFILE_SCOPE(name)

#endif
#else
#define PROFILE_FUNCTION()
#endif



struct InstrumentationSession
{
    std::string Name;
};

struct ProfileResult
{
    std::string Name;
    long long Start, End;
    uint32_t ThreadID;
};

class prof {
private:
    InstrumentationSession* m_CurrentSession{};
    std::ofstream m_OutputStream;
    int m_ProfileCount;
    sem_t semaphore ;

public:
    prof(): m_CurrentSession(nullptr), m_ProfileCount(0) {

    }

    void BeginSession(const std::string& name, const std::string& filepath = "results.json");
    void EndSession();
    void WriteProfile(const ProfileResult& result);
    void WriteHeader();
    void WriteFooter();
    static prof& Get();

};


#endif //UNTITLED2_PROF_H
