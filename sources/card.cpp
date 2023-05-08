#include "card.hpp"
#include <stdexcept>

using namespace ariel;
using namespace std;

namespace ariel {
    Card::Card(int num, const string &type) {
        if (num > 13 || num < 1) {
            throw invalid_argument("cards can only be between 1-13");
        }
        if (type != "Hearts" && type != "Spades" && type != "Diamonds" && type != "Clubs") {
            throw invalid_argument("Invalid card type");
        }
        this->number = num;
        //ace is the highest so I converted it to 14 for comfort.
        if (num == 1) {
            this->number = 14;
        }
        this->type = type;
    }

    int Card::getCard() const {
        return this->number;
    }

    string Card::cardName() const {
        if (this->number == 11) {
            return "Jack";
        }
        if (this->number == 12) {
            return "Queen";
        }
        if (this->number == 13) {
            return "King";
        }
        if (this->number == 14) {
            return "Ace";
        }
        return to_string(this->number);
    }

    string Card::getType() const {
        return this->type;
    }
}