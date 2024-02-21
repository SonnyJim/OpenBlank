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

enum
{
	ING_BOTTOM,
	ING_PATTY,
	ING_LETTUCE,
	ING_TOMATO,
	ING_TOP
};
#define MAX_INGREDIENTS 6

static int ingredients_used;
static int ingredients_needed;
static int recipe[MAX_INGREDIENTS];
static int burger[MAX_INGREDIENTS];

LTexture textureRecipe;

static void draw_recipe ()
{
	SDL_Rect r, t;
	r.x = 290 * SCALE_X;
	r.y = 23;
	r.w = 120;
	r.h = 166;

	SDL_SetRenderTarget (gRenderer, textureRecipe.getTexture());
	t.w = r.w;	
	t.h = textures[ING_BOTTOM].getHeight() / 2;
	t.x = r.x;
	t.y = r.h - t.h;
	SDL_RenderCopy (gRenderer, textures[ING_BOTTOM].getTexture(), NULL, &t);

	for (int i=0;i < ingredients_needed;i++)
	{
		t.y -= textures[recipe[i]].getHeight() /2;
		SDL_RenderCopy (gRenderer, textures[recipe[i]].getTexture(), NULL, &t);
	}

	t.h = textures[ING_TOP].getHeight() / 2;
	t.y -= t.h;
	SDL_RenderCopy (gRenderer, textures[ING_TOP].getTexture(), NULL, &t);

	SDL_SetRenderTarget (gRenderer, NULL);
	SDL_RenderCopy (gRenderer, textureRecipe.getTexture(), NULL, &r);
}

static void draw_burger ()
{
	SDL_Rect r;

	//Draw bottom bun
	r.x = 36 * SCALE_X;
	r.y = 264;
	r.w = textures[ING_BOTTOM].getWidth();
	r.h = textures[ING_BOTTOM].getHeight();
	SDL_RenderCopy (gRenderer, textures[ING_BOTTOM].getTexture(), NULL, &r);
	
	if (ingredients_used == 0)
		return;

	for (int i=0; i < ingredients_used;i++)
	{
		r.y -= textures[burger[i]].getHeight();
		SDL_RenderCopy (gRenderer, textures[burger[i]].getTexture(), NULL,&r);
	}
}

static void generate_recipe()
{
	fprintf (stdout, "Generating new recipe: ");
	ingredients_used = 0;
	for (int i=0; i < ingredients_needed;i++)
	{
		recipe[i] = getRandomInt(ING_PATTY, ING_TOMATO);
		fprintf (stdout, "%i,", recipe[i]);
	}
	fprintf (stdout, "\n");
}

static void add_ingredient (int ing)
{
	if (ing != recipe[ingredients_used])
	{
		fprintf (stdout, "Wrong ingredient, wanted %i, got %i\n", recipe[ingredients_used], ing);
		return;
	}
	burger[ingredients_used] = ing;
	ingredients_used++;
	if (ingredients_used == ingredients_needed)
	{
		sound.playRoundSFX (0);
		add_target (((SCREEN_WIDTH * SCALE_X) / 2) - gCheckmarkTexture.getWidth(), (SCREEN_HEIGHT /2) -gCheckmarkTexture.getHeight(), TARGET_CHECKMARK, gCheckmarkTexture.getWidth() * 2, gCheckmarkTexture.getHeight()* 2, 0);
		players[0].addHit(1);
		ingredients_needed++;
		generate_recipe();
	}
}

static void add_lettuce (LTarget* pTarget)
{
	fprintf (stdout, "Adding lettuce\n");
	add_ingredient (ING_LETTUCE);
}

static void add_patty (LTarget* pTarget)
{
	fprintf (stdout, "Adding patty\n");
	add_ingredient (ING_PATTY);
}

static void add_tomato (LTarget* pTarget)
{
	fprintf (stdout, "Adding tomato\n");
	add_ingredient (ING_TOMATO);
}

void burger_start ()
{
	int i;
	fprintf (stdout, "Quick draw start\n");
	sound.loadRoundSFX (0, "./data/sfx/221515__alaskarobotics__service-bell-ring.wav");
	bg.clear();
	bg.set ("./data/png/Burger/Burger_bg.png");
	//Render the nmbser 0-9 on some textres
	textures[ING_BOTTOM].loadFromFile("./data/png/Burger/Bap_bottom.png");
	textures[ING_PATTY].loadFromFile("./data/png/Burger/Patty.png");
	textures[ING_LETTUCE].loadFromFile("./data/png/Burger/Lettuce.png");
	textures[ING_TOMATO].loadFromFile("./data/png/Burger/Tomato.png");
	textures[ING_TOP].loadFromFile("./data/png/Burger/Bap_top.png");

	int t = add_target (7* SCALE_X, 389, TARGET_IMAGE, textures[ING_LETTUCE].getWidth() * SCALE_X, textures[ING_LETTUCE].getHeight(), ING_LETTUCE);
	t = add_target (13* SCALE_X, 319, TARGET_BUTTON, 184 * SCALE_X, 145, TEXTURE_INVISIBLE);
	gTargets[t].setDeathFunc(add_lettuce);
	t = add_target (220 * SCALE_X, 389, TARGET_IMAGE, textures[ING_PATTY].getWidth() * SCALE_X, textures[ING_PATTY].getHeight(), ING_PATTY);
	t = add_target (229* SCALE_X, 320, TARGET_BUTTON, 184 * SCALE_X, 145, TEXTURE_INVISIBLE);
	gTargets[t].setDeathFunc(add_patty);
	t = add_target (435 *SCALE_X, 389, TARGET_IMAGE, textures[ING_TOMATO].getWidth() * SCALE_X, textures[ING_TOMATO].getHeight(), ING_TOMATO);
	t = add_target (442* SCALE_X, 320, TARGET_BUTTON, 184 * SCALE_X, 145, TEXTURE_INVISIBLE);
	gTargets[t].setDeathFunc(add_tomato);
	
	ingredients_needed = 2;
	generate_recipe ();
	rnd.setTarget(10);
	rnd.setTimeout(30);
	rnd.setRoundUpdate(burger_update);
}

bool burger_update () //TODO Convert to skeet shooting?
{
	draw_recipe();
	draw_burger();
	if (players[0].getHits() >= rnd.getTarget())
	{
		return false;
	}
	return true;
}

