#include "doctest.h"
#include <stdexcept>
#include "sources/player.hpp"
#include "sources/game.hpp"
#include "sources/card.hpp"
using namespace std;
using namespace ariel;

TEST_CASE("The amount of cards before starting a game")
{
    Player p1("Alice");
    Player p2("Bob");

    CHECK(p1.stacksize() == 0);
    CHECK(p2.stacksize() == 0);
    CHECK(p1.cardesTaken() == 0);
    CHECK(p2.cardesTaken() == 0);
}

TEST_CASE("The amount of cards after starting a game")
{
    Player p1("Alice");
    Player p2("Bob");
    Game game(p1, p2);

    CHECK(p1.stacksize() == 26);
    CHECK(p2.stacksize() == 26);
    CHECK(p1.cardesTaken() == 0);
    CHECK(p2.cardesTaken() == 0);
}

TEST_CASE("The card scheme at the end of the game")
{
    Player p1("Alice");
    Player p2("Bob");
    Game game(p1, p2);
    game.playAll();
    int sum = p1.stacksize() + p1.cardesTaken() + p2.stacksize() + p2.cardesTaken();
    CHECK(sum == 52);
}

TEST_CASE("Throwing errors from the functions")
{
    Player p1("Alice");
    Player p2("Bob");
    Game game(p1, p2);
    for (int i = 0; i < 5; i++)
    {
        game.playTurn();
    }
    CHECK_NOTHROW(game.printLastTurn());
    CHECK_NOTHROW(game.printLog());
    CHECK_NOTHROW(game.printStats());
    CHECK_NOTHROW(game.printWiner());
}

TEST_CASE("Activating another turn after the game is over")
{
    Player p1("Alice");
    Player p2("Bob");
    Game game(p1, p2);
    game.playAll();
    CHECK(p1.stacksize() == 0);
    CHECK(p2.stacksize() == 0);
    CHECK_THROWS(game.playTurn());
}

TEST_CASE("One player")
{
    Player p1("Alice");
    Game game(p1, p1);
    CHECK_THROWS(game.playTurn());
}

TEST_CASE("Printing the winner")
{
    Player p1("Alice");
    Player p2("Bob");
    Game game(p1, p2);
    game.playAll();

    CHECK_NOTHROW(game.printWiner());
}

TEST_CASE("The game ends after at most 26 turns")
{
    Player p1("Alice");
    Player p2("Bob");
    Game game(p1, p2);
    int maxTurns = 26;
    int i = 0;
    for (; i < 26 && p1.stacksize() > 0; i++) {
        game.playTurn();
    }
    CHECK(maxTurns >= i);
    CHECK(p1.stacksize() == 0);
    CHECK(p2.stacksize() == 0);
}
TEST_CASE("illegal player") {
    CHECK_THROWS(Player(""));

}

TEST_CASE("no turns left") {
    Player p1("Alice");
    Player p2("Bob");
    Game game(p1, p2);
    CHECK_NOTHROW(game.playTurn());
    CHECK_NOTHROW(game.playAll());
    CHECK_THROWS(game.playTurn());
    CHECK_THROWS(game.playAll());

}

TEST_CASE("no previous turn/has previous turn") {
    Player p1("Alice");
    Player p2("Bob");
    Game game(p1, p2);
    CHECK_THROWS(game.printLastTurn());
    CHECK_THROWS(game.printLog());
    game.playTurn();
    CHECK_NOTHROW(game.printLastTurn());
    CHECK_NOTHROW(game.printLog());
}

TEST_CASE("game over/not over") {
    Player p1("Alice");
    Player p2("Bob");
    Game game(p1, p2);
    game.playTurn();
    game.playAll();
    CHECK_NOTHROW(game.printWiner());
}
//10

TEST_CASE("cards taken") {
    Player p1("Alice");
    Player p2("Bob");
    Game game(p1, p2);
    game.playTurn();
    CHECK((p2.cardesTaken() != p1.cardesTaken()));
}
//19

TEST_CASE("stats works") {
    Player p1("Alice");
    Player p2("Bob");
    Game game(p1, p2);
    CHECK_NOTHROW(game.printStats());
    game.playTurn();
    CHECK_NOTHROW(game.printStats());
}


