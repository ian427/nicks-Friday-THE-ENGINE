#include "Components.h"
#include "BitMaps.h"
#include "MyEventTypes.hpp"
#include "EventHandler.h"
#include "physics.h"

//base class in vector with virtual methods each child of base overloads that method
struct SDL_Renderer;

class BaseEntity
{
protected:
	
	 
	SDL_Renderer* m_Renderer;
public:
	Physics phi;//copy
	 float Radius;
	 Bitmap* Map;
	 Collider*  BoxCollider;
	 Transform transform;//26,27 getting this transforms data not flappys
	 Transform& GetTransform() { return transform; }
	 virtual void Draw()//genral class ?
	{
		Map->m_x = transform.GetPosition().x;
		Map->m_y = transform.GetPosition().y;
		Map->draw();
	}
	 
	 Collider* GetCollider()
	 {
		return BoxCollider;
	 }
	 float GetRadius()
	 {
		return Radius;
	 }

	 virtual void ApplyContinuousMoment() = 0;
	 ~BaseEntity()
	 {
		
		 Bitmap* Map = nullptr;
		 Collider* BoxCollider = nullptr;
		 SDL_Renderer* m_Renderer = nullptr;
		 
	 }

	
};

class Bird : public I_EventHandeler , public virtual BaseEntity
{
public:
	//collider 
	//	gravity
	//Hit Object
	//bitmap
	//phiysics check

	
	//anything that needs to move
	
	//Transform transform;
	//Transform Transform{ vec3{320.0f, 240.0f, 0.0f} };
	float Radius{ 10.0f };
	
	SDL_Renderer& m_Renderer;

	Bird(SDL_Renderer& renderer) : m_Renderer{renderer}
	{
		transform = vec3{ 320.0f, 240.0f, 0.0f };
		Map = new Bitmap(m_Renderer, "assets/Flappy.bmp", transform.GetPosition().x, transform.GetPosition().y);
		BoxCollider = new Collider(transform);
		
	}

	~Bird()
	{
		delete BoxCollider;  
		//delete Map;
	}
	
	void ApplyContinuousMoment()
	{
		phi.Move(transform, vec3(0, 1, 0));
	}
	

	void OnEvent(MyEventTypes eventType, Event* data)
	{
		switch (eventType)
		{
		case SPACE_PRESSED:
			phi.Move(transform, vec3(0, -2, 0));
			break;
		default:
			break;
		}
	}
	bool CollisionCheck( BaseEntity* CollidingAgainst)// needs to the the derived class
	{//calculates the position and hoe far apart so we can find where to check radii from 
		float Dx = transform.GetPosition().x - CollidingAgainst->GetTransform().GetPosition().x;
		float Dy = transform.GetPosition().y - CollidingAgainst->GetTransform().GetPosition().y;
		float D = (sqrt((Dx * Dx) + (Dy * Dy)));

		if ((D == Radius + CollidingAgainst->GetRadius()) || (D == Radius - CollidingAgainst->GetRadius()))//circle collision check
		{
			if (phi.AABBIntersection(BoxCollider, CollidingAgainst->GetCollider()))
			{
				return true;

			}

		}

	}
};
//?setBitmapWith input string implement if time
class Pipe : public virtual BaseEntity
{
	bool topPipe = true;
	bool inuse = false; //spawning
public:
	//bitmap
	//collider 

	//Collider* BoxCollider;
	float Radius;
	Transform Transform;
	SDL_Renderer* m_Renderer;
	Pipe(bool value) : topPipe(value)
	{
		BoxCollider = new Collider(Transform);
		if (topPipe)
		{
			Map = new Bitmap(m_Renderer, "assets/Pipes3Top.bmp", transform.GetPosition().x, transform.GetPosition().y);// loads top pipe png
		}
		else
		{
			Map = new Bitmap(m_Renderer, "assets/Pipes3Bottom.bmp", transform.GetPosition().x, transform.GetPosition().y);//loads bottom pipe png
		}

	}
	~Pipe()
	{

		SDL_Renderer* m_Renderer = nullptr;
	}
	void ApplyContinuousMoment()
	{
		phi.Move(transform, vec3(1, 0, 0));
	}
};
	


class Ground : public virtual BaseEntity
{
public:
	//bitmap
	//collider 
	
	//Collider* BoxCollider;
	float Radius;
	Transform Transform;
	SDL_Renderer* m_Renderer;
	Ground()
	{
		BoxCollider = new Collider(Transform);
		Map = new Bitmap(m_Renderer, "assets/Ground.bmp", transform.GetPosition().x, transform.GetPosition().y);
	}
	~Ground()
	{

		SDL_Renderer* m_Renderer = nullptr;
    }

	void ApplyContinuousMoment()
	{
	}
};
class UI : public virtual BaseEntity
{
public:
	//bitmap
	//collider 
	
	//Collider* BoxCollider;
	float Radius;
	Transform Transform;
	SDL_Renderer* m_Renderer;
	UI()
	{
		BoxCollider = new Collider(Transform);
		Map = new Bitmap(m_Renderer, "assets/UI.bmp", transform.GetPosition().x, transform.GetPosition().y);
	}
	~UI()
	{
		SDL_Renderer* m_Renderer = nullptr;
		
	}
	void ApplyContinuousMoment()
	{
	}
};
