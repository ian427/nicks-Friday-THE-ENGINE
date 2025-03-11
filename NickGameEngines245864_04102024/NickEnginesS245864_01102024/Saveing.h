#include <iostream>
#include <fstream>
#include "Entity2.hpp"
#include <vector>
class BasEntity;

void saveObject(const BasEntity& obj, const std::string& filename, const SDL_Renderer* m_Renderer, Physics phi, float Radius, Bitmap* Map, Collider* BoxCollider, Transform transform, int ID, std::string ObjectName);
std::vector<BasEntity> loadObjects(const std::string& filename);