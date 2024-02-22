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

void Hud::addCheckmark(int x, int y)
{
	add_target (x - gCheckmarkTexture.getWidth(), y - gCheckmarkTexture.getHeight(), TARGET_CHECKMARK, gCheckmarkTexture.getWidth() * 2, gCheckmarkTexture.getHeight()* 2, TEX_CHECKMARK);
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
	r.w = gHudTimer.getWidth() * SCALE_X;
	r.h = gHudTimer.getHeight();

	gHudTimer.render (((SCREEN_WIDTH * SCALE_X) / 2 ) - (r.w / 2), 0, &r);

	//Render targets left
	int lives = players[0].getLives();	
	int bullets = players[0].getBullets();	
	int targets = players[0].getHits();
	int goal = rnd.getTarget();
	std::string txtOutput = std::to_string(targets) + "/" + std::to_string(goal);
	gHudTargets.loadFromRenderedText (txtOutput, SDL_Color {0,0,0}, fontHud);
	r.w = gHudTargets.getWidth() * SCALE_X;
	r.h = gHudTargets.getHeight();
	gHudTargets.render (0, SCREEN_HEIGHT - (r.h * 2), &r);
	
	r.w = gHeartTexture.getWidth() * SCALE_X;
	r.h = gHeartTexture.getHeight();
	for (int i=0; i<lives;i++)
	{
		gHeartTexture.render (i * r.w, SCREEN_HEIGHT - r.h * 2, &r);
	}
}
