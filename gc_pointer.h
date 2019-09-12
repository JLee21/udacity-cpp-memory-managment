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
    //
    static std::list<PtrDetails<T>> refContainer;

    // addr points to the allocated memory to which
    // this Pointer pointer currently points.
    T *addr;

    // true if pointing to array
    bool isArray;

    // size of the array, if we are pointing to an array
    unsigned arraySize;

    // true when first Pointer is created
    static bool first;

    // Return an iterator to PtrDetails in refContainer.
    typename std::list<PtrDetails<T>>::iterator findPtrInfo(T *ptr);

public:
    // Define an iterator type for Pointer<T>.
    typedef Iter<T> GCiterator;

    // Empty constructor
    // NOTE: templates aren't able to have prototypes with default arguments
    // which is why constructor is designed like this:
    Pointer() { Pointer(NULL); }
    // want we want ultimately just want this
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
    // This overloaded operator is like a proxy
    T &operator*() { return *addr; }
    // Pointer p();
    // *pd

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
    addr = t;
    // Register shutdown() as an exit function.
    if (first)
        atexit(shutdown);
    first = false;

    if (size)
    {
        arraySize = size;
        isArray = true;
    }
    else
        isArray = false;

    typename std::list<PtrDetails<T>>::iterator p;
    p = findPtrInfo(t);
    // add a new PtrDetails instance to refCounter.
    PtrDetails<T> pd(t);
    cout << "refContainerSize Before=" << refContainerSize() << endl;
    refContainer.emplace_back(pd);
    cout << "refContainerSize After=" << refContainerSize() << endl;
    // at this point, ~pd is called
    p = refContainer.begin();
    cout << "refContainer now has one element that points to=" << p->memPtr << "\trefcount=" << p->refcount << endl;
    // *** At this point, pd is destructured
}

// Copy constructor.
template <class T, int size>
Pointer<T, size>::Pointer(const Pointer &ob)
{
    std::cout << "\nCOPYING Pointer=..." << ob.addr << "\n";
    addr = ob.addr;

    typename std::list<PtrDetails<T>>::iterator p;
    p = findPtrInfo(ob.addr);

    // TODO: Implement copy constructor
    // Lab: Smart Pointer Project Lab
    // Lab: References Project Lab (maybe)

    // increment ref count
    if (p->memPtr == ob.addr)
    {
        // update PtrDetails<T>'s refCount
        (p->refcount)++;
        cout << "Already using the memory address so the refcount is now " << p->refcount << endl;
    }
    else
    {
        cout << "Not using the memory address" << endl;
        // add a new PtrDetails instance to refCounter.
        PtrDetails<T> pd(ob.addr);
        cout << "Adding a new PtrDeatils to refContainer" << endl;
        cout << "pd.memPtr=" << pd.memPtr << endl;
        cout << "refContainer.size()=" << refContainer.size() << endl;
        refContainer.emplace_back(pd);
    }

    // decide whether it is an array
}

// Destructor for Pointer.
template <class T, int size>
Pointer<T, size>::~Pointer()
{
    cout << "\033[34m==============~Pointer()==============START\033[0m\n";
    typename std::list<PtrDetails<T>>::iterator pt;
    pt = refContainer.begin();
    cout << "refContainer has one element that points to=" << pt->memPtr << "\tand the refcount=" << pt->refcount << endl;

    typename std::list<PtrDetails<T>>::iterator p;
    p = findPtrInfo(addr);

    // decrement ref count
    (p->refcount)--;
    cout << "(p->refcount)--" << endl;
    cout << "refContainer has one element that points to=" << pt->memPtr << "\tand the refcount=" << pt->refcount << endl;

    // Collect garbage when a pointer goes out of scope.
    bool memfreed = collect();
    cout << " was memoryfreed?=" << memfreed << endl;

    // TIP: For real use, you might want to collect unused memory less frequently,
    // such as after refContainer has reached a certain size, after a certain number of Pointers have gone out of scope,
    // or when memory is low.
    cout << "\033[34m==============~Pointer()==============END\033[0m\n";
}

// Collect garbage. Returns true if at least
// one object was freed.
// When to call collect? One option, tie it to any delete.
template <class T, int size>
bool Pointer<T, size>::collect()
{
    cout << "\033[36m==============collect()==============START\033[0m\n";
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
            // *** how to tell if in-use? By looking at refcount
            cout << "p->refcount " << p->refcount << endl;

            if (p->refcount > 0)
            {
                cout << "p->refcount > 0 ... continue...\n";
                continue;
            }

            // Remove unused entry from refContainer.
            // *** How to do this?
            // *** Do I make a copy of it first and then? No.
            // since we have refCon, we can use erase, maybe remove
            // this will call PtrDetails destructor
            cout << "Erasing pointer=" << p->memPtr << endl;
            // at this point, program fails b/c it says p has already been deleted.
            cout << "refContainer size=" << refContainerSize() << endl;
            refContainer.erase(p);
            if (p->memPtr)
            {
                if (p->isArray)
                {
                    delete[] p->memPtr;
                }
                else
                {
                    delete p->memPtr;
                }
                memfreed = true;
            }
            // p is not longer valid, we can't use it anymore
            cout << "Are we at the end of refContainer = " << (p != refContainer.end()) << endl;

            // Free memory unless the Pointer is null.
            // *** How to do this? std::remove()
            // Restart the search.
            break;
        }
    } while (p != refContainer.end());
    cout << "\033[36m==============collect()==============END\033[0m\n";
    return memfreed;
}

// Overload assignment of pointer to Pointer.
template <class T, int size>
T *Pointer<T, size>::operator=(T *t)
{
    cout << "\033[36m==============Overload assignment of pointer to Pointer.==============START\033[0m\n";
    // TODO: Implement operator =
    // LAB: Smart Pointer Project Lab
    // maybe check https://knowledge.udacity.com/questions/53363

    // For example:
    //     Pointer<int> p = new int(19);
    //     p = new int(21);

    typename std::list<PtrDetails<T>>::iterator p;
    p = findPtrInfo(addr);

    // decrement ref count
    (p->refcount)--;


    cout << "\033[36m==============Overload assignment of pointer to Pointer.==============END\033[0m\n";
}

// Overload assignment of Pointer to Pointer.
template <class T, int size>
Pointer<T, size> &Pointer<T, size>::operator=(Pointer &rv)
{
    // TODO: Implement operator=
    // LAB: Smart Pointer Project Lab
    // Lab: References Project Lab (maybe)

    // First, decrement the reference count for the memory currently being pointed to.

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
    std::cout << "--------------------\n";
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
        std::cout << "address=" << (void *)p->memPtr
                  << " refcount=" << p->refcount << " ";

        // If p does points to a valid memory address, then derefernce it
        if (p->memPtr)
            std::cout << " value=" << *p->memPtr;
        else
            std::cout << "value=None";
        std::cout << std::endl;
    }
    std::cout << std::endl;
    std::cout << "--------------------\n";
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
            cout << "DID FIND PNTR" << endl;
            return p;
        }
    // Else, return just p?
    cout << "DID NOT FIND PNTR" << endl;
    return p;
}

// Clear refContainer when program exits.
template <class T, int size>
void Pointer<T, size>::shutdown()
{
    cout << "\033[33mShutting Down!\033[0m\n";

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
