#include <SDL2/SDL.h>
#include <string>
#include <cstdlib>
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

#define MAX_LENGTH 6

enum simonBtn
{
	SIMON_RED,
	SIMON_GREEN,
	SIMON_BLUE,
	SIMON_YELLOW,
	SIMON_ERROR
};

struct simon_t 
{
	int currentStep;
	int delay; //Delayt 
	int currentLength;
	Uint32 playbackActive;
	bool playing;
	int playbackStep;
	int sequence[MAX_LENGTH];
	int entered[MAX_LENGTH];
};

simon_t simon;

static SDL_Color simonColors[] =
{
	SDL_Color {120,0,0},
	SDL_Color {0,120,0},
	SDL_Color {0,0,120},
	SDL_Color {120,120,60},
};

static SDL_Color simonColorsLit[] =
{
	SDL_Color {255,0,0},
	SDL_Color {0,255,0},
	SDL_Color {0,0,255},
	SDL_Color {255,255,120},
};

static Uint32 btnHitTimer[4];


static const char* simonSndPaths[] = 
{
	"./data/sfx/Simon/1.wav",
	"./data/sfx/Simon/2.wav",
	"./data/sfx/Simon/3.wav",
	"./data/sfx/Simon/4.wav",
	"./data/sfx/572936__bloodpixelhero__error.wav",
};

static bool check_button (simonBtn btn)
{
	int step = simon.currentStep;
	if (btn == simon.sequence[step])
		return true;
	else
		return false;
}

static void append_sequence ()
{
	int s = simon.currentLength;
	
	int r = rand() % 4;
	fprintf (stdout,"RANDY %i\n", r);
	simon.sequence[s] = r;
	simon.currentLength++;
	if (simon.currentLength > MAX_LENGTH)
		simon.currentLength = MAX_LENGTH;
	
	fprintf (stdout, "Simon sequence: ");
	for (int i=0; i < simon.currentLength; i++)
	{
		fprintf (stdout, "%i:", simon.sequence[i]);
	}
	fprintf (stdout, " len:%i\n", simon.currentLength);
	
	simon.playbackActive = SDL_GetTicks();
	simon.playing = true;
	
}

static void new_sequence ()
{
	simon.playbackStep = 0;
	simon.currentStep = 0;
	simon.currentLength = 0;
	append_sequence();
}


static void draw_simon_single (int btn, SDL_Color color);
static void play_sequence ()
{
	if (simon.playbackActive == 0)
		return;
	int btn = simon.sequence[simon.playbackStep];
	draw_simon_single (btn, simonColorsLit[btn]);
	if (simon.playing == true)
	{
		sound.playRoundSFX(simon.sequence[simon.playbackStep]);
		simon.playing = false;
	}

	if (simon.playbackActive + simon.delay < SDL_GetTicks())
	{
		simon.playbackStep++;
		simon.playing = true;
		simon.playbackActive = SDL_GetTicks();
		if (simon.playbackStep > simon.currentLength)
		{
			simon.playbackActive = 0;
			simon.playbackStep = 0;
			simon.playing = false;
		}
	}
}

static void btn_pressed (simonBtn btn)
{
	fprintf (stdout, "%i pressed\n", btn);
	if (simon.playbackActive != 0)
	{
		fprintf (stdout, "Not allowing button press due to playbackActive\n");
		return;
	}
	if (btn == simon.sequence[simon.currentStep])
	{
		sound.playRoundSFX(btn);
		simon.currentStep++;
		btnHitTimer[btn] = SDL_GetTicks();
		if (simon.currentStep > simon.currentLength)
		{
			add_target (((SCREEN_WIDTH * SCALE_X) / 2) - gCheckmarkTexture.getWidth(), (SCREEN_HEIGHT /2) -gCheckmarkTexture.getHeight(), TARGET_CHECKMARK, gCheckmarkTexture.getWidth() * 2, gCheckmarkTexture.getHeight()* 2, 0);
			simon.currentStep = 0;
			append_sequence();
		}
		//TODO if currentstep bla
	}
	else
		sound.playRoundSFX(4);
}

static void yellow_pressed ()
{
	btn_pressed (SIMON_YELLOW);
}

static void blue_pressed ()
{
	btn_pressed (SIMON_BLUE);
}

static void red_pressed ()
{
	btn_pressed (SIMON_RED);
}

static void green_pressed ()
{
	btn_pressed (SIMON_GREEN);
}

static void load_sfx ()
{
	for (int i = 0; i <5; i++)
	{
		sound.loadRoundSFX (i, simonSndPaths[i]);
	}
}

void simon_start ()
{
	int i;
	fprintf (stdout, "Simon says\n");
	load_sfx();
	bg.clear();
	bg.set ("./data/png/Simon_bg.png");
	//Render the nmbser 0-9 on some textres
	SDL_Rect r;
	r.w = 160 * SCALE_X;
	r.h = 160;
	r.x = (SCREEN_WIDTH * SCALE_X) / 2 - r.w;
	r.y = SCREEN_HEIGHT / 2 - r.h;

	add_target (r.x, r.y, TARGET_BUTTON, r.w, r.h, -1);
	add_target (r.x, r.y + r.h, TARGET_BUTTON, r.w, r.h, -1);
	add_target (r.x + r.w, r.y, TARGET_BUTTON, r.w, r.h, -1);
	add_target (r.x + r.w, r.y + r.h, TARGET_BUTTON, r.w, r.h, -1);

	//Set the function to be called when the button is pressed
	gTargets[0].setDeathFunc(red_pressed);	
	gTargets[1].setDeathFunc(green_pressed);	
	gTargets[2].setDeathFunc(blue_pressed);	
	gTargets[3].setDeathFunc(yellow_pressed);	
	
	simon.delay = 800; //Set how long to wait between each teaching blink	
	new_sequence();
	
	rnd.setTarget(5);
	rnd.setTimeout(30);
	rnd.setRoundUpdate(simon_update);
	
}

static void draw_simon_single (int btn, SDL_Color color)
{

	SDL_Rect r;
	r = gTargets[btn].getRect();
	SDL_SetRenderDrawColor (gRenderer, color.r, color.g, color.b, SDL_ALPHA_OPAQUE);
	SDL_RenderFillRect (gRenderer, &r);
}
const int btn_delay = 300;

static void draw_simon ()
{
	SDL_Rect r;
	
	for (int i=0; i < 4;i++)
	{
		if (btnHitTimer[i] + btn_delay < SDL_GetTicks())
			draw_simon_single (i, simonColors[i]);
		else
			draw_simon_single (i, simonColorsLit[i]);

	};
}

bool simon_update ()
{
	draw_simon ();
	play_sequence();
	if (players[0].getHits() >= rnd.getTarget())
	{
		return false;
	}
	return true;
}

