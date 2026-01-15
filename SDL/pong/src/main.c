// Pong in SDL
// ======================================================

#include <stdio.h>
#include <SDL2/SDL.h>
#include "./constants.h"

int game_is_running = FALSE;
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

int last_frame_time = 0;

typedef struct Ball {
	float x;
	float y;
	float width;
	float height;
	int x_velocity;
	int y_velocity;
} Ball;

Ball ball;

typedef struct Paddle {
	float x;
	float y;
	float width;
	float height;
} Paddle;

Paddle paddle_1;
Paddle paddle_2;

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
	ball.x = 20;
	ball.y = 20;
	ball.width = 15;
	ball.height = 15;
	ball.x_velocity = 70;
	ball.y_velocity = 50;

	paddle_1.x = 10;
	paddle_1.y = WINDOW_HEIGHT / 2;
	paddle_1.width = 10;
	paddle_1.height = 50;

	paddle_2.x = WINDOW_WIDTH - 10;
	paddle_2.y = WINDOW_HEIGHT / 2;
	paddle_2.width = 10;
	paddle_2.height = 50;
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
	int time_to_wait = FRAME_TARGET_TIME - (SDL_GetTicks() - last_frame_time);

	if (time_to_wait > 0 && time_to_wait <= FRAME_TARGET_TIME){
		SDL_Delay(time_to_wait);
	}

	float delta_time = (SDL_GetTicks() - last_frame_time) / 1000.0f;
	last_frame_time = SDL_GetTicks();

	ball.x += ball.x_velocity * delta_time;
	ball.y += ball.y_velocity * delta_time;

	if (ball.x + ball.width > WINDOW_WIDTH || ball.x < 0){
		ball.x_velocity *= -1;
	}
	if (ball.y + ball.height > WINDOW_HEIGHT || ball.y < 0){
		ball.y_velocity *= -1;
	}
}

void render(){
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	SDL_Rect ball_rect = {
		(int)ball.x, 
		(int)ball.y, 
		(int)ball.width, 
		(int)ball.height
	};
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderFillRect(renderer, &ball_rect);

	SDL_Rect paddle_1_rect = {
		(int)paddle_1.x, 
		(int)paddle_1.y, 
		(int)paddle_1.width, 
		(int)paddle_1.height
	};
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderFillRect(renderer, &paddle_1_rect);
	
	SDL_Rect paddle_2_rect = {
		(int)paddle_2.x, 
		(int)paddle_2.y, 
		(int)paddle_2.width, 
		(int)paddle_2.height
	};
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderFillRect(renderer, &paddle_2_rect);

	SDL_RenderPresent(renderer);
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
