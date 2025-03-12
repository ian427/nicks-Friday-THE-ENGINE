#include "Saveing.h"
#include "Entity2.hpp"


void saveObject(const BaseEntity& obj, const std::string& filename, const SDL_Renderer* m_Renderer, Physics phi, float Radius, Bitmap* Map, Collider* BoxCollider, Transform transform, int ID, std::string ObjectName)
{
    std::ofstream file(filename, std::ios::app); // Append mode
    if (file.is_open()) {
        file << obj.m_Renderer << " " << obj.phi << " " << obj.Radius << " " << obj.state << obj.Map << " " << obj.BoxCollider << " " << obj.transform << " " << obj.ID << " " << obj.ObjectName << " " << "\n";
        file.close();
        std::cout << "Object saved to " << filename << std::endl;
    }
    else {
        std::cerr << "Error: Could not open file for writing!\n";
    }
}


std::vector<BaseEntity> loadObjects(const std::string& filename) {
    std::vector<BaseEntity> objects;
    std::ifstream file(filename);

    if (file.is_open()) {
        Physics phi;//copy
        float Radius;
        Bitmap* Map;
        Collider* BoxCollider;
        Transform transform;//26,27 getting this transforms data not flappys
        int ID;
        std::string ObjectName;

        while (file >> phi >> Radius >> Map >> BoxCollider>> transform>> ID>> ObjectName) {
            objects.push_back(BaseEntity*(phi, Radius, Map, BoxCollider, transform, ID, ObjectName));
        }

        file.close();
    } else {
        std::cerr << "Error: Could not open file for reading!\n";
    }

    return objects;
}
