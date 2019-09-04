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
    Pointer<int> p4 = new int(5);
    Pointer<int> p5 = p4;

    // Basics of a List and Iterator
    std::list<int> l = [ 0, 1, 2 ];

    return 0;
}