// Figuring out how to work with SDL on nixOS.
// Validation code below from 'Focus on SDL' (Ernest Pazera), page 14.
// Needed to modify the include slightly to find SDL.h.
// That book is 22 years old, so things have changed, but I'll
// start there. Code below compiles and reports successful 
// initialization so that's something. https://search.nixos.org shows
// SDL2 and SDL3 are available. We'll try '1' to match the book 
// text for now.
// 
// To install SDL:
//     nix-shell -p SDL
//
// Libraries will be found in /nix/store/<GUID>-SDL-1.2.15-dev/
//
// To compile, need -lSDL flag:
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
