#ifndef CPP_HW2_PLAYER_HPP
#define CPP_HW2_PLAYER_HPP

#include "card.hpp"
#include <cstring>
#include <array>

const int numOfCards = 26;

using namespace std;
namespace ariel {
    class Player {
        array<Card, numOfCards> cards;
        int CardIndex = -1;
        int winnings = 0;
        int wins=0;
        int losses=0;
        string name;

    public:
        Player();

        explicit Player(string name);

        int stacksize() const;

        int cardesTaken() const;

        void updateWininngs(int num);

        array<Card, numOfCards> getArr() const;

        string getName() const;

        void usedCard(){
            this->CardIndex--;
        }

        void setArr(array<Card,numOfCards>arr);

        int getWinnings() const;

        int getWins() const;
        int getLosses() const;
        void addWin(){this.wins++;}
        void addLoss(){this.lossses++;}
    };
}

#endif //CPP_HW2_PLAYER_HPP
