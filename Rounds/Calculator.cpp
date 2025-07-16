#include <SDL2/SDL.h>
#include <string>
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

static LTexture numberTexture;

static std::string targetQuestion;
static int answerInt;
static std::string targetAnswer;
static int digits_entered;

static const char* calcSndPaths[] = 
{
	"./data/sfx/Calculator/1.wav",
	"./data/sfx/Calculator/2.wav",
	"./data/sfx/Calculator/3.wav",
	"./data/sfx/Calculator/4.wav",
	"./data/sfx/Calculator/5.wav",
};


enum op_t
{
	OP_TIMES,
	OP_MINUS,
	OP_PLUS
};

struct answer_t
{
	std::string question;
	int	answer;
	int	firstNum;
	int	secondNum;
	op_t	operation;
};


static void generate_answer ()
{
}

static void generate_question ()
{
}

static void number_pressed (int number)
{
	fprintf (stdout, "%i pressed\n", number);
}

static void zero_pressed ()
{
	number_pressed (0);
}

static void one_pressed ()
{
	number_pressed (1);
}

static void two_pressed ()
{
	number_pressed (2);
}

static void three_pressed ()
{
	number_pressed (3);
}

static void four_pressed ()
{
	number_pressed (4);
}

static void five_pressed ()
{
	number_pressed (5);
}

static void six_pressed ()
{
	number_pressed (6);
}

static void seven_pressed ()
{
	number_pressed (7);
}

static void eight_pressed ()
{
	number_pressed (8);
}

static void nine_pressed ()
{
	number_pressed (9);
}

static void load_sfx ()
{
	for (int i = 0; i <5; i++)
	{
		sound.loadRoundSFX (i, calcSndPaths[i]);
	}
}

void calculator_start ()
{
	int i;
	fprintf (stdout, "Crunch some numbers\n");
	load_sfx();
	bg.clear();
	//bg.set ("./data/png/Telephone_bg.png");
	//bg.set ("./data/png/bg1.png");
	//Render the nmbser 0-9 on some textres
	for (i=0; i <= 9; i++)
	{
		textures[i].loadFromRenderedText (std::to_string(i), SDL_Color {0,0,0}, fontHud);
	}//TODO Render the numbers onto the btton bg
//	textures[10].loadFromFile ("./data/png/TelephoneButton.png");
	
	//Render the button in the form of a keypad
	int pos_x = 220;
	int pos_y = 250;
	int x_offset,y_offset;
	int w = textures[10].getWidth() * SCALE_X;
	int h = textures[10].getHeight();
	x_offset = w;
	y_offset = h;
	
	for (i=1; i <= 9; i++)
	{
		if (i == 4)
		{
			y_offset += h;
			x_offset = 0 - (2 * w);
		}
		else if (i == 7)
		{
			y_offset += h;
			x_offset = 0 - (5 * w);
		}
		add_target (x_offset + (i*w) +pos_x, y_offset + pos_y, TARGET_BUTTON, w, h, i);
	}
	//Add the zero button
	y_offset += h;
	x_offset = w * 3;
	add_target ( x_offset + pos_x, y_offset + pos_y, TARGET_BUTTON, w, h, 0);

	//Set the function to be called when the button is pressed
	gTargets[0].setDeathFunc(one_pressed);	
	gTargets[1].setDeathFunc(two_pressed);	
	gTargets[2].setDeathFunc(three_pressed);	
	gTargets[3].setDeathFunc(four_pressed);	
	gTargets[4].setDeathFunc(five_pressed);	
	gTargets[5].setDeathFunc(six_pressed);	
	gTargets[6].setDeathFunc(seven_pressed);	
	gTargets[7].setDeathFunc(eight_pressed);	
	gTargets[8].setDeathFunc(nine_pressed);	
	gTargets[9].setDeathFunc(zero_pressed);	

	//Generate the target number texture
	generate_number ();
	w = textures[11].getWidth() * SCALE_X + 30;
	h = textures[11].getHeight();
	//Find where the first keypad button is and put the display above it
	SDL_Point p = gTargets[0].getPosition();
	int x = p.x + 10;
	int y = p.y - h - 100;
	add_target ( x, y, TARGET_IMAGE, w, h, 11);
	
	generate_dialled();
	add_target ( x , y, TARGET_IMAGE, w, h, 12); //Add dialled numbers
	//Set quit condition and update callback
	rnd.setTarget(5);
	rnd.setTimeout(30);
	rnd.setRoundUpdate(telephone_update);
	
}

bool telephone_update () //TODO Convert to skeet shooting?
{
	//Draw number background
	/*
	SDL_Point p = gTargets[10].getPosition();
	SDL_Rect r;
	
	r.x = p.x;
	r.y = p.y;
	r.w = gTargets[10].mWidth;
	r.h = gTargets[10].mHeight;
	SDL_SetRenderDrawColor (gRenderer, 0,0,0,0);
	SDL_RenderFillRect (gRenderer, &r);
	*/
	if (players[0].getHits() >= rnd.getTarget())
	{
		return false;
	}
	return true;
}

