/*
 * =====================================================================================
 *
 *       Filename:  Movement.cpp
 *
 *    Description: 
 *
 *        Version:  1.0
 *        Created:  02/06/2024 12:47:26 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Dr. Fritz Mehner (mn), mehner@fh-swf.de
 *        Company:  FH Südwestfalen, Iserlohn
 *
 * =====================================================================================
 */

#include "LTarget.h"
#include "OpenBlank.h"
#include "BulletHole.h"

bool bounds_check (int x, int y, int w, int h)
{
	//fprintf (stdout, "x=%i,y=%i,w=%i,h=%i\n", x, y, w, h);
	if (x - w > SCREEN_WIDTH)
	{
		fprintf (stdout, "Offscreen + x\n");
		return false;
	}
	else if (x + w < 0)
		return false;
	else if (y < 0)
		return false;
	else if (y + h > SCREEN_HEIGHT)
		return false;
	else
		return true;
}

void movement_all ()
{
	int i;
	for (i = 0; i < MAX_TARGETS; ++i)
	{
		if (gTargets[i].getType() != TARGET_NONE )
		{
			gTargets[i].movement();
		}
	}

	for (i = 0; i < MAX_BULLETHOLES; i++)
	{
		gBulletHoles[i].update();
	}

}


