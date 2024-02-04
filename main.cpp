/*This source code copyrighted by Lazy Foo' Productions 2004-2024
and may not be redistributed without written permission.*/

//Using SDL, SDL_image, standard IO, and strings
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCALE_X = 2; //Because my arcade cab has double X resolution because reasons

//Button constants
//const int BUTTON_WIDTH = 300;
//const int BUTTON_HEIGHT = 200;
const int MAX_TARGETS = 4;

enum LTargetType
{
	TARGET_NONE,
	TARGET_RED,
	TARGET_BLUE,
};

class LTexture
{
	public:
		//Initializes variables
		LTexture();

		//Deallocates memory
		~LTexture();

		//Loads image at specified path
		bool loadFromFile( std::string path );
		
		#if defined(SDL_TTF_MAJOR_VERSION)
		//Creates image from font string
		bool loadFromRenderedText( std::string textureText, SDL_Color textColor );
		#endif
		
		//Deallocates texture
		void free();

		//Set color modulation
		void setColor( Uint8 red, Uint8 green, Uint8 blue );

		//Set blending
		void setBlendMode( SDL_BlendMode blending );

		//Set alpha modulation
		void setAlpha( Uint8 alpha );
		
		//Renders texture at given point
		void render( int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );

		//Gets image dimensions
		int getWidth();
		int getHeight();

	private:
		//The actual hardware texture
		SDL_Texture* mTexture;
		//Image dimensions
		int mWidth;
		int mHeight;
};

class LTarget
{
	public:
		//Initializes internal variables
		LTarget();

		//Sets top left position
		void setPosition( int x, int y );
		//Handles mouse event
		void handleEvent( SDL_Event* e );
		void setType (LTargetType type);
		LTargetType getType ();	
		//Shows button sprite
		void render();
		void movement();
		int mWidth;
		int mHeight;

	private:
		//Top left position
		SDL_Point mPosition;
		LTargetType  mType;
		//Currently used global sprite
		//LTargetSprite mCurrentSprite;
};

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

//Mouse button sprites
//SDL_Rect gSpriteClips[ BUTTON_SPRITE_TOTAL ];
//LTexture gButtonSpriteSheetTexture;
LTexture gRedTargetTexture;
LTexture gBlueTargetTexture;
LTexture gCrosshairTexture;
//Buttons objects
LTarget gTargets[ MAX_TARGETS ]; 

LTexture::LTexture()
{
	//Initialize
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}

LTexture::~LTexture()
{
	//Deallocate
	free();
}

bool LTexture::loadFromFile( std::string path )
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

#if defined(SDL_TTF_MAJOR_VERSION)
bool LTexture::loadFromRenderedText( std::string textureText, SDL_Color textColor )
{
	//Get rid of preexisting texture
	free();

	//Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Solid( gFont, textureText.c_str(), textColor );
	if( textSurface == NULL )
	{
		printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
	}
	else
	{
		//Create texture from surface pixels
        mTexture = SDL_CreateTextureFromSurface( gRenderer, textSurface );
		if( mTexture == NULL )
		{
			printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
		}
		else
		{
			//Get image dimensions
			mWidth = textSurface->w;
			mHeight = textSurface->h;
		}

		//Get rid of old surface
		SDL_FreeSurface( textSurface );
	}
	
	//Return success
	return mTexture != NULL;
}
#endif

void LTexture::free()
{
	//Free texture if it exists
	if( mTexture != NULL )
	{
		SDL_DestroyTexture( mTexture );
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

void LTexture::setColor( Uint8 red, Uint8 green, Uint8 blue )
{
	//Modulate texture rgb
	SDL_SetTextureColorMod( mTexture, red, green, blue );
}

void LTexture::setBlendMode( SDL_BlendMode blending )
{
	//Set blending function
	SDL_SetTextureBlendMode( mTexture, blending );
}
		
void LTexture::setAlpha( Uint8 alpha )
{
	//Modulate texture alpha
	SDL_SetTextureAlphaMod( mTexture, alpha );
}

void LTexture::render( int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip )
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };

	//Set clip rendering dimensions
	if( clip != NULL )
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Render to screen
	SDL_RenderCopyEx( gRenderer, mTexture, clip, &renderQuad, angle, center, flip );
}

int LTexture::getWidth()
{
	return mWidth;
}

int LTexture::getHeight()
{
	return mHeight;
}

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

void LTarget::handleEvent( SDL_Event* e )
{
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

void render_crosshair ()
{
	int x, y;
	SDL_Rect t;
	t.x = 0;
	t.y = 0;
	t.w = 40 * SCALE_X; //FIXME do dynamically
	t.h = 40;
	SDL_GetMouseState( &x, &y );
	gCrosshairTexture.render (x - (t.w/2), y - (t.h/2), &t);
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

bool bounds_check (int x, int y, int w, int h)
{
	if (x + h > SCREEN_WIDTH)
		return false;
	else if (x - h < 0)
		return false;
	else if (y - h < 0)
		return false;
	else if (y + h > SCREEN_HEIGHT)
		return false;
	else
		return true;
}

void LTarget::movement()
{
	if (getType () == TARGET_NONE)
		return;
	mPosition.x += 1 * SCALE_X;
	if (bounds_check (mPosition.x, mPosition.y, mWidth, mHeight))
		mType = TARGET_NONE;
}

bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		gWindow = SDL_CreateWindow( "Open Blank", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, (SCREEN_WIDTH * SCALE_X), SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create vsynced renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
			if( gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}
			}
		}
	}
	SDL_ShowCursor (0);
	return success;
}

bool loadMedia()
{
	//Loading success flag
	bool success = true;
	
	if ( !gRedTargetTexture.loadFromFile ("./data/png/RedTarget.png"))
	{
		success = false;
	}
	else if ( !gBlueTargetTexture.loadFromFile ("./data/png/BlueTarget.png"))
	{
		success = false;
	}
	else if ( !gCrosshairTexture.loadFromFile ("./data/png/crosshairs.png"))
		success = false;
	else
	{
		gTargets[0].setPosition (0, 0);
		gTargets[1].setPosition (0, 40);
		gTargets[0].setType (TARGET_RED);
		gTargets[1].setType (TARGET_BLUE);
		gTargets[0].mHeight = 40;
		gTargets[0].mWidth = 40 * SCALE_X;
		gTargets[1].mHeight = 40;
		gTargets[1].mWidth = 40 * SCALE_X;
	}
	
/*		
	}
	//Load sprites
	if( !gButtonSpriteSheetTexture.loadFromFile( "./button.png" ) )
	{
		printf( "Failed to load button sprite texture!\n" );
		success = false;
	}
	else
	{
		//Set sprites
		for( int i = 0; i < BUTTON_SPRITE_TOTAL; ++i )
		{
			gSpriteClips[ i ].x = 0;
			gSpriteClips[ i ].y = i * 200;
			gSpriteClips[ i ].w = BUTTON_WIDTH;
			gSpriteClips[ i ].h = BUTTON_HEIGHT;
		}

		//Set buttons in corners
		gTargets[ 0 ].setPosition( 0, 0 );
		gTargets[ 1 ].setPosition( SCREEN_WIDTH - BUTTON_WIDTH, 0 );
		gTargets[ 2 ].setPosition( 0, SCREEN_HEIGHT - BUTTON_HEIGHT );
		gTargets[ 3 ].setPosition( SCREEN_WIDTH - BUTTON_WIDTH, SCREEN_HEIGHT - BUTTON_HEIGHT );
	}
*/
	if (!success)
		fprintf (stderr, "Failed to load textures\n");
	return success;
}

void close()
{
	//Free loaded images
	gRedTargetTexture.free();
	gBlueTargetTexture.free();
	gCrosshairTexture.free();
	//Destroy window	
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

void sdl_handleevent ()
{
}

void sdl_render ()
{
	//Clear screen
	SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
	SDL_RenderClear( gRenderer );

	//Render buttons
	for( int i = 0; i < MAX_TARGETS; ++i )
	{
		gTargets[ i ].render();
	}
	render_crosshair();
	//Update screen
	SDL_RenderPresent( gRenderer );

}

void movement_all ()
{
	for (int i = 0; i < MAX_TARGETS; ++i)
	{
		if (gTargets[i].getType() != TARGET_NONE )
		{
			gTargets[i].movement();
		}
	}
}

int main( int argc, char* args[] )
{
	//Start up SDL and create window
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		//Load media
		if( !loadMedia() )
		{
			printf( "Failed to load media!\n" );
		}
		else
		{	
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;

			//While application is running
			while( !quit )
			{
				//Handle events on queue
				while( SDL_PollEvent( &e ) != 0 )
				{
					//User requests quit
					if( e.type == SDL_QUIT )
					{
						quit = true;
					}
					
					//Handle button events
					for( int i = 0; i < MAX_TARGETS; ++i )
					{
						gTargets[ i ].handleEvent( &e );
					}
				}
				movement_all ();
				sdl_render ();
			}
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}
