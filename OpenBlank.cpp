//#include <SDL2/SDL.h>
//#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include "OpenBlank.h"
#include "SDL.h"
#include "Media.h"
#include "Movement.h"
#include "LTarget.h"

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
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;

			//While application is running
			while( !quit )
			{
				//Handle events on queue
				while( SDL_PollEvent( &e ) != 0 )
				{
					//User requests quit
					if( e.type == SDL_QUIT )
					{
						quit = true;
					}
					
					//Handle button events
					for( int i = 0; i < MAX_TARGETS; ++i )
					{
						gTargets[ i ].handleEvent( &e );
					}
				}
				movement_all ();
				sdl_render ();
			}
		}
	}

	//Free resources and close SDL
	sdl_close();

	return 0;
}
