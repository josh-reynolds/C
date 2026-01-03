// 2D projection of 3D points
// from YouTube video by tsoding
// "One Formula That Demystifies 3D Graphics"
//
// Note: with the inclusion of math.h, need to 
// add -lm to compile:
// 
// gcc ./tsoding_cube.c -o cube.out -lSDL -lm

#include <SDL/SDL.h>
#include <stdio.h>
#include <math.h>

const int SCREEN_WIDTH=800;
const int SCREEN_HEIGHT=800;
const float FPS = 60;

SDL_Rect canvas = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
SDL_Surface* g_pDisplaySurface = NULL;
SDL_Event g_Event;
Uint32 FOREGROUND;
Uint32 BACKGROUND;
SDL_Rect g_Rect;
float g_dz = 0.0;
double angle = 0.0;

typedef struct {
	float x, y;
} Point;

typedef struct {
	float x, y, z;
} Point3;

void clear(){
	SDL_FillRect(g_pDisplaySurface, &canvas, BACKGROUND);
}

void point(Point p){
	SDL_Rect rect;
	int s = 20;
	rect.x = p.x - s/2;
	rect.y = p.y - s/2;
	rect.w = s;
	rect.h = s;
	SDL_FillRect(g_pDisplaySurface, &rect, FOREGROUND);
}

Point screen(Point p){
	Point result = { (p.x + 1)/2 * SCREEN_WIDTH,
	       	         (1 - (p.y + 1)/2) * SCREEN_HEIGHT };
	return result;
}

Point project(Point3 p){
	Point result = { p.x / p.z, p.y / p.z };
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

Point3 vs[8] = {
	{ 0.25,  0.25,  0.25},
	{-0.25,  0.25,  0.25},
	{ 0.25, -0.25,  0.25},
	{-0.25, -0.25,  0.25},

	{ 0.25,  0.25, -0.25},
	{-0.25,  0.25, -0.25},
	{ 0.25, -0.25, -0.25},
	{-0.25, -0.25, -0.25},
};

void frame() {
	float dt = 1/FPS;
	g_dz += 0.0005;
	angle += 3 * M_PI * dt;
	clear();

	for (int i = 0; i < 8; i++){
		point(screen(project(translate_z(rotate_xz(vs[i], angle), g_dz))));
	}
}

int main(void){
	if (SDL_Init(SDL_INIT_VIDEO) == -1){
		fprintf(stderr, "Could not initialize SDL!\n");
		exit(1);
	}

	g_pDisplaySurface = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 0, SDL_ANYFORMAT);

	FOREGROUND = SDL_MapRGB(g_pDisplaySurface->format, 80, 255, 80);
	BACKGROUND = SDL_MapRGB(g_pDisplaySurface->format, 16, 16, 16);

	for (;;){
		if (SDL_PollEvent(&g_Event) == 0){
			frame();

			SDL_UpdateRect(g_pDisplaySurface, 0, 0, 0, 0);
		} else {
			if (g_Event.type == SDL_QUIT){
				break;
			}
		}
	}
}

