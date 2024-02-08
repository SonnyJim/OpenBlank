#include "Title.h"
#include "Game.h"
#include "LTexture.h"
#include "LTarget.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "OpenBlank.h"
#include "Round.h"

Title titlescreen;
LTexture gTitlescreen;
extern bool quit;

void button_start_hit ()
{
	fprintf (stdout, "HIT BUTTON\n");
	titlescreen.stop();
}

void Title::start()
{
	game.setState (STATE_TITLESCREEN);
	if ( !textures[0].loadFromFile ("./data/png/button_start.png"))
	{
		fprintf (stderr, "Error loading texture! %s\n", SDL_GetError ());
		quit = true;
	}
	
	if ( !textures[1].loadFromFile ("./data/png/titlescreen.png"))
	{
		fprintf (stderr, "Error loading texture! %s\n", SDL_GetError ());
		quit = true;
	}

	//gTargets[0].loadFromFile ("./data/png/button_start.png");
	add_target (0,0, TARGET_IMAGE, textures[1].getWidth() * SCALE_X, textures[1].getHeight(), 1);
	add_target (82,193, TARGET_BUTTON, textures[0].getWidth() * SCALE_X, textures[0].getHeight(), 0);
	gTargets[0].setDeathFunc (NULL);
	gTargets[1].setDeathFunc (button_start_hit);
	
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
	//gTitlescreen.free();
	textures[0].free();
	gTargets[0].free();
	textures[1].free();
	gTargets[1].free();
	
	game.setState (STATE_ROUND_START);
	game.setRound (0);
	rnd.start();
}
void Title::render()
{
	/*
	SDL_Rect r;
	r.x = 0;
	r.y = 0;
	r.w = SCREEN_WIDTH * SCALE_X;
	r.h = SCREEN_HEIGHT;

	gTitlescreen.render (0,0,&r);
*/
}
