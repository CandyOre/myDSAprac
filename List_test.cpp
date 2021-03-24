#include <iostream>
#include <stdio.h>
#include "./List/list.h"

using std::cout;
using std::endl;
using namespace mySTL;

void out ( int a ) { cout << a << endl; }

int main(){
    List<int>* li = new List<int>();
    li->insertAsFirst(1);
    li->insertAsFirst(2);
    li->insertAsLast(3);
    li->insertAsFirst(1);
    li->traverse(*out);
    li->sort();
    li->traverse(*out);
    li->deduplicate();
    li->traverse(*out);
    cout << (*li)[1];
    return 0;
}