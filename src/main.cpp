#include "cardManagement.hpp"
#include "higherOrLower.hpp"

using namespace std;


int main(){
    list<Card> cards = generateCards();
    Deck deck = Deck(cards);

    HigherOrLower higherOrLower = HigherOrLower(&deck);
    //BlackJack blackjack = BlackJack(&deck);
}

