#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define hashsize(n) ((unsigned long)1 << (n))
#define hashmask(n) (hashsize(n) - 1)

unsigned long oaat(char *key, unsigned long len, unsigned long bits){
	unsigned long hash, i;
	for (hash = 0, i = 0; i < len; i++){
		hash += key[i];
		hash += (hash << 10);
		hash ^= (hash >> 6);
	}
	hash += (hash << 3);
	hash ^= (hash >> 11);
	hash += (hash << 15);
	return hash & hashmask(bits);
}

/* based on https://stackoverflow.com/questions/16870485 */
char *read_line(int size){
	char *str;
	int ch;
	int len = 0;
	str = malloc(size);
	if (str == NULL){
		fprintf(stderr, "malloc error\n");
		exit(1);
	}
	while ((ch = getchar()) != EOF && (ch != '\n')){
		str[len++] = ch;
		if (len == size){
			size = size * 2;
			str = realloc(str, size);
			if (str == NULL){
				fprintf(stderr, "realloc error\n");
				exit(1);
			}
		}
	}
	str[len] = '\0';
	return str;
}

int main(void){ // sample call of oaat
	
	long snowflake[] = {1, 2, 3, 4, 5, 6};
	// 2^17 is smallest power of 2 that is at least 100000
	unsigned long code = oaat((char *)snowflake,
			sizeof(snowflake), 17);
	printf("%u\n", code);
	return 0;
}
