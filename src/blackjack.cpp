#include "blackjack.hpp"
#include <iostream>

BlackJack::BlackJack(Deck* deck){
        
    this->deck = deck;
        
    std::list<Hand> hands = Dealer::dealHands(2, 2, deck);

    Hand playerHand = hands.front();
    hands.pop_front();
    Hand dealerHand = hands.front();
    hands.pop_front();

    //Game loop
    bool loop = true;

    while(loop){
        std::cout<< "Dealer Hand: " + generateHandString(dealerHand) + "\n";
        std::cout<< "Player Hand: " + generateHandString(playerHand) + "\n \n";
        std::cout<< "Hit or Stand \n \n";

        std::string input;
        std::cin >> input;

        if(input == "Hit"){
            playerHand.cards.push_back(Dealer::drawCard(deck));
        }
    }   
}