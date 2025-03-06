#include "Profiler.h"
#include <chrono>

void Profile::timeprocess()
{
    milliSecondsTaken = end - start;
}

void Profile::SetStart()
{
    start = std::clock();
}

void Profile::SetEnd()
{
    end = std::clock();

}

float Profile::Gettime()
{
    return milliSecondsTaken;
}



ProfilerSystem::ProfilerSystem()
{
}

ProfilerSystem::~ProfilerSystem()
{
}

void ProfilerSystem::startframe()
{
}

void ProfilerSystem::endFrame()
{
}

void ProfilerSystem::storeProfiledata(const char* name, float timetaken)
{
    ProfileData* data = new ProfileData();
    data->milliSecondsTaken = timetaken;
    data->Profilename = name;
}




void Frame::Calctotaltime()
{
    for (int i = 0; i < Thisframe.size(); i++)
    {
        frameTime = frameTime + Thisframe[i].milliSecondsTaken;
    }
   
}
