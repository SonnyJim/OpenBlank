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
#define SND_GUNSHOT_PATH "./data/sfx/cg1.wav"

#include <string>

#define MAX_ROUNDSOUNDS 16

#define MAX_SOUNDS 3
enum sfx_t
{
	SFX_GUNSHOT,
	SFX_ERROR,
	SFX_TICKING,
};

extern const char* soundpaths[];

class Sound
{
	public:
		bool init();
		void quit();
		void playSFX (sfx_t sfx);
		void playRoundSFX (int sfx_num);
		void loadRoundSFX (int sfx_num, const char* path);
		void freeRoundSounds ();
	private:
};
//extern Mix_Chunk* gGunshot;
extern Sound sound;
/*
extern Mix_Chunk* gGunshot;
extern bool sound_init ();
extern void sound_quit ();
*/
