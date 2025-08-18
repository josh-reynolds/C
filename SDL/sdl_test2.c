// From 'Focus on SDL' pp. 15-6
#include <SDL/SDL.h>
#include <stdio.h>
#include <stdlib.h>

SDL_Surface* g_pMainSurface = NULL;
SDL_Event g_Event;

int main(int argc, char* argv[]){
	if (SDL_Init(SDL_INIT_VIDEO) == -1){
		fprintf(stderr, "Could not initialize SDL!\n");
		exit(1);
	} else {
		fprintf(stdout, "SDL initialized properly!\n");
		atexit(SDL_Quit);
	}

	g_pMainSurface = SDL_SetVideoMode(640, 480, 0, SDL_ANYFORMAT);
	if (!g_pMainSurface){
		fprintf(stderr, "Could not create main surface!\n");
		exit(1);
	}

	for (;;){
		if (SDL_WaitEvent(&g_Event) == 0){
			fprintf(stderr, "Error while waiting for an event!\n");
			exit(1);
		}

		if (g_Event.type == SDL_QUIT){
			fprintf(stdout, "Quit event has occurred.\n");
			break;
		}
	}

	fprintf(stdout, "Terminating program normally.\n");
	return 0;
}
