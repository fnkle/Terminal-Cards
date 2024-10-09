#include <iostream>
#include <list>
#include <iterator>

using namespace std;



class Card{
public:
    string rank;
    string suit;

    Card(string rank, string suit){
        this->rank = rank;
        this->suit = suit;
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

    list<Card> cards = {};

    for(string suit: suits){
        for (string rank: ranks)
        {
            cards.push_back(Card(rank, suit));
        }
        
    }

    return cards;
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

    
    BlackJack blackjack = BlackJack(&deck);
}

