#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 255

int main(void){
	char line[SIZE + 1];
	int candy, digit1, digit2;
	gets(line);    // gets() should not be used...
	digit1 = line[0] - '0';
        digit2 = line[1] - '0';
	candy = 10 * digit1 + digit2;
	printf("%d\n", candy);
	return 0;
}

