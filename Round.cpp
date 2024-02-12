#include "Round.h"
#include "LTarget.h"
#include "OpenBlank.h"
#include "Player.h"
#include "LTexture.h"
#include "Movement.h"
#include "Game.h"

Round rnd; //I get around
extern bool quit;
static void round1_start ();
static void round2_start ();
static bool round1_update ();

#define NUM_ROUNDS 2
void (*round_p[NUM_ROUNDS]) () =
{
	round1_start, round2_start
};


Round::Round()
{
	rnd.setRoundStart(round1_start);
}

void Round::start ()
{
	for (int i = 1; i < MAX_TARGETS; i++) //TODO Should be in LTarget.cpp probably
	{
		gTargets[i].setType (TARGET_NONE);
	}
	players[0].roundStart();
	int r = game.getRound();
	fprintf (stdout, "Starting round #%i\n", r);
	if (r > NUM_ROUNDS - 1)
	{
		fprintf (stderr, "Cowardly refusing to load a level that doesn't exist\n");
		quit = true;
		return;
	}
	mTickStart = SDL_GetTicks();
	mActive = true;
	(*round_p[r]) (); //Call the level setup routine
	//rnd.callRoundStart();
}

void Round::end ()
{
	mActive = false;
	int r = game.getRound();
	fprintf (stdout, "Ending round #%i\n", r);
	game.setRound(r + 1);
	fprintf (stdout, "Should be round #%i\n", r);
	start();
	//round_next ();
	//quit = true;
}

void Round::update ()
{
	mDuration = SDL_GetTicks () - mTickStart;
	if (mDuration > (mTimeout * 1000))
		end();
	if (rnd.callRoundUpdate() != true)
		end();
}

int Round::getTimeout ()
{
	return mTimeout;
}


int Round::getDuration ()
{
	return mDuration;
}

void Round::setTimeout (int seconds)
{
	mTimeout = seconds;
}

bool Round::isActive ()
{
	return mActive;
}
void Round::setTarget (int value)
{
	target = value;
}

int Round::getTarget ()
{
	return target;
}

static Uint32 round1_lastSpawn;

static void round1_addTarget ()
{
	int t = add_target (640,400, TARGET_RED, 40 * SCALE_X, 40, 1);
	if (t == -1)
		return; //Didn't get a target
	fprintf (stdout, "Adding target %i\n", t);
	gTargets[t].setMoveFunc (move_gravity);
	gTargets[t].setVal(VAL_GRAVITY, -0.4);
	gTargets[t].setVal(VAL_DY, getRandom(13, 18));
	gTargets[t].setVal(VAL_DX, getRandom(-10, 10));
	fprintf (stdout, "Target gravity=%f dy=%f dx=%f\n", gTargets[t].getVal(VAL_GRAVITY), gTargets[t].getVal(VAL_DY), gTargets[t].getVal(VAL_DX));
}

static int round1_getSpawnDelay ()
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

static void round1_start ()
{
	fprintf (stdout, "Roooound 1.....FIGHT\n");

	textures[0].loadFromFile ("./data/png/bg1.png");
	textures[1].loadFromFile (TEXTURE_REDTARGET_PATH);
	textures[2].loadFromFile (TEXTURE_BLUETARGET_PATH);

	add_target (0,0, TARGET_IMAGE, 640 * SCALE_X, 480, 0); //TODO Backgrounds please, not this shit
	//add_target (640,400, TARGET_RED, 40 * SCALE_X, 40, 1);
	//round1_addTarget ();
	//add_target (0,40, TARGET_BLUE, 40 * SCALE_X, 40, 2);
	//gTargets[1].setVal(VAL_GRAVITY, -0.4);
	//gTargets[1].setVal(VAL_DY, 20);
	//gTargets[1].setVal(VAL_DX, 0);
	rnd.setTarget(30);
	rnd.setTimeout(30);
	rnd.setRoundUpdate(round1_update);
}

static bool round1_update ()
{
	int i;
	int active_targets = 0;
	for (i = 0; i < MAX_TARGETS;i++)
	{
		if (gTargets[i].getType() != TARGET_NONE && gTargets[i].getType() != TARGET_IMAGE)
			active_targets++;
	}

	if (active_targets < rnd.getTarget() && round1_lastSpawn + round1_getSpawnDelay() < SDL_GetTicks ()) //Don't spawn another one
	{
		round1_addTarget();
		round1_lastSpawn = SDL_GetTicks();
	}

	if (players[0].getHits() >= rnd.getTarget())
	{
		return false;
	}
	return true;
}

static void round2_start ()
{
	gTargets[0].setPosition (SDL_Point {0, 40});
	gTargets[1].setPosition (SDL_Point {0, 0});
	gTargets[0].setType (TARGET_RED);
	gTargets[1].setType (TARGET_BLUE);
	gTargets[0].mHeight = 40;
	gTargets[0].mWidth = 40 * SCALE_X;
	gTargets[1].mHeight = 40;
	gTargets[1].mWidth = 40 * SCALE_X;
	rnd.setTarget(2);
	rnd.setRoundUpdate(round1_update);
}
