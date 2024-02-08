#include <SDL2/SDL.h>
#include <string>

enum LTargetType
{
	TARGET_NONE,
	TARGET_RED,
	TARGET_BLUE,
	TARGET_BUTTON,
	TARGET_IMAGE, //A plain image that ignores the death callback
};

class LTarget
{
	public:
		//Initializes internal variables
		LTarget();

		//Sets top left position
		void setPosition( int x, int y );
		void setAngle(double degrees);
		void setCenter (SDL_Point point);
		void setFlip (SDL_RendererFlip type);
		SDL_Rect getRect ();
		//Handles mouse event
		//void handleEvent( SDL_Event* e );
		void setType (LTargetType type);
		LTargetType getType ();	
		//Shows button sprite
		void movement();
		void hit();
		int mWidth;
		int mHeight;
		int textureNumber;
		//void render( int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );
		void render();
		void free();
		
		typedef void (*FunctionPointer)();
		void setDeathFunc(FunctionPointer ptr) //Function to run when target is destroyed
		{
			fprintf (stdout, "Adding death func\n");
			funcDeath = ptr;
		}

		void callDeathFunc() 
		{
			fprintf (stdout, "Calling death func\n");
			if (funcDeath != nullptr) 
				funcDeath();
			else
				fprintf (stderr, "callDeathFunc() called but no function definted\n");
		}


	private:
		//Top left position
		LTargetType  mType;
		SDL_Point mPosition;
		SDL_Rect mClip;
		double mAngle;
		SDL_Point mCenter;
		SDL_RendererFlip mFlip;
		FunctionPointer funcDeath;
		//Currently used global sprite
		//LTargetSprite mCurrentSprite;
};

const int MAX_TARGETS = 4;
extern LTarget gTargets[ MAX_TARGETS ]; 

extern bool bounds_check (int x, int y, int w, int h);
extern bool add_target (int x, int y, LTargetType type, int height, int width, int texture);
