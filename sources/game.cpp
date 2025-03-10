#include "game.hpp"
#include <stdexcept>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <random>
#include <array>

#define DECK_SIZE 52

using namespace ariel;
using namespace std;

namespace ariel {

    //why const ?is it even ok?
    Game::Game(ariel::Player &player1, ariel::Player &player2) :
            player1(player1), player2(player2) {
        //reset player if was touched
        player1.resetPlayer();
        player2.resetPlayer();
        //create an array of indexes
        int indexes[DECK_SIZE];
        //we want to shuffle a deck later, so we create the deck before shuffle and the deck for after
        array<Card, DECK_SIZE> deckSrc;
        array<Card, DECK_SIZE> deckDst;
        //fill first deck
        for (int i = 0; i < 13; i++) {
            deckSrc[(unsigned int) (i * 4)] = Card(i + 1, "Hearts");
            deckSrc[(unsigned int) (i * 4) + 1] = Card(i + 1, "Spades");
            deckSrc[(unsigned int) (i * 4) + 2] = Card(i + 1, "Diamonds");
            deckSrc[(unsigned int) (i * 4) + 3] = Card(i + 1, "Clubs");
        }
        //fill array of indexes
        for (int i = 0; i < DECK_SIZE; i++) {
            indexes[(unsigned int) i] = i;
        }
        //shuffle indexes
        shuffle(indexes, indexes + 52, std::mt19937(std::random_device()()));
        //use the shuffled indexes to create the shuffled deck
        for (int i = 0; i < DECK_SIZE; i++) {
            deckDst[(unsigned int) i] = deckSrc[(unsigned int) indexes[(unsigned int) i]];
        }
        //split the decks
        array<Card, DECK_SIZE / 2> p1Deck;
        array<Card, DECK_SIZE / 2> p2Deck;
        for (int i = 0; i < 26; ++i) {
            p1Deck[(unsigned int) i] = deckDst[(unsigned int) i];
            p2Deck[(unsigned int) i] = deckDst[(unsigned int) i + 26];
        }
        this->player1 = player1;
        this->player2 = player2;
        this->player1.setArr(p1Deck);
        this->player2.setArr(p2Deck);
        for (int i = 0; i < 26; i++) {
            log[(unsigned int) i] = "";
        }
        this->turn = 0;
        this->draws=0;
    }

    void Game::playAll() {
        if (this->player1.stacksize() == 0) {
            throw runtime_error("the game is over");
        }
        while (this->player1.stacksize() != 0) {
            this->playTurn();
        }
    }

    void Game::playTurn() {
        if (player1.stacksize() == 0) {
            throw runtime_error("Game ended");
        }
        if (&player1 == &player2) {
            throw invalid_argument("same player");
        }
        //draw cards
        Card card1 = player1.getArr()[(unsigned int) player1.stacksize() - 1];
        Card card2 = player2.getArr()[(unsigned int) player2.stacksize() - 1];
        player1.usedCard();
        player2.usedCard();
        int numOfCards = 2;
        string result;
        while (true) {
            //add the draws to our result
            result += this->player1.getName() + " played " + card1.cardName() + " of " + card1.getType() +
                      " " + player2.getName() + " played " + card2.cardName() + " of " + card2.getType() + ". ";
            string endResult;
            //if p1 wins add that to result and update stats and finish turn
            if (card1.getCard() > card2.getCard() || (card1.getCard() == 2 && card2.getCard() == 14)) {
                endResult = result + this->player1.getName() + " wins.";
                player1.updateWininngs(numOfCards);
                this->log[(unsigned int) this->turn] = endResult;
                this->turn++;
                this->player2.addLoss();
                this->player1.addWin();
                return;
                //if p2 wins add that to result and update stats and finish turn
            } else if (card1.getCard() < card2.getCard() || (card2.getCard() == 2 && card1.getCard() == 14)) {
                endResult = result + " " + this->player2.getName() + " wins.";
                player2.updateWininngs(numOfCards);
                this->log[(unsigned int) this->turn] = endResult;
                this->player1.addLoss();
                this->player2.addWin();
                this->turn++;
                return;
            }
            //else it's a draw
            this->draws++;
            cout<<"there are "<<this->draws<<" draws"<<endl;
            //if the players have 1 or fewer cards left, just split it
            if ((player1.stacksize() == 1) || (player1.stacksize() == 0)) {
                if (player1.stacksize() == 1) {
                    player1.usedCard();
                    player2.usedCard();
                    numOfCards += 2;
                }
                result += " draw.";
                log[(unsigned int) this->turn] = result;
                player1.updateWininngs(numOfCards / 2);
                player2.updateWininngs(numOfCards / 2);
                break;
            }
            //use a card face down and a card face up and restart the loop
            player1.usedCard();
            player2.usedCard();
            card1 = player1.getArr()[(unsigned int) player1.stacksize() - 1];
            card2 = player2.getArr()[(unsigned int) player2.stacksize() - 1];
            player1.usedCard();
            player2.usedCard();
            numOfCards += 4;
            result += " draw.";
        }

    }

    void Game::printLastTurn() const {
        if (this->turn == 0) {
            throw runtime_error("There is no previous turn");
        }
        cout << this->log[(unsigned int) this->turn - 1] << endl;
    }

    void Game::printLog() {
        int i = 0;
        //no turns were played
        if (log[(unsigned int) i].empty()) {
            throw runtime_error("no turns were played");
        }
        while ((!log[(unsigned int) i].empty()) && (i < 26)) {
            cout << log[(unsigned int) i] << endl;
            i++;
        }
    }

    void Game::printStats() {
        if (this->turn > 0) {
            cout << player1.getName() << ":" << endl;
            cout << " win rate-" << int((double(player1.getWins()) / (this->turn)) * 100) << "%" << endl;
            cout << " cards won-" << player1.cardesTaken() << endl << endl;
            cout << player2.getName() << ":" << endl;
            cout << " win rate-" << int((double(player2.getWins()) / (this->turn)) * 100) << "%" << endl;
            cout << " cards won-" << player2.cardesTaken() << endl << endl;
            cout << "draw rate-" << int(double(this->draws) / (this->turn) * 100) << "%" << endl;
        } else {
            cout << player1.getName() << ":" << endl;
            cout << " win rate-" << 0 << endl;
            cout << " cards won-" << player1.cardesTaken() << endl << endl;
            cout << player2.getName() << ":" << endl;
            cout << " win rate-" << 0 << endl;
            cout << " cards won-" << player2.cardesTaken() << endl << endl;
            cout << "draw rate-" << 0 << endl;
        }
        cout << "There were a total of " << this->draws << " draws" << endl;
    }

    void Game::printWiner() {
        if (this->player1.stacksize() > 0) {
            cout << "the game isn't over" << endl;
        } else if (this->player1.cardesTaken() > this->player2.cardesTaken()) {
            cout << player1.getName() << " is the winner" << endl;
        } else if (this->player1.cardesTaken() < this->player2.cardesTaken()) {
            cout << player2.getName() << " is the winner" << endl;
        } else {
            cout << "no winner" << endl;
        }
    }

    int Game::getDraws() const {
        return this->draws;
    }

}
