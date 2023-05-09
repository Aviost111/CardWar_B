#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <array>

#include "sources/player.hpp"
#include "sources/game.hpp"
#include "sources/card.hpp"

using namespace std;
using namespace ariel;

int main() {
    // Create two players with their names
    Player p1("Alice");
    Player p2("Bob");

    // Test Player functions
    cout << "Testing Player functions:" << endl;
    cout << "Player 1 name: " << p1.getName() << endl;
    cout << "Player 2 name: " << p2.getName() << endl;

    Card c1(7, "Diamonds");
    Card c2(4, "Clubs");
    Card c3(13, "Spades");
    Card c4(2, "Hearts");
    Card c5(10, "Diamonds");

    array<Card, numOfCards> cards1{c1, c2, c3, c4, c5};
    array<Card, numOfCards> cards2{c5, c4, c3, c2, c1};

    p1.setArr(cards1);
    p2.setArr(cards2);

    cout << "Player 1's card stack size: " << p1.stacksize() << endl;
    cout << "Player 2's cards taken: " << p2.cardesTaken() << endl;

    p1.usedCard();
    p2.usedCard();

    cout << "Player 1's card stack size after using a card: " << p1.stacksize() << endl;
    cout << "Player 2's card stack size after using a card: " << p2.stacksize() << endl;

    p1.addWin();
    p1.addLoss();
    p2.addWin();
    p2.addWin();

    cout << "Player 1's win count: " << p1.getWins()<< endl;
    cout << "Player 1's loss count: " << p1.getLosses()<< endl;
    cout << "Player 2's win count: " << p2.getWins()<< endl;
    cout << "Player 2's loss count: " << p2.getLosses() << endl;

    // Test Card functions
    cout << "\nTesting Card functions:" << endl;
    cout << "Number on card 1: " << c1.getCard() << endl;
    cout << "Type of card 2: " << c2.getType() << endl;
    cout << "Name of card 3: " << c3.cardName() << endl;

    // Test Game functions
    cout << "\nTesting Game functions:" << endl;
    Game game(p1, p2);

    for (int i = 0; i < 5; i++) {
        game.playTurn();
    }

    cout << "Printing last turn stats:" << endl;
    game.printLastTurn();

    cout << "\nPrinting all turns played:" << endl;
    game.printLog();

    cout << "\nPrinting game statistics:" << endl;
    game.printStats();

    cout << "\nPlaying all turns until the end of the game:" << endl;
    game.playAll();

    cout << "\nPrinting the name of the winning player:" << endl;
    game.printWiner();

    game.printLog();

    return 0;
}
