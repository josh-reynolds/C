#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int identical_right(int snow1[], int snow2[], int start){
	int offset;
	for (offset = 0; offset < 6; offset++){
		if (snow1[offset] != snow2[(start + offset) % 6]){
			return 0;
		}
	}
	return 1;
}

int identical_left(int snow1[], int snow2[], int start){
	int offset, snow2_index;
	for (offset = 0; offset < 6; offset++){
		snow2_index = start - offset;
		if (snow2_index < 0){
			snow2_index = snow2_index + 6;
		}
		if (snow1[offset] != snow2[snow2_index]){
			return 0;
		}
	}
	return 1;
}

int are_identical(int snow1[], int snow2[]){
	int start;
	for (start = 0; start < 6; start++){
		if (identical_right(snow1, snow2, start)){
			return 1;
		}
		if (identical_left(snow1, snow2, start)){
			return 1;
		}
	}
	return 0;
}

void identify_identical(int values[], int n){
	int i, j;
	for (i = 0; i < n; i++){
		for (j = i+1; j < n; j++){
			if (values[i] == values[j]){
				printf("Twin integers found.\n");
				return;
			}
		}
	}
	printf("No two integers are alike.\n");
}

int main(void){
	int a[6] = {1, 2, 3, 4, 5, 6};
	int b[6] = {1, 2, 1, 4, 5, 6};
	int c[6] = {4, 5, 6, 1, 2, 3};
	int d[6] = {6, 5, 4, 3, 2, 1};

	int ab = are_identical(a,b);
	int ac = are_identical(a,c);
	int ad = are_identical(a,d);
	int bc = are_identical(b,c);
	int bd = are_identical(b,d);
	int cd = are_identical(c,d);

	if (ab){
		printf("A-B are identical.\n");
	} else {
		printf("A-B are NOT identical.\n");
	}
	
	if (ac){
		printf("A-C are identical.\n");
	} else {
		printf("A-C are NOT identical.\n");
	}

	if (ad){
		printf("A-D are identical.\n");
	} else {
		printf("A-D are NOT identical.\n");
	}

	if (bc){
		printf("B-C are identical.\n");
	} else {
		printf("B-C are NOT identical.\n");
	}
	
	if (bd){
		printf("B-D are identical.\n");
	} else {
		printf("B-D are NOT identical.\n");
	}

	if (cd){
		printf("C-D are identical.\n");
	} else {
		printf("C-D are NOT identical.\n");
	}
	return 0;
}
