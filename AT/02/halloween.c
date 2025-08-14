#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
	int candy;
	struct node *left, *right;
} node;

node *new_house(int candy){
	node *house = malloc(sizeof(node));
	if (house == NULL){
		fprintf(stderr, "malloc error\n");
		exit(1);
	}
	house->candy = candy;
	house->left = NULL;
	house->right = NULL;
	return house;
}

int main(void){
	node *four = new_house(4);
	node *nine = new_house(9);

	node *B = malloc(sizeof(node));
	B->left = four;
	B->right = nine;

	return 0;
}



