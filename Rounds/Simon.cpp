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
#include "../Hud.h"

#define MAX_LENGTH 10

LTexture gSimonTexture;

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
	int playbackDelay;//Delay between start of playback
	int delay; //Delay between beeps
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
	players[0].addHit(1);
	simon.delay -= 80;
	if (simon.delay < 40)
		simon.delay = 40;
	simon.currentLength++;
	if (simon.currentLength > MAX_LENGTH)
		simon.currentLength = MAX_LENGTH;

	int s = simon.currentLength;
	
	simon.sequence[s] = getRandomInt(0, 3);;
	
	fprintf (stdout, "Simon sequence: ");
	for (int i=0; i < simon.currentLength; i++)
	{
		fprintf (stdout, "%i:", simon.sequence[i]);
	}
	fprintf (stdout, " len:%i\n", simon.currentLength);
	
	simon.playbackDelay = 500 - (simon.currentLength * 50);
	if (simon.playbackDelay < 100)
		simon.playbackDelay = 100;
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
	if (SDL_GetTicks () - simon.playbackActive < simon.playbackDelay)
		return;
	int btn = simon.sequence[simon.playbackStep];
	if (simon.playbackActive + simon.playbackDelay < SDL_GetTicks())
	{
//		draw_simon_single (btn, simonColorsLit[btn]);
		btnHitTimer[btn] = SDL_GetTicks();
	}
	if (simon.playing == true)
	{
		sound.playRoundSFX(simon.sequence[simon.playbackStep]);
		simon.playing = false;
	}

	if (simon.playbackActive + simon.delay + simon.playbackDelay < SDL_GetTicks())
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
			hud.addCheckmark(SDL_Point {SCREEN_WIDTH /2, SCREEN_HEIGHT /2 });
			simon.currentStep = 0;
			append_sequence();
		}
		//TODO if currentstep bla
	}
	else
		sound.playRoundSFX(4);
}

static void yellow_pressed (LTarget* pTarget)
{
	btn_pressed (SIMON_YELLOW);
}

static void blue_pressed (LTarget* pTarget)
{
	btn_pressed (SIMON_BLUE);
}

static void red_pressed (LTarget* pTarget)
{
	btn_pressed (SIMON_RED);
}

static void green_pressed (LTarget* pTarget)
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
	//bg.set ("./data/png/Simon_bg.png");
	gSimonTexture.loadFromFile ("./data/png/Simon_bg.png");	
	//Render the nmbser 0-9 on some textres
	SDL_Rect r;
	r.w = 160 ;
	r.h = 160;
	r.x = (SCREEN_WIDTH ) / 2 - r.w;
	r.y = SCREEN_HEIGHT / 2 - r.h;

	add_target (r.x, r.y, TARGET_BUTTON, r.w, r.h, TEXTURE_INVISIBLE);
	add_target (r.x, r.y + r.h, TARGET_BUTTON, r.w, r.h, TEXTURE_INVISIBLE);
	add_target (r.x + r.w, r.y, TARGET_BUTTON, r.w, r.h, TEXTURE_INVISIBLE);
	add_target (r.x + r.w, r.y + r.h, TARGET_BUTTON, r.w, r.h, TEXTURE_INVISIBLE);

	//Set the function to be called when the button is pressed
	gTargets[0].setDeathFunc(red_pressed);	
	gTargets[1].setDeathFunc(green_pressed);	
	gTargets[2].setDeathFunc(blue_pressed);	
	gTargets[3].setDeathFunc(yellow_pressed);	

	simon.delay = 400; //Set how long to wait between each teaching blink	
	new_sequence();
	
	rnd.setTarget(MAX_LENGTH);
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
static void draw_simon ()
{
	int btn_delay = simon.delay;

	SDL_Rect r;
	
	for (int i=0; i < 4;i++)
	{
		if (btnHitTimer[i] + btn_delay < SDL_GetTicks())
			draw_simon_single (i, simonColors[i]);
		else
			draw_simon_single (i, simonColorsLit[i]);

	};
	r.x = 0;
	r.y = 0;
	r.w = SCREEN_WIDTH ;
	r.h = SCREEN_HEIGHT;
	SDL_RenderCopy (gRenderer, gSimonTexture.getTexture(), nullptr, &r);
}

bool simon_update ()
{
	play_sequence();
	draw_simon ();
	if (players[0].getHits() >= rnd.getTarget())
	{
		return false;
	}
	return true;
}

