#include "Round.h"
#include "LTarget.h"
#include "OpenBlank.h"
#include "Player.h"

Round rnd; //I get around
extern bool quit;
static void round1_start ();
static bool round1_update ();

Round::Round()
{
	rnd.setRoundStart(round1_start);
	rnd.setRoundUpdate(round1_update);
}

void Round::start ()
{
	rnd.callRoundStart();
}

void Round::end ()
{
	fprintf (stdout, "Ending round\n");
	//round_next ();
	quit = true;
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

static void round1_start ()
{
	fprintf (stdout, "Setting up round 1\n");
	gTargets[0].setPosition (0, 0);
	gTargets[1].setPosition (0, 40);
	gTargets[0].setType (TARGET_RED);
	gTargets[1].setType (TARGET_BLUE);
	gTargets[0].mHeight = 40;
	gTargets[0].mWidth = 40 * SCALE_X;
	gTargets[1].mHeight = 40;
	gTargets[1].mWidth = 40 * SCALE_X;
}

static bool round1_update ()
{
	if (players[0].getHits() > 1)
		return false;
	return true;
}
