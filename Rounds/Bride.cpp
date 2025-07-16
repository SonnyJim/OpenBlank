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

enum { TEX_ARM, TEX_BRIDE, TEX_PIE, TEX_DISTANCE};
static LTexture arm;
static LTexture pie;
static LTexture distance;
static double arm_angle;
static int arm_speed;
static const SDL_Point pivot_point = {11,75}; //Pivot point within the arm texture
static SDL_Point pieP;
static SDL_Point pieD;
static int pieTargetNum;
static int start;

enum state_t { ARM_WINDING, ARM_THROWING, PIE_OFFSCREEN};

static state_t state;

static void load_sfx ()
{
	sound.loadRoundSFX (0, "data/sfx/232967__reitanna__pinkie-pie-whee.wav");
}

SDL_Point calculateNewPosition(const SDL_Point& p, double angle, double radius) 
{
    // Convert the angle from degrees to radians
    angle = angle * M_PI / 180.0;
	angle -= 1.5706; //Wind it back 90 degrees

    // Calculate the new coordinates using trigonometry
    int newX = p.x + static_cast<int>(radius * std::cos(angle));
    int newY = p.y + static_cast<int>(radius * std::sin(angle));

    // Return the new position as an SDL_Point
    return {newX, newY};
}
static int calc_distance ()
{
	SDL_Point p;
	if (state == PIE_OFFSCREEN)
	{
		pieP.x += pieD.x;
		pieP.y += 1;
		p.x = pieP.x;
		p.y = pieP.y;
		fprintf (stdout, "x=%i, y=%i\n", p.x, p.y);
		if (p.y >= 460)
		{
			fprintf (stdout, "Calc killed target\n");
			state = ARM_WINDING;
		}
	}
	else
		p = gTargets[pieTargetNum].getPosition();
	return -(p.x - start);
}

static void draw_distance ()
{
	std::string text;
	text = std::to_string (calc_distance());
	text += "cm";
	//fprintf (stdout, "%i,%i,%s| ", i, sequence[i], text);
	textures[TEX_DISTANCE].loadFromRenderedText (text, SDL_Color {0,0,0}, fontHud);
	SDL_Rect r;
	r.x = 192;
	r.y = 120;
	r.w = textures[TEX_DISTANCE].getWidth();
	r.h = textures[TEX_DISTANCE].getHeight();
	SDL_RenderCopyEx (gRenderer, textures[TEX_DISTANCE].getTexture(), NULL, &r, 0, NULL, SDL_FLIP_NONE);

}

static void arm_move()
{
	SDL_Rect r;
	r.x = 540;
	r.y = 243;
	r.w = arm.getWidth();
	r.h = arm.getHeight();
	SDL_RenderCopyEx (gRenderer, arm.getTexture(), NULL, &r, arm_angle, &pivot_point, SDL_FLIP_NONE);

	r.w = textures[TEX_PIE].getWidth();
	r.h = textures[TEX_PIE].getHeight();
	SDL_Point center = {542, 317};
	SDL_Point p = calculateNewPosition (center, arm_angle, arm.getHeight());
	r.x = p.x - (r.w / 2);
	r.y = p.y - (r.h / 2);
	pieP.x = r.x;
	pieP.y = r.y;
	SDL_RenderCopyEx (gRenderer, textures[TEX_PIE].getTexture(), NULL, &r, 0, &pivot_point, SDL_FLIP_NONE);

	arm_angle -= arm_speed;
	if (arm_angle < 0)
	{
		arm_angle += 360;
	}

}

static void pie_death (LTarget* pTarget)
{
	fprintf (stdout, "Switching to virtual pie mode\n");
	pieP = gTargets[pieTargetNum].getPosition();
	if (pieP.y > SCREEN_HEIGHT)
	{
		state = ARM_WINDING;
		return;
	}
	pieD = SDL_Point {pTarget->getVal(VAL_DY), pTarget->getVal(VAL_DX)};
	fprintf (stdout, "start x=%i, y=%i\n", pieP.x, pieP.y);
	state = PIE_OFFSCREEN;
}

static SDL_Point calculateDeltas(double angleDegrees, double speed) 
{
    // Convert angle from degrees to radians
    double angleRadians = angleDegrees * M_PI / 180.0;
    angleRadians += 1.5706; //Wind it back 90 degrees
    int deltaY;
    int deltaX;
    // Calculate delta y and delta x using trigonometric functions
    deltaY = speed * std::sin(angleRadians);
    deltaX = speed * std::cos(angleRadians);
    return {deltaX, deltaY};
}

static void throw_pie ()
{
	int t = add_target (pieP.x ,pieP.y, TARGET_IMAGE, textures[TEX_PIE].getWidth(), textures[TEX_PIE].getHeight(), TEX_PIE);
	pieTargetNum = t;
	start = pieP.x;
	if (t == -1)
		return; //Didn't get a target
	fprintf (stdout, "Adding target %i\n", t);
	gTargets[t].setMoveFunc (move_gravity);
	gTargets[t].setDeathFunc (pie_death);
	gTargets[t].setVal(VAL_GRAVITY, -0.4);
	SDL_Point deltas = calculateDeltas (arm_angle, 20);
	gTargets[t].setVal(VAL_DY, deltas.y);
	gTargets[t].setVal(VAL_DX, -deltas.x);
	fprintf (stdout, "Target gravity=%f dy=%f dx=%f\n", gTargets[t].getVal(VAL_GRAVITY), gTargets[t].getVal(VAL_DY), gTargets[t].getVal(VAL_DX));

	sound.playRoundSFX(0);
}

static void bride_hit (LTarget* pTarget)
{
	if (state != ARM_WINDING)
		return;
	state = ARM_THROWING;
	throw_pie();
}
static void load_pie ()
{
	SDL_Rect r;
	r.w = textures[TEX_BRIDE].getWidth();
	r.h = textures[TEX_BRIDE].getHeight();
	r.x = SCREEN_WIDTH - r.w;
	r.y = SCREEN_HEIGHT - r.h;
	int t = add_target (r.x, r.y, TARGET_BUTTON, r.w, r.h, TEX_BRIDE);
	gTargets[t].setDeathFunc(bride_hit);
	arm_angle = 0;		
	arm_speed = 10;
	state = ARM_WINDING;
}

void bride_start ()
{
	int i;
	fprintf (stdout, "Bride start\n");
	load_sfx();
	bg.clear();
	//bg.set ("./data/png/Asteroids/bg.png");
	//Render the nmbser 0-9 on some textres
	textures[TEX_BRIDE].loadFromFile("./data/png/Bride/Bride.png");
	arm.loadFromFile("./data/png/Bride/Arm.png");
	textures[TEX_PIE].loadFromFile("./data/png/Bride/Pie.png");
	load_pie();	

	rnd.setTarget(1);
	rnd.setTimeout(30);
	rnd.setRoundUpdate(bride_update);
}

bool bride_update () //TODO Convert to skeet shooting?
{
	if (state == ARM_WINDING)
		arm_move();
	else
		draw_distance();
	if (state == ARM_THROWING && gTargets[pieTargetNum].getType() == TARGET_NONE)
	{
		load_pie();
	}
	if (players[0].getHits() >= rnd.getTarget())
	{
		return false;
	}
	return true;
}

