#include <iostream>
#include "cardManagement.hpp"

class BlackJack{
public:
    Deck* deck;

    void setupDeck(){
        list<string> suits = {"\u2665", "\u2666", "\u2663", "\u2660"};
        list<string> ranks = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
        list<int> values = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10};

        list<Card> cards = {};

        for(string suit: suits){
            auto valueIterator = values.begin();
            for (string rank: ranks)
            {
                cards.push_back(Card(rank, suit, *valueIterator));
                valueIterator++;
            }
        
        }

        Deck deck = Deck(cards);
        this->deck = &deck;
    }

    BlackJack(){
        
        setupDeck();
        
        list<Hand> hands = Dealer::dealHands(2, 2, deck);

        Hand playerHand = hands.front();
        hands.pop_front();
        Hand dealerHand = hands.front();
        hands.pop_front();

        //Game loop
        bool loop = true;

        while(loop){
            cout<< "Dealer Hand: " + generateHandString(dealerHand) + "\n";
            cout<< "Player Hand: " + generateHandString(playerHand) + "\n \n";
            cout<< "Hit or Stand \n \n";

            string input;
            cin >> input;

            if(input == "Hit"){
                playerHand.cards.push_back(Dealer::drawCard(deck));
            }
        }
        
    }
};
