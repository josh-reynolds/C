// From 'Focus on SDL' pp. 59-60
#include <SDL/SDL.h>
#include <stdlib.h>

const int SCREEN_WIDTH=640;
const int SCREEN_HEIGHT=480;

SDL_Surface* g_pDisplaySurface = NULL;
SDL_Event g_Event;

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

int main(int argc, char* argv[]){
	if (SDL_Init(SDL_INIT_VIDEO) == -1){
		fprintf(stderr, "Could not initialize SDL!\n");
		exit(1);
	}

	g_pDisplaySurface = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 0, SDL_ANYFORMAT);

	for (;;){
		if (SDL_PollEvent(&g_Event) == 0){
			Uint8 red = rand()%256;
			Uint8 green = rand()%256;
			Uint8 blue = rand()%256;
			Uint32 color = SDL_MapRGB(g_pDisplaySurface->format, 
					          red, green, blue);

			Uint32 x = rand()%SCREEN_WIDTH;
			Uint32 y = rand()%SCREEN_HEIGHT;

			set_pixel(get_pixel_data(x, y), &color);

			SDL_UpdateRect(g_pDisplaySurface, 0, 0, 0, 0);
		} else {
			if (g_Event.type == SDL_QUIT){
				break;
			}
		}
	}
}
