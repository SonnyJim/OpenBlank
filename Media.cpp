/*
 * =====================================================================================
 *
 *       Filename:  Media.cpp
 *
 *    Description: 
 *
 *        Version:  1.0
 *        Created:  02/06/2024 12:36:20 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Dr. Fritz Mehner (mn), mehner@fh-swf.de
 *        Company:  FH Südwestfalen, Iserlohn
 *
 * =====================================================================================
 */
#include "Media.h"
#include "OpenBlank.h"
#include "LTexture.h"
#include "LTarget.h"

TTF_Font* fontTitle = NULL;
#define FONT_TITLE_SIZE 60

static bool font_load ()
{
	bool success = true;
	
	if (TTF_Init() != 0)
	{
		fprintf(stderr, "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
		success = false;
	}
	fontTitle = TTF_OpenFont ( FONT_TITLE_PATH, FONT_TITLE_SIZE);
	if (fontTitle == NULL)
	{
		fprintf(stderr, "Failed to load %s SDL_ttf Error: %s\n", FONT_TITLE_PATH, TTF_GetError() );
		success = false;
	}
	return success;
}
bool media_init()
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
	else if (font_load () == false)
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
