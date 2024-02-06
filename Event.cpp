#include <SDL2/SDL.h>
#include "Player.h"

extern bool quit;
void event_handler ()
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
		

		if ( e.type == SDL_MOUSEBUTTONDOWN)
		{
			//	Mix_PlayChannel (-1, gGunshot, 0); //TODO Make a 'trigger pulled' function
			//bullet_add();
			players[0].shoot();
		}
	}
		/*
		//If mouse event happened
		if( e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP )
		{
			//Get mouse position
			int x, y;
			SDL_GetMouseState( &x, &y );

			//Check if mouse is in button
			bool inside = true;

			//Mouse is left of the button
			if( x < mPosition.x )
			{
				inside = false;
			}
			//Mouse is right of the button
			else if( x > mPosition.x + mWidth )
			{
				inside = false;
			}
			//Mouse above the button
			else if( y < mPosition.y )
			{
				inside = false;
			}
			//Mouse below the button
			else if( y > mPosition.y + mHeight )
			{
				inside = false;
			}

			//Mouse is inside button
			else
			if (inside)
			{
				//Set mouse over sprite
				switch( e->type )
				{
					case SDL_MOUSEMOTION:
					//mCurrentSprite = BUTTON_SPRITE_MOUSE_OVER_MOTION;
					break;
				
					case SDL_MOUSEBUTTONDOWN:
						setType (TARGET_NONE);
						//active = false;
						//mCurrentSprite = BUTTON_SPRITE_MOUSE_DOWN;
						break;
					
					case SDL_MOUSEBUTTONUP:
					//mCurrentSprite = BUTTON_SPRITE_MOUSE_UP;
					break;
				}
			}
		}

	}*/
}



