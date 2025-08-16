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

int tree_candy_stack(node *tree){
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

int tree_candy(node *tree){
	if (!tree->left && !tree->right){
		return tree->candy;
	} else {
		return tree_candy(tree->left) +
			tree_candy(tree->right);
	}
}

int tree_nodes(node *tree){
	if (!tree->left && !tree->right){
		return 1;
	} else {
		return 1 + tree_nodes(tree->left) +
			   tree_nodes(tree->right);
	}
}

int tree_leaves(node *tree){
	if (!tree->left && !tree->right){
		return 1;
	} else {
		return tree_leaves(tree->left) +
		       tree_leaves(tree->right);
	}
}

int tree_streets(node *tree){
	if (!tree->left && !tree->right){
		return 0;
	} else {
		return tree_streets(tree->left) +
		       tree_streets(tree->right) + 4;
	}
}

int max(int v1, int v2){
	if (v1 > v2){
		return v1;
	} else {
		return v2;
	}
}

int tree_height(node *tree){
	if (!tree->left && !tree->right){
		return 0;
	} else {
		return max(tree_height(tree->left),
		           tree_height(tree->right)) + 1;
	}
}

int main(void){
	node *n;
	n = new_nonhouse(new_house(20), 
			new_nonhouse(new_house(30),
				     new_house(10)));
	printf("Candy = %d\n", tree_candy(n));
	printf("Nodes = %d\n", tree_nodes(n));
	printf("Leaves = %d\n", tree_leaves(n));
	printf("Streets = %d\n", tree_streets(n));
	printf("Height = %d\n", tree_height(n));
	return 0;
}
