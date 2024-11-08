#pragma once
#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>
#include "MyEventTypes.hpp"



using namespace std;


#include "MyEventTypes.hpp"

class Event
{
public:
	string name;
	Event(string Name)
	{
		name = Name;
	}

};

class I_EventHandeler
{
public:
	virtual void OnEvent(MyEventTypes eventType, Event* data) = 0;
};





class EventSystem
{
public:

	vector<I_EventHandeler*> EventListeners;//list of events
	vector<pair<MyEventTypes, Event*>> EventPool;
	void HandelEvents()
	{
		for (size_t j = 0; j < EventPool.size(); j++)
		{
			for (int i = 0; i < EventListeners.size(); i++)
			{
				EventListeners[i]->OnEvent(EventPool[j].first,
					EventPool[j].second);
			}
		}
	}
	void AddEvent(MyEventTypes eventType, Event* data)
	{
		EventPool.push_back(make_pair(eventType, data));
	}

	void AddListener(I_EventHandeler* listener)
	{
		EventListeners.push_back(listener);
	}
};
///h/ttps://www.geeksforgeeks.org/working-and-examples-of-bind-in-cpp-stl/