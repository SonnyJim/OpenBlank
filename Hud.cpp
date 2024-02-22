#include "Hud.h"
#include "Round.h"
#include "Media.h"
#include "OpenBlank.h"
#include "LTexture.h"
#include "LTarget.h"
#include "Player.h"
#include "Sound.h"
#include <string>
Hud hud;
LTexture gHudTimer;
LTexture gHudTargets;
LTexture gHudBullets;
LTexture gHeartTexture;

void render_crosshair ()
{
	int x, y;
	SDL_Rect t;
	t.x = 0;
	t.y = 0;
	t.w = 40; //FIXME do dynamically
	t.h = 40;
	SDL_GetMouseState( &x, &y );
	x = x / SCALE_X;
	gCrosshairTexture.render (x - (t.w/2), y - (t.h/2), &t);
}



void Hud::addCheckmark(SDL_Point p)
{
	add_target (p.x - gCheckmarkTexture.getWidth(), p.y - gCheckmarkTexture.getHeight(), TARGET_CHECKMARK, gCheckmarkTexture.getWidth() * 2, gCheckmarkTexture.getHeight()* 2, TEX_CHECKMARK);
}

void Hud::addCross(SDL_Point p)
{
	sound.playSFX (SFX_ERROR);
	add_target (p.x - gRedCrossTexture.getWidth(), p.y - gRedCrossTexture.getHeight(), TARGET_REDCROSS, gRedCrossTexture.getWidth() * 2, gRedCrossTexture.getHeight()* 2, TEX_REDCROSS);
}

void Hud::draw ()
{
	if (rnd.isActive() == false)
		return;
	SDL_Rect r;

	//Draw tieer
	int timer = (rnd.getTimeout() * 1000 )- rnd.getDuration();
	gHudTimer.loadFromRenderedText (std::to_string(timer / 1000), SDL_Color {0,0,0}, fontHud);
	r.x = 0;
	r.y = 0;
	r.w = gHudTimer.getWidth();
	r.h = gHudTimer.getHeight();

	gHudTimer.render (((SCREEN_WIDTH) / 2 ) - (r.w / 2), 0, &r);

	//Render targets left
	int lives = players[0].getLives();	
	int bullets = players[0].getBullets();	
	int targets = players[0].getHits();
	int goal = rnd.getTarget();
	
	r.w = gHeartTexture.getWidth();
	r.h = gHeartTexture.getHeight();
	for (int i=0; i<lives;i++)
	{
		gHeartTexture.render (i * r.w, SCREEN_HEIGHT - r.h, &r);
	}
	int txt_offset = SCREEN_HEIGHT - r.h;

	std::string txtOutput = std::to_string(targets) + "/" + std::to_string(goal);
	gHudTargets.loadFromRenderedText (txtOutput, SDL_Color {0,0,0}, fontHud);
	r.w = gHudTargets.getWidth();
	r.h = gHudTargets.getHeight();
	gHudTargets.render (0, txt_offset - r.h, &r);
	
	}
