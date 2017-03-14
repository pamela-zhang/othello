#include "player.hpp"

/*
 * Constructor for the player; initialize everything here. The side your AI is
 * on (BLACK or WHITE) is passed in as "side". The constructor must finish
 * within 30 seconds.
 */
Player::Player(Side playerSide) {
    // Will be set to true in test_minimax.cpp.
    testingMinimax = false;

    board = new Board();
    side = playerSide;
    other = (side == BLACK) ? WHITE : BLACK;
}

/*
 * Destructor for the player.
 */
Player::~Player() {
    delete board;
}

/*
 * Return the heuristic score, given a board position.
 */
int Player::heuristics(Board *board) {
    int score, cornerMultiplier, badCornerMultiplier, edgeMultiplier;
    
    // basic score = difference in piece count
    score = board->count(side) - board->count(other);
    
    if(testingMinimax)
        return score;
    
    // take into account the difference in corner piece count
    int sideCorners = 0, otherCorners = 0;
    int sideBadCorners = 0, otherBadCorners = 0;
    int sideEdges = 0, otherEdges = 0;
    for(int i = 0; i <= 7; i += 7) {
        for(int j = 0; j <= 7; j += 7) {
            if(board->get(side, i, j))
                sideCorners++;
            else if(board->get(other, i, j))
				otherCorners++;
        }
    }
    for(int i = 1; i <= 6; i += 5) {
        for(int j = 1; j <= 6; j += 5) {
            if(board->get(side, i, j))
                sideBadCorners++;
            else if(board->get(other, i, j))
				otherBadCorners++;
        }
    }
    for(int i = 0; i <= 7; i += 7) {
        for(int j = 2; j <= 5; j++) {
            if(board->get(side, i, j))
                sideEdges++;
            else if(board->get(other, i, j))
				otherEdges++;
        }
    }
    for(int i = 2; i <= 5; i++) {
        for(int j = 0; j <= 7; j += 7) {
            if(board->get(side, i, j))
                sideEdges++;
            else if(board->get(other, i, j))
				otherEdges++;
        }
    }
    
    cornerMultiplier = 2000 * (sideCorners - otherCorners);
	badCornerMultiplier = (-1) * 50 * (sideBadCorners - otherBadCorners);
	edgeMultiplier = 20 * (sideEdges - otherEdges);
    return score + cornerMultiplier + badCornerMultiplier + edgeMultiplier;
}

/*
 * Returns the minimax score, given the board and a tree level.
 */
int Player::score(Board *board, int level) {
    Side curr;
    if(level % 2 == 0)
        curr = side;
    else
        curr = other;
    
    std::vector<Move*> moves;
    moves = board->getLegalMoves(curr);
    
    if(moves.size() == 0)
        return heuristics(board);
    
    std::vector<int> scores;
    for(int i = 0; i < (int) moves.size(); i++) {
        int s = heuristics(board);
        Board *boardCopy = board->copy();
        boardCopy->doMove(moves[i], curr);
        if(level < 4)
            s = score(boardCopy, level + 1);
        scores.push_back(s);
    }
    
    //if level is even, return max of scores
    if(level % 2 == 0) {
        int max = 0;
        for(int i = 0; i < (int) scores.size(); i++) {
            if(scores[i] >= scores[max])
                max = i;
        }
        return scores[max];
    }
    //if level is odd, return min of scores
    else {
        int min = 0;
        for(int i = 0; i < (int) scores.size(); i++) {
            if(scores[i] <= scores[min])
                min = i;
        }
        return scores[min];
    }
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
    board->doMove(opponentsMove, other);
    
    // get possible moves
    std::vector<Move*> moves = board->getLegalMoves(side);    
    if(moves.size() == 0)
        return nullptr;
    
    // get scores for each move
    std::vector<int> scores;
    for(int i = 0; i < (int) moves.size(); i++) {
        Board *boardCopy = board->copy();
        boardCopy->doMove(moves[i], side);
        scores.push_back(score(boardCopy, 1));
    }
    
    // find the move that maximizes score
    int max = 0;
    for(int i = 1; i < (int) moves.size(); i++) {
        if(scores[i] >= scores[max])
            max = i;
    }
    
    // PRINT MOVES & SCORES
    /*
    fprintf(stderr, "Possible moves:\n");
    for(int i = 0; i < (int) moves.size(); i++)
        fprintf(stderr, "(%i, %i): %i; ", moves[i]->getX(), moves[i]->getY(), scores[i]);
    fprintf(stderr, "\nChose move (%i, %i)\n", moves[max]->getX(), moves[max]->getY());
    */
    
    board->doMove(moves[max], side);
    return moves[max];
}
