#include <string>
#include "LTarget.h"
#include "LTexture.h"
#include "OpenBlank.h"
#include "SDL.h"

LTarget gTargets[ MAX_TARGETS ]; 

LTarget::LTarget()
{
	mPosition.x = 0;
	mPosition.y = 0;
	mWidth = 40; //FIXME
	mHeight = 40;
	mType = TARGET_NONE;
	setDeathFunc(NULL);
	//mCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
}

void LTarget::hit()
{
	//Target was hit, do some stuff
	mType = TARGET_NONE;
	callDeathFunc();
}

void LTarget::setPosition( int x, int y )
{
	mPosition.x = x;
	mPosition.y = y;
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

bool LTarget::loadFromFile( std::string path )
{
	//Get rid of preexisting texture
	free();

	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}
	else
	{
		//Color key image
		SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );

		//Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
		if( newTexture == NULL )
		{
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}
		else
		{
			//Get image dimensions
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}

	//Return success
	mTexture = newTexture;
	return mTexture != NULL;
}


void LTarget::free()
{
	//Free texture if it exists
	if( mTexture != NULL )
	{
		SDL_DestroyTexture( mTexture );
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
		mType = TARGET_NONE;
		mAngle = 0;
	}
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
	SDL_RenderCopyEx( gRenderer, mTexture, NULL, &renderQuad, mAngle, &mCenter, mFlip );
}



