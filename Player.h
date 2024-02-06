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
	private:
		int bullets;
		int score;
		int lives;
};

