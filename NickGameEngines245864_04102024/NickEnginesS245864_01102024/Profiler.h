#pragma once

#include <vector>
#include "string"
#include <ctime>
#include <SDL.h>

struct Profile
{
	const char* Profilename;
	float milliSecondsTaken;
	float start, end;
	void timeprocess();
	void SetStart();
	void SetEnd();
	float Gettime();
	Profile(const char* name )
	{
		SetStart();
		Profilename = name;
	}
	~Profile()
	{
		
		SetEnd();
		timeprocess();

		ProfilerSystem::Instance().storeProfiledata(Profilename, (1000 * Gettime()) / CLOCKS_PER_SEC);

	}
	
	

};
#define PROFILE(name) Profile p(name)
struct ProfileData
{
	const char* Profilename;
	float milliSecondsTaken;

};
class Frame
{
	int FrameNum = 0;
	float frameTime;
	vector<ProfileData> Thisframe;
	void Calctotaltime();
};
class ProfilerSystem
{
	ProfilerSystem();
	~ProfilerSystem();
	vector<Frame> Profiler;
	void startframe();
	void storeProfiledata(const char* name ,float timetaken);
	void endFrame();
	static ProfilerSystem& Instance()
	{
		static ProfilerSystem INSTANCE;
		return INSTANCE;
	}

};
