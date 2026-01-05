// simple game loop project from YouTube video by pikuma:
// "Creating a Game Loop with C & SDL (Tutorial)"
// ======================================================

#include <stdio.h>
#include <SDL2/SDL.h>
#include "./constants.h"

void initialize_window(void){
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
		fprintf(stderr, "Error initializing SDL.\n");
		exit(1);    // tutorial returns FALSE here instead of exiting
	}
	// tutorial returns TRUE on success
}

int main(){
	initialize_window();
	return 0;
}


