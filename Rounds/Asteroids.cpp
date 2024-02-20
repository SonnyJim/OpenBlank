#include <SDL2/SDL.h>
#include "Rounds.h"
#include "../LTarget.h"
#include "../LTexture.h"
#include "../Background.h"
#include "../Movement.h"
#include "../OpenBlank.h"
#include "../Round.h"
#include "../Player.h"
#include "../Media.h"
#include "../Sound.h"
#include "../SDL.h"

#define NUM_SIZES 4

static void asteroid_add (int x, int y, int size);

static const int sizes[] = {320,160,80,60};
static void asteroid_split (LTarget* pTarget)
{
	double size = pTarget->getVal(VAL_SIZE);
	SDL_Point p = pTarget->getPosition();
	fprintf (stdout, "Target hit size %f\n", size);
	size = size /2;
	if (size >= 40)
	{
		asteroid_add (p.x, p.y, size);	
		asteroid_add (p.x, p.y, size);	
	}
}

static void asteroid_move (LTarget* pTarget)
{
	double dy, dx, angle, size;
	dx = pTarget->getVal(VAL_DX);
	dy = pTarget->getVal(VAL_DY);
	size = pTarget->getVal(VAL_SIZE);
	angle = pTarget->getAngle();
	SDL_Point p = pTarget->getPosition();
	//Bounds check
	if (p.x + dx + size >= (SCREEN_WIDTH * SCALE_X) || p.x + dx <= 0)
	{
		dx = -dx;
	}
	if (p.y + dy + size >= SCREEN_HEIGHT || p.y + dy <= 0)
	{
		dy = -dy;
	}
		
	pTarget->setVal(VAL_DX, dx);
	pTarget->setVal(VAL_DY, dy);
	p.x += dx;
	p.y += dy; //SDL coords are 0,0 is top left
	pTarget->setPosition(p);
/*
	angle += pTarget->getVal(VAL_ROTSPEED);
	pTarget->setAngle(angle);
	*/
}


static void asteroid_add (int x, int y, int size)
{
	fprintf (stdout, "Adding asteroid %i,%i size: %i\n", x, y, size);
	int t = add_target (x, y, TARGET_RED, size, size, getRandom(0,2));
	gTargets[t].setMoveFunc (asteroid_move);
	gTargets[t].setDeathFunc (asteroid_split);
	gTargets[t].setVal (VAL_SIZE, size);
	gTargets[t].setVal(VAL_DX, getRandom(-10, 10));
	gTargets[t].setVal(VAL_DY, getRandom(-10, 10));
	/*
	gTargets[t].setVal(VAL_GRAVITY, 0);
	gTargets[t].setVal(VAL_ROTSPEED, getRandom(-10, 10));
	gTargets[t].setAngle (getRandom (0, 359));
	*/

}

void asteroids_start ()
{
	int i;
	fprintf (stdout, "Asteroids start\n");
	//load_sfx();
	bg.clear();
	bg.set ("./data/png/Asteroids/bg.png");
	//Render the nmbser 0-9 on some textres
	textures[0].loadFromFile("./data/png/Asteroids/1.png");
	textures[1].loadFromFile("./data/png/Asteroids/2.png");
	textures[2].loadFromFile("./data/png/Asteroids/3.png");

	fprintf (stdout, "\n");
	asteroid_add (SCREEN_WIDTH /2, SCREEN_HEIGHT /2, sizes[0]);	
			
	rnd.setTarget(10);
	rnd.setTimeout(30);
	rnd.setRoundUpdate(shootNumbers_update);
}

bool asteroids_update () //TODO Convert to skeet shooting?
{
	if (players[0].getHits() >= rnd.getTarget())
	{
		return false;
	}
	return true;
}

