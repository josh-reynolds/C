// simple game loop project from YouTube video by pikuma:
// "Creating a Game Loop with C & SDL (Tutorial)"
// ======================================================

#include <stdio.h>
#include <SDL2/SDL.h>
#include "./constants.h"

int game_is_running = FALSE;
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

int initialize_window(void){
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
		fprintf(stderr, "Error initializing SDL.\n");
		return FALSE;
	}

	window = SDL_CreateWindow(
			NULL,
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			WINDOW_WIDTH,
			WINDOW_HEIGHT,
			SDL_WINDOW_BORDERLESS
			);
	if (!window){
		fprintf(stderr, "Error creating SDL window.\n");
		return FALSE;
	}

	renderer = SDL_CreateRenderer(window, -1, 0);
	if (!renderer){
		fprintf(stderr, "Error creating SDL renderer.\n");
		return FALSE;
	}

	return TRUE;
}

void setup(){
}

void process_input(){
	SDL_Event event;
	SDL_PollEvent(&event);

	switch (event.type){
		case SDL_QUIT:
			game_is_running = FALSE;
			break;
		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_ESCAPE)
				game_is_running = FALSE;
			break;
	}
}

void update(){
	// TO_DO
}

void render(){
	// TO_DO
}

void destroy_window(){
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

int main(){
	game_is_running = initialize_window();

	setup();

	while(game_is_running){
		process_input();
		update();
		render();
	}

	destroy_window();

	return 0;
}
