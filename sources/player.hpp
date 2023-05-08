#ifndef CPP_HW2_PLAYER_HPP
#define CPP_HW2_PLAYER_HPP

#include "card.hpp"
#include <cstring>
#include <array>

const int numOfCards = 26;

using namespace std;
namespace ariel {
    class Player {
        array <Card, numOfCards> cards;
        int CardIndex = -1;
        int winnings = 0;
        int wins = 0;
        int losses = 0;
        string name;

    public:
        Player();

        explicit Player(const string& name);

        int stacksize() const;

        int cardesTaken() const;

        void updateWininngs(int num);

        array <Card, numOfCards> getArr() const;

        string getName() const;

        void usedCard();

        void setArr(array <Card, numOfCards> arr);

        int getWins() const;

        int getLosses() const;

        void addWin();

        void addLoss();
    };
}

#endif //CPP_HW2_PLAYER_HPP
