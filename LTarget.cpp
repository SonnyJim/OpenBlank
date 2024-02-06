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

void LTarget::setPosition( int x, int y )
{
	mPosition.x = x;
	mPosition.y = y;
}

void LTarget::setType(LTargetType type)
{
	mType = type;
}


LTargetType LTarget::getType ()
{
	return mType;
}
/*
void LTarget::handleEvent( SDL_Event* e )
{	
	if ( e->type == SDL_MOUSEBUTTONDOWN)
	{
		Mix_PlayChannel (-1, gGunshot, 0); //TODO Make a 'trigger pulled' function
		bullet_add();
	}
	//If mouse event happened
	if( e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP )
	{
		//Get mouse position
		int x, y;
		SDL_GetMouseState( &x, &y );

		//Check if mouse is in button
		bool inside = true;

		//Mouse is left of the button
		if( x < mPosition.x )
		{
			inside = false;
		}
		//Mouse is right of the button
		else if( x > mPosition.x + mWidth )
		{
			inside = false;
		}
		//Mouse above the button
		else if( y < mPosition.y )
		{
			inside = false;
		}
		//Mouse below the button
		else if( y > mPosition.y + mHeight )
		{
			inside = false;
		}

		//Mouse is inside button
		else
		if (inside)
		{
			//Set mouse over sprite
			switch( e->type )
			{
				case SDL_MOUSEMOTION:
				//mCurrentSprite = BUTTON_SPRITE_MOUSE_OVER_MOTION;
				break;
			
				case SDL_MOUSEBUTTONDOWN:
					setType (TARGET_NONE);
					//active = false;
					//mCurrentSprite = BUTTON_SPRITE_MOUSE_DOWN;
					break;
				
				case SDL_MOUSEBUTTONUP:
				//mCurrentSprite = BUTTON_SPRITE_MOUSE_UP;
				break;
			}
		}
	}
}

*/

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
