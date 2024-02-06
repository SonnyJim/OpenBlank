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
#include "BulletHole.h"
#include "Sound.h"
#include "Detect.h"
#include <stdio.h>

Player players[MAX_PLAYERS];

Player::Player()
{
	setLives (3);
	setScore (0);
	setBullets (6);
	setPosition (SDL_Point {0,0});
}

void Player::setPosition (SDL_Point pos)
{
	position = pos;
}

SDL_Point Player::getPosition ()
{
	return position;
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
	sound.playSFX (SFX_GUNSHOT);
	SDL_Point pos;
	SDL_GetMouseState (&pos.x, &pos.y);
	setPosition (pos);
	detect_shot ();
	bullet_add ();
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

void Player::addHit (int value)
{
	hits += value;
	//TODO probably some bounds checking
}
void Player::addMiss (int value)
{
	misses += value;
}

int Player::getHits()
{
	return hits;
}

int Player::getMisses()
{
	return misses;
}

void Player::setMisses(int value)
{
	misses = value;
}

void Player::setHits(int value)
{
	hits = value;
}

void Player::endRound ()
{
	hits = 0;
	misses = 0;
}
