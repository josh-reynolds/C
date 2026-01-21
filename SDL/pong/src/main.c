// Pong in SDL
// ======================================================

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>
#include "./constants.h"

int game_is_running = FALSE;
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

int last_frame_time = 0;

typedef struct Sprite {
	float x;
	float y;
	float width;
	float height;
	int x_velocity;
	int y_velocity;
} Sprite;

Sprite ball;
Sprite paddle_1;
Sprite paddle_2;

int player_1_score = 0;
int player_2_score = 0;

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

void reset(int direction){
	ball.x = WINDOW_WIDTH/2 - 8;
	ball.y = WINDOW_HEIGHT/2 - 8;
	ball.width = 16;
	ball.height = 16;

	ball.x_velocity = (rand() % 30) + 200 * direction;

	ball.y_velocity = (rand() % 10) + 10;
	int y_dir = rand() % 2;
	if (y_dir == 0)
		ball.y_velocity *= -1;

	fprintf(stdout, "Player 1: %d | Player 2: %d\n", player_1_score, player_2_score);
}

void setup(){
	reset(1);

	paddle_1.x = 10;
	paddle_1.y = WINDOW_HEIGHT / 2 - 40;
	paddle_1.width = 10;
	paddle_1.height = 80;

	paddle_2.x = WINDOW_WIDTH - 10 - 10;
	paddle_2.y = WINDOW_HEIGHT / 2 - 40;
	paddle_2.width = 10;
	paddle_2.height = 80;
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

	if (ball.x + ball.width > WINDOW_WIDTH){
		player_1_score++;
		reset(-1);
	}
	if (ball.x < 0){
		player_2_score++;
		reset(1);
	}

	if (ball.y + ball.height > WINDOW_HEIGHT || ball.y < 0){
		ball.y_velocity *= -1;
	}
	
	if (ball.x < WINDOW_WIDTH / 2){
		// paddle_1
		if (ball.x > paddle_1.x && ball.x < paddle_1.x + paddle_1.width){
			if (ball.y > paddle_1.y && ball.y < paddle_1.y + paddle_1.height){
				ball.x_velocity *= -1;
			}
		}
	} else {
		// paddle_2
		if (ball.x + ball.width > paddle_2.x && 
				ball.x + ball.width < paddle_2.x + paddle_2.width){
			if (ball.y > paddle_2.y && ball.y < paddle_2.y + paddle_2.height){
				ball.x_velocity *= -1;
			}
		}
	}

	const Uint8* key_states = SDL_GetKeyboardState(NULL);

	if (key_states[SDL_SCANCODE_A]){
		paddle_1.y -= 10;
		if (paddle_1.y <= 0)
			paddle_1.y = 0;
	}
	if (key_states[SDL_SCANCODE_Z]){
		paddle_1.y += 10;
		if (paddle_1.y + paddle_1.height >= WINDOW_HEIGHT)
			paddle_1.y = WINDOW_HEIGHT - paddle_1.height;
	}
	if (key_states[SDL_SCANCODE_J]){
		paddle_2.y -= 10;
		if (paddle_2.y <= 0)
			paddle_2.y = 0;
	}
	if (key_states[SDL_SCANCODE_M]){
		paddle_2.y += 10;
		if (paddle_2.y + paddle_2.height >= WINDOW_HEIGHT)
			paddle_2.y = WINDOW_HEIGHT - paddle_2.height;
	}

	// update all objects
	//     paddle - move by player input
	//     ball   - move by current velocity/direction
	//              handle collisions w/ paddles
	//              handle collisions w/ bounds
	// handle scoring/reset if ball is out of bounds
}

void draw(Sprite* s){
	SDL_Rect rect = {
		(int)s->x, 
		(int)s->y, 
		(int)s->width, 
		(int)s->height
	};
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderFillRect(renderer, &rect);
}

void render(){
	SDL_SetRenderDrawColor(renderer, 0, 0, 128, 255);
	SDL_RenderClear(renderer);

	draw( &ball );
	draw( &paddle_1 );
	draw( &paddle_2 );

	SDL_RenderPresent(renderer);
}

void destroy_window(){
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

int main(){
	srand((unsigned) time(NULL));
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
