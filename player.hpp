#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <iostream>
#include <vector>
#include <limits>
#include "common.hpp"
#include "board.hpp"
using namespace std;

class Player {

private:
    Side side;
    Side other;

public:
    Board *board;
    Player(Side playerSide);
    ~Player();

    int heuristics(Board *board);
    int score(Board *board, int level);
    Move *doMove(Move *opponentsMove, int msLeft);

    // Flag to tell if the player is running within the test_minimax context
    bool testingMinimax;
};

#endif
