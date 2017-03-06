#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <iostream>
#include <vector>
#include "common.hpp"
#include "board.hpp"
#include <limits>
using namespace std;

class Player {

private:
    Side side;
    double **heu = new double *[8];

public:
    Board *board;
    Player(Side playerSide);
    ~Player();

    Move *doMove(Move *opponentsMove, int msLeft);

    // Flag to tell if the player is running within the test_minimax context
    bool testingMinimax;
};

#endif
