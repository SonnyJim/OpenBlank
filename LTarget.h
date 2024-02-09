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
		void setPosition(SDL_Point p);
		SDL_Point getPosition();
		//TODO Can probably nuke these 3
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
		double getVal (int val);
		void setVal (int val, double value);
		
		typedef void (*FunctionPointer)();
		typedef void (*fpMove)(LTarget*);
		void setDeathFunc(FunctionPointer ptr) //Function to run when target is destroyed
		{
			funcDeath = ptr;
		}

		void callDeathFunc() 
		{
			if (funcDeath != nullptr) 
				funcDeath();
		}

		void setMoveFunc(fpMove mPtr) //Function to move the target
		{
			funcMove = mPtr;
		}

		void callMoveFunc(LTarget* pTarget) 
		{
			if (funcMove != nullptr) 
				funcMove(pTarget);

		}


	private:
		//Top left position
		LTargetType  mType;
		SDL_Point mPosition;
		SDL_Rect mClip;
		//TODO Nuke these 3
		double mAngle;
		SDL_Point mCenter;
		SDL_RendererFlip mFlip;
#define MAX_VALS 2
		double mVals[MAX_VALS];
		FunctionPointer funcDeath;
		fpMove funcMove;

		//Currently used global sprite
		//LTargetSprite mCurrentSprite;
};

const int MAX_TARGETS = 4;
extern LTarget gTargets[ MAX_TARGETS ]; 

extern bool bounds_check (int x, int y, int w, int h);
extern bool add_target (int x, int y, LTargetType type, int height, int width, int texture);

extern void move_right (LTarget* pTarget); //In Movement.cpp
extern void move_circle(LTarget* pTarget);
