#include "Components.h"
#include "BitMaps.h"
#include "MyEventTypes.hpp"
#include "EventHandler.h"


class Bird : public I_EventHandeler
{
public:
	//collider 
	//	gravity
	//Hit Object
	//bitmap
	//phiysics check

	Collider* FlappysBoxCollider;
	Bitmap* Map;
	Transform flappy_Transform;
	float Radius;
	
	Bird()
	{
		
		FlappysBoxCollider = new Collider(flappy_Transform);
		
	}
	~Bird()
	{

	}
	
	void OnEvent(MyEventTypes eventType, Event* data)
	{
		switch (eventType)
		{
		case TEST_EVENT:
			cout << "Bird on event "<< data->name << endl;
			break;
		case APPLY_GRAVITY:
			
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
	Bitmap* Map;
	float Radius;
};
class ground
{
	//bitmap
	//collider 
	Bitmap* Map;
	float Radius;
};
class UI
{
	//bitmap
	//collider 
	Bitmap* Map;
	float Radius;
};