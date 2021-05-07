#include <iostream>
#include <stdio.h>
#include "Stack/stack.h"
#include "Queue/queue.h"
using namespace mySTL;

int main(){
    Queue<int> que;
    que.enqueue(1);
    que.enqueue(2);
    std::cout << que.dequeue();
    std::cout << que.empty();
    std::cout << que.dequeue();
    std::cout << que.empty();
    return 0;
}