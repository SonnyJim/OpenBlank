#include <SDL2/SDL.h>
#include <string>
#include "Rounds.h"
#include "../LTarget.h"
#include "../Hud.h"
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
#include <sstream>

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
		sound.playRoundSFX(number - 1);
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
	else
		hud.addCross(players[0].getPosition());
}

static void one_pressed (LTarget* pTarget)
{
	button_pressed (1);
}

static void two_pressed (LTarget* pTarget)
{
	button_pressed (2);
}

static void three_pressed (LTarget* pTarget)
{
	button_pressed (3);
}

static void four_pressed (LTarget* pTarget)
{
	button_pressed (4);
}

static void five_pressed (LTarget* pTarget)
{
	button_pressed (5);
}

static void six_pressed (LTarget* pTarget)
{
	button_pressed (6);
}

static void seven_pressed (LTarget* pTarget)
{
	button_pressed (7);
}

static void eight_pressed (LTarget* pTarget)
{
	button_pressed (8);
}

static void nine_pressed (LTarget* pTarget)
{
	button_pressed (9);
}

static void ten_pressed (LTarget* pTarget)
{
	button_pressed(10);
}
static void eleven_pressed (LTarget* pTarget)
{
	button_pressed(11);
}

static void twelve_pressed (LTarget* pTarget)
{
	button_pressed(12);
}

static void thirteen_pressed (LTarget* pTarget)
{
	button_pressed(13);
}

static void fourteen_pressed (LTarget* pTarget)
{
	button_pressed(14);
}

static void fiveteen_pressed (LTarget* pTarget)
{
	button_pressed(15);
}

static void sixteen_pressed (LTarget* pTarget)
{
	button_pressed(16);
}

const char* sfxpaths[] = 
{
	"./data/sfx/ShootNumbers/01Label.wav",
	"./data/sfx/ShootNumbers/02Label.wav",
	"./data/sfx/ShootNumbers/03Label.wav",
	"./data/sfx/ShootNumbers/04Label.wav",
	"./data/sfx/ShootNumbers/05Label.wav",
	"./data/sfx/ShootNumbers/06Label.wav",
	"./data/sfx/ShootNumbers/07Label.wav",
	"./data/sfx/ShootNumbers/08Label.wav",
	"./data/sfx/ShootNumbers/09Label.wav",
	"./data/sfx/ShootNumbers/10Label.wav",
	"./data/sfx/ShootNumbers/11Label.wav",
	"./data/sfx/ShootNumbers/12Label.wav",
	"./data/sfx/ShootNumbers/13Label.wav",
	"./data/sfx/ShootNumbers/14Label.wav",
	"./data/sfx/ShootNumbers/15Label.wav",
	"./data/sfx/Asteroids/atari_boom6.wav",
};

static void load_sfx ()
{
	for (int i = 0; i <16; i++)
	{
		sound.loadRoundSFX (i, sfxpaths[i]);
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

static void draw_outline(SDL_Texture* texture)
{
    // Get the dimensions of the texture
    int texWidth, texHeight;
    SDL_QueryTexture(texture, NULL, NULL, &texWidth, &texHeight);

    // Create a temporary texture to hold the original texture
    SDL_Texture* temp = SDL_CreateTexture(gRenderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, texWidth, texHeight);
    if (!temp) {
        // Handle error
        fprintf(stderr, "Failed to create temporary texture: %s\n", SDL_GetError());
        return;
    }

    // Set the rendering target to the temporary texture
    SDL_SetRenderTarget(gRenderer, temp);

    // Copy the original texture to the temporary texture
    SDL_RenderCopy(gRenderer, texture, NULL, NULL);

    // Set the rendering target back to the original texture
    SDL_SetRenderTarget(gRenderer, texture);

    // Clear the original texture with a transparent color
    SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0);
    SDL_RenderClear(gRenderer);

    // Set the render draw color to random color for the outline
    SDL_SetRenderDrawColor(gRenderer, 255,255,0,0);

    // Draw the outline rect around the texture
    SDL_Rect outlineRect = {0, 0, texWidth, texHeight};
    SDL_RenderDrawRect(gRenderer, &outlineRect);

    // Copy the contents of the temporary texture back to the original texture
    SDL_RenderCopy(gRenderer, temp, NULL, NULL);

    // Reset the rendering target to the default (screen)
    SDL_SetRenderTarget(gRenderer, NULL);

    // Destroy the temporary texture
    SDL_DestroyTexture(temp);
}

std::string getFilename(int number)
{
    // Construct the filename pattern
    std::string pattern = "./data/png/ShootNumbers/";
    
    // Convert the number to a string and append it to the pattern
    std::stringstream ss;
    ss << pattern << number << ".png";
    
    // Return the concatenated string
    return ss.str();
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
		textures[i].loadFromFile(getFilename(sequence[i]));
		//textures[i].loadFromRenderedText (text, SDL_Color {0,0,0,0}, fontMoby);
		//draw_outline (textures[i].getTexture());
		assign_func (i, sequence[i]);
	}//TODO Render the numbers onto the btton bg
	fprintf (stdout, "\n");
	
	//Render the button in the form of a keypad
	int pos_x = ((SCREEN_WIDTH) /2 ) - ( 3 * 60);
	int pos_y = 0;
	int x_offset,y_offset;
	int w = 60 ;
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
	rnd.setTimeout(15);
	//TODO If you miss a shot reudce the timer?
	rnd.setRoundUpdate(shootNumbers_update);
	for (int i =0; i < sequenceLength; i++)
	{
		fprintf	(stdout, "%i|", sequence[i]);
	}
		fprintf	(stdout, "\n");
}

bool shootNumbers_update ()
{
	if (players[0].getHits() >= rnd.getTarget())
	{
		return false;
	}
	return true;
}

