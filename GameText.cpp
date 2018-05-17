#include"GameText.hpp"
bool GameText::loadFromRenderedText(TTF_Font *gFont, std::string textureText, SDL_Color textColor, SDL_Renderer *gRenderer )
{
	//Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Solid( gFont, textureText.c_str(), textColor );

	if( textSurface == NULL )
	{
		printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
	}
	else
	{
		//Create texture from surface pixels
        p_object_ = SDL_CreateTextureFromSurface( gRenderer, textSurface );
		if( p_object_ == NULL )
		{
			printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
		}
		else
		{
			//Get image dimensions
			rect_.w = textSurface->w;
			rect_.h = textSurface->h;
		}
		//Get rid of old surface
		SDL_FreeSurface( textSurface );
	}

	//Return success
	return p_object_ != NULL;
}

void GameText::Present(SDL_Renderer *ren)
{
    SDL_RenderCopy(ren,p_object_,NULL,&rect_);
    SDL_RenderPresent(ren);
};

string GameText::ConvertIntToString(){
    int v = value_ ;
    string stringText ;
    if(v<=0) stringText = '0' ;
    while(v){
        stringText =(char)(v%10+48) + stringText ;
        v/=10;
    }
    return stringText ;
}

void GameText::ShowNum (TTF_Font *gFont, SDL_Color textColor, SDL_Renderer *gRenderer  )
{
    if ( loadFromRenderedText(gFont, ConvertIntToString() , textColor,gRenderer ) )
    {
        SDL_RenderCopy(gRenderer,p_object_,NULL,&rect_);
        SDL_RenderPresent(gRenderer);
    }
}
