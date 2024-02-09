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
#include <SDL2/SDL.h>

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
#include <cmath> // for trigonometric functions like sin and cos

// Define constants for the circular motion
const double centerX = SCREEN_WIDTH / 2; // X-coordinate of the center of the circle
const double centerY = SCREEN_HEIGHT / 2; // Y-coordinate of the center of the circle
const double radius = 100;  // Radius of the circle
const double speed = 0.05;  // Angular speed (radians per frame)

enum valMove_t
{
	VAL_ANGLE,
};

// Update function (called once per frame)
void move_circle(LTarget* pTarget)
{
	double angle = pTarget->getVal(VAL_ANGLE); // Initial angle
	SDL_Point p = pTarget->getPosition();
	
	
    // Calculate new position based on the current angle
    p.x = centerX + radius * std::cos(angle);
    p.y = centerY + radius * std::sin(angle);

    // Set the position of the sprite
    pTarget->setPosition(p);

    // Increment the angle for the next frame
	angle += speed;

	// Ensure the angle stays within the range [0, 2*pi)
	if (angle >= 2 * M_PI)
	{
		angle -= 2 * M_PI;
	}
	pTarget->setVal (VAL_ANGLE, angle);
}

void move_right (LTarget* pTarget)
{
	SDL_Point p = pTarget->getPosition ();
	p.x += 1;
	pTarget->setPosition (p);
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


