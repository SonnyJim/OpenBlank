#include <SDL2/SDL.h>

enum LTargetType
{
	TARGET_NONE,
	TARGET_RED,
	TARGET_BLUE,
};

class LTarget
{
	public:
		//Initializes internal variables
		LTarget();

		//Sets top left position
		void setPosition( int x, int y );
		//Handles mouse event
		//void handleEvent( SDL_Event* e );
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

const int MAX_TARGETS = 4;
extern LTarget gTargets[ MAX_TARGETS ]; 

extern bool bounds_check (int x, int y, int w, int h);
//extern LTexture gRedTargetTexture;
//extern LTexture gBlueTargetTexture;
//extern LTexture gCrosshairTexture;
