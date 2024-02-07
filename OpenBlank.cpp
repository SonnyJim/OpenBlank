#include <stdio.h>
#include <string>
#include "SDL.h"
#include "Media.h"
#include "Game.h"
#include "Title.h"

bool quit = false;

int main( int argc, char* args[] )
{
	if( !sdl_init() || !media_init() )
	{
		fprintf(stderr, "Failed to initialize!\n" );
		sdl_close();
		return -1;
	}
	else
	{
		titlescreen.start();
		//game.start();
		while (!quit)
		{
			game.update();
		}
	}
	sdl_close();
	return 0;
}
