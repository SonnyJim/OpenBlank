#include <SDL2/SDL.h>
#include <cstdlib>
#include "Rounds.h"
#include "../LTarget.h"
#include "../LTexture.h"
#include "../Background.h"
#include "../Movement.h"
#include "../OpenBlank.h"
#include "../Round.h"
#include "../Player.h"
#include "../Sound.h"

static Uint32 fountain_lastSpawn;

const int numSfx = 3;
static const char* FountainSndPaths[] = 
{
	"./data/sfx/Fountain/194683__kingsrow__breakingvase03.wav",
	"./data/sfx/Fountain/194684__kingsrow__breakingvase02.wav",
	"./data/sfx/Fountain/194685__kingsrow__breakingvase01.wav",
};

static void load_sfx ()
{
	for (int i = 0; i <numSfx; i++)
	{
		sound.loadRoundSFX (i, FountainSndPaths[i]);
	}
}


static LTargetType fountain_getRandomTarget (int percent) //TODO This isn't percent
{
	int random = getRandomInt(0,percent);
	if (random == 1)
		return TARGET_BOMB;
	else
		return TARGET_RED;
}

static void FountainDeathFunc (LTarget* pTarget)
{
	fprintf (stdout, "Pop\n");
	sound.playRoundSFX (rand() % 3);
}
static void fountain_addTarget ()
{
	int t = add_target (640,400, fountain_getRandomTarget(10), 40 * SCALE_X, 40, 1);
	if (t == -1)
		return; //Didn't get a target
	if (gTargets[t].getType() == TARGET_BOMB)
		gTargets[t].textureNumber = 3;
	fprintf (stdout, "Adding target %i\n", t);
	gTargets[t].setMoveFunc (move_gravity);
	gTargets[t].setDeathFunc (FountainDeathFunc);
	gTargets[t].setVal(VAL_GRAVITY, -0.4);
	gTargets[t].setVal(VAL_DY, getRandom(13, 18));
	gTargets[t].setVal(VAL_DX, getRandom(-10, 10));
	fprintf (stdout, "Target gravity=%f dy=%f dx=%f\n", gTargets[t].getVal(VAL_GRAVITY), gTargets[t].getVal(VAL_DY), gTargets[t].getVal(VAL_DX));
}

static int fountain_getSpawnDelay ()
{
	int duration = rnd.getDuration() / 1000;

	if (duration < 5)
		return 2000;
	else if (duration < 10)
		return 1000;
	else if (duration < 20)
		return 500;
	else if (duration < 25)
		return 200;
	else
		return 40;
	
}

void fountain_start ()
{
	fprintf (stdout, "Roooound 1.....FIGHT\n");
	load_sfx ();
//	textures[0].loadFromFile ("./data/png/bg1.png");
	bg.set ("./data/png/bg1.png");
	textures[1].loadFromFile (TEXTURE_REDTARGET_PATH);
	textures[2].loadFromFile (TEXTURE_BLUETARGET_PATH);
	textures[3].loadFromFile (TEXTURE_BOMB_PATH);
//	add_target (0,0, TARGET_IMAGE, 640 * SCALE_X, 480, 0); //TODO Backgrounds please, not this shit
	//add_target (640,400, TARGET_RED, 40 * SCALE_X, 40, 1);
	//fountain_addTarget ();
	//add_target (0,40, TARGET_BLUE, 40 * SCALE_X, 40, 2);
	//gTargets[1].setVal(VAL_GRAVITY, -0.4);
	//gTargets[1].setVal(VAL_DY, 20);
	//gTargets[1].setVal(VAL_DX, 0);
	rnd.setTarget(30);
	rnd.setTimeout(30);
	rnd.setRoundUpdate(fountain_update);
}

bool fountain_update () //TODO Convert to skeet shooting?
{
	int i;
	int active_targets = 0;
	for (i = 0; i < MAX_TARGETS;i++)
	{
		if (gTargets[i].getType() != TARGET_NONE && gTargets[i].getType() != TARGET_IMAGE)
			active_targets++;
	}

	if (active_targets < rnd.getTarget() && fountain_lastSpawn + fountain_getSpawnDelay() < SDL_GetTicks ()) //Don't spawn another one
	{
		fountain_addTarget();
		fountain_lastSpawn = SDL_GetTicks();
	}

	if (players[0].getHits() >= rnd.getTarget())
	{
		return false;
	}
	return true;
}

