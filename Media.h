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

extern bool media_init ();

#define FONT_TITLE_SIZE 60
#define FONT_HUD_SIZE 60
#define FONT_TITLE_PATH "./data/ttf/Christmas Graffiti.ttf"
#define FONT_HUD_PATH "./data/ttf/Star Cartoon.ttf"
extern TTF_Font* fontTitle;
extern TTF_Font* fontHud;
