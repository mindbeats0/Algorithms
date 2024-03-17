#include<iostream>
using namespace std;

class SmartPtr
{
   int *ptr;  // Actual pointer
public:

   SmartPtr(int *p = NULL) { ptr = p; }

   ~SmartPtr() { delete(ptr); }

   int &operator *() {  return *ptr; }
};

int main()
{
    SmartPtr ptr(new int()); //ptr wrapper
    *ptr = 20;
    cout << *ptr;

    // We don't need to call delete ptr: when the object
    // ptr goes out of scope, destructor for it is automatically
    // called and destructor does delete ptr.

    return 0;
}
