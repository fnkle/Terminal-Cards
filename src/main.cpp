#include <iostream>
#include <list>
#include <iterator>
#include <string>

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

string generateHandString(Hand hand){
    string handString = "";
    for(Card card: hand.cards){
        handString += card.rank + " " + card.suit + " ";
    }
    return handString;
};

list<Card> generateCards(){ 
    //Hearts, Diamonds, CLubs, Spades
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

    return cards;
};

class HigherOrLower{
    public:
    Deck* deck;
    
    HigherOrLower(Deck* deck){
        this->deck = deck;

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
                if(newCard.value > playerCards.cards.back().value){
                    currentScore++;
                    playerCards.cards.push_back(newCard);
                }
                else{
                    loop = false;
                    cout << "Thats unfortunate the card was the " + newCard.rank + newCard.suit;
                }
            }
            else if (userInput == "l"){
                if(newCard.value < playerCards.cards.back().value){
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

class BlackJack{
public:
    Deck* deck;

    BlackJack(Deck* deck){
        
        this->deck = deck;
        
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



int main(){
    list<Card> cards = generateCards();
    Deck deck = Deck(cards);

    for (int i =0; i < 4; i ++){
        auto iterator = deck.cards.begin();
        advance(iterator, i);
        Card tempCard = *iterator;
        cout << tempCard.rank + " " + tempCard.suit + "\n";
    }
    cout << "\n";

    HigherOrLower higherOrLower = HigherOrLower(&deck);
    //BlackJack blackjack = BlackJack(&deck);
}

