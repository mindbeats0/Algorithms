rvalues can be called as:
const reference // but not non-const ref!!
   OR
rvalue reference

int sum(const int& a,const int& b){  return a+b;}
int sum(int&& a,int&& b){  return a+b;}
  ---int sum(int& a,int& b){  return a+b;} // IS WRONG!!  -----
int main(){ cout<<sum(3,4)<<endl; }


& : lvalue reference
&& : rvalue reference

void foo(A a);

in all cases constructor will be called
if the passed argument is lvalue: copy constructor
if the passed argument is rvalue: move constructor

on the other hand: NO constructors called here
void foo(A& a);
void foo(const A& a);
void foo(A&& a);
void foo(const A&& a);
