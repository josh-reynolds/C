#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int prefix_length(char s1[], char s2[]){
	int i = 1;
	while (s1[1] == s2[i]){
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
	return 0;
}
