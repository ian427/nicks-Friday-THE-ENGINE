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

	Collider* BoxCollider;
	Bitmap* Map;
	Transform flappy_Transform;
	float Radius;
	
	

	Bird()
	{
		
		BoxCollider = new Collider(flappy_Transform);
		//Map = new Bitmap();
		
	}
	~Bird()
	{
		delete BoxCollider;  
		//delete Map;
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
public:
	//bitmap
	//collider 
	Bitmap* Map;
	Collider* BoxCollider;
	float Radius;
	Transform Transform;
};
class Ground 
{
public:
	//bitmap
	//collider 
	Bitmap* Map;
	Collider* BoxCollider;
	float Radius;
	Transform Transform;
};
class UI 
{
public:
	//bitmap
	//collider 
	Bitmap* Map;
	Collider* BoxCollider;
	float Radius;
	Transform Transform;
};
