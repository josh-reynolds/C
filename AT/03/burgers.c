#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int max(int v1, int v2){
	if (v1 > v2){
		return v1;
	} else {
		return v2;
	}
}

int solve_t(int m, int n, int t){
	int first, second;
	if (t == 0){
		return 0;
	}

	if (t >= m){
		first = solve_t(m, n, t - m);
	} else {
		first = -1;
	}

	if (t >= n){
		second = solve_t(m, n, t - n);
	} else {
		second = -1;
	}

	if (first == -1 && second == -1){
		return -1;
	} else {
		return max(first, second) + 1;
	}
}

int main(void){
	return 0;
}

