/*
 * =====================================================================================
 *
 *       Filename:  Media.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  02/06/2024 12:40:29 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Dr. Fritz Mehner (mn), mehner@fh-swf.de
 *        Company:  FH Südwestfalen, Iserlohn
 *
 * =====================================================================================
 */

#include <SDL2/SDL_ttf.h>

extern bool media_load ();

#define FONT_TITLE_PATH "./data/ttf/Christmas Graffiti.ttf"
extern TTF_Font* fontTitle;
