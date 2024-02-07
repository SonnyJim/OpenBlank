#include "Title.h"
#include "Game.h"
#include "LTexture.h"
#include "LTarget.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "OpenBlank.h"

Title titlescreen;
LTexture gTitlescreen;
extern bool quit;

void button_start_hit ()
{
	fprintf (stdout, "HIT BUTTON\n");
}

void Title::start()
{
	game.setState (STATE_TITLESCREEN);
	if ( !gTitlescreen.loadFromFile ("./data/png/titlescreen.png"))
	{
		fprintf (stderr, "Error loading texture! %s\n", SDL_GetError ());
		quit = true;
	}

	gTargets[0].loadFromFile ("./data/png/button_start.png");
	gTargets[0].setPosition (82, 193);
	gTargets[0].setType (TARGET_BUTTON);
	gTargets[0].setDeathFunc (button_start_hit);
	//Load textures and setup buttons to shoot
	/*
	if (!gTitlescreen.loadFromFile ("./data/png/RedTarget.png)"))
	{
		fprintf (stderr, "Error loading menu background: %s\n", IMG_GetError());
		quit = true;
	}
	*/

}
void Title::stop()
{
	gTitlescreen.free();
	gTargets[0].free();
	game.setState (STATE_ROUND_START);
}
void Title::render()
{
	SDL_Rect r;
	r.x = 0;
	r.y = 0;
	r.w = SCREEN_WIDTH * SCALE_X;
	r.h = SCREEN_HEIGHT;

	gTitlescreen.render (0,0,&r);
}
