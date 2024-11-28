#include <iostream>
#include <vector>

// Step 1: Define the base class
class Base {
public:
    virtual void display() const { // Virtual function for polymorphism
        std::cout << "Base class" << std::endl;
    }

    virtual ~Base() = default; // Virtual destructor for proper cleanup
};

// Step 2: Define derived classes
class Derived1 : public Base {
public:
    void display() const override {
        std::cout << "Derived1 class" << std::endl;
    }
};

class Derived2 : public Base {
public:
    void display() const override {
        std::cout << "Derived2 class" << std::endl;
    }
};

// Step 3: Main function where we create objects and store them
int main() {
    // Create objects of specific derived classes
    Derived1 obj1;
    Derived1 obj2;
    Derived2 obj3;

    // Create a vector of Base pointers to store the objects
    std::vector<Base*> objects;

    // Add addresses of obj1, obj2, obj3 to the vector
    objects.push_back(&obj1);
    objects.push_back(&obj2);
    objects.push_back(&obj3);

    // Access the objects through the base class pointers
    for (Base* obj : objects) {
        obj->display(); // Polymorphic call
    }

    // No need to delete the objects since they are not dynamically allocated

    return 0;
}


for (int i = 0; i < Entitys.size(); i++) {
    // Call the virtual function to access the Map (polymorphic behavior)
    Bitmap* map = Entitys[i]->getMap();  // This works for any derived class

    if (map != nullptr) {
        float A = map->m_x;  // Access m_x of Map
        float B = map->m_y;  // Access m_y of Map
        Entitys[i]->Radius = (sqrt((A * A) + (B * B))) / 2;  // Calculate the radius
        std::cout << "Radius: " << Entitys[i]->Radius << std::endl;
    }
}