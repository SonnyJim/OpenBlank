/*
 * =====================================================================================
 *
 *       Filename:  SDL.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  02/06/2024 12:06:04 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Dr. Fritz Mehner (mn), mehner@fh-swf.de
 *        Company:  FH Südwestfalen, Iserlohn
 *
 * =====================================================================================
 */
#include <SDL2/SDL.h>
//The window we'll be rendering to
extern SDL_Window* gWindow;

//The window renderer
extern SDL_Renderer* gRenderer;

extern bool sdl_init ();
