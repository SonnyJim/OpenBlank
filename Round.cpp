#include "Round.h"
#include "LTarget.h"
#include "OpenBlank.h"
#include "Player.h"
#include "LTexture.h"
#include "Movement.h"
#include "Game.h"
#include "Background.h"
#include "Sound.h"
#include "Rounds/Rounds.h"

extern bool quit;

#define NUM_ROUNDS 9
void (*round_p[NUM_ROUNDS]) () =
{
	 telephone_start, simon_start, fountain_start, quickdraw_start, shootNumbers_start, asteroids_start, saloon_start, burger_start, speller_start
};

Round rnd; //I get around
Round::Round()
{
	rnd.setRoundStart(round_p[0]);
}

void Round::start ()
{
	clear_targets();
	sound.freeRoundSounds();
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
	hurryUpActive = false;
	(*round_p[r]) (); //Call the level setup routine
	//rnd.callRoundStart();
}

void Round::end ()
{
	mActive = false;
	sound.stopSFX(-1);
	bg.clear ();
	//TODO Free textures?
	int r = game.getRound();
	fprintf (stdout, "Ending round #%i\n", r);
	game.setRound(r + 1);
	start();
}

void Round::update ()
{
	mDuration = SDL_GetTicks () - mTickStart;
	if ((mTimeout * 1000) - mDuration < 5000 && !hurryUpActive)
	{
		hurryUpActive = true;
		sound.playSFX(SFX_TICKING);
	}
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
