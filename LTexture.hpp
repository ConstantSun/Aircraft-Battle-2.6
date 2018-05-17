
#ifndef LTEXTURE_H_
#define LTEXTURE_H_
#include"General_Function.hpp"

class LTexture
{
	public:
		LTexture(SDL_Renderer *g_renderer_, SDL_Rect rect );
		~LTexture();

		bool loadFromFile( std::string path );
		void free();
		void setColor( Uint8 red, Uint8 green, Uint8 blue );
		void setAlpha( Uint8 alpha );
		void render( );
		int getWidth();
		int getHeight();

	private:
	    SDL_Renderer *g_renderer ;
		SDL_Texture* mTexture;
		SDL_Rect rect_ ;
		int mWidth;
		int mHeight;
};

#endif // LTEXTURE_H_
