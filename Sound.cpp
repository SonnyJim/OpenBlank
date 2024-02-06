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
#include <SDL2/SDL_mixer.h>

//Mix_Chunk* gGunshot = NULL;
Mix_Chunk* sounds[MAX_SOUNDS];

const char* soundpaths[] = 
{
	"./data/sfx/cg1.wav",
};


Sound sound;
static bool sound_load_media ()
{
	for (int i = 0; i < MAX_SOUNDS; i++)
	{
		sounds[i] = Mix_LoadWAV(soundpaths[i]);
		if (sounds[i] == NULL)
		{
			fprintf (stderr, "Failed to load %s\nSDL_mixer error: %s\n", soundpaths[i], Mix_GetError());
			return false;
		}
	}
	return true;
}

bool Sound::init ()
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

void Sound::quit ()
{
	for (int i = 0; i < MAX_SOUNDS; i++)
		Mix_FreeChunk (sounds[i]);
	Mix_Quit();
}

void Sound::playSFX (sfx_t sfx)
{
	Mix_PlayChannel (-1, sounds[sfx], 0);
}
