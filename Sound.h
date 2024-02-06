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
#define MAX_SOUNDS 1

enum sfx_t
{
	SFX_GUNSHOT,
};

extern const char* soundpaths[];

class Sound
{
	public:
		bool init();
		void quit();
		void playSFX (sfx_t sfx);
	private:
};
//extern Mix_Chunk* gGunshot;
extern Sound sound;
/*
extern Mix_Chunk* gGunshot;
extern bool sound_init ();
extern void sound_quit ();
*/
