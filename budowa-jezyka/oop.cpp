#include <iostream>
#include <string>
#include <vector>

// 1. Encapsulation: Bundling data (variables) and methods that operate on the data into a single unit (class).
class Animal {
private:
    std::string name;  // private data member

public:
    // Constructor (automatically called when an object is created)
    Animal(std::string n) : name(n) {}
    // Destructor (automatically called when an object is destroyed)
    ~Animal() {
        std::cout << "Animal destructor called for " << name << std::endl;
    }
    // Public method to set the name of the animal (encapsulation).
    void setName(const std::string& animalName) {
        name = animalName;
    }

    // Public method to get the name of the animal.
    std::string getName() const {
        return name;
    }

    // A virtual function (to demonstrate polymorphism).
    virtual void speak() const {
        std::cout << "The animal makes a sound." << std::endl;
    }

    // 2. Copy Constructor (Deep Copy Example)
    Animal(const Animal& other) : name(other.name) {
        std::cout << "Copy constructor called for " << name << std::endl;
    }

    // 3. Copy Assignment Operator
    Animal& operator=(const Animal& other) {
        if (this != &other) {  // Prevent self-assignment
            name = other.name;
            std::cout << "Copy assignment operator called for " << name << std::endl;
        }
        return *this;
    }

    // 4. Move Constructor (R-value references)
    Animal(Animal&& other) noexcept : name(std::move(other.name)) {
        std::cout << "Move constructor called for " << name << std::endl;
    }

    // 5. Move Assignment Operator
    Animal& operator=(Animal&& other) noexcept {
        if (this != &other) {
            name = std::move(other.name);
            std::cout << "Move assignment operator called for " << name << std::endl;
        }
        return *this;
    }
};

// 2. Inheritance: Deriving a new class from an existing class.
class Dog : public Animal {
public:
    // Override the speak method (polymorphism).
    void speak() const override {
        std::cout << "The dog barks." << std::endl;
    }

    // 6. Constructor with Initialization List
    Dog(std::string n) : Animal(n) {
        std::cout << "Dog constructor called for " << n << std::endl;
    }
};

// 3. Polymorphism: Ability of different classes to be treated as instances of the same class through inheritance.
void animalSpeak(const Animal& animal) {
    animal.speak();  // This will call the appropriate method based on the object's actual type.
}

// 4. Union: Demonstrating union to store different data types in the same memory location
union AnimalData {
    int age;
    float weight;
    char gender;
};

// 5. Struct: Demonstrating struct to hold animal data (different from class because it's public by default)
struct AnimalInfo {
    std::string name;
    AnimalData data;  // Union within a struct

    // Display the animal's info
    void displayInfo() const {
        std::cout << "Name: " << name << ", Age: " << data.age << " years" << std::endl;
    }
};

// 6. Static member example outside of main
class AnimalWithStatic {
public:
    static int count;  // Static variable to hold count of AnimalWithStatic objects

    static void displayCount() {
        std::cout << "Count of AnimalWithStatic objects: " << count << std::endl;
    }
};

// Initialize static variable
int AnimalWithStatic::count = 0;

int main() {
    // 7. Abstraction: Hiding complex implementation details and exposing only essential features.
    Animal animal("Generic Animal");
    std::cout << "Animal's Name: " << animal.getName() << std::endl;
    animal.speak();  // Calls the base class version of speak()

    Dog dog("Rex");
    std::cout << "Dog's Name: " << dog.getName() << std::endl;
    dog.speak();  // Calls the derived class version of speak()

    // Demonstrating polymorphism by passing the derived class object to a function expecting the base class.
    animalSpeak(dog);

    // 8. Using Union to store animal's age, weight, or gender
    AnimalData data;
    data.age = 5;  // Only one of these can be used at a time
    std::cout << "Animal's age (from union): " << data.age << " years" << std::endl;

    // 9. Using Struct to store animal's information
    AnimalInfo dogInfo;
    dogInfo.name = "Rex";
    dogInfo.data.age = 5;
    dogInfo.displayInfo();  // Display animal info using struct

    // 10. Creating Objects on the Stack and Heap:
    // Creating an object on the stack:
    Animal stackAnimal("Stack Animal");
    std::cout << "Stack Animal's Name: " << stackAnimal.getName() << std::endl;
    stackAnimal.speak();  // Directly calling the method using dot operator

    // Creating an object on the heap:
    Animal* heapAnimal = new Animal("Heap Animal");
    std::cout << "Heap Animal's Name: " << heapAnimal->getName() << std::endl;
    heapAnimal->speak();  // Calling the method using the arrow (->) operator

    // Clean up dynamically allocated memory
    delete heapAnimal;

    // 11. Accessing Members Using `.` and `->`:
    // The dot operator is used to access members of an object (when it's on the stack or a direct object reference).
    Dog myDog("Buddy");
    std::cout << "My Dog's Name: " << myDog.getName() << std::endl;
    myDog.speak();  // Accessing members using dot operator

    // The arrow operator (->) is used when working with pointers to access members of an object.
    Dog* dogPtr = new Dog("Max");
    dogPtr->setName("Maximus");
    std::cout << "Pointer Dog's Name: " << dogPtr->getName() << std::endl;
    dogPtr->speak();  // Accessing members using arrow operator

    // Clean up dynamically allocated memory for the pointer object
    delete dogPtr;

    // 12. Using the Scope Resolution Operator `::`:
    // The `::` operator is used to access types or members that are nested within a class, namespace, or template.
    // Example: Accessing nested types like `iterator` in a container:

    std::cout << "Using :: to access nested types:" << std::endl;
    std::vector<int>::iterator it;  // Using `::` to access the `iterator` type of `std::vector<int>`
    std::cout << "Iterator type for std::vector<int> is: " << typeid(it).name() << std::endl;

    // The `::` operator can also be used to access static members or nested classes:
    // For example, accessing static variable of AnimalWithStatic class:
    AnimalWithStatic::count = 10;  // Accessing static variable using `::`
    AnimalWithStatic::displayCount();  // Calling static method using `::`

    // 13. Demonstrating Copy Constructor:
    Animal animal2 = animal;  // Calls copy constructor
    std::cout << "Copied animal's name: " << animal2.getName() << std::endl;

    // 14. Demonstrating Move Constructor:
    Animal movedAnimal = std::move(animal);  // Calls move constructor
    std::cout << "Moved animal's name: " << movedAnimal.getName() << std::endl;

    // 15. Demonstrating Copy Assignment:
    Animal anotherAnimal("Another Animal");
    anotherAnimal = animal2;  // Calls copy assignment operator

    // 16. Demonstrating Move Assignment:
    Animal movedAssignmentAnimal("Old Animal");
    movedAssignmentAnimal = std::move(movedAnimal);  // Calls move assignment operator

    return 0;
}
