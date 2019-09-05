#include <iostream>  // remove me
using namespace std; // remove me

/*
         foreground background
black        30         40
red          31         41
green        32         42
yellow       33         43
blue         34         44
magenta      35         45
cyan         36         46
white        37         47
*/

// This class defines an element that is stored
// in the garbage collection information list.
template <class T>
class PtrDetails
{
public:
    unsigned refcount; // current reference count
    T *memPtr;         // pointer to allocated memory

    // true if pointing to array
    bool isArray;

    // If memPtr is pointing to an allocated, size of array
    unsigned arraySize;

    // PtrDetails(T *memPtr_) : memPtr(memPtr_)
    PtrDetails(T *memPtr_)
    {
        // TODO: Implement PtrDetails
        // Pointer Project LAB
        cout << "\033[36mConstructing PtrDetails memPtr=" << memPtr_ << "\033[0m\n";
    }
};

// Overloading operator== allows two class objects to be compared.
// This is needed by the STL list class.
template <class T>
bool operator==(const PtrDetails<T> &ob1,
                const PtrDetails<T> &ob2)
{
    return (ob1.memPtr == ob2.memPtr);
}