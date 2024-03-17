#include <cstdio>
using namespace std;

class a {
public:
    a() {
        printf("constructor called\n");
    };
    a(const a& other) {
        printf("copy constructor called\n");
    };
   a& operator=(const a& other) {
        printf("copy assignment operator called\n");
        return *this;
    };
};
int main(){
    a b; //constructor
    a c; //constructor
    b = c; //copy assignment
    c = a(b); //copy constructor, then copy assignment
}
