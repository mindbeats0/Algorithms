#include <iostream>
using namespace std;
int n;
int& test();

int main() {
    test() = 5;
    cout<<n;
    return 0;
}

int& test() {
    n=2;
    return n;
}
