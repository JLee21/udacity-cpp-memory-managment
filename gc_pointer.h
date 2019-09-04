#include <iostream>
#include <list>
#include <typeinfo>
#include <cstdlib>
#include "gc_details.h"
#include "gc_iterator.h"

/*
    Pointer implements a pointer type that uses
    garbage collection to release unused memory.
    A Pointer must only be used to point to memory
    that was dynamically allocated using new.
    When used to refer to an allocated array,
    specify the array size.
*/
template <class T, int size = 0>
class Pointer
{
private:
    // refContainer maintains the garbage collection list.
    // static that all Pointer objects will reference the same exact instance
    // of refContainer.
    static std::list<PtrDetails<T>> refContainer;

    // addr points to the allocated memory to which
    // this Pointer pointer currently points.
    T *addr;

    // true if pointing to array
    bool isArray;

    // size of the array, if we are pointing to an array
    unsigned arraySize;

    // true when first Pointer is created
    // *** why do we need this
    static bool first;

    // Return an iterator to PtrDetails in refContainer.
    // *** What does this mean??
    // NOTE
    // "typename" is used to tell the class that "std::list<PtrDetails<T>>::iterator"
    // is a type and not some static member of "class" "std::list<PtrDetails<T>>"
    typename std::list<PtrDetails<T>>::iterator findPtrInfo(T *ptr);

public:
    // Define an iterator type for Pointer<T>.
    typedef Iter<T> GCiterator;

    // Empty constructor
    // NOTE: templates aren't able to have prototypes with default arguments
    // this is why constructor is designed like this:
    Pointer() { Pointer(NULL); }
    Pointer(T *);

    // Copy constructor.
    Pointer(const Pointer &);

    // Destructor for Pointer.
    ~Pointer();

    // Collect garbage. Returns true if at least
    // one object was freed.
    static bool collect();

    // Overload assignment of pointer to Pointer.
    T *operator=(T *t);

    // Overload assignment of Pointer to Pointer.
    Pointer &operator=(Pointer &rv);

    // Return a reference to the object pointed
    // to by this Pointer.
    // *** Does that then equate to --> T &fooref = *addr;
    // *** Where the value at address "addr" is passed by reference to fooref?
    T &operator*() { return *addr; }

    // Return the address being pointed to.
    T *operator->() { return addr; }

    // Return a reference to the object at the
    // index specified by i.
    T &operator[](int i) { return addr[i]; }

    // Conversion function to T *.
    operator T *() { return addr; }

    // Return an Iter to the start of the allocated memory.
    Iter<T> begin()
    {
        int _size;
        if (isArray)
            _size = arraySize;
        else
            _size = 1;
        return Iter<T>(addr, addr, addr + _size);
    }
    // Return an Iter to one past the end of an allocated array.
    Iter<T> end()
    {
        int _size;
        if (isArray)
            _size = arraySize;
        else
            _size = 1;
        return Iter<T>(addr + _size, addr, addr + _size);
    }

    // Return the size of refContainer for this type of Pointer.
    static int refContainerSize() { return refContainer.size(); }

    // A utility function that displays refContainer.
    static void showlist();

    // Clear refContainer when program exits.
    static void shutdown();
};

// STATIC INITIALIZATION
// Creates storage for the static variables
template <class T, int size>
std::list<PtrDetails<T>> Pointer<T, size>::refContainer;

template <class T, int size>
bool Pointer<T, size>::first = true;

// Constructor for both initialized and uninitialized objects.
template <class T, int size>
Pointer<T, size>::Pointer(T *t)
{
    // Register shutdown() as an exit function.
    if (first)
        atexit(shutdown);
    first = false;

    // TODO: Implement Pointer constructor
    // Lab: Smart Pointer Project Lab

    if (size)
        arraySize = size;
    isArray = true;

    addr = t;

    // first, try to find if we are already using "addr"
    typename std::list<PtrDetails<T>>::iterator p;
    p = findPtrInfo(t);
    cout << "p->memPtr=" << p->memPtr << endl;
    if (p->memPtr == t)
    {
        cout << "Already using the memory address" << endl;
        // update PtrDetails<T>'s refCount
        cout << p->refcount << endl;
    }
    else
    {
        cout << "Not using the memory address" << endl;
        // FIXME:
        // add a new PtrDetails instance to refCounter.
        PtrDetails<T> pd(t);
        // refContainer.push_back(pd);
    }
}

// Copy constructor.
template <class T, int size>
Pointer<T, size>::Pointer(const Pointer &ob)
{
    std::cout << "\nI am copy constructoring..." << ob.addr << "\n";

    typename std::list<PtrDetails<T>>::iterator p;
    p = findPtrInfo(ob.addr);

    // TODO: Implement copy constructor
    // Lab: Smart Pointer Project Lab
    // Lab: References Project Lab (maybe)

    // increment ref count
    if (p->memPtr == ob.addr)
    {
        cout << "Already using the memory address" << endl;
        // update PtrDetails<T>'s refCount
        cout << p->refcount << endl;
    }
    else
    {
        cout << "Not using the memory address" << endl;
        // FIXME:
        // add a new PtrDetails instance to refCounter.
        PtrDetails<T> pd(ob.addr);
        cout << "pd.memPtr=" << pd.memPtr << endl;
        cout << "refContainer.size()=" << refContainer.size() << endl;

        refContainer.push_back(pd);
    }

    // decide whether it is an array
}

// Destructor for Pointer.
template <class T, int size>
Pointer<T, size>::~Pointer()
{
    std::cout << "I am destructoring..." << addr;
    if (isArray)
        std::cout << " WHICH IS ARRAY";
    std::cout << "\n";

    // TODO: Implement Pointer destructor
    // Lab: New and Delete Project Lab

    typename std::list<PtrDetails<T>>::iterator p;
    p = findPtrInfo(addr);

    // decrement ref count

    // Collect garbage when a pointer goes out of scope.

    // TIP: For real use, you might want to collect unused memory less frequently,
    // such as after refContainer has reached a certain size, after a certain number of Pointers have gone out of scope,
    // or when memory is low.
}

// Collect garbage. Returns true if at least
// one object was freed.
template <class T, int size>
bool Pointer<T, size>::collect()
{
    std::cout << "I am collecting...";

    // TODO: Implement collect function
    // LAB: New and Delete Project Lab
    // Note: collect() will be called in the destructor

    bool memfreed = false;
    typename std::list<PtrDetails<T>>::iterator p;
    do
    {
        // Scan refContainer looking for unreferenced pointers.
        for (p = refContainer.begin(); p != refContainer.end(); p++)
        {
            // If in-use, skip.

            // Remove unused entry from refContainer.

            // Free memory unless the Pointer is null.

            // Restart the search.
            break;
        }
    } while (p != refContainer.end());
    return memfreed;
}

// Overload assignment of pointer to Pointer.
template <class T, int size>
T *Pointer<T, size>::operator=(T *t)
{
    // TODO: Implement operator==
    // LAB: Smart Pointer Project Lab
    // maybe check https://knowledge.udacity.com/questions/53363
}

// Overload assignment of Pointer to Pointer.
template <class T, int size>
Pointer<T, size> &Pointer<T, size>::operator=(Pointer &rv)
{
    // TODO: Implement operator==
    // LAB: Smart Pointer Project Lab
    // Lab: References Project Lab (maybe)

    // First, decrement the reference count
    // for the memory currently being pointed to.

    // Then, increment the reference count of
    // the new address.

    // increment ref count
    // store the address.
    // return
}

// Display refContainer.
template <class T, int size>
void Pointer<T, size>::showlist()
{
    typename std::list<PtrDetails<T>>::iterator p;
    std::cout << "===========================\n";
    std::cout << "refContainer<" << typeid(T).name() << ", " << size << ">:\n\n";
    std::cout << "memPtr refcount value\n";
    if (refContainer.begin() == refContainer.end())
    {
        std::cout << "-->Container is empty!\n\n ";
    }

    // Else, refContainer is full of data
    for (p = refContainer.begin(); p != refContainer.end(); p++)
    {
        // point to the memory address that memPtr is holding,
        // then dereference to get the value at that address
        std::cout << "[" << (void *)p->memPtr << "]"
                  << " " << p->refcount << " ";

        // If p does points to a valid memory address, then derefernce it
        if (p->memPtr)
            std::cout << " " << *p->memPtr;
        else
            std::cout << "---";
        std::cout << std::endl;
    }
    std::cout << std::endl;
    std::cout << "===========================\n";
}

// Find a pointer in refContainer.
// *** Return an iterator or maybe an iterator's element?
template <class T, int size>
typename std::list<PtrDetails<T>>::iterator
Pointer<T, size>::findPtrInfo(T *ptr)
{
    typename std::list<PtrDetails<T>>::iterator p;

    // Maybe find ptr in refContainer.
    for (p = refContainer.begin(); p != refContainer.end(); p++)
        if (p->memPtr == ptr)
        {
            // cout << "DID FIND PNTR" << endl;
            return p;
        }
    // Else, return just p?
    // cout << "DID NOT FIND PNTR" << endl;
    return p;
}

// Clear refContainer when program exits.
template <class T, int size>
void Pointer<T, size>::shutdown()
{
    if (refContainerSize() == 0)
        return; // list is empty
    typename std::list<PtrDetails<T>>::iterator p;
    for (p = refContainer.begin(); p != refContainer.end(); p++)
    {
        // Set all reference counts to zero
        p->refcount = 0;
    }
    collect();
}