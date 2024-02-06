#include <stdio.h>
#include <string>
#include "SDL.h"
#include "Media.h"
#include "Game.h"

bool quit = false;

int main( int argc, char* args[] )
{
	//Start up SDL and create window
	if( !sdl_init() )
	{
		printf( "Failed to initialize SDL!\n" );
	}
	else
	{
		//Load media
		if( !media_load() )
		{
			printf( "Failed to load media!\n" );
		}
		else
		{	
			while (!quit)
				game.update();
		}
	}
	//Free resources and close SDL
	sdl_close();

	return 0;
}
