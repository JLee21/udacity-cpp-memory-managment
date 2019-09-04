#include "gc_pointer.h"
#include <list> // remove me
// #include "LeakTester.h"

#include <iostream>  // remove me
using namespace std; // remove me

int main()
{
    Pointer<int> p = new int(19);

    cout << "\n\n\n\n";

    // How is isArray being set?
    Pointer<int, 5> p1 = new int[5];
    Pointer<int, 6> p2 = new int[6];
    Pointer<int, 7> p3 = new int[7];
    cout << "p1.collect() " << p1.collect() << endl;
    cout << "p2.collect() " << p2.collect() << endl;
    cout << "p3.collect() " << p3.collect() << endl;

    // Example of Copy Constructor
    Pointer<float, 1> p4 = new float(5);
    Pointer<float, 1> p5 = p4;

    //
    p5.showlist();
    cout << "refContainerSize=" << p5.refContainerSize();

    // Basics of a List and Iterator
    cout << "\n\n\n\n";
    std::list<int> l = {0, 1, 2};
    std::list<int>::iterator it;
    for (it = l.begin(); it != l.end(); it++)
    {
        cout << "meow\n";
    }

    // PtrDetails
    Pointer<int> foo = new int(19);
    Pointer<int> foo2 = new int(19);
    Pointer<int> foo3 = new int[5];
    PtrDetails<int> pd(foo);
    PtrDetails<int> pd2(foo);
    PtrDetails<int> pd3(foo2);
    PtrDetails<int> pd4(foo3);
    cout << "*foo=" << *foo << endl;
    cout << "*foo3=" << *foo3 << endl;
    // cout << pd4.isArray << pd4.addr << endl;

    return 0;
}