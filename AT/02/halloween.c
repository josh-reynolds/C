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

int tree_candy(node *tree){
	int total = 0;
	stack *s = new_stack();
	while (tree != NULL){
		if (tree->left && tree->right){
			push_stack(s, tree->left);
			tree = tree->right;
		} else {
			total = total + tree->candy;
			if (is_empty_stack(s)){
				tree = NULL;
			} else {
				tree = pop_stack(s);
			}
		}
	}
	return total;
}

int main(void){
	node *n;
	n = new_nonhouse(new_house(20), 
			new_nonhouse(new_house(30),
				     new_house(10)));
	printf("%d\n", tree_candy(n));
	return 0;
}
