#define __STDC_WANT_LIB_EXT1__ 1   // recommended for gets_s()
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 20

// Exploring alternatives to gets()

int main(void){
	// -------------------------------------------------
	// gets() is dangerous and should not be used
	// -------------------------------------------------
	char s0[SIZE];
	printf("Please enter a word: ");
	gets(s0);
	printf("GETS word = %s\n", s0);

	// -------------------------------------------------
	// gets_s() is often recommended, but apparently
	// comes from MS Visual Studio and is not 
	// included with the GCC I'm using...
	// -------------------------------------------------
	//char s1[SIZE];
	//printf("Please enter a word: ");
	//gets_s(&s1, SIZE);
	//printf("GETS_S word = %s\n", s1);
	
	// -------------------------------------------------
	// scanf() is also sometimes recommended, but while
	// it hasn't been deprecated yet (unlike gets()), it's
	// apparently not much better than and should
	// also be avoided
	// -------------------------------------------------
	//char s2[SIZE];
	//printf("Please enter a word: ");
	//scanf("%s", s2);
	//printf("SCANF word = %s\n", s2);

	// -------------------------------------------------
	// fgets() is the top recommended replacement, though
	// managing against stdin can be tricky
	// the following requires user to enter Ctrl-D to
	// exit (EOF)
	// -------------------------------------------------
	//char s3[SIZE];
	//printf("Please enter a word: ");
	//while (fgets(s3, sizeof s3, stdin) != NULL){
		//printf("FGETS STDIN word = %s\n", s3);
	//}
	
	// -------------------------------------------------
	// this version checks for newline - but note that 
	// the previous scanf/fgets operations are leaving a
	// newline in the buffer, so unless they are commented
	// out, this will immediately exit its loop
	// -------------------------------------------------
	char s4[SIZE];
	printf("Please enter a word: ");
	while (fgets(s4, sizeof s4, stdin) != NULL){
		printf("FGETS STDIN w/ newlines word = %s\n", s4);
		if (s4[strlen(s4) - 1] == '\n'){
			break;
		}
	}

	// -------------------------------------------------
	// fgets() can also be used with an actual file,
	// of course - can create a temp if necessary
	// -------------------------------------------------
	char s5[SIZE];
	FILE* tmpf = tmpfile();
	fputs("Gorgonzola\n", tmpf);
	fputs("Wensleydale\n", tmpf);
	fputs("Cheddar\n", tmpf);
	fputs("Cambozola\n", tmpf);
	fputs("Gruyere\n", tmpf);
	rewind(tmpf);

	while (fgets(s5, sizeof s5, tmpf) != NULL){
		printf("FGETS TMPF word = %s\n", s5);
	}

	if (feof(tmpf)){
		puts("End of file reached.\n");
	}

	return 0;
}

