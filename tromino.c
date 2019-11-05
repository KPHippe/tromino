#include <stdio.h>
#include <stdlib.h>
#include <time.h> 

int trominoNum = 0;


void solve(int boardSize, int xMisisng, int yMissing, int curX, int curY, int curSize, int (*board)[boardSize]);
void printMatrix(int coloumn, int (*board)[coloumn]);

int main(int argc, char *args[]){
    int size = 16;
	int board [size][size];
	int xMissing = 0, yMissing = size-2; 
	clock_t start, end; 
	double totalTime;

	board[xMissing][yMissing] = -1;

	start = clock();
    solve(size, xMissing, yMissing, 0,0, size, board);
	end = clock();
	totalTime = ((double) (end - start)) / CLOCKS_PER_SEC; 

    printMatrix(size, board);
	printf("Time: %f\n", totalTime);

}

//board size is total board size
//xMissing, yMissing, are coordinates of missing square
//curX curY are coordinates of subsections (0,0)
//curSize is the size of the current sub-board
//board is the overall representation of the board
void solve(int boardSize, int xMisisng, int yMissing, int curX, int curY, int curSize, int (*board)[boardSize]){
    //base case
	int tilePoint[2] = {0,0};
	char* tileName; 
    if (curSize == 2){
        int i,j;
        trominoNum++;
        for(i = curX; i < (curX + curSize); i++){
            for(j = curY; j < (curY + curSize);j++){
                
                if(!(i == xMisisng && j == yMissing)){//fix for missing coordinates
                    //printf("inside solve \n");
                    board[i][j] = trominoNum;
                }
				
            }
        }
		//notation for board
		tilePoint[0] = curX + 1;
		tilePoint[1] = boardSize - curY -1;
		if(curX == xMisisng && curY == yMissing){ //for LR Tromino
			tileName = "LR";
		}
		else if(curX + 1 == xMisisng && curY == yMissing){ //for UR Tromino
			tileName = "UR";
		}
		else if(curX == xMisisng && curY + 1 == yMissing){// for LL Tromino
			tileName = "LL";
		}
		else if(curX + 1 == xMisisng && curY + 1 == yMissing){// for UL Tromino
			tileName = "UL";
		}

	//print this tile to the console
	printf("(%-2d,%-2d) %s\n", tilePoint[0], tilePoint[1], tileName);
    return;

    }

    
    /* 
     * Divide and conquer below here
    */
    //check for missing square, and if there is none, put one there
    trominoNum++;
	int halfSize=curSize/2,xCenter,yCenter;
	int xUR ,yUR,  xUL ,yUL, xLR ,yLR,  xLL ,yLL;
	xCenter=curX+halfSize;
	yCenter=curY+halfSize;
	tilePoint[0] = xCenter;
	tilePoint[1] = yCenter;
	
	if(xMisisng <xCenter && yMissing< yCenter){ // checking that hole in the first quad, if yes than put solve in center opposite quad.
		board[xCenter-1][yCenter]= trominoNum;
		board[xCenter][yCenter-1]= trominoNum;
		board[xCenter][yCenter]=trominoNum;
		
		xUL =xMisisng;
		yUL=yMissing;

		xUR =xCenter-1; 
		yUR=yCenter;

		xLL =xCenter; 
		yLL=yCenter-1;

		xLR =xCenter; 
		yLR=yCenter;

		tileName = "LR";

	}
    else if(xMisisng <xCenter && yMissing>=yCenter){ // checking that hole in the second quad, if yes than put solve in center opposite quad.
		board[xCenter-1][yCenter-1]= trominoNum;
		board[xCenter][yCenter-1]= trominoNum;
		board[xCenter][yCenter]=trominoNum;

		xUL =xCenter-1;
		yUL=yCenter-1;

		xUR =xMisisng; 
		yUR=yMissing;

		xLL =xCenter; 
		yLL= yCenter-1;

		xLR  = xCenter ; 
		yLR = yCenter;

		tileName = "LL";
	}
    else if(xMisisng >=xCenter && yMissing<yCenter){ // checking that hole in the third quad, if yes than put solve in center opposite quad.
		board[xCenter-1][yCenter-1]= trominoNum;
		board[xCenter-1][yCenter]= trominoNum;
		board[xCenter][yCenter]= trominoNum;

		xUL =xCenter-1;
        yUL=yCenter-1;

		xUR =xCenter-1;
        yUR=yCenter;

		xLL =xMisisng;
        yLL=yMissing;

		xLR =xCenter;
        yLR=yCenter;

		tileName = "UR";
	}
    else if(xMisisng >=xCenter && yMissing>=yCenter){ // checking that hole in the fourth quad, if yes than put solve in center opposite quad.
		board[xCenter-1][yCenter-1]= trominoNum;
		board[xCenter-1][yCenter]= trominoNum;
		board[xCenter][yCenter-1]= trominoNum;

		xUL =xCenter-1;
		yUL=yCenter-1;

		xUR =xCenter-1; 
		yUR=yCenter;

		xLL =xCenter; 
		yLL=yCenter-1;

		xLR =xMisisng ; 
		yLR=yMissing;

		tileName = "UL";
	}

	//print non base case tile 
	printf("(%-2d,%-2d) %s\n", tilePoint[0], tilePoint[1], tileName);	

    //recurse over each quadrant
	solve(boardSize,xUL , yUL, curX,curY,halfSize,board); // recursive call to the first quadrant
	solve(boardSize,xUR , yUR, curX,curY+halfSize,halfSize,board); // recursive call to the second quadrant
	solve(boardSize,xLR , yLR, curX+halfSize,curY+halfSize,halfSize,board); // recursive call to the third quadrant
	solve(boardSize,xLL , yLL, curX+halfSize,curY,halfSize,board); // recursive call to the fourth quadrant
}

void printMatrix(int size, int (*board)[size]){ // printing the matrix
	int i,j; 
	printf("\n* * * * * * * * * * * * * * * *\n");
	for (i = 0; i < size;i++){
		for ( j = 0; j < size;j++){

				if(board[i][j]==(-1)){
					printf("%-2s ", "X");
				}
                else{
					printf("%-2d ", board[i][j]);
				}

			}
		printf("\n");		
	}
	printf("\n");

}
