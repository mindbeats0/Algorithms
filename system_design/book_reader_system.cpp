#include <bits/stdc++.h>
using namespace std;


class Book {
     static set<Book> books; // FOR ALL BOOKS OBJECTS

     int ID;
     string details;

public:
    const bool operator<(const Book&other)const{ // AY KALAM  MUST BE PUBLIC!!!
        return true;
    }

     long getID(){return ID;}
     Book() { }
     Book(long iD, string details) { }


    static void addBook(long iD, string details){
        books.insert(*new Book(iD, details));
     }
    static void dlt(Book b) { books.erase(b); }
    static Book find(long id){
         for (Book b : books)
            if(b.getID() == id) return b;
         throw -1;
     }

};
class User {
     int ID;
     string details;
     int accountType;
     static set<User> users;


public:

    const bool operator<(const User & user)const{
            return true;
    }

     User() { }
     User(long iD, string details, int accountType) { }

     int getID(){return ID;}

     void renewMembership() { }

     static User find(long ID) {
        for (User u : users) {
             if (u.getID() == ID) return u;
         }
         throw -1;
         // throw no_such_attribute_error;
         // OR You can easily create a static object that represents a NULL return.
    }
     static void addUser(long ID, string details,int accountType) {
        users.insert(*new User(ID, details, accountType));
    }

    Book searchLibrary(int id) { return Book::find(id); }

};
class OnlineReaderSystem { //service class
     Book b;
     User u;
public:
     OnlineReaderSystem(Book b, User u) { }
     void listenRequest() { }

     Book searchBook(long ID) { return Book::find(ID); }// static function access
     User searchUser(long ID){ return User::find(ID); }

     void display() { }
};
int main(){

}
