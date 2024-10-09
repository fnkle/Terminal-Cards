#include "cardManagement.hpp"

#include <ctime>
#include <string>
#include <list>




Card::Card(std::string rank, std::string suit, int value){
    this->rank = rank;
    this->suit = suit;
    this->value = value;
}


Deck::Deck(std::list<Card> listCards){
        this->cards={};
        shuffleDeck(listCards);
    }


void Deck::shuffleDeck(std::list<Card> listCards){
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


Card Hand::drawCard(Deck deck){
    Card tempCard = deck.cards.front();
    deck.cards.pop_front();
    return tempCard;
}

Hand::Hand(std::list<Card> cards){
    this->cards = cards;
}

std::list<Hand> Dealer::dealHands(int numCards, int numHands, Deck* deck){

    std::list<Hand> hands = {};
    std::list<Card> cardsForAllHands = {};

    int totalCards =numCards *numHands;

    while(cardsForAllHands.size() < totalCards){
        cardsForAllHands.push_back(drawCard(deck));
    }

    for(int numHandsDone = 0; numHandsDone < numHands; numHandsDone++){
        std::list<Card> cardsForOneHand = {};
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

Card Dealer::drawCard(Deck *deck){
    Card tempCard = deck->cards.front();
    deck->cards.pop_front();
    return tempCard;
}


std::string generateHandString(Hand hand){
    
    std::string handString = "";
    for(Card card: hand.cards){
        handString += card.rank + " " + card.suit + " ";
    }
    return handString;
};

std::list<Card> generateCards(){ 
    //Hearts, Diamonds, CLubs, Spades
    std::list<std::string> suits = {"\u2665", "\u2666", "\u2663", "\u2660"};
    std::list<std::string> ranks = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
    std::list<int> values = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10};

    std::list<Card> cards = {};

    for(std::string suit: suits){
        auto valueIterator = values.begin();
        for (std::string rank: ranks)
        {
            cards.push_back(Card(rank, suit, *valueIterator));
            valueIterator++;
        }
        
    }

    return cards;
};

