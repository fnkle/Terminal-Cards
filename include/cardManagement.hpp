#ifndef CARD_MANAGEMENT
#define CARD_MANAGEMENT
#include <string>
#include <list>

class Card{
public:
    std::string rank;
    std::string suit;
    int value;
    Card(std::string rank, std::string suit, int value);
};

class Deck{
public:
    std::list<Card> cards;
    Deck(std::list<Card> listCards);


    void shuffleDeck(std::list<Card> listCards);
};

class Hand{
public:
    std::list<Card> cards;
    int handLimit;

    Hand(std::list<Card> cards);
};

class Dealer{
public:
    static std::list<Hand> dealHands(int numCards, int numHands, Deck* deck);
    static Card drawCard(Deck* deck);
};

std::string generateHandString(Hand hand);
std::list<Card> generateCards();

#endif