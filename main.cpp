#include "gc_pointer.h"
#include <list> // remove me
// #include "LeakTester.h"

#include <iostream>  // remove me
using namespace std; // remove me

typename std::list<int>::iterator findIt()
{
    std::list<int> l = {0, 1, 2};
    l.push_back(3);
    std::list<int>::iterator it;
    for (it = l.begin(); it != l.end(); it++)
    {
        if (4 == *it)
        {
            cout << "DID FIND IT" << endl;
            return it;
        }
    }
    cout << "DID NOT FIND IT" << endl;
    // return it;
    // as suggested from Sasha
    return std::end(l);
}

class Details
{
public:
    int var;
    Details(int var) : var(var){};
};

class Tester
{
private:
    static std::list<Details> myList;
    int myvar;

public:
    Tester(int myvar) : myvar(myvar)
    {
        Details d(myvar);
        myList.push_back(d);
    };
    void add(Details foo);
    void print();
};

// Init Static
std::list<Details> Tester::myList;

void Tester::add(Details foo)
{
    myList.push_back(foo);
}

void Tester::print()
{
    cout << "Size=" << myList.size() << endl;
}

// Tester::Tester(int foo)
// {
//     // int foo = 4;
//     myList.push_back(foo);
// };

int main()
{
    // Pointer<int> p = new int(19);
    // cout << "\n\n\n\n";

    // // How is isArray being set?
    // Pointer<int, 5> p1 = new int[5];
    // Pointer<int, 6> p2 = new int[6];
    // Pointer<int, 7> p3 = new int[7];
    // cout << "p1.collect() " << p1.collect() << endl;
    // cout << "p2.collect() " << p2.collect() << endl;
    // cout << "p3.collect() " << p3.collect() << endl;

    cout << "===========================\n";
    cout << "\033[35mExample of Copy Constructor\033[0m\n";
    Pointer<float> p4 = new float(5);
    Pointer<float> p5 = new float(5);
    // Pointer<float, 1> p5 = p4;
    // Pointer<float, 1> p5 = p4;
    p4.showlist();
    cout << "===========================\n";

    // List example
    // p5.showlist();
    // cout << "refContainerSize=" << p5.refContainerSize();
    // int foo = 5;
    // Tester t(foo);
    // Tester t2(foo);
    // t.add(foo);
    // t.add(foo);
    // t.print();

    // // Basics of a List and Iterator
    // cout << "\n\n\n\n";
    // std::list<int>::iterator it;
    // it = findIt();
    // cout << "findIt() " << *it << endl;

    // // PtrDetails
    // Pointer<int> foo = new int(19);
    // Pointer<int> foo2 = new int(19);
    // Pointer<int> foo3 = new int[5];
    // PtrDetails<int> pd2(foo);
    // PtrDetails<int> pd3(foo2);
    // PtrDetails<int> pd4(foo3);
    // cout << "*foo=" << *foo << endl;
    // cout << "*foo3=" << *foo3 << endl;
    // // cout << pd4.isArray << pd4.addr << endl;

    // Testing an add too a list
    // Pointer<int> stalls = new int(19);
    // std::list<PtrDetails<int>> refContainer;
    // PtrDetails<int> pd(stalls);
    // refContainer.push_back(pd);
    // // Does NOT stall at 100 % CPU

    return 0;
}