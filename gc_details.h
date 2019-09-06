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
    unsigned refcount = 0; // current reference count
    T *memPtr;             // pointer to allocated memory

    // true if pointing to array
    bool isArray;

    // If memPtr is pointing to an allocated, size of array
    unsigned arraySize;

    // PtrDetails(T *memPtr_) : memPtr(memPtr_)
    PtrDetails(T *memPtr_) : memPtr(memPtr_)
    {
        cout << "\033[36mConstructing PtrDetails memPtr=" << memPtr_ << "\033[0m\n";
        refcount++;
    }

    // Copy Constructor
    PtrDetails(const PtrDetails &ob)
    {
        cout << "\033[36mCopying PtrDetails memPtr" << ob.memPtr << "\033[0m\n";
        memPtr = ob.memPtr;
        refcount++;
    }

    // PtrDeatils destructor
    // or del memPtr
    // or del [] memPtr (no need to iterate through ptnr)
    // we don't care about refcount here b/c that is the job of
    // the GC -- keeping track of refcount
    ~PtrDetails()
    {
        // cout << "\033[44m==============~PtrDetails()==============\033[0m\n";
        // cout << "Trying to delete " << memPtr << endl;
        // cout << "refcount=" << refcount << endl;
        // if (isArray)
        //     delete[] memPtr;
        // else
        //     delete memPtr;
        // cout << "Deleted memPtr=" << memPtr << endl;
        // cout << "\033[44m==============~PtrDetails()==============END\033[0m\n";
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