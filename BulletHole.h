/*
 * =====================================================================================
 *
 *       Filename:  BulletHole.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  02/05/2024 01:23:00 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Dr. Fritz Mehner (mn), mehner@fh-swf.de
 *        Company:  FH Südwestfalen, Iserlohn
 *
 * =====================================================================================
 */
#include <SDL2/SDL.h>
class BulletHole
{
	public:
		BulletHole();
		void add();
		void render();
		void update();
	private:
		bool	mActive;
		SDL_Point mPosition;
		Uint32	  mTicks;
};
const int MAX_BULLETHOLES = 16;
extern BulletHole gBulletHoles[MAX_BULLETHOLES];


