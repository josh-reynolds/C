#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 1000000

int prefix_length(char s1[], char s2[]){
	int i = 1;
	while (s1[i] == s2[i]){
		i++;
	}
	return i - 1;
}

int suffix_length(char s1[], char s2[], int len){
	int i = len;
	while (i >= 2 && s1[i] == s2[i-1]){
		i--;
	}
	return len - i;
}

int main(void){
	static char s1[SIZE + 2], s2[SIZE + 2];
	int len, prefix, suffix, total;

	// gets() is dangerous and should not be used
	// see https://stackoverflow.com/questions/1694036
	// following lines are from the book's text
	gets(&s1[1]);
	gets(&s2[1]);
	//printf("first: %s\n", &s1[1]);
	//printf("second: %s\n", &s2[1]);

	len = strlen(&s1[1]);
	//printf("length: %i\n", len);

	prefix = prefix_length(s1, s2);
	//printf("prefix: %i\n", prefix);

	suffix = suffix_length(s1, s2, len);
	//printf("suffix: %i\n", suffix);

	total = (prefix + 1) - (len - suffix) + 1;
	if (total < 0){
		total = 0;
	}
	//printf("total: %d\n", total);
	printf("%d\n", total);

	for (int i = 0; i < total; i++){
		printf("%d", i + len - suffix);
		if (i < total - 1){
			printf(" ");
		} else {
			printf("\n");
		}
	}
	return 0;
}
