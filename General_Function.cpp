#include "General_Function.hpp"
SDL_Texture * SDL_General::LoadImage(string path, SDL_Renderer *gRenderer) {

	SDL_Texture* newTexture = NULL;
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		newTexture = SDL_CreateTextureFromSurface( gRenderer , loadedSurface);
		if (newTexture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}
		SDL_FreeSurface(loadedSurface);
	}

	return newTexture;

}

void SDL_General::ApplySurface( SDL_Renderer *renderer , SDL_Texture *src, int x, int y, int w, int h) {
	SDL_Rect offset;
	offset.x = x;
	offset.y = y;
	offset.h = h;
	offset.w = w;
	SDL_RenderCopy(renderer, src , NULL, &offset);
	SDL_RenderPresent(renderer);
}

void SDL_General::CleanUp() {
	SDL_DestroyWindow(g_Window);
	SDL_DestroyRenderer(g_renderer);
	SDL_Quit();
}

void SDL_General::LoadIntro(SDL_Renderer* ren)
{
    g_intro = SDL_General::LoadImage("gameShooting/intro.png", ren);
}
void SDL_General::ShowIntro(SDL_Renderer* ren)
{
    rect_screen.w = SCREEN_WIDTH ;
	rect_screen.h = SCREEN_HEIGHT ;

    SDL_RenderCopy(ren,g_intro,NULL,&rect_screen);
    SDL_RenderPresent(ren);
}
void SDL_General::LoadBackGround(SDL_Renderer* ren)
{
    g_background = SDL_General::LoadImage("gameShooting/perfectBK.png", ren);

    rect_background.w = BKGROUND_WIDTH ;
    rect_background.h = BKGROUND_HEIGHT/3 ;
    rect_background.x = 0;
    rect_background.y = BKGROUND_HEIGHT/3;

    rect_screen.w = SCREEN_WIDTH;
    rect_screen.h = SCREEN_HEIGHT;
    rect_screen.x = 0;
    rect_screen.y = 0;
}
void SDL_General::ShowBackGround(SDL_Renderer* ren)
{
	SDL_RenderCopy(ren,g_background,&rect_background,&rect_screen);
    SDL_RenderPresent(ren);

    if ( rect_background.y <= PIXEL_LIM ) {
        rect_background.y = PIXEL_START ;
    }
    else {
        rect_background.y-=PIXEL;
    }

}


bool SDL_General::Do_main_bullet_overlap_enemy(SDL_Rect mainbullet, SDL_Rect enemy) {
    if ( mainbullet.y - enemy.y >=0 && mainbullet.y - enemy.y <= 74 && mainbullet.x - enemy.x > 36 &&  mainbullet.x - enemy.x < (80 - 11) ) {
        return true;
    }
    if (mainbullet.y - enemy.y >=0 && mainbullet.y - enemy.y < 60 && ( (mainbullet.x - enemy.x >=0 && mainbullet.x - enemy.x <= 36) ||  (mainbullet.x - enemy.x >=80 && mainbullet.x - enemy.x<=103) )) {
        return true;
    }
    return false;
}
bool SDL_General::Do_enemy_bullet_overlap_main_object(SDL_Rect enemybullet, SDL_Rect mainobject)
{
    if ( mainobject.y - enemybullet.y < 25 && enemybullet.x - mainobject.x >52 && enemybullet.x - mainobject.x < 60 )
        return true;
    if (  mainobject.y - enemybullet.y < 21 && enemybullet.x - mainobject.x > 80 && enemybullet.x - mainobject.x <90 )
        return true;
    if (  mainobject.y - enemybullet.y <35 && (   ( enemybullet.x - mainobject.x >0 && enemybullet.x - mainobject.x <10  )   ||  (  enemybullet.x - mainobject.x > 100  &&  enemybullet.x - mainobject.x< 112    )   )  )
        return true;
    return false;
}

bool SDL_General::Do_two_objects_overlap(SDL_Rect ob1, SDL_Rect ob2)
{
    if( ob1.x + ob1.w < ob2.x || ob2.x + ob2.w <ob1.x ){
        return false;
    }
    if ( ob1.y + ob1.h < ob2.y || ob2.y + ob2.h < ob1.y ) {
        return false;
    }
    return true;
};
