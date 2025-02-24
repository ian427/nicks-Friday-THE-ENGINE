#include "Components.h"
#include "BitMaps.h"
#include "MyEventTypes.hpp"
#include "EventHandler.h"
#include "physics.h"

//base class in vector with virtual methods each child of base overloads that method
struct SDL_Renderer;
class ITreeNode
{
public:
	ITreeNode* Parent;
	std::vector<ITreeNode*>Children;

	void addToChildren(ITreeNode* newChild)
	{
		Children.push_back(newChild);
	}
};


class BaseEntity: public ITreeNode
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
	 bool IsSelected = false;

	 

	 int ID;
	 std::string ObjectName;

	 BaseEntity(SDL_Renderer* renderer, std::string fileName, int xpos, int ypos, bool useTransparancy)
	 {
		 m_Renderer = renderer;
		 ObjectName = "Object name to be changed";

		 transform.SetPosition(vec3(xpos, ypos, 0));

		 Map = new Bitmap(m_Renderer, fileName, xpos, ypos, useTransparancy);
		 BoxCollider = new Collider(transform, Map->GetWidth(), Map->GetHeight() );

	 }


	 

	 virtual void Draw()//genral class ?
	{
		
		BoxCollider->Update(transform);
		Map->draw(transform.GetPosition().x, transform.GetPosition().y);
		BoxCollider->DrawDebug(transform, m_Renderer);
	}

	
	 
	 Collider* GetCollider()
	 {
		return BoxCollider;
	 }
	 float GetRadius()
	 {
		return Radius;
	 }

	 virtual void ApplyContinuousMoment() {};
	 ~BaseEntity()
	 {
		
		 Bitmap* Map = nullptr;
		 Collider* BoxCollider = nullptr;
		 SDL_Renderer* m_Renderer = nullptr;
		 
	 }
	
 protected:
	 //BaseEntity()
	 //{
		// ObjectName = "Object name to be changed";

		// //Map->m_x = transform.GetPosition().x;
		// //Map->m_y = transform.GetPosition().y;
	 //}
	
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
	
	

	Bird(SDL_Renderer* renderer, int X, int Y) : BaseEntity(renderer, "assets/Flappy.bmp", X, Y, true)
	{

		//m_Renderer = renderer;
		
		
		
	
	}

	~Bird()
	{
		delete BoxCollider;  
		//delete Map;
	}
	
	void ApplyContinuousMoment()
	{
		phi.Move(transform, vec3(0, 2, 0));
	}
	

	void OnEvent(MyEventTypes eventType, Event* data)
	{
		switch (eventType)
		{
		case SPACE_PRESSED:
			phi.Move(transform, vec3(0, -20, 0));
			break;
		default:
			break;
		}
	}
	bool CollisionCheck( BaseEntity* CollidingAgainst)// needs to the the derived class
	{//calculates the position and hoe far apart so we can find where to check radii from 
		//float Dx = transform.GetPosition().x - CollidingAgainst->GetTransform().GetPosition().x;
		//float Dy = transform.GetPosition().y - CollidingAgainst->GetTransform().GetPosition().y;
		//float D = (sqrt((Dx * Dx) + (Dy * Dy)));

		//if ((D == Radius + CollidingAgainst->GetRadius()) || (D == Radius - CollidingAgainst->GetRadius()))//circle collision check
	
		//if(D <= Radius + CollidingAgainst->GetRadius())
		//{
				bool Result = false;
			if (phi.AABBIntersection(BoxCollider, CollidingAgainst->GetCollider()))
			{
				
				Result = true;
			}

		//}
		return Result;

	}
};
//?setBitmapWith input string implement if time
class Pipe : public virtual BaseEntity
{
	
	bool inuse = false; //spawning
public:
	bool topPipe = true;
	//bitmap
	//collider 

	//Collider* BoxCollider;
	
	
	Pipe(bool value,SDL_Renderer* renderer, int X, int Y) : BaseEntity(renderer, "assets/Pipes3Bottom.bmp", X, Y, true)
	{
		delete Map;
		Map = nullptr;
		topPipe = value;
		if (topPipe)
		{
			//Map = new Bitmap(m_Renderer, "assets/Pipes3Top.bmp", transform.GetPosition().x, transform.GetPosition().y);// loads top pipe png
			Map = new Bitmap(m_Renderer, "assets/Pipes3Bottom.bmp", transform.GetPosition().x, transform.GetPosition().y);// loads top pipe png
		}
		else
		{
			Map = new Bitmap(m_Renderer, "assets/Pipes3Top.bmp", transform.GetPosition().x, transform.GetPosition().y);//loads bottom pipe png
		}

	}
	~Pipe()
	{

		SDL_Renderer* m_Renderer = nullptr;
	}
	void ApplyContinuousMoment()
	{
		phi.Move(transform, vec3(-3, 0, 0));
	}
};
	


class Ground : public virtual BaseEntity
{
	public:
	//bitmap
	//collider 
	
	//Collider* BoxCollider;
	
	
	Ground(SDL_Renderer* renderer, int X, int Y) : BaseEntity(renderer, "assets/Ground.bmp", X, Y, true)
	{
		
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
	

	UI(SDL_Renderer* renderer, int X, int Y) : BaseEntity(renderer, "assets/UI.bmp", X, Y, true)
	{
	}
	~UI()
	{
		SDL_Renderer* m_Renderer = nullptr;
		
	}
	void ApplyContinuousMoment()
	{
	}
};
class Trigger :public virtual BaseEntity
{
	
public:
	bool isTrigger = true;
	//bitmap
	//collider 

	//Collider* BoxCollider;
	
	
	Trigger( SDL_Renderer* renderer, int X, int Y) : BaseEntity(renderer, "assets/Trigger.bmp", X, Y, true)
	{
		
	}
	~Trigger()
	{

		SDL_Renderer* m_Renderer = nullptr;
	}
	void ApplyContinuousMoment()
	{
		phi.Move(transform, vec3(-3, 0, 0));
	}

};

class Seed :public virtual BaseEntity
{

public:
	
	Seed(SDL_Renderer* renderer, int X, int Y) : BaseEntity(renderer, "assets/Seed.bmp", X, Y, true)
	{
	}
	~Seed()
	{
	}
	void ApplyContinuousMoment()
	{
		phi.Move(transform, vec3(-3, 0, 0));
	}

};