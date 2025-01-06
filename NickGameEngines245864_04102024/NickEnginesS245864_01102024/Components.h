#pragma once
#include "Transform.hpp"
//#include "physics.h"


//give new box collider .... this is a factory method, look it up
class Commponent //should this be an interface
{
	virtual void Update() =0;
};


 class Collider : public Commponent
{
private:

public:
	vec3 TL = vec3(0, 0, 0);
	vec3 TR = vec3(1, 0, 0);
	vec3 BL = vec3(0, -1, 0);
	vec3 BR = vec3(1, -1, 0);
	float Width;
	float Height;
	Collider(const Transform&  t)
	{
		vec3 Pos = t.GetPosition();
		vec3 Scale = t.GetScale();

		TR = TR * Scale;
		TL = TL * Scale;
		BR = BR * Scale;
		BL = BL * Scale;

		TR = TR + Pos;
		TL = TL + Pos;
		BR = BR + Pos;
		BL = BL + Pos;
		Width = (TR.x - TL.x);
		Height = (TR.y - BR.y);
	}

		vec3 GetColliderPoints();

		void Update()
		{

		}
};