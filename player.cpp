#include "player.hpp"
#include <limits>
#include <iostream>

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
    
    for(int i = 0; i < 8; i++)
    {
		heu[i] = new double[8];
	}
    
    for(int x = 0; x < 8; x++)
    {
		for(int y = 0; y < 8; y++)
		{
			heu[x][y] = 1;
		}
	}
    heu[0][0] = std::numeric_limits<double>::infinity();
    heu[0][7] = std::numeric_limits<double>::infinity();
    heu[7][7] = std::numeric_limits<double>::infinity();
    heu[7][0] = std::numeric_limits<double>::infinity();
    
    heu[1][1] = (-1) * std::numeric_limits<double>::infinity();
    heu[1][6] = (-1) * std::numeric_limits<double>::infinity();
    heu[6][1] = (-1) * std::numeric_limits<double>::infinity();
    heu[6][6] = (-1) * std::numeric_limits<double>::infinity();
    heu[0][1] = -4;
    heu[1][0] = -4;
    heu[6][0] = -4;
    heu[7][1] = -4;
    heu[7][6] = -4;
    heu[6][7] = -4;
    heu[0][6] = -4;
    heu[1][7] = -4;
    
    for(int x = 0; x < 8; x++)
    {
		for(int y = 0; y < 8; y++)
		{
			if((x == 0 || x == 7) && y >=2 && y <=5)
			{
				heu[x][y] = 4;
			}
			else if((y == 0 || y == 7) && x >=2 && x <=5)
			{
				heu[x][y] = 4;
			}
		}
	}
}

/*
 * Destructor for the player.
 */
Player::~Player() {
    delete board;
    for(int i = 0; i < 8; i++)
    {
		delete[] heu[i];
	}
	delete[] heu;
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
	/*
	//1st task: just make AI work
    if(side == BLACK)
        board->doMove(opponentsMove, WHITE);
    else
        board->doMove(opponentsMove, BLACK);
    
    std::vector<Move*> moves = getLegalMoves(side);
    
    if(moves.size() == 0)
        return nullptr;
    
    int random = rand() % moves.size();
    
    board->doMove(moves[random], side);
    return moves[random];
    */
    
    //2nd task: make AI consistently beat SimplePlayer
    /*
    if(side == BLACK)
        board->doMove(opponentsMove, WHITE);
    else
        board->doMove(opponentsMove, BLACK);
    
    std::vector<Move*> moves = getLegalMoves(side);
    
    if(moves.size() == 0)
        return nullptr;
    int max = 0;
    for(int i = 0; i < (int) moves.size(); i++)
    {
		if(heu[moves[i]->getX()][moves[i]->getY()] >= heu[moves[max]->getX()][moves[max]->getY()])
			max = i;
	}
	board->doMove(moves[max], side);
	return moves[max];
    */
    
    //3rd task: implement minimax algorithm
    Side other = (side == BLACK) ? WHITE : BLACK;
    board->doMove(opponentsMove, other);
    
    std::vector<Move*> moves = board->getLegalMoves(side);
    
    if(moves.size() == 0)
        return nullptr;

    std::vector<double> minScores;
    
    for(int i = 0; i < (int) moves.size(); i++)
    {
        // make move on a copy of the board
        Board *boardCopy = board->copy();
        boardCopy->doMove(moves[i], side);
        
        double min = 0;
        double minScore = std::numeric_limits<double>::infinity();
        // loop through opponent's possible moves
        std::vector<Move*> opponentMoves = boardCopy->getLegalMoves(other);
        for(int j = 0; j < (int) opponentMoves.size(); j++)
        {
            Board *boardCopy2 = boardCopy->copy();
            boardCopy2->doMove(opponentMoves[j], other);
            double score = boardCopy2->count(side) - boardCopy2->count(other);
            //score *= heu[moves[i]->getX()][moves[i]->getY()];
            
            if(score <= minScore)
            {
                min = j;
                minScore = score;
            }
        }
        
        minScores.push_back(minScore);
	}
    
    int minimax = 0;
    for(int i = 0; i < (int) minScores.size(); i++)
    {
        if(minScores[i] >= minScores[minimax])
            minimax = i;
    }
    
	board->doMove(moves[minimax], side);
	return moves[minimax];
}
