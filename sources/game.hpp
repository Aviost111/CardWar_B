#ifndef CPP_HW2_GAME_HPP
#define CPP_HW2_GAME_HPP

#include "player.hpp"
#include <cstring>
#include <array>
const int MaxTurns=26;

using namespace std;
namespace ariel {
    class Game {
        Player& player1;
        Player& player2;
        array<string ,MaxTurns> log;
        int turn;
        int draws;


    public:
        Game(Player &player1,Player &player2);

        void playTurn();

        void playAll();

        void printWiner();

        void printLog();

        void printStats();

        void printLastTurn() const;
        int getDraws() const;
    };
}

#endif //CPP_HW2_GAME_HPP
