#include <iostream>
#include <string>
using namespace std;

//A string representing a float number to a double number
double func ( string str ) {
    int i;
    for ( i = 0; i < str.size(); i++ ) if ( str[i] == '.' ) break;
    if ( i == str.size() ) return 0;
    int a = 0;
    for ( int j = 0; j < i; j++ ) a = a * 10 + ( str[j] - '0' );
    double b = 0;
    for ( int j = str.size() - 1; j > i; j--) b = b / 10 + 0.1 * ( str[j] - '0' );
    return a + b;
}

int main () {
    string str = "123.45";
    cout << func ( str ); 
    return 0;
}