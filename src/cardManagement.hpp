#ifndef CARD_MANAGEMENT
#define CARD_MANAGEMENT

#include <ctime>
#include <string>
#include <list>
using namespace std;



class Card{
public:
    string rank;
    string suit;
    int value;

    Card(string rank, string suit, int value){
        this->rank = rank;
        this->suit = suit;
        this->value = value;
    }
};

class Deck{
public:
    list<Card> cards = {};

    Deck(list<Card> listCards){
        shuffleDeck(listCards);
    }


    void shuffleDeck(list<Card> listCards){
        srand((unsigned) time(NULL));
        while (listCards.size() > 0)
        {
            int randCard = rand() % (listCards.size());
            auto iterator = listCards.begin();
            advance(iterator, randCard );
            cards.push_back(*iterator);
            listCards.erase(iterator);
        }
        
    }
};

class Hand{
public:
    list<Card> cards;
    int handLimit;

    Card drawCard(Deck deck){
        Card tempCard = deck.cards.front();
        deck.cards.pop_front();
        return tempCard;
    }

    Hand(list<Card> cards){
        this->cards = cards;
    }
};

class Dealer{
public:
    static list<Hand> dealHands(int numCards, int numHands, Deck* deck){

        list<Hand> hands = {};
        list<Card> cardsForAllHands = {};

        int totalCards =numCards *numHands;

        while(cardsForAllHands.size() < totalCards){
            cardsForAllHands.push_back(drawCard(deck));
        }

        for(int numHandsDone = 0; numHandsDone < numHands; numHandsDone++){
            list<Card> cardsForOneHand = {};
            auto iterator = cardsForAllHands.begin();
            for(int offset = 0; offset < numHandsDone; offset++){
                iterator++;
            }

            while(cardsForOneHand.size() < numCards){
                cardsForOneHand.push_back(*iterator);
                advance(iterator, numHands);
            }

            hands.push_back(Hand(cardsForOneHand));
        }

        return hands;
    }

    static Card drawCard(Deck* deck){
        
        Card tempCard = deck->cards.front();
        deck->cards.pop_front();
        return tempCard;
    }
};

inline string generateHandString(Hand hand){
    
    string handString = "";
    for(Card card: hand.cards){
        handString += card.rank + " " + card.suit + " ";
    }
    return handString;
};

#endif