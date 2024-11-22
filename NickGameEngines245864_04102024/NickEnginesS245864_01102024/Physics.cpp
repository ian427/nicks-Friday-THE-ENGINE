#include "Physics.h"
#include "Debug.h" //|6|

void Physics::ApplyForces(Transform transform)
{
    vec3 currentForce = vec3(0);

    currentForce = AccumulateForces(forces);

    //auto it;//purpose

    for (auto it = impulses.begin(); it != impulses.end(); it++)//modern for loop
    {
        currentForce += *it;
    }
    impulses.clear();
    
    //apply currentFocre to transform
    vec3 Pos = transform.GetPosition();
    Pos + currentForce;
}

void Physics::Gravity(Transform transform)
{
    vec3 Pos = transform.GetPosition();
    Pos + gravity;
     
}

vec3 Physics::AccumulateForces(const std::vector<vec3> foreces)
{
    vec3 Force = vec3(0);

    for (int i = 0; i < foreces.size(); i++)
    {
        Force += forces[i];
    }

    

	return Force;
}

vec3 Collider::GetColliderPoints()
{
    return TL;
    return TR;
    return BL;
    return BR;
}

bool Physics::AABBIntersection(Collider& Collider1 , Collider& Collider2)
{
    if (rectA.x < rectB.x + rectB.width &&
        rectA.x + rectA.width > rectB.x &&
        rectA.y < rectB.y + rectB.height &&
        rectA.height + rectA.y > rectB.y)
    {
        return true;
    }
    else
    {
        return false;
    }

}

void Physics::UpdatePhysics()
{
}

void  Physics::Move(Transform transform, vec3 movement)
{
    //set impulse apply movment
    
    impulses.push_back(movement);
    void ApplyForces(Transform transform);
}

void Physics::CheckCollisions(float radiusobj, vector <Bitmap>Entitys)
{
    AABBIntersection(Collider & Collider1, Collider & Collider2);
}
