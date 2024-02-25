#include <SDL2/SDL.h>
#include <string>
#include "Background.h"
#include "OpenBlank.h"
#include "LTexture.h"
#include "SDL.h"

Background bg;
LTexture bgTexture;

void Background::render()
{
	if (!active)
		return;
	SDL_Rect renderQuad = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
	
	//Render to screen
	SDL_RenderCopyEx( gRenderer, bgTexture.getTexture(), NULL, &renderQuad, 0,0, SDL_FLIP_NONE);
}

void Background::clear()
{
	active = false;
	bgTexture.free();
}
void Background::set(std::string path)
{
	//TODO error checking
	if (bgTexture.loadFromFile(path))
		active = true;
}
