/*
 * =====================================================================================
 *
 *       Filename:  SDL.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  02/06/2024 12:06:00 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Dr. Fritz Mehner (mn), mehner@fh-swf.de
 *        Company:  FH Südwestfalen, Iserlohn
 *
 * =====================================================================================
 */
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <cstdlib>
#include <ctime>
#include "SDL.h"
#include "OpenBlank.h"
#include "Sound.h"
#include "LTexture.h"
#include "LTarget.h"
#include "BulletHole.h"
#include "Title.h"
#include "Game.h"
#include "Hud.h"
#include "Background.h"

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

bool sdl_init()
{
	//Initialization flag
	bool success = true;
	
	srand(time(nullptr)); //Seed RNG
	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else if (sound.init() != true)
	{
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}
		//Create window
		//gWindow = SDL_CreateWindow( "Open Blank", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, (SCREEN_WIDTH * SCALE_X), SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		gWindow = SDL_CreateWindow( "Open Blank", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, (SCREEN_WIDTH * SCALE_X), SCREEN_HEIGHT, SDL_WINDOW_FULLSCREEN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create vsynced renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
			if( gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}
			}
		}
	}
	SDL_ShowCursor (0);
	return success;
}

void sdl_close()
{
	fprintf (stdout, "Shutting down SDL\n");
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
	sound.quit();
	IMG_Quit();
	TTF_Quit();
	SDL_Quit();
}

void sdl_clear ()
{
	SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
	SDL_RenderClear( gRenderer );
	//Clear screen
	bg.render();
}

#define TARGET_FPS 30
void sdl_render ()
{
	Uint32 frameStart = SDL_GetTicks();
	int frameTime;
	SDL_RenderSetScale (gRenderer, SCALE_X, 1);

	if (game.getState () == STATE_TITLESCREEN)
		titlescreen.render();
	//Render buttons
	for( int i = 0; i < MAX_TARGETS; ++i )
	{
		gTargets[ i ].render();
	}

	for (int i = 0; i < MAX_BULLETHOLES; i++)
	{
		gBulletHoles[i].render();
	}
	hud.draw();
	render_crosshair();
	//Update screen
	SDL_RenderPresent( gRenderer );
	frameTime = SDL_GetTicks() - frameStart;
	if (frameTime < (1000 / TARGET_FPS))
	{
		SDL_Delay((1000 / TARGET_FPS) - frameTime);
	}
	else
		fprintf (stdout, "System too slow? frameTime %i\n", frameTime);
}
