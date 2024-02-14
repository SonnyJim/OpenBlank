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


#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <algorithm>
#include <random>

static LTexture guessTexture; 
static std::string dictPath = "./data/4_Letter_Words.txt";
static std::string letters;
static std::string guess;
static std::string answer;
static int lettersSpelled;

static std::string getRandomLineFromFile(const std::string& filename) 
{
    // Open the file
    std::ifstream file(filename);
    
    // Check if the file is opened successfully
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return "";
    }
    
    // Count the number of lines in the file
    int lineCount = 0;
    std::string line;
    while (std::getline(file, line)) {
        lineCount++;
    }
    
    // Generate a random line number
    int randomLineNumber = rand() % lineCount + 1;
    // Reset file stream to the beginning
    file.clear();
    file.seekg(0, std::ios::beg);
    
    // Read the random line from the file
    int currentLineNumber = 0;
    while (std::getline(file, line)) {
        currentLineNumber++;
        if (currentLineNumber == randomLineNumber) {
            // Close the file
            file.close();
            return line;
        }
    }
    
    // Close the file
    file.close();
    
    // Return an empty string if the file is empty or random line couldn't be found
    return "";
}

static bool searchStringInFile(const std::string& filename, const std::string& searchString) 
{

    // Open the file
    std::ifstream file(filename);
    
    // Check if the file is opened successfully
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return false;
    }
    
    // Read the file line by line
    std::string line;
    while (std::getline(file, line)) {
        // Check if the line contains the search string
        if (line.find(searchString) != std::string::npos) {
            // Close the file
            file.close();
            return true;
        }
    }
    
    // Close the file
    file.close();
    
    // Search string not found in the file
    return false;
}

static std::string randomizeString(const std::string& str) 
{
    // Create a copy of the input string
    std::string randomizedStr = str;
    
    // Obtain a random seed using std::random_device
    std::random_device rd;
    
    // Initialize a random number generator with the random seed
    std::default_random_engine rng(rd());
    
    // Shuffle the characters of the string using std::shuffle
    std::shuffle(randomizedStr.begin(), randomizedStr.end(), rng);
    
    return randomizedStr;
}

static void generate_new_answer ();

static void word_correct ()
{
	players[0].addHit(1);
	add_target (((SCREEN_WIDTH * SCALE_X) / 2) - gCheckmarkTexture.getWidth(), (SCREEN_HEIGHT /2) -gCheckmarkTexture.getHeight(), TARGET_CHECKMARK, gCheckmarkTexture.getWidth() * 2, gCheckmarkTexture.getHeight()* 2, 0);
	sound.playRoundSFX (0);
}

static void shot_letter (int num)
{
	gTargets[num].setType(TARGET_NONE);
	guess += std::string(1,letters[num]);
	lettersSpelled++;
	fprintf (stdout, "Letters spelled %i guess %s\n", lettersSpelled, guess.c_str());
	if (lettersSpelled > 3)
	{
		if (searchStringInFile(dictPath, guess))
			word_correct();
		else
			sound.playRoundSFX (1);
		
		generate_new_answer();
	}
}

static void shot_1 ()
{
	fprintf (stdout, "Shot 1\n");
	shot_letter (0);
}

static void shot_2 ()
{
	fprintf (stdout, "Shot 2\n");
	shot_letter (1);
}
static void shot_3 ()
{
	fprintf (stdout, "Shot 3\n");
	shot_letter (2);
}
static void shot_4 ()
{
	fprintf (stdout, "Shot 4\n");
	shot_letter (3);
}
/*
static void clear_targets ()
{
	for (int i=0;i<4;i++)
	{
		gTargets[i].free();
	}
}
*/
static void generate_new_answer ()
{
	clear_targets();
	lettersSpelled = 0;
	guess = "";
	answer = getRandomLineFromFile (dictPath);
	letters = randomizeString (answer);
	while (letters == answer)
		letters = randomizeString (answer);
	fprintf (stdout, "Answer is now %s, Letters is %s\n", answer.c_str(), letters.c_str());
	const int w = FONT_SCHOOL_SIZE;
	int x_offset = ((SCREEN_WIDTH * SCALE_X) / 2) - w * 2;
	int y_offset = SCREEN_HEIGHT - (w * 2);
	int t[4];	
	for (int i=0; i < 4; i++)
	{
		fprintf (stdout, "Creating button %i with letter %s\n", i, std::string(1, letters[i]).c_str());
		textures[i].loadFromRenderedText (std::string(1, letters[i]), SDL_Color {0,0,0}, fontSchool);
		t[i] = add_target (x_offset + (i*w), y_offset, TARGET_BUTTON, w, w, i);
	//	fprintf (stdout, "x=%i y=%i w=%i\n", x_offset + (i*w), y_offset, w);
	}
	gTargets[t[0]].setDeathFunc (shot_1);
	gTargets[t[1]].setDeathFunc (shot_2);
	gTargets[t[2]].setDeathFunc (shot_3);
	gTargets[t[3]].setDeathFunc (shot_4);
}

void speller_start ()
{
	int i;
	fprintf (stdout, "Spell some words\n");
//	load_sfx();
	bg.clear();
	bg.set ("./data/png/Speller_bg.png");
	generate_new_answer ();
	sound.loadRoundSFX (0, "./data/sfx/627084__netvillage__ok.wav");
	sound.loadRoundSFX (1, "./data/sfx/572936__bloodpixelhero__error.wav");
	rnd.setTarget(20);
	rnd.setTimeout(30);
	rnd.setRoundUpdate(speller_update);
	
}
static void render_guess ()
{
	if (guess.length() == 0)
		return;
	guessTexture.loadFromRenderedText (guess, SDL_Color {255,255,255}, fontSchool);	
	SDL_Rect r;
	r.x = ((SCREEN_WIDTH *SCALE_X) / 2) - ( 100);
	r.y = 80;
	r.w = guessTexture.getWidth() * SCALE_X;
	r.h = guessTexture.getHeight();
	SDL_RenderCopy (gRenderer, guessTexture.getTexture(), nullptr, &r);
}

bool speller_update ()
{
	render_guess ();
	if (players[0].getHits() >= rnd.getTarget())
	{
		return false;
	}
	return true;
}
