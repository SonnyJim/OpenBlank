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

enum 
{
	RED,
	GREEN,
	BLUE,
};

enum
{
	WORD,
	COLOR
};
static LTexture gQuestion;
static LTexture gClue;

static const char* colorNames[] = { "Red", "Green", "Blue"};
static const SDL_Color colors[] = { SDL_Color {200,0,0}, SDL_Color {0,200,0}, SDL_Color {0,0,200}};
static const SDL_Rect Rects[] = { SDL_Rect {189, 289, 126 ,164}, SDL_Rect {344, 289, 126, 164}, SDL_Rect {491,289,126,164}};

static int answer;
static int twist;

static void draw_buttons ()
{
	SDL_SetRenderDrawColor (gRenderer, colors[RED].r, colors[RED].g, colors[RED].b, SDL_ALPHA_OPAQUE);
	SDL_RenderFillRect (gRenderer, &Rects[RED]);
	SDL_SetRenderDrawColor (gRenderer, colors[GREEN].r, colors[GREEN].g, colors[GREEN].b, SDL_ALPHA_OPAQUE);
	SDL_RenderFillRect (gRenderer, &Rects[GREEN]);
	SDL_SetRenderDrawColor (gRenderer, colors[BLUE].r, colors[BLUE].g, colors[BLUE].b, SDL_ALPHA_OPAQUE);
	SDL_RenderFillRect (gRenderer, &Rects[BLUE]);
	
	SDL_Rect r;
	r.x =250;
	r.y = 60;
	r.w = gQuestion.getWidth();
	r.h = gQuestion.getHeight();
	SDL_RenderCopy (gRenderer, gQuestion.getTexture(), NULL, &r);
	r.x =320;
	r.y = 100;
	r.w = gClue.getWidth();
	r.h = gClue.getHeight();
	SDL_RenderCopy (gRenderer, gClue.getTexture(), NULL, &r);


}

static void generate_question()
{
	std::string output;
	fprintf (stdout, "Generating new question: ");
	answer = getRandomInt (RED, BLUE);
	twist = getRandomInt (WORD, COLOR);

	output = "SHOOT THE "; 
	if (twist == WORD)
		output += "WORD";
	else
		output += "COLOR";
	gQuestion.loadFromRenderedText (output, SDL_Color {0,0,0}, fontMobySmall);
	if (twist == WORD)
		gClue.loadFromRenderedText (colorNames[answer], colors[getRandomInt(RED, BLUE)], fontHud);
	else
		gClue.loadFromRenderedText (colorNames[getRandomInt(RED, BLUE)], colors[answer], fontHud);

	fprintf (stdout, "answer=%i twist=%i\n", answer, twist);
	fprintf (stdout, "%s\n", output.c_str());
}

static void button_pressed (int button)
{
	if (button == answer)
	{
		players[0].addHit(1);
		generate_question();
		hud.addCheckmark (players[0].getPosition());
		sound.playRoundSFX (0);
	}
	else
		hud.addCross (players[0].getPosition());
}

static void red_pressed (LTarget* pTarget)
{
	fprintf (stdout, "Red pressed\n");
	button_pressed (RED);
}


static void green_pressed (LTarget* pTarget)
{
	fprintf (stdout, "Green pressed\n");
	button_pressed (GREEN);
}


static void blue_pressed (LTarget* pTarget)
{
	fprintf (stdout, "Blue pressed\n");
	button_pressed (BLUE);
}

void doctor_start ()
{
	int i;
	fprintf (stdout, "Doctor start\n");
	sound.loadRoundSFX (0, "./data/sfx/221515__alaskarobotics__service-bell-ring.wav");
	bg.clear();
	bg.set ("./data/png/Doctor/Doctor_bg.png");
	//Render the nmbser 0-9 on some textres

	int t = add_target (Rects[RED].x, Rects[RED].y, TARGET_BUTTON, Rects[RED].w, Rects[RED].h, TEXTURE_INVISIBLE);
	gTargets[t].setDeathFunc(red_pressed);
	t = add_target (Rects[GREEN].x, Rects[GREEN].y, TARGET_BUTTON, Rects[GREEN].w, Rects[GREEN].h, TEXTURE_INVISIBLE);
	gTargets[t].setDeathFunc(green_pressed);
	t = add_target (Rects[BLUE].x, Rects[BLUE].y, TARGET_BUTTON, Rects[BLUE].w, Rects[BLUE].h, TEXTURE_INVISIBLE);
	gTargets[t].setDeathFunc(blue_pressed);
	
	generate_question ();
	rnd.setTarget(10);
	rnd.setTimeout(30);
	rnd.setRoundUpdate(doctor_update);
}

bool doctor_update () //TODO Convert to skeet shooting?
{
	draw_buttons();
	if (players[0].getHits() >= rnd.getTarget())
	{
		return false;
	}
	return true;
}

