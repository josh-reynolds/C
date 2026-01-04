// 2D projection of 3D points
// from YouTube video by tsoding
// "One Formula That Demystifies 3D Graphics"
//
// Note: with the inclusion of math.h, need to 
// add -lm to compile:
// 
// gcc ./tsoding_cube.c -o cube.out -lSDL -lm && ./cube.out

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>

const int SCREEN_WIDTH=800;
const int SCREEN_HEIGHT=800;
const float FPS = 60;

SDL_Rect canvas = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
SDL_Surface* g_pDisplaySurface = NULL;
SDL_Event g_Event;

Uint32 FOREGROUND;
Uint32 BACKGROUND;

float g_dz = 1.0;
double angle = 0.0;

float target_frame_time = 1/FPS;
int last_frame_time = 0;
float dt;

typedef struct {
	float x, y;
} Point;

typedef struct {
	float x, y, z;
} Point3;

void set_pixel(char* pixels, Uint32* color){
	if (SDL_MUSTLOCK(g_pDisplaySurface)) SDL_LockSurface(g_pDisplaySurface);
	memcpy(pixels, color, g_pDisplaySurface->format->BytesPerPixel);
	if (SDL_MUSTLOCK(g_pDisplaySurface)) SDL_UnlockSurface(g_pDisplaySurface);
}

char* get_pixel_data(Uint32 x, Uint32 y){
	char* pData;
	pData = (char*)g_pDisplaySurface->pixels;
	pData += (y * g_pDisplaySurface->pitch);
	pData += (x * g_pDisplaySurface->format->BytesPerPixel);
	return pData;
}

void clear(){
	SDL_FillRect(g_pDisplaySurface, &canvas, BACKGROUND);
}

void point(Point p){
	//SDL_Rect rect;
	//int s = 20;
	//rect.x = p.x - s/2;
	//rect.y = p.y - s/2;
	//rect.w = s;
	//rect.h = s;
	//SDL_FillRect(g_pDisplaySurface, &rect, FOREGROUND);
	set_pixel(get_pixel_data(p.x, p.y), &FOREGROUND);
}

// Bresenham's line drawing algorithm
void line(Point p1, Point p2){
	int dx = p2.x - p1.x;
	int dy = p2.y - p1.y;

	int ax = 2 * abs(dx);
	int ay = 2 * abs(dy);

	int sx = copysign(1, dx);
	int sy = copysign(1, dy);

	int x = p1.x;
	int y = p1.y;

	int d;

	Point p;


	if (ax > ay){                 // x dominant
		d = ay - ax/2;
		while(1 == 1){
			if (x == round(p2.x)){
				return;
			}


			p.x = x;
			p.y = y;
			point(p);

			if (d >= 0){
				y = y + sy;
				d = d - ax;
			}
			x = x + sx;
			d = d + ay;
		}
	} else {                     // y dominant
		d = ax - ay/2;
		while(1 == 1){
			if (y == round(p2.y)){
				return;
			}

			p.x = x;
			p.y = y;
			point(p);

			if (d >= 0){
				x = x + sx;
				d = d - ay;
			}
			y = y + sy;
			d = d + ax;
		}
	}
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
	{-0.25, -0.25,  0.25},
	{ 0.25, -0.25,  0.25},

	{ 0.25,  0.25, -0.25},
	{-0.25,  0.25, -0.25},
	{-0.25, -0.25, -0.25},
	{ 0.25, -0.25, -0.25},
};

int edges[12][2] = {
	{0, 1},
	{1, 2},
	{2, 3},
	{3, 0},
	{0, 4},
	{1, 5},
	{2, 6},
	{3, 7},
	{4, 5},
	{5, 6},
	{6, 7},
	{7, 4},
};

void frame() {
	int time_to_wait = target_frame_time - (SDL_GetTicks() - last_frame_time);

	if (time_to_wait > 0 && time_to_wait <= target_frame_time){
		SDL_Delay(time_to_wait);
	}

	dt = (SDL_GetTicks() - last_frame_time) / 1000.0f;
	last_frame_time = SDL_GetTicks();

	angle += 8 * M_PI * dt;
	clear();

	for (int i = 0; i < 12; i++){
		int index1 = edges[i][0];
		int index2 = edges[i][1];

		Point p1 = screen(project(translate_z(rotate_xz(vs[index1], angle), g_dz)));
		Point p2 = screen(project(translate_z(rotate_xz(vs[index2], angle), g_dz)));

		line(p1, p2);
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
