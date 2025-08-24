#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ROWS 99
#define MAX_COLS 99

typedef int board[MAX_ROWS + 1][MAX_COLS +1];

typedef struct position {
	int row, col;
} position;

typedef position positions[MAX_ROWS * MAX_COLS];

void add_position(int from_row, int from_col,
		  int to_row, int to_col,
		  int num_rows, int num_cols,
		  positions new_positions, int *num_new_positions,
		  board min_moves){
}


int find_distance(int knight_row, int knight_col,
		 int dest_row, int dest_col,
		 int num_rows, int num_cols){
	positions cur_positions, new_positions;
	int num_cur_positions, num_new_positions;
	int i, j, from_row, from_col;

	board min_moves;
	for (i = 1; i <= num_rows; i++){
		for (j = 1; j <= num_cols;j++){
			min_moves[i][j] = -1;
		}
	}
	min_moves[knight_row][knight_col] = 0;
	
	cur_positions[0] = (position){knight_row, knight_col};
	num_cur_positions = 1;

	while (num_cur_positions > 0){
		num_new_positions = 0;
		for (i = 0; i < num_cur_positions; i++){
			from_row = cur_positions[i].row;
			from_col = cur_positions[i].col;
			if (from_row == dest_row && from_col == dest_col){
				return min_moves[dest_row][dest_col];
			}
			add_position(from_row, from_col, from_row + 1, from_col + 2,
					num_rows, num_cols, new_positions,
					&num_new_positions, min_moves);
			add_position(from_row, from_col, from_row + 1, from_col - 2,
					num_rows, num_cols, new_positions,
					&num_new_positions, min_moves);
			add_position(from_row, from_col, from_row - 1, from_col + 2,
					num_rows, num_cols, new_positions,
					&num_new_positions, min_moves);
			add_position(from_row, from_col, from_row - 1, from_col - 2,
					num_rows, num_cols, new_positions,
					&num_new_positions, min_moves);
			add_position(from_row, from_col, from_row + 2, from_col + 1,
					num_rows, num_cols, new_positions,
					&num_new_positions, min_moves);
			add_position(from_row, from_col, from_row + 2, from_col - 1,
					num_rows, num_cols, new_positions,
					&num_new_positions, min_moves);
			add_position(from_row, from_col, from_row - 2, from_col + 1,
					num_rows, num_cols, new_positions,
					&num_new_positions, min_moves);
			add_position(from_row, from_col, from_row - 2, from_col - 1,
					num_rows, num_cols, new_positions,
					&num_new_positions, min_moves);
		}

		num_cur_positions = num_new_positions;
		for (i = 0; i < num_cur_positions; i++){
			cur_positions[i] = new_positions[i];
		}
	}
	return -1;
}
int main(void){
	return 0;
}
