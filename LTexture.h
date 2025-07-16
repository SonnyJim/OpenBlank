#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string>

class LTexture
{
	public:
		//Initializes variables
		LTexture();

		//Deallocates memory
		~LTexture();

		//Creates a blank texture for use
		bool createBlank(int width, int height);

		//Loads image at specified path
		bool loadFromFile( std::string path );
		
		//Creates image from font string
		bool loadFromRenderedText( std::string textureText, SDL_Color textColor , TTF_Font* gFont);

		//Deallocates texture
		void free();

		//Set color modulation
		void setColor( Uint8 red, Uint8 green, Uint8 blue );

		//Set blending
		void setBlendMode( SDL_BlendMode blending );

		//Set alpha modulation
		void setAlpha( Uint8 alpha );
		
		//Renders texture at given point
		void render( int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );

		//Gets image dimensions
		int getWidth();
		int getHeight();
		SDL_Texture* getTexture();

	private:
		//The actual hardware texture
		SDL_Texture* mTexture;
		//Image dimensions
		int mWidth;
		int mHeight;
};

#define MAX_TEXTURES 20

#define TEXTURE_REDTARGET_PATH "./data/png/RedTarget.png"
#define TEXTURE_BLUETARGET_PATH "./data/png/BlueTarget.png"
#define TEXTURE_BOMB_PATH "./data/png/Bomb.png"
#define TEXTURE_HEART_PATH "./data/png/Heart.png"

extern LTexture textures[MAX_TEXTURES]; //Array of textures dynamically loaded at round start
extern LTexture gRedTargetTexture;
extern LTexture gBlueTargetTexture;
extern LTexture gBombTexture;
extern LTexture gCrosshairTexture;
extern LTexture gHeartTexture;
extern LTexture gTitlescreen;
extern LTexture gHudTimer;
//extern LTexture gHudLives;
extern LTexture gHudTargets;
extern LTexture gHudBullets;
extern LTexture bgTexture;
extern LTexture gCheckmarkTexture;
extern LTexture gRedCrossTexture;

enum { TEX_CHECKMARK, TEX_REDCROSS};
