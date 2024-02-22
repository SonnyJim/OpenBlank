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

const int drawDelay = 1000;

#define VAL_DRAWDELAY 3 //How long before they draw
#define VAL_FIREDELAY 4 //How long after they draw before they fire
#define VAL_FIRING 5 //How long after they draw before they fire
			//
static void cowboy_move (LTarget* pTarget)
{
	if (pTarget->getSpawnTime () + drawDelay + pTarget->getVal(VAL_DRAWDELAY) < SDL_GetTicks() &&
			pTarget->getType() == TARGET_IMAGE)
	{
		fprintf (stdout, "DRAW!\n");
		pTarget->setType(TARGET_RED);
		pTarget->textureNumber = 1;
		pTarget->setSpawnTime();
	}
	else if (pTarget->getType() == TARGET_RED && pTarget->getVal(VAL_FIRING) == 0 &&
			pTarget->getSpawnTime() + pTarget->getVal(VAL_FIREDELAY) < SDL_GetTicks())
	{
		int lives = players[0].getLives();
		pTarget->setVal(VAL_FIRING, 1);
		lives -= 1;
		players[0].setLives(lives);
		fprintf (stdout,"Got you\n");
	}

}


static void cowboy_add (int x, int y)
{
	fprintf (stdout, "Adding Cowboy %i,%i\n", x, y);
	int w = textures[0].getWidth() * SCALE_X;
	int h = textures[0].getHeight();

	int t = add_target (x, y, TARGET_IMAGE, w, h, 0);
	gTargets[t].setMoveFunc (cowboy_move);
	//gTargets[t].setDeathFunc (asteroid_split);
	gTargets[t].setVal(VAL_DRAWDELAY, getRandom(0, 2000));
	gTargets[t].setVal(VAL_FIREDELAY, getRandom(500, 1000));
	gTargets[t].setVal(VAL_FIRING, 0);
}

void quickdraw_start ()
{
	int i;
	fprintf (stdout, "Quick draw start\n");
	//load_sfx();
	bg.clear();
	bg.set ("./data/png/QuickDraw/bg.png");
	//Render the nmbser 0-9 on some textres
	textures[0].loadFromFile("./data/png/QuickDraw/Cowboy.png");
	textures[1].loadFromFile("./data/png/QuickDraw/Cowboy_Gun.png");

	int w = textures[0].getWidth() * SCALE_X;
	cowboy_add ((SCREEN_WIDTH * SCALE_X /2) - w, 50);	
			
	rnd.setTarget(1);
	rnd.setTimeout(30);
	rnd.setRoundUpdate(quickdraw_update);
}

bool quickdraw_update () //TODO Convert to skeet shooting?
{
	if (players[0].getHits() >= rnd.getTarget())
	{
		return false;
	}
	return true;
}

