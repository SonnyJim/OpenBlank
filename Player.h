/*
 * =====================================================================================
 *
 *       Filename:  Player.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  02/06/2024 01:04:26 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Dr. Fritz Mehner (mn), mehner@fh-swf.de
 *        Company:  FH Südwestfalen, Iserlohn
 *
 * =====================================================================================
 */

#include <SDL2/SDL.h>
class Player {
	public:
		Player();
		void addScore(int amount);
		void setScore(int amount);
		int getScore ();
		void shoot ();
		int getLives ();
		void setLives (int lives);
		int getBullets ();
		void setBullets (int amount);
		SDL_Point getPosition();
		void setPosition (SDL_Point pos);
		void addHit(int hits);
		void addMiss(int hits);
		int getHits();
		int getMisses();
		void setMisses(int value);
		void setHits (int value);
	private:
		int bullets;
		int score;
		int lives;
		int hits;
		int misses;
		SDL_Point position;
};

#define MAX_PLAYERS 1
extern Player players[MAX_PLAYERS];
