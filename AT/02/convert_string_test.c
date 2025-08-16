#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 255

int main(void){
	char line[SIZE + 1];
	int candy;
	gets(line);    // gets() should not be used...
	candy = line[0] - '0';
	printf("%d\n", candy);
	return 0;
}

