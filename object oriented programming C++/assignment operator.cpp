// overloading operators example
#include <iostream>
using namespace std;

class CVector {
  public:
    int x,y;
    CVector () {};
    CVector (int a,int b) : x(a), y(b) {}
    CVector operator+ ( const CVector&);
    CVector& operator = (const CVector&);
};

CVector CVector::operator+ ( const CVector& param) {
  CVector temp;
  temp.x = x + param.x;
  temp.y = y + param.y;
  return temp;
}

CVector& CVector::operator = (const CVector& param)
{
  x=param.x;
  y=param.y;
  cout<<x<<"  ** "<<y<<endl;
  return *this;
}
int main () {
  CVector foo (3,1);
  CVector bar (1,2);
  CVector result;

  result.operator=(foo + bar);


  cout << result.x << ',' << result.y << '\n';
  return 0;
}
