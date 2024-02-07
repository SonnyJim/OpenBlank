#include "Game.h"
#include "Movement.h"
#include "LTarget.h"
#include "SDL.h"
#include "Round.h"
#include "Title.h"

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
	round = 0;
	rnd.start();
}

void Game::end()
{
}

int Game::getRound ()
{
	return round;
}

void Game::setRound (int value)
{
	round = value;
}

extern void event_handler ();
void Game::update()
{
	event_handler ();
	if (game.getState() == STATE_TITLESCREEN)
	{
		titlescreen.render ();
	}
	else
	{
		rnd.update();
		movement_all ();
	}
	sdl_render ();
}
