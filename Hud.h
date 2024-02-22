#include <SDL2/SDL.h>
class Hud
{
	public:
		void draw ();
		void addCheckmark(SDL_Point p);
		void addCross(SDL_Point p);
	private:
};
extern Hud hud;
extern void render_crosshair ();
