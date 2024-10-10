#include "cardManagement.hpp"

#include <ctime>
#include <string>
#include <list>



//Define card constructor
Card::Card(std::string rank, std::string suit, int value){
    this->rank = rank;
    this->suit = suit;
    this->value = value;
}

//Define Deck constructor that creates random order of cards
Deck::Deck(std::list<Card> listCards){
        this->cards={};
        shuffleDeck(listCards);
    }

//Define shuffle function of the Deck class
void Deck::shuffleDeck(std::list<Card> listCards){
    //Set up randomiser
    srand((unsigned) time(NULL));
    //While there is still cards to be put in deck
    while (listCards.size() > 0)
    {   
        //Choose a random card then add it to deck before removing it from list of all cards
        int randCard = rand() % (listCards.size());
        auto iterator = listCards.begin();
        advance(iterator, randCard );
        cards.push_back(*iterator);
        listCards.erase(iterator);
    }
        
}

//Define Hand constructor that takes in a list of cards in the hand
Hand::Hand(std::list<Card> cards){
    this->cards = cards;
}

/*
    Dealer class function to be used to create a certain number of Hand objects.
    The number of cards to be in each handis also to be passed
*/

std::list<Hand> Dealer::dealHands(int numCards, int numHands, Deck* deck){

    std::list<Hand> hands = {};
    std::list<Card> cardsForAllHands = {};

    //Calculate the total number of cards needed total
    int totalCards =numCards *numHands;

    //While less cards drawn then required draw a card 
    while(cardsForAllHands.size() < totalCards){
        cardsForAllHands.push_back(drawCard(deck));
    }

    //Loop for each hand to be created
    for(int numHandsDone = 0; numHandsDone < numHands; numHandsDone++){
        std::list<Card> cardsForOneHand = {};

        /*
            The dealing function gets a bit confusing here.
            Currently i've taken all the cards needed to create the required hands off the deck and put them in a seperate list
            However, now i need a way to split these into there correct hands.
            I start with the first hand with 0 offset and until it has enough cards I access a card in the list before advancing to the next card.
            Each time i advance by the number of hands to be made so that the iterator skips over the cards meant for the other hands.
            Then for the next card i start with 1 offset and repeat accessing card in the list then advancing the iterator by the number of hands.
            This is repeated until I have the correct ammount of hands
        */
        auto iterator = cardsForAllHands.begin();
        for(int offset = 0; offset < numHandsDone; offset++){
            iterator++;
        }

        while(cardsForOneHand.size() < numCards){
            cardsForOneHand.push_back(*iterator);
            advance(iterator, numHands);
        }

        //Finally using the cards I create a hand object and push it to the back of the list ready to be returned at the end of the function
        hands.push_back(Hand(cardsForOneHand));
    }

    return hands;
}

//Dealer function to draw card from passed by refrence deck and return the card
Card Dealer::drawCard(Deck *deck){
    Card tempCard = deck->cards.front();
    deck->cards.pop_front();
    return tempCard;
}

//Function to generate a string from a hand of cards for printing to the console
std::string generateHandString(Hand hand){
    
    std::string handString = "";
    for(Card card: hand.cards){
        handString += card.rank + " " + card.suit + " ";
    }
    return handString;
};

//Function to setup the cards the values are subject to change depending on the game but im unsufe how to implement that currently.
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

