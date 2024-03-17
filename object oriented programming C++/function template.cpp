// function template
#include <iostream>
using namespace std;

template <class T>
T sum (T a, T b)
{
  T result;
  result = a + b;
  return result;
}

int main () {
  int k;
  double h;
  k=sum<int>(5,6);
  h=sum<double>(2.0,0.5);
  // same as
   //k = sum (5,6);
   //h = sum (2.0,0.5);
  cout << k << '\n';
  cout << h << '\n';
  return 0;
}
