#include "gc_pointer.h"
#include <list> // remove me
#include "LeakTester.h"

#include <iostream>  // remove me
using namespace std; // remove me

// typename std::list<int>::iterator findIt()
// {
//     std::list<int> l = {0, 1, 2};
//     l.push_back(3);
//     std::list<int>::iterator it;
//     for (it = l.begin(); it != l.end(); it++)
//     {
//         if (4 == *it)
//         {
//             cout << "DID FIND IT" << endl;
//             return it;
//         }
//     }
//     cout << "DID NOT FIND IT" << endl;
//     // return it;
//     // as suggested from Sasha
//     return std::end(l);
// }

// class DetailsPtr
// {
// public:
//     int *var;
//     DetailsPtr(int *var_)
//     {
//         var = var_;
//     };
// };

// class Details
// {
// public:
//     int var;
//     Details(int var) : var(var){};
// };

// class Tester
// {
// private:
//     static std::list<Details> myList;
//     int myvar;

// public:
//     Tester(int myvar) : myvar(myvar)
//     {
//         Details d(myvar);
//         myList.push_back(d);
//     };
//     void add(Details foo);
//     void print();
// };

// // Init Static
// std::list<Details> Tester::myList;

// void Tester::add(Details foo)
// {
//     myList.push_back(foo);
// }

// void Tester::print()
// {
//     cout << "Size=" << myList.size() << endl;
// }

// Tester::Tester(int foo)
// {
//     // int foo = 4;
//     myList.push_back(foo);
// };

int main()
{
    // Test Pointer's Initialization Constructor
    Pointer<int> p = new int(19);

    // Test Pointer's Overload assignment of pointer to Pointer
    p = new int(21);
    p = new int(28);

    // Test Pointer's Overload assignment of Pointer to Pointer.
    Pointer<float> pPoint = new float(3);
    Pointer<float> pCopy;
    pCopy = pPoint;

    // Test Pointer's Copy Constructor
    Pointer<float> pOrig = new float(5);
    Pointer<float> pCopyCon = pOrig;

    // Test Pointer's Array
    Pointer<float, 2> pArr = new float[2]{3,4};


    // p.showlist();



    // cout << "\033[35m==============Example of Copy Constructor==============\033[0m\n";
    // Pointer<float> p4 = new float(5);
    // Pointer<float> p5 = new float(5);
    // cout << "\033[35m==============Example of Copy Constructor==============\033[0m\n";

    return 0;
}