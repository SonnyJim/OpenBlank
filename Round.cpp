#include "Round.h"
#include "LTarget.h"
#include "OpenBlank.h"
#include "Player.h"
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
	players[0].roundStart();
	int r = game.getRound();
	fprintf (stdout, "Starting round #%i\n", r);
	if (r > NUM_ROUNDS - 1)
	{
		fprintf (stderr, "Cowardly refusing to load a level that doesn't exist\n");
		quit = true;
		return;
	}
	(*round_p[r]) (); //Call the level setup routine
	//rnd.callRoundStart();
}

void Round::end ()
{
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
	if (rnd.callRoundUpdate() != true)
		end();
}

bool Round::isActive ()
{
	return false;
}
void Round::setTarget (int value)
{
	target = value;
}

int Round::getTarget ()
{
	return target;
}

static void round1_start ()
{
	fprintf (stdout, "Roooound 1.....FIGHT\n");
	if (!gTargets[0].loadFromFile ("./data/png/RedTarget.png"))
	{
		fprintf (stderr, "Error loading texture RedTarget\n");
		quit = true;
	}
	
	if (!gTargets[1].loadFromFile ("./data/png/BlueTarget.png"))
	{
		fprintf (stderr, "Error loading texture BlueTarget\n");
		quit = true;
	}

	gTargets[0].setPosition (0, 0);
	gTargets[1].setPosition (0, 40);
	gTargets[0].setType (TARGET_RED);
	gTargets[1].setType (TARGET_BLUE);
	gTargets[0].mHeight = 40;
	gTargets[0].mWidth = 40 * SCALE_X;
	gTargets[1].mHeight = 40;
	gTargets[1].mWidth = 40 * SCALE_X;

	rnd.setTarget(2);
	rnd.setRoundUpdate(round1_update);
}

static bool round1_update ()
{
	if (players[0].getHits() >= rnd.getTarget())
	{
		return false;
	}
	return true;
}

static void round2_start ()
{
	gTargets[0].setPosition (0, 40);
	gTargets[1].setPosition (0, 0);
	gTargets[0].setType (TARGET_RED);
	gTargets[1].setType (TARGET_BLUE);
	gTargets[0].mHeight = 40;
	gTargets[0].mWidth = 40 * SCALE_X;
	gTargets[1].mHeight = 40;
	gTargets[1].mWidth = 40 * SCALE_X;
	rnd.setTarget(2);
	rnd.setRoundUpdate(round1_update);
}
