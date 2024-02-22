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
#define FONT_HUD_SIZE 50
#define FONT_PHONE_SIZE 60
#define FONT_SCHOOL_SIZE 80
#define FONT_MOBY_SIZE 80
#define FONT_MOBY_SMALL_SIZE 20
#define FONT_TITLE_PATH "./data/ttf/Christmas Graffiti.ttf"
#define FONT_HUD_PATH "./data/ttf/Star Cartoon.ttf"
#define FONT_PHONE_PATH "./data/ttf/digital-7 (mono).ttf"
#define FONT_SCHOOL_PATH "./data/ttf/Schoolwork-Regular.ttf"
#define FONT_MOBY_PATH "./data/ttf/moby.monospace.ttf"
extern TTF_Font* fontTitle;
extern TTF_Font* fontHud;
extern TTF_Font* fontPhone;
extern TTF_Font* fontSchool;
extern TTF_Font* fontMoby;
extern TTF_Font* fontMobySmall;
