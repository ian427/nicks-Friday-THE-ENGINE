#include "Physics.h"
#include "Debug.h" //|6|

void Physics::ApplyForces(Transform& transform)
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
    transform.SetPosition(Pos + currentForce);
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

bool Physics::AABBIntersection(Collider* Collider1 , Collider* Collider2)
{
    if ((Collider1->TL.x>=Collider2->TL.x && Collider1->TR.x >=Collider2->TL.x) ||//check width
       (Collider1->TR.x >= Collider2->TR.x && Collider1->TL.x >= Collider2->TR.x) ||
       (Collider1->BL.x >= Collider2->BL.x && Collider1->BR.x >= Collider2->BL.x) ||
       (Collider1->BR.x >= Collider2->BR.x && Collider1->BL.x >= Collider2->BR.x) ||

        (Collider1->TL.y >= Collider2->TL.y && Collider1->TR.y >= Collider2->TL.y) ||//check height
        (Collider1->TR.y >= Collider2->TR.y && Collider1->TL.y >= Collider2->TR.y) ||
        (Collider1->BL.y >= Collider2->BL.y && Collider1->BR.y >= Collider2->BL.y) ||/////////////////////////exception
        (Collider1->BR.y >= Collider2->BR.y && Collider1->BL.y >= Collider2->BR.y))
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

void  Physics::Move(Transform& transform, vec3 movement)
{
    //set impulse apply movment
    
    impulses.push_back(movement);
    ApplyForces(transform);
}
/*
void Physics::CollisionCheck(BaseEntity Object, BaseEntity CollidingAgainst)
{


}*/




