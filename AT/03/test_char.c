#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int get_number(int *num){
	printf("Entering get_number()\n");
	int ch;
	int ret = 0;
	printf("Type a number and press <Enter>: ");
	ch = getchar();
	printf("Before loop: char = %d num = %d\n", ch, ret);
	while (ch != ' ' && ch != '\n'){
		ret = ret * 10 + ch - '0';
		ch = getchar();
		printf("In loop: char = %d num = %d\n", ch, ret);
	}
	printf("Exited loop\n");
	printf("After loop: char = %d num = %d\n", ch, ret);
	*num = ret;
	printf("Here?\n");
	printf("FOO?\n");
	printf("Number = %d\n", ret);
	printf("%d\n", (ch == ' '));
	return (ch == ' ');
}

int main(void){
	int more, num_items;
	more = get_number(&num_items);
	printf("More = %d num_items = %d\n", more, num_items);
	return 0;
}
