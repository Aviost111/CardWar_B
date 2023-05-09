#include "player.hpp"
#include <stdexcept>
#include <cstring>

#define NUM_OF_CARDS 26

using namespace ariel;
using namespace std;

namespace ariel {
    Player::Player() {
        this->name = "avi";
    }

    Player::Player(const string& name) {
        if (name.empty()) {
            throw invalid_argument("you did not enter a name");
        }
        this->name = name;
    }

    int Player::cardesTaken() const {
        return this->winnings;
    }

    int Player::stacksize() const {
        return this->CardIndex + 1;
    }

    array<Card, NUM_OF_CARDS> Player::getArr() const {
        return this->cards;
    }

    string Player::getName() const {
        return this->name;
    }

    void Player::updateWininngs(int num) {
        this->winnings += num;
    }

    void Player::setArr(array<Card, 26> arr) {
        for (int i = 0; i < 26; i++) {
            this->cards[(unsigned int) i] = arr[(unsigned int) i];
            this->CardIndex++;
        }

    }
    void Player::usedCard() {
        this->CardIndex--;
    }
    int Player::getWins() const { return this->wins; }

    int Player::getLosses() const { return this->losses; }

    void Player::addWin() { this->wins++; }

    void Player::addLoss() { this->losses++; }

    void Player::resetPlayer() {
        this->CardIndex = -1;
        this->winnings = 0;
        this->wins = 0;
        this->losses = 0;
    }
}
