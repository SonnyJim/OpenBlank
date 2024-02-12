#include "Title.h"
#include "Game.h"
#include "LTexture.h"
#include "LTarget.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "OpenBlank.h"
#include "Round.h"
#include "Background.h"

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
	
	bg.set ("./data/png/titlescreen.png");
	add_target (82,193, TARGET_BUTTON, textures[0].getWidth() * SCALE_X, textures[0].getHeight(), 0);
	gTargets[0].setDeathFunc (button_start_hit);
	
}

void Title::stop()
{
	//gTitlescreen.free();
	textures[0].free();
	gTargets[0].free();
	
	game.setState (STATE_ROUND_START);
	game.setRound (0);
	rnd.start();
}
void Title::render()
{
	//TODO Get rid
}
