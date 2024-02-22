#include <SDL2/SDL.h>
#include "Rounds.h"
#include "../LTarget.h"
#include "../LTexture.h"
#include "../Background.h"
#include "../Movement.h"
#include "../OpenBlank.h"
#include "../Round.h"
#include "../Player.h"
#include "../Media.h"
#include "../Sound.h"
#include "../SDL.h"

#define MAX_BOTTLE_TEXTURES 10
static const char* texturePaths[] =
{
	"./data/png/Saloon/Bottle1.png",
	"./data/png/Saloon/Bottle2.png",
	"./data/png/Saloon/Bottle3.png",
	"./data/png/Saloon/Bottle4.png",
	"./data/png/Saloon/Bottle5.png",
	"./data/png/Saloon/Bottle6.png",
	"./data/png/Saloon/Bottle7.png",
	"./data/png/Saloon/Bottle8.png",
	"./data/png/Saloon/Bottle9.png",
	"./data/png/Saloon/Bottle10.png"
};

static void bottle_deathFunc (LTarget* pTarget)
{
	sound.playRoundSFX(getRandomInt(0,9));
	//pTarget->free();
}

static void load_sfx ()
{
	sound.loadRoundSFX (0, "./data/sfx/Saloon/1.wav");
	sound.loadRoundSFX (1, "./data/sfx/Saloon/2.wav");
	sound.loadRoundSFX (2, "./data/sfx/Saloon/3.wav");
	sound.loadRoundSFX (3, "./data/sfx/Saloon/4.wav");
	sound.loadRoundSFX (4, "./data/sfx/Saloon/5.wav");
	sound.loadRoundSFX (5, "./data/sfx/Saloon/6.wav");
	sound.loadRoundSFX (6, "./data/sfx/Saloon/7.wav");
	sound.loadRoundSFX (7, "./data/sfx/Saloon/8.wav");
	sound.loadRoundSFX (8, "./data/sfx/Saloon/9.wav");
	sound.loadRoundSFX (9, "./data/sfx/Saloon/10.wav");
}
static void load_textures ()
{
	fprintf (stdout, "Loading round textures: \n");
	for (int i=0; i < 10; i++)
	{
		fprintf (stdout, "%s\n", texturePaths[i]);
		textures[i].loadFromFile(texturePaths[i]);
	}
}

static void generate_bottleline (SDL_Point s, int end, int size)
{
	int w,h;
	int x_offset = 0;
	int t, texture; //Target
	while (x_offset < end)
	{
		texture = getRandom (0, MAX_BOTTLE_TEXTURES);
		w = textures[texture].getWidth() / size;
		h = textures[texture].getHeight() / size;
		
		t = add_target ((s.x * SCALE_X + x_offset), s.y - h, TARGET_RED, w * SCALE_X, h, texture);
		gTargets[t].setDeathFunc(bottle_deathFunc);
		x_offset += w * SCALE_X;
		x_offset += getRandomInt (-5,1);
	}
}

static void generate_bottles()
{
	fprintf (stdout, "Generating bottles\n");
	SDL_Point s; //Starting point
	s.x = 35;
	s.y = 266;
	generate_bottleline (s, SCREEN_WIDTH * SCALE_X, 1);
	s.x = 238;
	s.y = 192;
	generate_bottleline (s, 600, 2);
	s.x = 334;
	s.y = 161;
	generate_bottleline (s, 400, 2);
	s.x = 335;
	s.y = 122;
	generate_bottleline (s, 400, 2);
	s.x = 417;
	s.y = 80;
	generate_bottleline (s, 200, 2);
	s.x = 98;
	s.y = 200;
	generate_bottleline (s, 160, 2);
}

void saloon_start ()
{
	int i;
	fprintf (stdout, "Saloon start\n");
	bg.clear();
	bg.set ("./data/png/Saloon/Saloon_bg.png");
	load_sfx();
	load_textures();
	generate_bottles();

	rnd.setTarget(40);
	rnd.setTimeout(15);
	rnd.setRoundUpdate(saloon_update);
}

bool saloon_update ()
{
	if (players[0].getHits() >= rnd.getTarget())
	{
		return false;
	}
	return true;
}

