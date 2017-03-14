What each person did:

	We planned out and wrote most of the code together, side by side, one person coding at a time, the work
	evenly divided. Pamela started off the heuristics function. which was later improved by Sharon. Sharon 
	implemented the minimax function.

Documentation of progress:
	Week 1:
		Made AI work correctly
		Beat SimplePlayer
		Implemented function to return all moves for current player
		Implemented heuristics function
		Implemented minimax

	Week 2:
		Improved heuristics by accounting for edges
		Increased depth of minimax

Why our strategy will work:
	We went to office hours multiple times in order to make sure we were optimizing our minimax function and
	heuristic function, so we are confident in their performances. We also go to a minimax search depth of 4, 
	which is more than BetterPlayer, which goes to a depth of 3, so we are confident that our AI has a more
	comprehensive understanding of the best moves.

Ideas that were tried but did not work out:
	We tried to add mobility and frontier squares to our heuristic functions, but because we had to find all possible
	moves for every iteration of the heuristic function, which was called for every recursive call, the program was
	much too slow. We also ran into some bugs trying to implement these functions and felt that our functioning
	current code was better than our attempted improvements.