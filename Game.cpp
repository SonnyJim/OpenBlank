#include "Game.h"
#include "Movement.h"
#include "LTarget.h"
#include "SDL.h"

Game game;

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

extern void event_handler ();
void Game::update()
{
	event_handler ();
	movement_all ();
	sdl_render ();
}
