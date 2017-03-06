#include "player.hpp"

// small change

/*
 * Constructor for the player; initialize everything here. The side your AI is
 * on (BLACK or WHITE) is passed in as "side". The constructor must finish
 * within 30 seconds.
 */
 
//small change

Player::Player(Side playerSide) {
    // Will be set to true in test_minimax.cpp.
    testingMinimax = false;

    board = new Board();
    side = playerSide;
}

/*
 * Destructor for the player.
 */
Player::~Player() {
    delete board;
}

/**
 * 
 */
std::vector<Move*> Player::getLegalMoves() {
    std::vector<Move*> moves;
    
    if(board->hasMoves(side)) {
        for(int x = 0; x < 8; x++) {
            for(int y = 0; y < 8; y++) {
                if(!board->occupied(x, y)) {
                    Move *m = new Move(x, y);
                    if(board->checkMove(m, side))
                        moves.push_back(m);
                }
            }
        }
    }
    
    return moves;
}

/*
 * Compute the next move given the opponent's last move. Your AI is
 * expected to keep track of the board on its own. If this is the first move,
 * or if the opponent passed on the last move, then opponentsMove will be
 * nullptr.
 *
 * msLeft represents the time your AI has left for the total game, in
 * milliseconds. doMove() must take no longer than msLeft, or your AI will
 * be disqualified! An msLeft value of -1 indicates no time limit.
 *
 * The move returned must be legal; if there are no valid moves for your side,
 * return nullptr.
 */
Move *Player::doMove(Move *opponentsMove, int msLeft) {
    std::vector<Move*> moves = getLegalMoves();
    
    if(side == BLACK)
        board->doMove(opponentsMove, WHITE);
    else
        board->doMove(opponentsMove, BLACK);
    
    if(moves.size() == 0)
        return nullptr;
    
    return moves[rand() % moves.size()];
}
