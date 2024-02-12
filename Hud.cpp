#include "Hud.h"
#include "Round.h"
#include "Media.h"
#include "OpenBlank.h"
#include "LTexture.h"
#include "Player.h"
#include <string>
Hud hud;
LTexture gHudTimer;
LTexture gHudTargets;
LTexture gHudBullets;
LTexture gHeartTexture;

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
