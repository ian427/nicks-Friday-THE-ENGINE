#include "Components.h"
#include "BitMaps.h"
#include "MyEventTypes.hpp"
#include "EventHandler.h"
 #include "physics.h"


class SDL_Renderer;


class Bird : public I_EventHandeler 
{
public:
	//collider 
	//	gravity
	//Hit Object
	//bitmap
	//phiysics check

	Collider* BoxCollider;
	Physics phi;
	Bitmap* Map;
	Transform flappy_Transform;
	float Radius;
	SDL_Renderer* m_Renderer;
	

	Bird()
	{
		
		BoxCollider = new Collider(flappy_Transform);
		Map = new Bitmap(m_Renderer, "assets/monster.bmp", 100, 100);
		
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
			
			phi.Gravity(flappy_Transform);
			break;
		default:
			break;
		}
	}

};

class Pipe
{
	bool topPipe  = true;
public:
	//bitmap
	//collider 
	Bitmap* Map;
	Collider* BoxCollider;
	float Radius;
	Transform Transform;
	SDL_Renderer* m_Renderer;
	Pipe(bool value) : topPipe(value) 
	{
		BoxCollider = new Collider(Transform);
		if (topPipe)
		{
			Map = new Bitmap(m_Renderer, "assets/Pipes3Top.png", 100, 1000);// loads top pipe png
		}
		else
		{
			Map = new Bitmap(m_Renderer, "assets/Pipes3Bottom.png", 100, 1000);//loads bottom pipe png
		}
		
	}
	~Pipe()
	{


	}
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
	SDL_Renderer* m_Renderer;
	Ground()
	{
		BoxCollider = new Collider(Transform);
		Map = new Bitmap(m_Renderer, "assets/Ground.png", 80, 640);
	}
	~Ground()
	{


    }
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
	SDL_Renderer* m_Renderer;
	UI()
	{
		BoxCollider = new Collider(Transform);
		Map = new Bitmap(m_Renderer, "assets/UI.png", 100, 100);
	}
	~UI()
	{

	}
};
