#include "Components.h"
#include "MyEventTypes.hpp"
#include "EventHandler.h"


class Bird : public I_EventHandeler
{
public:
	//collider 
	//	gravity
	//Hit Object
	//bitmap
	Bird()
	{

	}
	~Bird()
	{

	}

	void OnEvent(MyEventTypes eventType, Event* data)
	{
		switch (eventType)
		{
		case TEST_EVENT:
			cout << "Birst on event "<< data->name << endl;
			break;
		default:
			break;
		}
	}

};

class Pipe
{
	
	//bitmap
	//collider 
};
class ground
{
	//bitmap
	//collider 
};
class UI
{
	//bitmap
	//collider 
};