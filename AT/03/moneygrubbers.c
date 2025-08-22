#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 200
#define MAX_SCHEMES 20

double min(double v1, double v2){
	if (v1 < v2){
		return v1;
	} else {
		return v2;
	}
}

double solve_k(int num[], double price[], int num_schemes,
		double unit_price, int num_items, double memo[]){
	//printf("Entering solve_k()\n");
	//printf("num_items = %d\n", num_items);
	double best, result;
	int i;
	//exit(0);
	if (memo[num_items] != -1){
		return memo[num_items];
	}
	if (num_items == 0){
		//printf("Exiting solve_k()\n");
		memo[num_items] = 0;
		return memo[num_items];
	} else {
		//printf("Non-zero num_items\n");
		result = solve_k(num, price, num_schemes, unit_price,
				num_items - 1, memo);
		best = result + unit_price;
		for (i = 0; i < num_schemes; i++){
			if (num_items - num[i] >= 0){
				//printf("Reentering solve_k()\n");
				//printf("next num_items = %d\n", (num_items - num[i]));
				//exit(0);
				result = solve_k(num, price, num_schemes,
						unit_price, num_items - num[i], memo);
				//printf("Result = %f\n", result);
				best = min(best, result + price[i]);
			}
		}
		//printf("Exiting solve_k()\n");
		memo[num_items] = best;
		return memo[num_items];
	}
}

double solve(int num[], double price[], int num_schemes,
		double unit_price, int num_items, double memo[]){
	//printf("Entering solve()\n");
	double best;
	int i;
	//printf("Before loop ===================\n");
	best = solve_k(num, price, num_schemes, unit_price, num_items, memo);
	for (i = num_items + 1; i < SIZE; i++){
	//for (i = num_items + 1; i < 20; i++){
		//printf("In loop\n");
		best = min(best, solve_k(num, price, num_schemes,
					unit_price, i, memo));
		//exit(0);
	}
	//printf("Exiting solve() ===================\n");
	return best;
}

int get_number(int *num){
	//printf("Entering get_number()\n");
	int ch;
	int ret = 0;
	ch = getchar();
	while (ch != ' ' && ch != '\n'){
		ret = ret * 10 + ch - '0';
		ch = getchar();
	}
	*num = ret;
	//printf("Exiting get_number()\n");
	return ch == ' ';
}

int main(void){
	int test_case, num_schemes, num_items, more, i;
	double unit_price, result;
	int num[MAX_SCHEMES];
	double price[MAX_SCHEMES];
	double memo[SIZE];
	test_case = 0;
	while (scanf("%lf%d", &unit_price, &num_schemes) != -1){
		test_case++;
		for (i = 0; i < num_schemes; i++){
			scanf("%d%lf", &num[i], &price[i]);
		}
		scanf(" ");
		printf("Case %d:\n", test_case);
		for (i = 0; i < SIZE; i++){
			memo[i] = -1;
		}
		more = get_number(&num_items);
		while (more){
			//for (i = 0; i < num_schemes; i++){
				//printf("num %d = %d, price %d = %lf\n", i, num[i], i, price[i]);
			//}
			//printf("num_schemes = %d unit_price = %f\n", num_schemes, unit_price);
			//printf("num_items = %d\n", num_items);
			result = solve(num, price, num_schemes, unit_price,
					num_items, memo);
			printf("Buy %d for $%.2f\n", num_items, result);
			more = get_number(&num_items);
		}
		//printf("Last entry - - -\n");
		//printf("num_items = %d\n", num_items);
		result = solve(num, price, num_schemes, unit_price, num_items, memo);
		printf("Buy %d for $%.2f\n", num_items, result);
	}
	return 0;
}
