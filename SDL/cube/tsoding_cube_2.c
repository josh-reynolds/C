// 2D projection of 3D points
// from YouTube video by tsoding
// "One Formula That Demystifies 3D Graphics"
//
// Redoing this project with SDL2
//
// gcc ./tsoding_cube_2.c -o cube2.out -lSDL2 -lm && ./cube2.out

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <SDL2/SDL.h>

const int SCREEN_WIDTH=800;
const int SCREEN_HEIGHT=800;

SDL_Window* g_pWindow = NULL;
SDL_Renderer* g_pRenderer = NULL;

float g_dz = 2.0;
double g_angle = 0.0;

bool is_running = false;

typedef struct {
	float x, y;
} Point;

typedef struct {
	float x, y, z;
} Point3;

void point(Point p){
	SDL_Rect rect;
	int s = 20;
	rect.x = p.x - s/2;
	rect.y = p.y - s/2;
	rect.w = s;
	rect.h = s;

	SDL_SetRenderDrawColor(g_pRenderer, 80, 255, 80, 255);
	SDL_RenderFillRect(g_pRenderer, &rect);
}

void clear(){
	SDL_SetRenderDrawColor(g_pRenderer, 16, 16, 16, 255);
	SDL_RenderClear(g_pRenderer);
}

Point project(Point3 p){
	Point result = { p.x / p.z, p.y / p.z };
	return result;
}

Point screen(Point p){
	Point result = { (p.x + 1)/2 * SCREEN_WIDTH,
		         (1 - (p.y + 1)/2) * SCREEN_HEIGHT };
	return result;
}

Point3 translate_z(Point3 p, float dz){
	Point3 result = {p.x, p.y, p.z + dz};
	return result;
}

Point3 rotate_xz(Point3 p, double angle){
	double theta = angle * (M_PI / 180.0);
	double c = cos(theta);
	double s = sin(theta);
	Point3 result = {
		p.x * c - p.z * s,
		p.y,
		p.x * s + p.z * c
	};
	return result;
}

// CUBE ====================================
//Point3 vs[8] = {
	//{ 0.25,  0.25,  0.25},
	//{-0.25,  0.25,  0.25},
	//{-0.25, -0.25,  0.25},
	//{ 0.25, -0.25,  0.25},
//
	//{ 0.25,  0.25, -0.25},
	//{-0.25,  0.25, -0.25},
	//{-0.25, -0.25, -0.25},
	//{ 0.25, -0.25, -0.25},
//};
//
//int edges[12][2] = {
	//{0, 1},
	//{1, 2},
	//{2, 3},
	//{3, 0},
	//{0, 4},
	//{1, 5},
	//{2, 6},
	//{3, 7},
	//{4, 5},
	//{5, 6},
	//{6, 7},
	//{7, 4},
//};
// END CUBE ================================

// TETRAHEDRON =================================
// TO_DO: calculate proper vertex positions for a regular tetrahedron
Point3 vs[4] = {
	{ 0.0,  0.5,  0.0},
	{ 0.5, -0.5, -0.28},
	{-0.5, -0.5, -0.28},
	{ 0.0, -0.5,  0.58},
};

int edges[6][2] = {
	{0, 1},
	{0, 2},
	{0, 3},
	{1, 2},
	{2, 3},
	{3, 1},
};
// END TETRAHEDRON =============================

void frame(){
	g_angle += M_PI/200;

	clear();

	for (int i = 0; i < 6; i++){
		int index1 = edges[i][0];
		int index2 = edges[i][1];

		Point p1 = screen(project(translate_z(rotate_xz(vs[index1], g_angle), g_dz)));
		Point p2 = screen(project(translate_z(rotate_xz(vs[index2], g_angle), g_dz)));

		SDL_SetRenderDrawColor(g_pRenderer, 80, 255, 80, 255);
		SDL_RenderDrawLine(g_pRenderer, p1.x, p1.y, p2.x, p2.y);
	}
}

int main(void){
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
		fprintf(stderr, "Error initializing SDL.\n");
		exit(1);
	}

	g_pWindow = SDL_CreateWindow(
			NULL,
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH,
			SCREEN_HEIGHT,
			SDL_WINDOW_BORDERLESS
			);

	g_pRenderer = SDL_CreateRenderer(g_pWindow, -1, 0);

	is_running = true;
	while(is_running){
		SDL_Event event;
		SDL_PollEvent(&event);

		switch (event.type){
			case SDL_QUIT:
				is_running = false;
				break;
			case SDL_KEYDOWN:
				if (event.key.keysym.sym == SDLK_ESCAPE)
					is_running = false;
				break;
		}

		frame();
		SDL_RenderPresent(g_pRenderer);
	}

	SDL_DestroyRenderer(g_pRenderer);
	SDL_DestroyWindow(g_pWindow);
	g_pRenderer = NULL;
	g_pWindow = NULL;
	SDL_Quit();
}
