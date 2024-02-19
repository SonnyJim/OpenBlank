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
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>

// Function to shuffle an array using the Fisher-Yates algorithm
static void shuffleSequence(int arr[], int size) {
    // Initialize random seed
    std::srand(std::time(nullptr));

    // Start from the last element and swap one by one
    for (int i = size - 1; i > 0; --i) {
        // Generate a random index between 0 and i
        int j = std::rand() % (i + 1);

        // Swap arr[i] with the element at random index
        std::swap(arr[i], arr[j]);
    }
}

static const int sequenceLength = 16;
static int sequence[sequenceLength];
static int sequenceStep = 0;

static void generate_sequence ()
{
	for (int i=0;i< sequenceLength;i++)
	{
		sequence[i] = i + 1;
	}
	shuffleSequence(sequence, sequenceLength);
	sequenceStep = 1;
}


static void button_pressed (int number)
{
	fprintf (stdout, "%i pressed, looking for %i\n", number, sequenceStep);
	if (number == sequenceStep)
	{
		sequenceStep++;
		if (sequenceStep > sequenceLength)
		{
			fprintf (stdout, "END ROUND\n");
		}
		fprintf (stdout, "HIT!\n");
		players[0].addHit(1);
		//Kill target
		for (int i=0; i<sequenceLength;i++)
		{
			if (number == sequence[i])
			{
				fprintf (stdout, "Killing target %i\n", i);
				gTargets[i].free();
				break;
			}
		}
	}
	
/*	
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
*/
}


static void one_pressed ()
{
	button_pressed (1);
}

static void two_pressed ()
{
	button_pressed (2);
}

static void three_pressed ()
{
	button_pressed (3);
}

static void four_pressed ()
{
	button_pressed (4);
}

static void five_pressed ()
{
	button_pressed (5);
}

static void six_pressed ()
{
	button_pressed (6);
}

static void seven_pressed ()
{
	button_pressed (7);
}

static void eight_pressed ()
{
	button_pressed (8);
}

static void nine_pressed ()
{
	button_pressed (9);
}

static void ten_pressed ()
{
	button_pressed(10);
}
static void eleven_pressed ()
{
	button_pressed(11);
}

static void twelve_pressed ()
{
	button_pressed(12);
}

static void thirteen_pressed ()
{
	button_pressed(13);
}

static void fourteen_pressed ()
{
	button_pressed(14);
}

static void fiveteen_pressed ()
{
	button_pressed(15);
}

static void sixteen_pressed ()
{
	button_pressed(16);
}

static void load_sfx ()
{
	for (int i = 0; i <11; i++)
	{
		//sound.loadRoundSFX (i, dtmfpaths[i]);
	}
}

static void assign_func (int num, int value)
{
	fprintf (stderr, "Setting gTarget[%i] deathFunc to %i \n", num, value);
	switch (value)
	{
		case 1:
			gTargets[num].setDeathFunc(one_pressed);
			break;

		case 2:
			gTargets[num].setDeathFunc(two_pressed);
			break;

		case 3:
			gTargets[num].setDeathFunc(three_pressed);
			break;

		case 4:
			gTargets[num].setDeathFunc(four_pressed);
			break;

		case 5:
			gTargets[num].setDeathFunc(five_pressed);
			break;

		case 6:
			gTargets[num].setDeathFunc(six_pressed);
			break;

		case 7:
			gTargets[num].setDeathFunc(seven_pressed);
			break;

		case 8:
			gTargets[num].setDeathFunc(eight_pressed);
			break;

		case 9:
			gTargets[num].setDeathFunc(nine_pressed);
			break;

		case 10:
			gTargets[num].setDeathFunc(ten_pressed);
			break;

		case 11:
			gTargets[num].setDeathFunc(eleven_pressed);
			break;

		case 12:
			gTargets[num].setDeathFunc(twelve_pressed);
			break;

		case 13:
			gTargets[num].setDeathFunc(thirteen_pressed);
			break;

		case 14:
			gTargets[num].setDeathFunc(fourteen_pressed);
			break;

		case 15:
			gTargets[num].setDeathFunc(fiveteen_pressed);
			break;

		case 16:
			gTargets[num].setDeathFunc(sixteen_pressed);
			break;
		default:
			fprintf (stderr, "Undefined call to set deathfunc %i\n", num);
			break;
	}
}

void shootNumbers_start ()
{
	int i;
	fprintf (stdout, "Shoot some numbers\n");
	load_sfx();
	bg.clear();
	generate_sequence();
	//bg.set ("./data/png/bg1.png");
	//Render the nmbser 0-9 on some textres
	for (i=0; i < sequenceLength; i++)
	{
		char text[3];
		sprintf (text, "%02d", sequence[i]);
		fprintf (stdout, "%i,%i,%s| ", i, sequence[i], text);
		textures[i].loadFromRenderedText (text, SDL_Color {0,0,0}, fontMoby);
		assign_func (i, sequence[i]);
	}//TODO Render the numbers onto the btton bg
	fprintf (stdout, "\n");
	
	//Render the button in the form of a keypad
	int pos_x = ((SCREEN_WIDTH / SCALE_X) /2 ) + 120;
	int pos_y = 0;
	int x_offset,y_offset;
	int w = 60 * SCALE_X;
	int h = 60;
	x_offset = w;
	y_offset = h;
	
	for (i=0; i <sequenceLength; i++)
	{
		if (i == 4)
		{
			y_offset += h;
			x_offset = 0 - (3 * w);
		}
		else if (i == 8)
		{
			y_offset += h;
			x_offset = 0 - (7 * w);
		}
		else if (i == 12)
		{
			y_offset += h;
			x_offset = 0 - (11 * w);
		}
		add_target (x_offset + (i*w) +pos_x, y_offset + pos_y, TARGET_BUTTON, w, h, i);
	}

	rnd.setTarget(sequenceLength);
	rnd.setTimeout(30);
	rnd.setRoundUpdate(shootNumbers_update);
	for (int i =0; i < sequenceLength; i++)
	{
		fprintf	(stdout, "%i|", sequence[i]);
	}
		fprintf	(stdout, "\n");
}

bool shootNumbers_update () //TODO Convert to skeet shooting?
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

