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
#include <SDL2/SDL_ttf.h>

TTF_Font* fontTitle = NULL;
TTF_Font* fontHud = NULL;
TTF_Font* fontPhone = NULL;
TTF_Font* fontSchool = NULL;
TTF_Font* fontMoby = NULL;
TTF_Font* fontMobySmall = NULL;

static bool font_load ()
{
	fprintf (stdout, "Loading fonts\n");
	bool success = true;
//TODO Thios is lame	
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
	fontHud = TTF_OpenFont ( FONT_HUD_PATH, FONT_HUD_SIZE);
	if (fontHud == NULL)
	{
		fprintf(stderr, "Failed to load %s SDL_ttf Error: %s\n", FONT_HUD_PATH, TTF_GetError() );
		success = false;
	}
	fontPhone = TTF_OpenFont ( FONT_PHONE_PATH, FONT_PHONE_SIZE);
	if (fontPhone == NULL)
	{
		fprintf(stderr, "Failed to load %s SDL_ttf Error: %s\n", FONT_PHONE_PATH, TTF_GetError() );
		success = false;
	}
	
	fontSchool = TTF_OpenFont ( FONT_SCHOOL_PATH, FONT_SCHOOL_SIZE);
	if (fontSchool == NULL)
	{
		fprintf(stderr, "Failed to load %s SDL_ttf Error: %s\n", FONT_SCHOOL_PATH, TTF_GetError() );
		success = false;
	}
	fontMoby = TTF_OpenFont ( FONT_MOBY_PATH, FONT_MOBY_SIZE);
	if (fontMoby == NULL)
	{
		fprintf(stderr, "Failed to load %s SDL_ttf Error: %s\n", FONT_MOBY_PATH, TTF_GetError() );
		success = false;
	}
	fontMobySmall = TTF_OpenFont ( FONT_MOBY_PATH, FONT_MOBY_SMALL_SIZE);
	if (fontMobySmall == NULL)
	{
		fprintf(stderr, "Failed to load %s SDL_ttf Error: %s\n", FONT_MOBY_PATH, TTF_GetError() );
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
	if ( !gBlueTargetTexture.loadFromFile ("./data/png/BlueTarget.png"))
	{
		fprintf (stderr, "Error loading texture! %s\n", SDL_GetError ());
		success = false;
	}
	if ( !gHeartTexture.loadFromFile (TEXTURE_HEART_PATH))
	{
		fprintf (stderr, "Error loading texture! %s\n", SDL_GetError ());
		success = false;
	}
	
	if ( !gBombTexture.loadFromFile (TEXTURE_BOMB_PATH))
	{
		fprintf (stderr, "Error loading texture! %s\n", SDL_GetError ());
		success = false;
	}
	

	
	if ( !gCrosshairTexture.loadFromFile ("./data/png/crosshairs.png"))
		success = false;
	
	if ( !gCheckmarkTexture.loadFromFile ("./data/png/Checkmark.png"))
		success = false;

	if ( !gRedCrossTexture.loadFromFile ("./data/png/RedCross.png"))
		success = false;

	if (font_load () == false)
		success = false;
	if (!success)
		fprintf (stderr, "Failed to load textures\n");
	return success;
}
