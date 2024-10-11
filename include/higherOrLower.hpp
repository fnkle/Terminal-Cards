#include "cardManagement.hpp"

class HigherOrLower{
    public:
    Deck* deck;
    int currentScore;

    HigherOrLower(Deck* deck);

    private:
    void correct(Hand* playerCards, Card newCard);
    void incorrect(bool* loop, Card newCard);
};

