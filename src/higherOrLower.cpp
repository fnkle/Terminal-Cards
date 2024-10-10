#include "cardManagement.hpp"
#include "higherOrLower.hpp"
#include <iostream>



HigherOrLower::HigherOrLower(Deck* deck){
    this->deck = deck;

    int currentScore = 0;

    //Generate hand
    std::list<Hand> hands = Dealer::dealHands(1, 1, deck);
    Hand playerCards = hands.front();
    hands.clear();

    bool loop = true;

    while (loop) {
        //Print current game state
        std::cout<< "Current Score: " + std::to_string(currentScore) + "\n";
        std::cout<< "Previous Cards: " + generateHandString(playerCards) + "\n \n";
        std::cout<< "Higher (h) or Lower (l)";

        //Draw card the player is guessing about
        Card newCard = Dealer::drawCard(deck);

        std::string userInput;
        std::cin >> userInput;

        //Compare card values depending on the user input
        if(userInput == "h"){
            if(newCard.value > playerCards.cards.back().value){
                //If they were correct increase score and add new card to the hand
                currentScore++;
                playerCards.cards.push_back(newCard);
            }
            else if((newCard.value == playerCards.cards.back().value) && newCard.value == 10){
                
            }
            else{
                //If incoreect end loop and print lose message
                loop = false;
                std::cout << "Thats unfortunate the card was the " + newCard.rank + newCard.suit;
            }
        }
        else if (userInput == "l"){
            if(newCard.value < playerCards.cards.back().value){
                 //If they were correct increase score and add new card to the hand
                currentScore++;
                playerCards.cards.push_back(newCard);
            }
            else{
                //If incoreect end loop and print lose message
                loop = false;
                std::cout << "Thats unfortunate the card was the " + newCard.rank + newCard.suit;
            }
        }
        else{
            //Catch for invalid inputs
            std::cout<< "Invalid input try again \n \n";
        }        
    }
};