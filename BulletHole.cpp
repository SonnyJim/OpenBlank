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
#include "OpenBlank.h"
#include "SDL.h"

BulletHole gBulletHoles[MAX_BULLETHOLES];

BulletHole::BulletHole()
{
	mTicks = 0;
	mActive = false;
	mPosition = {0,0};
}

void bullet_add()
{
	for (int i = 0; i < MAX_BULLETHOLES;i++)
	{
		if (gBulletHoles[i].isActive() == false)
		{
			gBulletHoles[i].add();
			return;
		}
	}
	//TODO Handle if we don't find an empty spot
}


bool BulletHole::isActive()
{
	return mActive;
}

void BulletHole::add()
{
	mActive = true;
	mTicks = SDL_GetTicks();
	SDL_GetMouseState (&mPosition.x, &mPosition.y);
}

void BulletHole::render()
{
	if (mActive == false)
		return;
	SDL_Rect t;
	const int bullethole_size = 4;

	t.x = mPosition.x - (bullethole_size / 2);
	t.y = mPosition.y - (bullethole_size / 2);
	t.w = bullethole_size * SCALE_X; //FIXME do dynamically
	t.h = bullethole_size;
	
	SDL_SetRenderDrawColor( gRenderer, 0xFF, 0x00, 0xFF, 0xFF );
	SDL_RenderFillRect (gRenderer, &t);
		
}

#define BULLET_LIFETIME 2000
void BulletHole::update()
{
	if (mActive == false)
		return;
	else if (mTicks + BULLET_LIFETIME < SDL_GetTicks())
	{
		mActive = false;
		mTicks = 0;
	}
}

