#include <iostream>
#include <cstring> 
using namespace std;

template<typename T>
class Container {
private:
    T* elements;   
    int capacity;  
    int size;      

public:

    Container(int initialCapacity = 10) : capacity(initialCapacity), size(0) {
        elements = new T[capacity]; 
    }


    ~Container() {
        delete[] elements; 
    }

    void addElement(const T& element) {
        if (size >= capacity) {

            int newCapacity = capacity * 2; 
            T* newElements = new T[newCapacity];


            for (int i = 0; i < size; ++i) {
                newElements[i] = elements[i];
            }


            delete[] elements;


            capacity = newCapacity;
            elements = newElements;
        }

        elements[size++] = element;
    }

    void displayElements() const {
        for (int i = 0; i < size; ++i) {
            cout << elements[i] << " ";
        }
        cout << endl;
    }
};

// Main program to test the Container class
int main() {
    // Testing with integer elements
    Container<int> intContainer(5); // Initialize container with a capacity of 5
    intContainer.addElement(2);
    intContainer.addElement(4);
    intContainer.addElement(6);
    intContainer.addElement(8);

    cout << "Integer Container elements: ";
    intContainer.displayElements(); // Display all integer elements

    // Testing with string elements
    Container<string> stringContainer(3); // Initialize container with a capacity of 3
    stringContainer.addElement("Hello");
    stringContainer.addElement("World");

    cout << "String Container elements: ";
    stringContainer.displayElements(); // Display all string elements

    return 0;
}

