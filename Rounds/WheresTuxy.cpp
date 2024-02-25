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
#include "../Hud.h"

static void generate_targets();

static const int MAX_TUXS = 14;
static int sample;
static bool dirty;
extern int quit;

static void draw_sample ()
{
	SDL_Rect r;
	r.w = textures[sample].getWidth() / 2;
	r.h = textures[sample].getHeight() / 2;
	r.x = 0;
	r.y = 0;
	SDL_RenderCopy (gRenderer, textures[sample].getTexture(), NULL, &r);
}

static int get_random_tux ()
{
	int tux;
	tux = getRandomInt(0,MAX_TUXS);
	while (tux == sample)
		tux = getRandomInt(0,MAX_TUXS);
	return tux;
}

static void add_tux (SDL_Rect r)
{
	add_target (r.x, r.y, TARGET_BOMB, r.w, r.h, get_random_tux());
}

static void missed (LTarget* pTarget)
{
	hud.addCross (players[0].getPosition());
}


static void spotted (LTarget* pTarget)
{
	fprintf (stdout, "Found him! \n");
	sound.playRoundSFX(0);
	hud.addCheckmark (players[0].getPosition());
	dirty = true;
}

static void generate_targets()
{
	dirty = false;
	fprintf (stdout, "Generating targets\n");
	int x_offset, y_offset = 0;
	SDL_Rect r;
	int scale = 1;
	int t, i, tex;
	int random = getRandomInt (0,2);
	sample = getRandomInt(0,MAX_TUXS);
	
	
	r.w = textures[sample].getWidth();
	r.h = textures[sample].getHeight();
	r.x = r.w / 2;
	
	r.y = SCREEN_HEIGHT - r.h - 100;
	scale = 1;
	fprintf (stdout, "Random = %i, sample = %i\n", random, sample);
	for (i=0; i <=2;i++)
	{
		gTargets[i].setType(TARGET_NONE);
		tex = get_random_tux();
		if (random == i)
		{
			t = add_target (r.x, r.y, TARGET_RED, r.w, r.h, sample);
			tex = sample;
			fprintf (stdout, "Adding real tux at %i, tex=%i\n", t, tex);
			gTargets[t].setDeathFunc(spotted);
		}
		else
		{
			t = add_target (r.x, r.y, TARGET_BOMB, r.w, r.h, tex);
			gTargets[t].setDeathFunc(missed);
		}
		fprintf (stdout, "Target %i type %i x=%i y=%i w=%i h=%i tex=%i t=%i\n", i, gTargets[i].getType(), r.x, r.y, r.w, r.h, tex, t);
		if (textures[tex].getTexture() == NULL)
		{
			fprintf (stdout, "NULL texture!\n");
			quit = true;
		}
		r.x += r.w;
	}
}

void wherestuxy_start ()
{
	dirty = true;
	int i, r;
	std::string filename;
	fprintf (stdout, "Where's Tuxy?\n");
	//load_sfx();
	bg.clear();
	bg.set ("./data/png/WheresTuxy/Tux_bg.png");
	sound.loadRoundSFX (0, "./data/sfx/221515__alaskarobotics__service-bell-ring.wav");
	//Render the nmbser 0-9 on some textres
	textures[0].loadFromFile("./data/png/WheresTuxy/Tux.png");
	for (int i=1;i <= MAX_TUXS; i++)
	{
		filename ="./data/png/WheresTuxy/Tux_" + std::to_string (i) + ".png";
		fprintf (stdout, "Loading texture: %s\n", filename.c_str());
		if (textures[i].loadFromFile (filename) != true)
		{
			fprintf (stdout, "Error loading %s\n", filename.c_str());
			quit = true;
		}
	}
	
	generate_targets();
	fprintf (stdout, "\n");
			
	rnd.setTarget(10);
	rnd.setTimeout(15);
	rnd.setRoundUpdate(wherestuxy_update);
}

bool wherestuxy_update () //TODO Convert to skeet shooting?
{
	draw_sample();
	if (dirty)
		generate_targets();
	if (players[0].getHits() >= rnd.getTarget())
	{
		return false;
	}
	return true;
}

