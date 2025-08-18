// nix-shell -p SDL
// drops into /nix/store/<UNIQUE>/
// pulled version 1.2.15
// to compile, need -lSDL flag:
//    gcc ./sdl_test.c -o sdl.out -lSDL

#include <SDL/SDL.h>
#include <stdio.h>

int main(void){
	if (SDL_Init(SDL_INIT_VIDEO) == -1){
		fprintf(stderr, "Could not initialize SDL!\n");
	} else {
		fprintf(stderr, "SDL initialized properly!\n");
		SDL_Quit();
	}
	return 0;
}
