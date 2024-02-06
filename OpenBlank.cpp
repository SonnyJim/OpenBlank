#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include "LTexture.h"
#include "LTarget.h"
#include "OpenBlank.h"
#include "BulletHole.h"
#include "Sound.h"
#include "SDL.h"

//Screen dimension constants

//Button constants
//const int BUTTON_WIDTH = 300;
//const int BUTTON_HEIGHT = 200;

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

void render_crosshair ()
{
	int x, y;
	SDL_Rect t;
	t.x = 0;
	t.y = 0;
	t.w = 40 * SCALE_X; //FIXME do dynamically
	t.h = 40;
	SDL_GetMouseState( &x, &y );
	gCrosshairTexture.render (x - (t.w/2), y - (t.h/2), &t);
}

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

bool loadMedia()
{
	//Loading success flag
	bool success = true;
	
	if ( !gRedTargetTexture.loadFromFile ("./data/png/RedTarget.png"))
	{
		success = false;
	}
	else if ( !gBlueTargetTexture.loadFromFile ("./data/png/BlueTarget.png"))
	{
		success = false;
	}
	else if ( !gCrosshairTexture.loadFromFile ("./data/png/crosshairs.png"))
		success = false;
	else
	{
		gTargets[0].setPosition (0, 0);
		gTargets[1].setPosition (0, 40);
		gTargets[0].setType (TARGET_RED);
		gTargets[1].setType (TARGET_BLUE);
		gTargets[0].mHeight = 40;
		gTargets[0].mWidth = 40 * SCALE_X;
		gTargets[1].mHeight = 40;
		gTargets[1].mWidth = 40 * SCALE_X;
	}
	
/*		
	}
	//Load sprites
	if( !gButtonSpriteSheetTexture.loadFromFile( "./button.png" ) )
	{
		printf( "Failed to load button sprite texture!\n" );
		success = false;
	}
	else
	{
		//Set sprites
		for( int i = 0; i < BUTTON_SPRITE_TOTAL; ++i )
		{
			gSpriteClips[ i ].x = 0;
			gSpriteClips[ i ].y = i * 200;
			gSpriteClips[ i ].w = BUTTON_WIDTH;
			gSpriteClips[ i ].h = BUTTON_HEIGHT;
		}

		//Set buttons in corners
		gTargets[ 0 ].setPosition( 0, 0 );
		gTargets[ 1 ].setPosition( SCREEN_WIDTH - BUTTON_WIDTH, 0 );
		gTargets[ 2 ].setPosition( 0, SCREEN_HEIGHT - BUTTON_HEIGHT );
		gTargets[ 3 ].setPosition( SCREEN_WIDTH - BUTTON_WIDTH, SCREEN_HEIGHT - BUTTON_HEIGHT );
	}
*/
	if (!success)
		fprintf (stderr, "Failed to load textures\n");
	return success;
}

void close()
{
	//Free loaded images
	gRedTargetTexture.free();
	gBlueTargetTexture.free();
	gCrosshairTexture.free();
	//Destroy window	
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	sound_quit();
	IMG_Quit();
	SDL_Quit();
}

void sdl_handleevent ()
{
}

void sdl_render ()
{
	//Clear screen
	SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
	SDL_RenderClear( gRenderer );

	//Render buttons
	for( int i = 0; i < MAX_TARGETS; ++i )
	{
		gTargets[ i ].render();
	}

	for (int i = 0; i < MAX_BULLETHOLES; i++)
	{
		gBulletHoles[i].render();
	}
	render_crosshair();
	//Update screen
	SDL_RenderPresent( gRenderer );

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
		if( !loadMedia() )
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
	close();

	return 0;
}
