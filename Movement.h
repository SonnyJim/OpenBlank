/*
 * =====================================================================================
 *
 *       Filename:  Movement.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  02/06/2024 12:47:51 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Dr. Fritz Mehner (mn), mehner@fh-swf.de
 *        Company:  FH Südwestfalen, Iserlohn
 *
 * =====================================================================================
 */
#include <SDL2/SDL.h>

enum valMove_t
{
	VAL_ROTSPEED,
	VAL_ANGLE,
	VAL_DY,
	VAL_DX,
	VAL_GRAVITY
};

extern void movement_all ();
extern bool bounds_check (int x, int y, int w, int h);
extern double getRandom(double min, double max);
