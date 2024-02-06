#include "Game.h"
#include "Movement.h"
#include "LTarget.h"
#include "SDL.h"

Game game;
extern bool quit;

GameState Game::getState()
{
	return state;
}

void Game::setState(GameState s)
{
	state = s;
}
void Game::start()
{
	round = 1;
}

void Game::end()
{
}

void Game::update()
{
	SDL_Event e;
	//Handle events on queue
	while( SDL_PollEvent( &e ) != 0 )
	{
		//User requests quit
		if( e.type == SDL_QUIT )
		{
			quit = true;
		}
		
		//Handle button events
		for( int i = 0; i < MAX_TARGETS; ++i )
		{
			gTargets[ i ].handleEvent( &e );
		}
	}
	movement_all ();
	sdl_render ();
}
