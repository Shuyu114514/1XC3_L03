#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

// ♔ ♕ ♖ ♗ ♘ ♙

/* ┌ └ ┐ ┘

├ ┤ ┬ ┴
 
─ │ ┼
 
 might need these...
 
 ╟ ╢ ╧ ╤
 
*/
void showBoard (int board[8][8]) {
	printf("\n\n╔════════╗\n");
	for (int i = 0; i < 8; i++) {
		printf("║"); 
	printf("\n\n┌─┬─┬─┬─┬─┬─┬─┬─┐\n");
	for (int i = 0; i < 8; i++) {
//		printf("│"); 
		bool flag = true;
		for (int j = 0; j < 8; j++) {
			if (!flag) {
				printf("│"); 
			}
			flag = false;
//			printf(""); 
			switch (board[i][j]) {
				case 0: 
					printf(" ");
					break;
				case 1:
					printf("♔");
					break;
				case 2: 
					printf("♕");
					break;
				case 3: 
					printf("♗");
					break;
				case 4: 
					printf("♘");
					break;
				case 5: 
					printf("♙");
			}
		}
		printf("║\n") ;
	}
	printf("╚════════╝\n");
		printf("│\n") ;
		if (i < 7) {
			printf("├─┼─┼─┼─┼─┼─┼─┼─┤\n") ;
		}
	}
	printf("└─┴─┴─┴─┴─┴─┴─┴─┘\n");
}


//bool memberOf (int *ValidMoves[2], int x, int y) ; 

void makeMove (char* input, int board[8][8]) {
	int start_y = input[0] - 48;
	int start_x = input[1] - 48;
	int end_y = input[3] - 48;
	int end_x = input[4] - 48;
	
	board[end_x][end_y] = board[start_x][start_y];
	board[start_x][start_y] = 0;
}

int main () {
	printf("Welcome to Terminal Chess!\n");
	printf("Initializing Board...\n")	;
	int board [8][8] = { {5, 4, 3, 2, 1, 3, 4, 5}
				             , {6, 6, 6, 6, 6, 6, 6, 6}
				 	           , {0, 0, 0, 0, 0, 0, 0, 0}
					           , {0, 0, 0, 0, 0, 0, 0, 0}
				             , {0, 0, 0, 0, 0, 0, 0, 0} 
				             , {0, 0, 0, 0, 0, 0, 0, 0}
				             , {6, 6, 6, 6, 6, 6, 6, 6}
				             , {5, 4, 3, 2, 1, 3, 4, 5}
				             } ;
  char buf[100];
  bool whitesMove = true;
	printf("Board Initialized!\n") ;
	
// 	showBoard(board);

  printf("Enter `q` to quit at any time.\n");
  printf("Moves are entered as co-ordinate pairs, such as \"13-33\" \n");
  do {
    bool flag = false; 
    showBoard(board);
    do {
	if (flag) {
		printf("Move Invalid! Try again!");
	}
    	if (whitesMove) {
      		printf("White to move.\n");
    	} else {
      		printf("Black to move.\n");
    	}
    	printf("♔ >> ");
	scanf("%s", buf);
	flag = true;
    } while (!isValidMove(buf, board) && buf[0] != 'q' && buf[0] != 'Q');
    makeMove(buf, board);
	whitesMove = !whitesMove;
  } while (buf[0] != 'q' && buf[0] != 'Q') ;
    
	printf("Terminating...\n") ;
}

bool isValidMove (int x1, int x2, int y1, int y2, int board[8][8]) {
	int xcheck = x1;
	int ycheck = y1;
	int piecesInWay = 0;
	if (board[x1][x2] == 0) {
		return false;
	} else if (board[x1][y2] == 1) { // king
		if (abs(x1 - x2) <= 1 && abs(y1-y2) <= 1) {
			return true;
		}
	} else if (board[x1][y2] == 2) { 
		// queen
	} else if (board[x1][y2] == 3) {  // bishop
		while (true) {
			xcheck += (x1 > x2)? -1 : 1;
			ycheck += (y1 > y2)? -1 : 1;
		 	if (xcheck < 0 || ycheck < 0 || xcheck > 7 || ycheck > 7) {
				break;
			}
			if (board[xcheck][ycheck] != 0) {
				piecesInWay += 1;
			} 
			if (piecesInWay == 2) {
				break;
			}
			if (xcheck == x2 && ycheck == y2) {
				return true;
			}
		}
	} else if (board[x1][y2] == 4) { 
		// knight
	} else if (board[x1][y2] == 5) { // Rook
		while (true) {
			if (y1 == y2) {
				xcheck += (x1 > x2)? -1 : 1;
			} else if (x1 == x2) {
				ycheck += (y1 > y2)? -1 : 1;
			} else {
				return false;
			}
			
		 	if (xcheck < 0 || ycheck < 0 || xcheck > 7 || ycheck > 7) {
				break;
			}
			if (board[xcheck][ycheck] != 0) {
				piecesInWay += 1;
			} 
			if (piecesInWay == 2) {
				break;
			}
			if (xcheck == x2 && ycheck == y2) {
				return true;
			}
		}
	} else if (board[x1][y2] == 6) { // Pawn
		//printf("Pawn Selected\n");
		//printf("Moving in column %d \n", y1);
		//printf("y1-y2=%d\n", x1-x2);
		if (x1 - x2 == 1 && y1 == y2) { // forward one
			printf("Detected forward move by 1\n");
			if (board[x2][y2] == 0) {
				return true;
			}
		} else if (x1 - x2 == 2 && y1 == y2) { // forward two
//			printf("Detected forward move by 2\n");
			if (board[x2][y2] == 0 && board[x2+1][y2] == 0 && x1 == 6) {
				return true;
			}
		} else if (abs(y1 - y2) == 1 && x1-x2 == 1) { // capture left or right
			//printf("Detected Capture\n");
			if (board[x2][y2] != 0) {
				return true;
			}
		}
	}
	return false;
}
