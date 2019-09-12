#include <iostream>  // remove me
using namespace std; // remove me

/*
COLORS!
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
    unsigned refcount = 0; // current reference count
    T *memPtr;             // pointer to allocated memory

    // Assign true if memPtr is pointing to array
    bool isArray;

    // Assign arraySize if memPtr is pointing to a an array
    unsigned arraySize;

    PtrDetails(T *memPtr_, int size) : memPtr(memPtr_), arraySize(size)
    {
        refcount++;
        if(arraySize>0)
            isArray = true;
    }

    // Copy Constructor
    PtrDetails(const PtrDetails &ob)
    {
        memPtr = ob.memPtr;
        refcount++;
        if(ob.arraySize>0)
            isArray = true;
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