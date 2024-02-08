#include <string>
#include "LTarget.h"
#include "LTexture.h"
#include "OpenBlank.h"
#include "Player.h"
#include "Movement.h"
#include "SDL.h"

LTarget gTargets[ MAX_TARGETS ]; 

LTarget::LTarget()
{
	mPosition.x = 0;
	mPosition.y = 0;
	mWidth = 40; //FIXME
	mHeight = 40;
	mType = TARGET_NONE;
	setDeathFunc(nullptr);
	//mCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
}

void LTarget::hit()
{
	//Target was hit, do some stuff
	//TODO this is skeleton code that will need to be replaced
	if (mType != TARGET_BUTTON && mType != TARGET_IMAGE)
	{
		players[0].addHit (1);
		fprintf (stdout, "HIT %i\n", players[0].getHits());
		mType = TARGET_NONE;
		free();
	}

	if (mType != TARGET_IMAGE)
		callDeathFunc();

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
	mAngle = degrees;
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

void LTarget::movement()
{
	if (getType () == TARGET_NONE || getType () == TARGET_IMAGE)
		return;
	
	SDL_Point r = callMoveFunc(getPosition());
	setPosition(r);
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

//TODO add custom function pointer stuff
bool add_target (int x, int y, LTargetType type, int width, int height, int texture)
{
	int i;
	//Find an empty target spot
	for (i = 0; i < MAX_TARGETS; i++)
	{
		fprintf (stdout, "#%i type %i\n", i, gTargets[i].getType());
		//Fill it with the data
		//TODO Add in defaults
		if (gTargets[i].getType() == TARGET_NONE)
		{
			fprintf (stdout, "Creating target #%i type %i\n", i, type);
			gTargets[i].setPosition (SDL_Point {x, y});
			gTargets[i].setType (type);
			fprintf (stdout, "Type is now %i\n", gTargets[i].getType());
			gTargets[i].mHeight = height;
			gTargets[i].mWidth = width;
			gTargets[i].textureNumber = texture;
			return true;
		}
	}
	fprintf (stderr, "No target for you!");
	return false;
}

void LTarget::free()
{
	//Free texture if it exists
	mWidth = 0;
	mHeight = 0;
	mType = TARGET_NONE;
	mAngle = 0;
	setDeathFunc (NULL);

}

//void LTarget::render( int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip )
void LTarget::render()
{
	if (mType == TARGET_NONE)
		return;
	int x = mPosition.x;
	int y = mPosition.y;
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };
	
	/*
	//Set clip rendering dimensions
	if( mClip != NULL )
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}
*/
	//Render to screen
	SDL_RenderCopyEx( gRenderer, textures[textureNumber].getTexture(), NULL, &renderQuad, mAngle, &mCenter, mFlip );
}



