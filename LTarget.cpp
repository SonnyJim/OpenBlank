#include "LTarget.h"
#include "LTexture.h"
#include "OpenBlank.h"

LTarget gTargets[ MAX_TARGETS ]; 

LTarget::LTarget()
{
	mPosition.x = 0;
	mPosition.y = 0;
	mWidth = 40; //FIXME
	mHeight = 40;
	mType = TARGET_NONE;
	//mCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
}

void LTarget::hit()
{
	//Target was hit, do some stuff
	mType = TARGET_NONE;
}

void LTarget::setPosition( int x, int y )
{
	mPosition.x = x;
	mPosition.y = y;
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

void LTarget::render()
{
	if (getType() == TARGET_NONE)
		return;
	SDL_Rect t;
	t.x = 0;
	t.y = 0;
	t.w = 40 * SCALE_X; //FIXME do dynamically
	t.h = 40;
	if (getType() == TARGET_RED)
		gRedTargetTexture.render (mPosition.x, mPosition.y, &t);
	else if (getType() == TARGET_BLUE)
		gBlueTargetTexture.render (mPosition.x, mPosition.y, &t);
	
}

void LTarget::movement()
{
	if (getType () == TARGET_NONE)
		return;
	mPosition.x += 1 * SCALE_X;
	if (bounds_check (mPosition.x, mPosition.y, mWidth, mHeight) == false)
	{
		fprintf(stdout, "Killing target\n");
		mType = TARGET_NONE;
		exit(1);
	}
}
