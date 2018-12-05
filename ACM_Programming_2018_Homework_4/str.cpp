#include <string>
#include <stdio.h>
#include <iostream>
using namespace std;

int c[40];

int main() {
    cin >> (char*)c;
    for (int i = 0; i < 40; i++) {
        cout << c[i] << endl;
    }
    cout << (char*)c << endl;
    return 0;
}
