/*
 * =====================================================================================
 *
 *       Filename:  Bullethole.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  02/04/2024 10:40:00 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Dr. Fritz Mehner (mn), mehner@fh-swf.de
 *        Company:  FH Südwestfalen, Iserlohn
 *
 * =====================================================================================
 */

#include "BulletHole.h"

BulletHole gBulletHoles[MAX_BULLETHOLES];

BulletHole::BulletHole()
{
	mTicks = 0;
	mActive = false;
	mPosition = {0,0};
}

void BulletHole::add()
{
	for (int i = 0; i < MAX_BULLETHOLES;i++)
	{
		if (gBulletHoles[i].mActive == false)
		{
			gBulletHoles[i].mActive = true;
			gBulletHoles[i].mTicks = SDL_GetTicks();
			SDL_GetMouseState (&gBulletHoles[i].mPosition.x, &gBulletHoles[i].mPosition.y);
			break;
		}
	}
	//TODO Handle if we don't find an empty spot
}

void BulletHole::render()
{

}

#define BULLET_LIFETIME 2000
void BulletHole::update()
{
	if (mTicks + BULLET_LIFETIME < SDL_GetTicks())
	{
		mActive = false;
		mTicks = 0;
	}
}

