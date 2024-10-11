#include "cardManagement.hpp"
#include "higherOrLower.hpp"
#include <iostream>
#include <string>



HigherOrLower::HigherOrLower(Deck* deck){
    this->deck = deck;

    this->currentScore = 0;

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
                correct(&playerCards, newCard);
            }
            else if(newCard.value == playerCards.cards.back().value){
                //What happens if cards have the same value

                std::string newCardRank = newCard.rank;
                std::string currentCardRank = playerCards.cards.back().rank;

                //If statements to deal with face cards
                if(newCardRank == "K"){
                    correct(&playerCards, newCard);
                }
                else if (newCardRank == "Q") {
                    if(currentCardRank == "K"){
                        correct(&playerCards, newCard);
                    } 
                    else{
                        correct(&playerCards, newCard);
                    }
                }
                else if (newCardRank == "J" ) {
                    if(currentCardRank == "K"){
                        correct(&playerCards, newCard);
                    }
                    else if (currentCardRank == "Q"){
                        correct(&playerCards, newCard);
                    } 
                    else{
                        incorrect(&loop, newCard);
                    }
                }
                else if (newCardRank == "10" ) {
                    if(currentCardRank == "10"){
                        correct(&playerCards, newCard);
                    }
                    else{
                        incorrect(&loop, newCard);
                    }
                    
                }
                else{
                    correct(&playerCards, newCard);
                }
            }
            else{
                //If incoreect end loop and print lose message
                incorrect(&loop, newCard);
            }
        }
        else if (userInput == "l"){
            if(newCard.value < playerCards.cards.back().value){
                 //If they were correct increase score and add new card to the hand
                correct(&playerCards, newCard);
            }
            else if(newCard.value == playerCards.cards.back().value){
                std::string newCardRank = newCard.rank;
                std::string currentCardRank = playerCards.cards.back().rank;

                //If statements for face cards
                if(newCardRank == "K"){
                    if(currentCardRank == "K"){
                        correct(&playerCards, newCard);
                    }else{
                        incorrect(&loop, newCard);
                    }
                }
                else if (newCardRank == "Q") {
                    if(currentCardRank == "K"){
                        incorrect(&loop, newCard);
                    } 
                    else{
                        correct(&playerCards, newCard);
                    }
                }
                else if (newCardRank == "J" ) {
                    if(currentCardRank == "K"){
                        incorrect(&loop, newCard);
                    }
                    else if (currentCardRank == "Q"){
                        incorrect(&loop, newCard);
                    } 
                    else{
                        correct(&playerCards, newCard);
                    }
                }
                else if (newCardRank == "10" ) {
                    if(currentCardRank == "K"){
                        incorrect(&loop, newCard);
                    }
                    else if (currentCardRank == "Q"){
                        incorrect(&loop, newCard);
                    }
                    else if (currentCardRank == "J"){
                        incorrect(&loop, newCard);
                    } 
                    else{
                        correct(&playerCards, newCard);
                    }
                }
                else{
                    correct(&playerCards, newCard);
                }
            }
            else{
                //If incoreect end loop and print lose message
                incorrect(&loop, newCard);
            }
        }
        else{
            //Catch for invalid inputs
            std::cout<< "Invalid input try again \n \n";
        }        
    }
};

void HigherOrLower::correct(Hand* playerCards, Card newCard){
    currentScore++;
    playerCards->cards.push_back(newCard);
};

void HigherOrLower::incorrect(bool* loop, Card newCard){
    *loop = false;
    std::cout << "Thats unfortunate the card was the " + newCard.rank + newCard.suit;
};