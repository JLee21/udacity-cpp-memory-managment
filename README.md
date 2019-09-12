# Udacity C++ Nanodegree

## `Project: Memory Management aka Garbage-Collector`

The goal of this project is to learn and development memory management in C++ by creating my own Smart Pointer -- in other words, to create a garbage collector.

Starter code for this project is provided by Udacity [here](https://github.com/udacity/CppND-Garbage-Collector)

# Basic Build Instructions

Complie and run : `./make`

# The following tests are run from main.cpp and LeakTester.h

```c++
#include "gc_pointer.h"
#include "LeakTester.h"

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

    return 0;
}
```
