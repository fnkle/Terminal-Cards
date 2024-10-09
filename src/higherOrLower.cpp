#include "cardManagement.hpp"
#include "higherOrLower.hpp"
#include <iostream>



HigherOrLower::HigherOrLower(Deck* deck){
    this->deck = deck;

    int currentScore = 0;

    std::list<Hand> hands = Dealer::dealHands(1, 1, deck);
    Hand playerCards = hands.front();
    hands.clear();

    bool loop = true;

    while (loop) {
        std::cout<< "Current Score: " + std::to_string(currentScore) + "\n";
        std::cout<< "Previous Cards: " + generateHandString(playerCards) + "\n \n";
        std::cout<< "Higher (h) or Lower (l)";

        Card newCard = Dealer::drawCard(deck);

        std::string userInput;
        std::cin >> userInput;

        if(userInput == "h"){
            if(newCard.value > playerCards.cards.back().value){
                currentScore++;
                playerCards.cards.push_back(newCard);
            }
            else{
                loop = false;
                std::cout << "Thats unfortunate the card was the " + newCard.rank + newCard.suit;
            }
        }
        else if (userInput == "l"){
            if(newCard.value < playerCards.cards.back().value){
                currentScore++;
                playerCards.cards.push_back(newCard);
            }
            else{
                loop = false;
                std::cout << "Thats unfortunate the card was the " + newCard.rank + newCard.suit;
            }
        }
        else{
            std::cout<< "Invalid input try again \n \n";
        }        
    }
};