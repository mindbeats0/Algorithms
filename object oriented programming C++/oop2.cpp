#include <bits/stdc++.h>
using namespace std;

enum Suit {Clubs, Spades, Diamonds, Hearts};
struct Card {
  Suit suit;
  char digit;
};

class Deck {
public:
       Deck();      //Constructor
       ~Deck();     //Destructor
  void CreateDeck();//Fills array with legal cards
  void Shuffle();   //Shuffles those cards
  Card DrawCard();  //Gets a card from the deck
private:
  Card* cards;
};


Deck::Deck() {
  cards = new Card[52];//Allocate memory
  CreateDeck();        //Set up the deck
}
Deck::~Deck() {
  delete[] cards;      //Deallocate memory
}

int main(){

}

