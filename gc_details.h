#include <iostream>  // remove me
using namespace std; // remove me

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

    PtrDetails(T *memPtr_)
    {
        // TODO: Implement PtrDetails
        // Pointer Project LAB

        // Check if we are creating another reference to an allocated memory
        // cout << "memPtr=" << memPtr->addr << endl;
        cout << "memPtr=" << memPtr_ << endl;
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