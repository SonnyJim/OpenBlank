/*
 * =====================================================================================
 *
 *       Filename:  Player.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  02/06/2024 01:18:17 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Dr. Fritz Mehner (mn), mehner@fh-swf.de
 *        Company:  FH Südwestfalen, Iserlohn
 *
 * =====================================================================================
 */
#include "Player.h"
#include <stdio.h>

Player::Player()
{
	setLives (3);
	setScore (0);
	setBullets (6);
}

void Player::addScore (int amount)
{
	score += amount;
}

void Player::setScore (int amount)
{
	score = amount;
}

int Player::getScore ()
{
	return score;
}

void Player::shoot ()
{
	fprintf (stdout, "Pew! ");
}

int Player::getLives ()
{
	return lives;
}

void Player::setLives (int amount)
{
	lives = amount;
}
int Player::getBullets ()
{
	return bullets;
}

void Player::setBullets (int amount)
{
	bullets = amount;
}
