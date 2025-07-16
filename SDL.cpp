/*
 * =====================================================================================
 *
 *       Filename:  SDL.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  02/06/2024 12:06:00 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Dr. Fritz Mehner (mn), mehner@fh-swf.de
 *        Company:  FH Südwestfalen, Iserlohn
 *
 * =====================================================================================
 */
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <cstdlib>
#include <ctime>
#include "SDL.h"
#include "OpenBlank.h"
#include "Sound.h"
#include "LTexture.h"
#include "LTarget.h"
#include "BulletHole.h"
#include "Title.h"
#include "Game.h"
#include "Hud.h"
#include "Background.h"

const int INTERNAL_WIDTH = 640;
const int INTERNAL_HEIGHT = 480;
SDL_Texture* gRenderTexture = NULL;

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

bool sdl_init()
{
	bool success = true;

	srand(time(nullptr));

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		return false;
	}

	if (!sound.init())
	{
		return false;
	}

	if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
	{
		printf("Warning: Linear texture filtering not enabled!\n");
	}

	// Create fullscreen window
	gWindow = SDL_CreateWindow("Open Blank",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		INTERNAL_WIDTH * 2, INTERNAL_HEIGHT * 2, // Default size, will scale anyway
		SDL_WINDOW_FULLSCREEN_DESKTOP);

	if (!gWindow)
	{
		printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
		return false;
	}

	gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!gRenderer)
	{
		printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
		return false;
	}

	SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF); // Default black

	// Create internal render target
	gRenderTexture = SDL_CreateTexture(gRenderer,
		SDL_PIXELFORMAT_RGBA8888,
		SDL_TEXTUREACCESS_TARGET,
		INTERNAL_WIDTH, INTERNAL_HEIGHT);

	if (!gRenderTexture)
	{
		printf("Render texture creation failed! SDL Error: %s\n", SDL_GetError());
		return false;
	}

	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
		return false;
	}

	SDL_ShowCursor(0);
	return true;
}

void sdl_close()
{
	fprintf (stdout, "Shutting down SDL\n");
	//Free loaded images
	gRedTargetTexture.free();
	gBlueTargetTexture.free();
	gCrosshairTexture.free();
	//Destroy window	
	SDL_DestroyTexture(gRenderTexture);
	gRenderTexture = NULL;
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	sound.quit();
	IMG_Quit();
	TTF_Quit();
	SDL_Quit();
}

void sdl_clear()
{
	SDL_SetRenderTarget(gRenderer, gRenderTexture);
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(gRenderer);
	bg.render();
}

#define TARGET_FPS 30
void sdl_render()
{
	Uint32 frameStart = SDL_GetTicks();

	// Render scene to gRenderTexture
	SDL_SetRenderTarget(gRenderer, gRenderTexture);

	if (game.getState() == STATE_TITLESCREEN)
		titlescreen.render();

	for (int i = 0; i < MAX_TARGETS; ++i)
		gTargets[i].render();

	for (int i = 0; i < MAX_BULLETHOLES; ++i)
		gBulletHoles[i].render();

	hud.draw();
	render_crosshair();

	// Render gRenderTexture to screen
	SDL_SetRenderTarget(gRenderer, NULL);

	int winW, winH;
	SDL_GetRendererOutputSize(gRenderer, &winW, &winH);

	float scaleX = (float)winW / INTERNAL_WIDTH;
	float scaleY = (float)winH / INTERNAL_HEIGHT;
	float scale = fmin(scaleX, scaleY);

	int destW = INTERNAL_WIDTH * scale;
	int destH = INTERNAL_HEIGHT * scale;
	int offsetX = (winW - destW) / 2;
	int offsetY = (winH - destH) / 2;

	SDL_Rect destRect = { offsetX, offsetY, destW, destH };

	SDL_RenderClear(gRenderer); // clear black background
	SDL_RenderCopy(gRenderer, gRenderTexture, NULL, &destRect);
	SDL_RenderPresent(gRenderer);

	int frameTime = SDL_GetTicks() - frameStart;
	if (frameTime < (1000 / TARGET_FPS))
		SDL_Delay((1000 / TARGET_FPS) - frameTime);
	else
		fprintf(stdout, "System too slow? frameTime %i\n", frameTime);
}
