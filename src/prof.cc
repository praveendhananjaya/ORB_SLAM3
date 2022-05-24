//
// Created by Acer on 3/19/2022.
//

#include "prof.h"


void prof::BeginSession(const std::string& name, const std::string& filepath )
{
    m_OutputStream.open(filepath);
    WriteHeader();
    m_CurrentSession = new InstrumentationSession { name };
    sem_init(&semaphore,1,1);
}

void prof::EndSession()
{
    WriteFooter();
    m_OutputStream.close();
    delete m_CurrentSession;
    m_CurrentSession = nullptr;
    m_ProfileCount = 0;
    sem_destroy(&semaphore);
}

void prof::WriteProfile(const ProfileResult& result)
{


    std::string name = result.Name;
    std::replace(name.begin(), name.end(), '"', '\'');
    sem_wait(&semaphore);
    if((result.End - result.Start)>=PROFE_PERIOD) {
        if (m_ProfileCount++ > 0)
            m_OutputStream << ",";

        m_OutputStream << "{";
        m_OutputStream << "\"cat\":\"function\",";
        m_OutputStream << "\"dur\":" << (result.End - result.Start) << ',';
        m_OutputStream << "\"name\":\"" << name << "\",";
        m_OutputStream << "\"ph\":\"X\",";
        m_OutputStream << "\"pid\":0,";
        m_OutputStream << "\"tid\":" << result.ThreadID << ",";
        m_OutputStream << "\"ts\":" << result.Start;
        m_OutputStream << "}";

        m_OutputStream.flush();
    }
    sem_post(&semaphore);
}

void prof::WriteHeader()
{
    m_OutputStream << "{\"otherData\": {},\"traceEvents\":[";
    m_OutputStream.flush();
}

void prof::WriteFooter()
{
    m_OutputStream << "]}";
    m_OutputStream.flush();
}

prof &prof::Get() {
    static prof instance;
    return instance;
}

