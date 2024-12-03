#include <iostream>

class MyClass {
private:
    bool flag;

public:
    // Constructor to initialize flag
    MyClass(bool value) : flag(value) {}

    // Getter to check the value of flag
    bool getFlag() const {
        return flag;
    }
};

int main() {
    MyClass objTrue(true);  // Initializes flag as true
    MyClass objFalse(false); // Initializes flag as false

    std::cout << "Object 1 flag: " << objTrue.getFlag() << std::endl;
    std::cout << "Object 2 flag: " << objFalse.getFlag() << std::endl;

    return 0;
}
