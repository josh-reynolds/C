#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 200

double min(double v1, double v2){
	if (v1 < v2){
		return v1;
	} else {
		return v2;
	}
}

double solve_k(int num[], double price[], int num_schemes,
		double unit_price, int num_items){
	double best, result;
	int i;
	if (num_items == 0){
		return 0;
	} else {
		result = solve_k(num, price, num_schemes, unit_price,
				num_items - 1);
		best = result + unit_price;
		for (i = 0; i < num_schemes; i++){
			if (num_items - num[i] >= 0){
				result = solve_k(num, price, num_schemes,
						unit_price, num_items - num[i]);
				best = min(best, result + price[i]);
			}
		}
		return best;
	}
}

double solve(int num[], double price[], int num_schemes,
		double unit_price, int num_items){
	double best;
	int i;
	best = solve_k(num, price, num_schemes, unit_price, num_items);
	for (i = num_items + 1; i < SIZE; i++){
		best = min(best, solve_k(num, price, num_schemes,
					unit_price, i));
	}
	return best;
}

int main(void){
	return 0;
}
