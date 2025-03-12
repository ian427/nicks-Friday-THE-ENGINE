#include <iostream>
#include <fstream>
//#include "Entity2.hpp"
#include <vector>

#include <SDL.h>
class BaseEntity;
class Bitmap;
class Physics;
class Collider;
class Transform;

void saveObject(const BaseEntity& obj, const std::string& filename, const SDL_Renderer* m_Renderer, Physics phi, float Radius, Bitmap* Map,
	Collider* BoxCollider, Transform transform, int ID, std::string ObjectName);
std::vector<BaseEntity> loadObjects(const std::string& filename);