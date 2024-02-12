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
#include "Movement.h"
#include <SDL2/SDL.h>

#include <random>

double getRandom(double min, double max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dis(min, max);
    return dis(gen);
}


bool bounds_check (SDL_Rect r)
{
	//fprintf (stdout, "x=%i,y=%i,w=%i,h=%i\n", x, y, w, h);
	if (r.x - r.w > (SCREEN_WIDTH * SCALE_X))
	{
		return false;
	}
	else if (r.x + r.w < 0)
		return false;
	else if (r.y < (0 - (SCREEN_HEIGHT / 2))) //Allow half a screens worth up top
		return false;
	else if (r.y + r.h > SCREEN_HEIGHT)
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

void move_gravity(LTarget* pTarget)
{
	double dy, gravity;
	//fprintf (stdout, "move_gravity gravity=%f dy=%f dx=%f\n", pTarget->getVal(VAL_GRAVITY), pTarget->getVal(VAL_DY), pTarget->getVal(VAL_DX));
	dy = pTarget->getVal(VAL_DY);
	gravity = pTarget->getVal(VAL_GRAVITY);
	dy += gravity;
	pTarget->setVal(VAL_DY, dy);
	//fprintf (stdout, "dy: %f gravity %f\n", dy, gravity);
	SDL_Point p = pTarget->getPosition();
	p.y -= pTarget->getVal(VAL_DY); //SDL coords are 0,0 is top left
	p.x += pTarget->getVal(VAL_DX);
	pTarget->setPosition(p);
}

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
			if (bounds_check (gTargets[i].getRect()) == false && i != 0)//TODO Hack for the background
			{
				fprintf (stdout, "Killing offscreen target\n");
				gTargets[i].setType (TARGET_NONE);
			}
		}
	}

	for (i = 0; i < MAX_BULLETHOLES; i++)
	{
		gBulletHoles[i].update();
	}

}


