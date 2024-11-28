#include "Components.h"
#include "BitMaps.h"
#include "MyEventTypes.hpp"
#include "EventHandler.h"

class Base {
public:
	virtual void display() const { // Virtual function for polymorphism
		std::cout << "Base class" << std::endl;
	}

	

	virtual ~Base() = default; // Virtual destructor for proper cleanup
};

class Bird : public I_EventHandeler , public Base
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

class Pipe: public Base
{
public:
	//bitmap
	//collider 
	Bitmap* Map;
	Collider* BoxCollider;
	float Radius;
};
class ground : public Base
{
public:
	//bitmap
	//collider 
	Bitmap* Map;
	Collider* BoxCollider;
	float Radius;
};
class UI : public Base
{
public:
	//bitmap
	//collider 
	Bitmap* Map;
	Collider* BoxCollider;
	float Radius;
};