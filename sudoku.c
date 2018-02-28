#include <stdio.h>
#include <stdbool.h>

#define ROW 9
#define COL 9
#define FIRST 0

void create_puzzle(char *fileName, int puzzle[ROW][COL]);
void print_puzzle(int puzzle[ROW][COL]);
void solve_puzzle(int puzzle[ROW][COL], int row, int col);
bool checkValid(int puzzle[ROW][COL], int row, int col, int val);
void getQuadrant(int row, int col, int *rArea, int *cArea);

int main (int argc, char *argv[]) {
	int puzzle[ROW][COL];
	create_puzzle(argv[1], puzzle);
	print_puzzle(puzzle);
	solve_puzzle(puzzle, FIRST, FIRST);
	print_puzzle(puzzle);
    
	return 0;
}

void create_puzzle(char *fileName, int puzzle[ROW][ROW]) {
	FILE *fp;
	fp = fopen(fileName, "r");
	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COL; j++) {
			fscanf(fp, "%1d", &puzzle[i][j]);
		}
	}
	fclose(fp);
}

void print_puzzle(int puzzle[ROW][COL]) {
	printf("------------------------------------\n");
	for (int i = 0; i < ROW; i++) {
		printf("|");
		for (int j = 0; j < COL; j++) {
			printf(" %d ", puzzle[i][j]);
			if ((j + 1) % 3 == 0) {
				printf(" | ");
			}
		}
		printf("\n");
		if ((i + 1) % 3 == 0){
			printf("------------------------------------\n");
		}
		
   }
}

void solve_puzzle(int puzzle[ROW][COL], int row, int col) {
	if (puzzle[row][col] == 0) {
		int val = 1;
		while (val <= 9) {
			if (checkValid(puzzle, row, col, val)) {
				puzzle[row][col] = val;
				if (col == 8) {
					solve_puzzle(puzzle, row +1, 0);
				} else {
					solve_puzzle(puzzle, row, col + 1);
				}
			}
			printf(" %d ", val);
			val++;
		}
		
	} else if (col == 8) {
		solve_puzzle(puzzle, row +1, 0);
	} else {
		solve_puzzle(puzzle, row, col + 1);
	}
		
}
		


bool checkValid(int puzzle[ROW][COL], int row, int col, int val) {
	int rArea, cArea;
	getQuadrant(row, col, &rArea, &cArea);
	//printf("%d %d", rArea, cArea);
	
	for (int i = 0; i < 9; i++) {
		if (val == puzzle[i][col] && i != row) {
			//printf("FUCK");
			return false;
		} else if (val == puzzle[row][i] && i != col) {
			return false;
		}
	}
	
	for (int j = rArea; j < rArea + 3; j++) {
		for(int k = cArea; k < cArea + 3; k++) {
			if (val == puzzle[j][k] && (j != row && k != col)) {
					return false;
			}
		}
	} 
	//printf("TRUE");
	return true;
}

void getQuadrant(int row, int col, int *rArea, int *cArea) {
	switch(row) {
		case 0:
		case 1:
		case 2:
			*rArea = 0;
			break;
		case 3:
		case 4:
		case 5:
			*rArea = 3;
			break;
		case 6:
		case 7:
		case 8:
			*rArea = 6;
			break;
		default:
			printf("Error in getting quadrant row");
			
	}
	
	switch(col) {
		case 0:
		case 1:
		case 2:
			*cArea = 0;
			break;
		case 3:
		case 4:
		case 5:
			*cArea = 3;
			break;
		case 6:
		case 7:
		case 8:
			*cArea = 6;
			break;
		default:
			printf("Error in getting quadrant column");
			printf("%d", col);
			printf("%d", *cArea);
	}
	
}











