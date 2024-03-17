#include <iostream>
using namespace std;

class A{
public:
  A(){
    cout << "default ctor" << endl;
  }
  A(int id){
    pointer = new int(id);
    cout << "ctor of " << (*pointer) << endl;
  }
  ~A() {
    cout << "dtor of " << (*pointer) << endl;
    clear();
  }
  A(const A& a) {
    pointer = new int(*a.pointer);
    cout << "copy ctor of " << (*pointer) << endl;
  }

  A& operator=(const A& a) {
    if(&a == this) {
      return *this;
    }
    clear();
    pointer = new int(*a.pointer);
    cout << "operator= of " << (*pointer) << endl;
    return *this;
  }

  void print() {
    cout << (*pointer) << endl;
  }
  void setId(int id) {
    (*pointer) = id;
  }
  int *pointer;

private:
  void clear() {
    delete pointer;
    pointer = NULL;
  }
};

void func1() {
  cout << "DECLARING a, b" << endl;
  A a(1), b(2);
  cout << "DECLARING e" << endl;
  A e = A(3);
  cout << "POINTER TO A" << endl;
  A *pointerToA = new A(4);
  cout << "DELETING POITNER TO A" << endl;
  delete pointerToA;
  cout << "IN THE MIDDLE OF FUNC1" << endl;
}

void func2(A y) {
  cout << "IN THE MIDDLE OF FUNC2" << endl;
  y.setId(5);
  cout << "PRINT CONTENT OF y" << endl;
  y.print();
}

int main() {

    A x(1),y(2);

    x=y;
}

// ya nada, you there?
