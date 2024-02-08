#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

class LTexture
{
	public:
		//Initializes variables
		LTexture();

		//Deallocates memory
		~LTexture();

		//Loads image at specified path
		bool loadFromFile( std::string path );
		
		#if defined(SDL_TTF_MAJOR_VERSION)
		//Creates image from font string
		bool loadFromRenderedText( std::string textureText, SDL_Color textColor );
		#endif
		
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

#define MAX_TEXTURES 10

#define TEXTURE_REDTARGET_PATH "./data/png/RedTarget.png"
#define TEXTURE_BLUETARGET_PATH "./data/png/BlueTarget.png"

extern LTexture textures[MAX_TEXTURES];
extern LTexture gRedTargetTexture;
extern LTexture gBlueTargetTexture;
extern LTexture gCrosshairTexture;
extern LTexture gTitlescreen;
