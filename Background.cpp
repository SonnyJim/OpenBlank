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
	if (bgTexture.getTexture() == NULL)
		return;
	SDL_Rect renderQuad = { 0, 0, SCREEN_WIDTH * SCALE_X, SCREEN_HEIGHT};
	
	//Render to screen
	SDL_RenderCopyEx( gRenderer, bgTexture.getTexture(), NULL, &renderQuad, 0,0, SDL_FLIP_NONE);
}

void Background::clear()
{
	bgTexture.free();
}
void Background::set(std::string path)
{
	//TODO error checking
	bgTexture.loadFromFile(path);
}
