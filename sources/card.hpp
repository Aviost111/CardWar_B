#ifndef CPP_HW2_CARD_HPP
#define CPP_HW2_CARD_HPP

#include <stdexcept>
#include <cstring>

using namespace std;
namespace ariel {
    class Card {
        int number;
        string type;


    public:
        Card(int num = 1, const string &type = "Hearts");

        int getCard() const;

        string cardName() const;

        string getType() const;

    };

}


#endif //CPP_HW2_CARD_HPP
