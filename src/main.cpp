// main.cpp
#include <iostream>

#include <vector>
#include "ThreadSafeStack.h"

int main()
{
    ts::SafeStack<int> stack1;

    stack1.push(5);

    stack1.push(4);
    stack1.push(3);

    std::cout<<"hiiii\n";
}

