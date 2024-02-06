#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include "LTexture.h"
#include "LTarget.h"
#include "OpenBlank.h"
#include "BulletHole.h"
//#include "Sound.h"
#include "SDL.h"
#include "Media.h"

//Loads media
bool loadMedia();

bool bounds_check (int x, int y, int w, int h)
{
	//fprintf (stdout, "x=%i,y=%i,w=%i,h=%i\n", x, y, w, h);
	if (x - w > SCREEN_WIDTH)
	{
		fprintf (stdout, "Offscreen + x\n");
		return false;
	}
	else if (x + w < 0)
		return false;
	else if (y < 0)
		return false;
	else if (y + h > SCREEN_HEIGHT)
		return false;
	else
		return true;
}

void movement_all ()
{
	for (int i = 0; i < MAX_TARGETS; ++i)
	{
		if (gTargets[i].getType() != TARGET_NONE )
		{
			gTargets[i].movement();
		}
	}

	for (int i = 0; i < MAX_BULLETHOLES; i++)
	{
		gBulletHoles[i].update();
	}

}

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
