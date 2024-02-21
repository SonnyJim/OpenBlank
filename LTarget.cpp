#include <string>
#include "LTarget.h"
#include "LTexture.h"
#include "OpenBlank.h"
#include "Player.h"
#include "Movement.h"
#include "SDL.h"
extern bool quit;

LTarget gTargets[ MAX_TARGETS ]; 

LTarget::LTarget()
{
	mPosition.x = 0;
	mPosition.y = 0;
	mWidth = 40; //FIXME
	mHeight = 40;
	mType = TARGET_NONE;
	setDeathFunc(nullptr);
	setMoveFunc(nullptr);
	//mCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
}

void LTarget::hit()
{
	//Target was hit, do some stuff
	//TODO this is skeleton code that will need to be replaced
	if (mType == TARGET_BOMB)
	{
		int lives = players[0].getLives();
		lives -= 1;
		players[0].setLives(lives);
		mType = TARGET_NONE;
	}
	else if (mType != TARGET_BUTTON && mType != TARGET_IMAGE && mType != TARGET_CHECKMARK) //TODO Probably shorter to specficy what I want, rather want I don't want
	{
		callDeathFunc(this);
		players[0].addHit (1);
		fprintf (stdout, "HIT %i\n", players[0].getHits());
		mType = TARGET_NONE;
		free();
	}

	if (mType != TARGET_IMAGE)
		callDeathFunc(this);

}

void LTarget::setPosition( SDL_Point p)
{
	mPosition.x = p.x;
	mPosition.y = p.y;
}

SDL_Point LTarget::getPosition()
{
	SDL_Point p;
	p.x = mPosition.x;
	p.y = mPosition.y;
	return p;
}


void LTarget::setAngle(double degrees)
{
	if (degrees > 360)
		degrees = degrees - 360;
	mAngle = degrees;
}

double LTarget::getAngle()
{
	return mAngle;;
}



void LTarget::setCenter (SDL_Point point)
{
	mCenter = point;
}

void LTarget::setFlip (SDL_RendererFlip type)
{
	mFlip = type;
}

void LTarget::setType(LTargetType type)
{
	mType = type;
}

SDL_Rect LTarget::getRect ()
{
	SDL_Rect r;
	r.x = mPosition.x;
	r.y = mPosition.y;
	r.w = mWidth;
	r.h = mHeight;
	return r;
}

LTargetType LTarget::getType ()
{
	return mType;
}

double LTarget::getVal(int val)
{
	if (val > MAX_VALS)
	{
		fprintf (stderr, "Target getVal error, %i is more than %i\n", val, MAX_VALS);
		quit = true;
		return 0;
	}
	else
		return mVals[val];
}

void LTarget::setVal(int val, double value)
{
	if (val > MAX_VALS)
	{
		fprintf (stderr, "Target setVal error, %i is more than %i\n", val, MAX_VALS);
		quit = true;
	}
	else
		mVals[val] = value;
}
/*
void LTarget::setMoveType()
{
}
*/
void LTarget::movement()
{
	if (getType () == TARGET_NONE)
		return;
	
	callMoveFunc (this);
	//setPosition(r);
	/*
	mPosition.x += 1 * SCALE_X;
	if (bounds_check (mPosition.x, mPosition.y, mWidth, mHeight) == false)
	{
		fprintf(stdout, "Killing target\n");
		mType = TARGET_NONE;
		exit(1);
	}
	*/
}

int add_target (int x, int y, LTargetType type, int width, int height, int texture)
{
	int i;
	//Find an empty target spot
	for (i = 0; i < MAX_TARGETS; i++)
	{
		//Fill it with the data
		//TODO Add in defaults
		if (gTargets[i].getType() == TARGET_NONE)
		{
			fprintf (stdout, "Creating target #%i type %i\n", i, type);
			gTargets[i].setPosition (SDL_Point {x, y});
			gTargets[i].setType (type);
			gTargets[i].mHeight = height;
			gTargets[i].mWidth = width;
			gTargets[i].textureNumber = texture;
			gTargets[i].setSpawnTime();
			return i;
		}
	}
	fprintf (stderr, "No target for you!\n");
	return -1;
}

void clear_targets ()
{
	for (int i=0;i < MAX_TARGETS; i++)
		gTargets[i].free();
}

void LTarget::setSpawnTime ()
{
	mSpawnTime = SDL_GetTicks();
}

Uint32 LTarget::getSpawnTime ()
{
	return mSpawnTime;
}


void LTarget::free()
{
	//Free texture if it exists
	mWidth = 0;
	mHeight = 0;
	mType = TARGET_NONE;
	mAngle = 0;
	setDeathFunc (NULL);
	setMoveFunc (NULL);

}

#define CHECKMARK_DELAY 500
//void LTarget::render( int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip )
void LTarget::render()
{
	if (mType == TARGET_NONE)
		return;
	int x = mPosition.x;
	int y = mPosition.y;
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };
	
	if (mType == TARGET_CHECKMARK && getSpawnTime() + CHECKMARK_DELAY < SDL_GetTicks())
	{
		free();
		return; //Don't try to render an deleted target
	}
	//Render to screen
	if (textureNumber != TEXTURE_INVISIBLE)
	{
		if (mType == TARGET_CHECKMARK)
			SDL_RenderCopyEx( gRenderer, gCheckmarkTexture.getTexture(), NULL, &renderQuad, mAngle, &mCenter, mFlip );
		else
			SDL_RenderCopyEx( gRenderer, textures[textureNumber].getTexture(), NULL, &renderQuad, mAngle, &mCenter, mFlip );
	}
}
