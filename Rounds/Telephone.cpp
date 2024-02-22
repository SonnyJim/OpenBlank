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

static std::string targetNumber;
static std::string targetDialled;
static int digits_entered;

static const int numDigits = 6;
static const char* dtmfpaths[] = 
{
	"./data/sfx/dtmf/0.wav",
	"./data/sfx/dtmf/1.wav",
	"./data/sfx/dtmf/2.wav",
	"./data/sfx/dtmf/3.wav",
	"./data/sfx/dtmf/4.wav",
	"./data/sfx/dtmf/5.wav",
	"./data/sfx/dtmf/6.wav",
	"./data/sfx/dtmf/7.wav",
	"./data/sfx/dtmf/8.wav",
	"./data/sfx/dtmf/9.wav",
	"./data/sfx/dtmf/633878__aesterial-arts__phone-ring.wav"
};

static void generate_dialled ()
{
	std::string output;
	int i;	
	if (digits_entered == 0)
		return;
	output = targetDialled.substr (0, digits_entered);
	textures[12].loadFromRenderedText(output, SDL_Color {0,20,0}, fontPhone);
	gTargets[11].mWidth = digits_entered * (gTargets[10].mWidth / numDigits);
}

static void generate_number ()
{
	int number = getRandom(0,999999);
	targetNumber = std::to_string(number);
	//Pad leading zeros
	while (targetNumber.length() < numDigits)
	{
		targetNumber = "0" + targetNumber;
	}
	fprintf (stdout, "Generated %s\n", targetNumber.c_str());
	textures[11].loadFromRenderedText(targetNumber, SDL_Color {60,80,60}, fontPhone);
	digits_entered = 0;
	targetDialled.clear();
	generate_dialled();
}


static void number_pressed (int number)
{
	fprintf (stdout, "%i pressed\n", number);
	
	//Check if it's the right one
	std::string  numberString = std::to_string (number);
	if (targetNumber[digits_entered] == numberString[0])
	{
		targetDialled.append(numberString);
		digits_entered++;
		generate_dialled();
		fprintf (stdout, "Dialled %s\n", targetDialled.c_str());
		sound.playRoundSFX (number);
	}
	if (digits_entered >= targetNumber.size())
	{
		players[0].addHit(1);
		generate_number();
		sound.playRoundSFX(10);
	}
}

static void zero_pressed (LTarget* pTarget)
{
	number_pressed (0);
}

static void one_pressed (LTarget* pTarget)
{
	number_pressed (1);
}

static void two_pressed (LTarget* pTarget)
{
	number_pressed (2);
}

static void three_pressed (LTarget* pTarget)
{
	number_pressed (3);
}

static void four_pressed (LTarget* pTarget)
{
	number_pressed (4);
}

static void five_pressed (LTarget* pTarget)
{
	number_pressed (5);
}

static void six_pressed (LTarget* pTarget)
{
	number_pressed (6);
}

static void seven_pressed (LTarget* pTarget)
{
	number_pressed (7);
}

static void eight_pressed (LTarget* pTarget)
{
	number_pressed (8);
}

static void nine_pressed (LTarget* pTarget)
{
	number_pressed (9);
}

static void load_sfx ()
{
	for (int i = 0; i <11; i++)
	{
		sound.loadRoundSFX (i, dtmfpaths[i]);
	}
}

void telephone_start ()
{
	int i;
	fprintf (stdout, "Dial some numbers\n");
	load_sfx();
	bg.clear();
	bg.set ("./data/png/Telephone_bg.png");
	//Render the nmbser 0-9 on some textures
	for (i=0; i <= 9; i++)
	{
		textures[i].loadFromRenderedText (std::to_string(i), SDL_Color {0,0,0}, fontHud);
	}//TODO Render the numbers onto the btton bg
	textures[10].loadFromFile ("./data/png/TelephoneButton.png");
	
	//Render the button in the form of a keypad
	int pos_x = 110;
	int pos_y = 245;
	int x_offset,y_offset;
	int w = textures[10].getWidth() ;
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
	gTargets[1].setDeathFunc(two_pressed );	
	gTargets[2].setDeathFunc(three_pressed );	
	gTargets[3].setDeathFunc(four_pressed );	
	gTargets[4].setDeathFunc(five_pressed );	
	gTargets[5].setDeathFunc(six_pressed );	
	gTargets[6].setDeathFunc(seven_pressed );	
	gTargets[7].setDeathFunc(eight_pressed );	
	gTargets[8].setDeathFunc(nine_pressed );	
	gTargets[9].setDeathFunc(zero_pressed );	

	//Generate the target number texture
	generate_number ();
	w = textures[11].getWidth()  + 20;
	h = textures[11].getHeight();
	//Find where the first keypad button is and put the display above it
	SDL_Point p = gTargets[0].getPosition();
	int x = p.x ;
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
	if (players[0].getHits() >= rnd.getTarget())
	{
		return false;
	}
	return true;
}

