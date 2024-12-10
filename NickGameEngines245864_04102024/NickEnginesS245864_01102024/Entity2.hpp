#include "Components.h"
#include "BitMaps.h"
#include "MyEventTypes.hpp"
#include "EventHandler.h"
#include "physics.h"


struct SDL_Renderer;

class BaseEntity
{
private:
	Collider* collider;
	Bitmap* Map;
	Transform _transform;
	float Radius;
	SDL_Renderer* m_Renderer;
public:
	Transform& GetTransform() { return _transform; }
void Draw()
	{
		Map->m_x = _transform.GetPosition().x;
		Map->m_y = _transform.GetPosition().y;
		Map->draw();
	}
Collider* GetCollider()
{
	return collider;
}
float GetRadius()
{
	return Radius;
}


	
};

class Bird : public I_EventHandeler , public BaseEntity
{
public:
	//collider 
	//	gravity
	//Hit Object
	//bitmap
	//phiysics check

	Collider* BoxCollider;
	Physics phi;//anything that needs to move
	Bitmap* Map;
	Transform Transform{ vec3{320.0f, 240.0f, 0.0f} };
	float Radius{ 10.0f };
	SDL_Renderer* m_Renderer;
	

	Bird(SDL_Renderer* renderer) : m_Renderer{renderer}, BoxCollider{new Collider(Transform)}
	{
		Map = new Bitmap(m_Renderer, "assets/Flappy.bmp", 320.0f, 240.0f);
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
			std::cout << "Bird on event " << data->name << '\n';
			break;
		case APPLY_GRAVITY:
			
			phi.Gravity(Transform);
			break;
		default:
			break;
		}
	}
	bool CollisionCheck( BaseEntity* CollidingAgainst)// needs to the the derived class
	{//calculates the position and hoe far apart so we can find where to check radii from 
		float Dx = Transform.GetPosition().x - CollidingAgainst->GetTransform().GetPosition().x;
		float Dy = Transform.GetPosition().y - CollidingAgainst->GetTransform().GetPosition().y;
		float D = (sqrt((Dx * Dx) + (Dy * Dy)));

		if ((D == Radius + CollidingAgainst->GetRadius()) || (D == Radius - CollidingAgainst->GetRadius()))//circle collision check
		{
			if (phi.AABBIntersection(BoxCollider, CollidingAgainst->GetCollider()))
			{


			}

		}

	}
};

class Pipe : public BaseEntity

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
