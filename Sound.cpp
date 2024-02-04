/*
 * =====================================================================================
 *
 *       Filename:  sound.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  02/04/2024 10:02:05 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Dr. Fritz Mehner (mn), mehner@fh-swf.de
 *        Company:  FH Südwestfalen, Iserlohn
 *
 * =====================================================================================
 */
#include "Sound.h"

Mix_Chunk* gGunshot = NULL;

bool sound_load_media ()
{
	gGunshot = Mix_LoadWAV(SND_GUNSHOT_PATH);
	if (gGunshot == NULL)
	{
		fprintf (stderr, "Failed to load %s\nSDL_mixer error: %s\n", SND_GUNSHOT_PATH, Mix_GetError());
		return false;
	}

	return true;
}
bool sound_init ()
{
	if (Mix_OpenAudio (44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		fprintf(stderr,"SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
		return false;
	}
	else if (!sound_load_media())
		return false;
	else
		return true;
}

void sound_quit ()
{
	Mix_FreeChunk (gGunshot);
	Mix_Quit();
}
