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
Mix_Chunk* roundSounds[MAX_ROUNDSOUNDS];

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

void Sound::freeRoundSounds()
{
	fprintf (stdout, "Freeing roundSounds\n");
	for (int i = 0; i < MAX_ROUNDSOUNDS; i++)
	{
		if (roundSounds[i] != NULL)
		{
			fprintf (stdout, "Freeing #%i\n", i);
			Mix_FreeChunk (roundSounds[i]);
			roundSounds[i] = NULL;
		}
	}
}

void Sound::quit ()
{
	//TODO Fix me, seems to try and free things it shouldn't
	//freeRoundSounds();
	fprintf (stdout, "Freeing other sounds\n");
	for (int i = 0; i < MAX_SOUNDS; i++)
		Mix_FreeChunk (sounds[i]);
	Mix_Quit();
}

void Sound::loadRoundSFX (int sfx_num, const char* path)
{
	roundSounds[sfx_num] = Mix_LoadWAV(path);
	if (roundSounds[sfx_num] == NULL)
	{
		fprintf (stderr, "Failed to load %s\nSDL_mixer error: %s\n", path, Mix_GetError());
		return;
	}
	else
		fprintf (stdout, "Loaded %s into slot #%i\n", path, sfx_num);
}

void Sound::playRoundSFX (int sfx)
{
	//TODO Check for null?
	Mix_PlayChannel (-1, roundSounds[sfx], 0);
}

void Sound::playSFX (sfx_t sfx)
{
	Mix_PlayChannel (-1, sounds[sfx], 0);
}
