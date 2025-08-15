#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 255

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

node *new_nonhouse(node *left, node *right){
	node *nonhouse = malloc(sizeof(node));
	if (nonhouse == NULL){
		fprintf(stderr, "malloc error\n");
		exit(1);
	}
	nonhouse->left = left;
	nonhouse->right = right;
	return nonhouse;
}

int tree_candy(node *tree){

}

typedef struct stack {
	node * values[SIZE];
	int highest_used;
} stack;

stack *new_stack(void){
	stack *s = malloc(sizeof(stack));
	if (s == NULL){
		fprintf(stderr, "malloc error\n");
		exit(1);
	}
	s->highest_used = -1;
	return s;
}

void push_stack(stack *s, node *value){
	s->highest_used++;
	s->values[s->highest_used] = value;
}

node * pop_stack(stack *s){
	node * ret = s->values[s->highest_used];
	s->highest_used--;
	return ret;
}

int is_empty_stack(stack *s){
	return s->highest_used == -1;
}

int main(void){
	node *four = new_house(4);
	node *nine = new_house(9);
	node *B = new_nonhouse(four, nine);
	node *fifteen = new_house(15);
	node *C = new_nonhouse(B, fifteen);

	return 0;
}



