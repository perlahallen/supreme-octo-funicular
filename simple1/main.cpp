#include <iostream>
using namespace std;

class Animal {
public:
    virtual void speak() {
        cout << "Animal makes a sound" << endl;
    }

    virtual ~Animal() {
        cout << "Animal Destructor" << endl;
    }
};

class Dog : public Animal {
public:
    void speak() override {
        cout << "Dog barks" << endl;
    }

    ~Dog() override {
        cout << "Dog Destructor" << endl;
    }
};

class Bird : public Animal {
public:
    void speak() override {
        cout << "Bird chirps" << endl;
    }

    ~Bird() override {
        cout << "Bird Destructor" << endl;
    }
};

int main() {
    Animal* a1 = new Dog();
    Animal* a2 = new Bird();

    a1->speak();
    a2->speak();

    delete a1;
    delete a2;

    return 0;
}
