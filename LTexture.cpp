#include "LTexture.hpp"
#include "General_Function.hpp"

LTexture::LTexture(SDL_Renderer *g_renderer_,SDL_Rect rect)
{
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
	g_renderer = g_renderer_ ;
	rect_ = rect ;
}
LTexture::~LTexture()
{
	free();
}
bool LTexture::loadFromFile( std::string path )
{
    free();
	mTexture  = SDL_General::LoadImage(path,g_renderer);
	return mTexture != NULL;
}
void LTexture::free()
{
	if( mTexture != NULL )
	{
		SDL_DestroyTexture( mTexture );
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

void LTexture::setColor( Uint8 red, Uint8 green, Uint8 blue )
{
	//Modulate texture rgb
	SDL_SetTextureColorMod( mTexture, red, green, blue );
}
void LTexture::setAlpha( Uint8 alpha )
{
	//Modulate texture alpha
	SDL_SetTextureAlphaMod( mTexture, alpha );
}
void LTexture::render()
{
    SDL_RenderCopy( g_renderer, mTexture, NULL, &rect_ );
}
int LTexture::getWidth()
{
	return mWidth;
}

int LTexture::getHeight()
{
	return mHeight;
}
