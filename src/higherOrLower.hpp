#include <iostream>
#include "cardManagement.hpp"


class HigherOrLower{
    public:
    Deck* deck;

    void setupDeck(){
        cout << "test";
        
        list<string> suits = {"\u2665", "\u2666", "\u2663", "\u2660"};
        list<string> ranks = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
        list<int> values = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};


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
    
    HigherOrLower(){
        cout<<"test";
        setupDeck();

        int currentScore = 0;

        list<Hand> hands = Dealer::dealHands(1, 1, deck);
        Hand playerCards = hands.front();
        hands.clear();

        bool loop = true;

        while (loop) {
            cout<< "Current Score: " + to_string(currentScore) + "\n";
            cout<< "Previous Cards: " + generateHandString(playerCards) + "\n \n";
            cout<< "Higher (h) or Lower (l)";

            Card newCard = Dealer::drawCard(deck);

            string userInput;
            cin >> userInput;

            if(userInput == "h"){
                if(newCard.value >= playerCards.cards.back().value){
                    currentScore++;
                    playerCards.cards.push_back(newCard);
                }
                else{
                    loop = false;
                    cout << "Thats unfortunate the card was the " + newCard.rank + newCard.suit;
                }
            }
            else if (userInput == "l"){
                if(newCard.value <= playerCards.cards.back().value){
                    currentScore++;
                    playerCards.cards.push_back(newCard);
                }
                else{
                    loop = false;
                    cout << "Thats unfortunate the card was the " + newCard.rank + newCard.suit;
                }
            }
            else{
                cout<< "Invalid input try again \n \n";
            }

            
        }
        
    }

};