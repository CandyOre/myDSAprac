#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>

using std::cout;
using std::endl;
using namespace std;

void out ( int a ) { cout << a << endl; }

int main(){
    vector<int> a = { 1,3,2,4 };
    sort(a.begin(),a.end());
    for(int i=0;i<a.size();i++) cout << a[i] << endl;
    return 0;
}