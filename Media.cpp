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
#include "Title.h"

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
		fprintf (stderr, "Error loading texture! %s\n", SDL_GetError ());
		success = false;
	}
	else if ( !gBlueTargetTexture.loadFromFile ("./data/png/BlueTarget.png"))
	{
		fprintf (stderr, "Error loading texture! %s\n", SDL_GetError ());
		success = false;
	}
	else if ( !gCrosshairTexture.loadFromFile ("./data/png/crosshairs.png"))
		success = false;
	else if (font_load () == false)
		success = false;
	/*
	else if ( !gTitlescreen.loadFromFile ("./data/png/menu_background.png"))
	{
		fprintf (stderr, "Error loading texture! %s\n", SDL_GetError ());
		success = false;
	}
*/
	/*
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
	*/
	if (!success)
		fprintf (stderr, "Failed to load textures\n");
	return success;
}
