#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
	char *name;
	int num_children;
	struct node **children;
	int score;
} node;

node *find_node(node *nodes[], int num_nodes, char *name){
	int i;
	for (i = 0; i < num_nodes; i++){
		if (strcmp(nodes[i]->name, name) == 0){
			return nodes[i];
		}
	}
	return NULL;
}

int main(void){
	return 0;
}

