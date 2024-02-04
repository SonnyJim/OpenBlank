/*
 * =====================================================================================
 *
 *       Filename:  sound.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  02/04/2024 10:03:40 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Dr. Fritz Mehner (mn), mehner@fh-swf.de
 *        Company:  FH Südwestfalen, Iserlohn
 *
 * =====================================================================================
 */
#include <SDL2/SDL_mixer.h>

#define SND_GUNSHOT_PATH "./data/sfx/cg1.wav"
extern Mix_Chunk* gGunshot;
extern bool sound_init ();
extern void sound_quit ();
