#include"MainObject.hpp"
MainObject::MainObject() {
	rect_.x = SCREEN_WIDTH/2 - WIDTH_MAIN_OBJECT/2  ;
	rect_.y = SCREEN_HEIGHT- HEIGHT_MAIN_OBJECT;
	rect_.w = WIDTH_MAIN_OBJECT;
	rect_.h = HEIGHT_MAIN_OBJECT;

	x_val_ = rect_.x;
	y_val_ = rect_.y;

    rectTexture[0].x=0;
    rectTexture[0].y=0;
    rectTexture[0].w=122;
    rectTexture[0].h=106;

    rectTexture[1].x=152;
    rectTexture[1].y=0;
    rectTexture[1].w=122;
    rectTexture[1].h=106;

    rectTexture[2].x=304;
    rectTexture[2].y=0;
    rectTexture[2].w=122;
    rectTexture[2].h=106;


    rectTexture[3].x=456;
    rectTexture[3].y=0;
    rectTexture[3].w=122;
    rectTexture[3].h=106;


    rectTexture[4].x=608;
    rectTexture[4].y=0;
    rectTexture[4].w=122;
    rectTexture[4].h=106;


    rectTexture[5].x=760;
    rectTexture[5].y=0;
    rectTexture[5].w=122;
    rectTexture[5].h=106;


    rectTexture[6].x=912;
    rectTexture[6].y=0;
    rectTexture[6].w=122;
    rectTexture[6].h=106;

    rect_injured[0].x = 0;
    rect_injured[0].y = 0;
    rect_injured[0].w = 122;
    rect_injured[0].h = 106;

    rect_injured[1].x = 152;
    rect_injured[1].y = 0;
    rect_injured[1].w = 122;
    rect_injured[1].h = 106;

    rect_injured[2].x = 152*2;
    rect_injured[2].y = 0;
    rect_injured[2].w = 122;
    rect_injured[2].h = 106;


    rect_injured[3].x = 152*3;
    rect_injured[3].y = 0;
    rect_injured[3].w = 122;
    rect_injured[3].h = 106;

    rect_death[0].x = 0 ;
    rect_death[0].y = 0 ;
    rect_death[0].w = 122 ;
    rect_death[0].h = 124 ;

    rect_death[1].x = 150 ;
    rect_death[1].y = 0 ;
    rect_death[1].w = 122 ;
    rect_death[1].h = 124 ;

    rect_death[2].x = 150*2 ;
    rect_death[2].y = 0 ;
    rect_death[2].w = 122 ;
    rect_death[2].h = 124 ;

    rect_death[3].x = 150*3 ;
    rect_death[3].y = 0 ;
    rect_death[3].w = 122 ;
    rect_death[3].h = 124 ;

    rect_death[4].x = 150*4 ;
    rect_death[4].y = 0 ;
    rect_death[4].w = 122 ;
    rect_death[4].h = 124 ;

    rect_death[5].x = 150*5 ;
    rect_death[5].y = 0 ;
    rect_death[5].w = 122 ;
    rect_death[5].h = 124 ;

    rect_death[6].x = 150*6 ;
    rect_death[6].y = 0 ;
    rect_death[6].w = 122 ;
    rect_death[6].h = 124 ;
}
MainObject::~MainObject() {
}

bool MainObject::LoadInjuredImg(string path, SDL_Renderer *ren)
{
    injured_ = SDL_General::LoadImage(path.c_str(),ren);
    if (injured_ == NULL)
    {
        return false;
    }
	return true;
}

void MainObject::ShowInjured(SDL_Renderer* ren)
{
    SDL_RenderCopy(ren,injured_,&rect_injured[1] , &rect_) ;
    SDL_RenderPresent(ren);
    count_injured_times_++;
    if ( count_injured_times_ >= MAX_INJURED_TIMES )
    {
        is_shown_injured_ = false ;
        count_injured_times_ = 0 ;
    }

};
void MainObject::HandleInputAction(SDL_Event events, SDL_Renderer* ren, Mix_Music* m_bullet) {
	switch (events.type)
	{
	case SDL_KEYDOWN:
		switch (events.key.keysym.sym)
		{
		case SDLK_UP:
			if (y_val_ - HEIGHT_MAIN_OBJECT / 4 >= 0)
				y_val_ = y_val_ - HEIGHT_MAIN_OBJECT/4 ;
			break;

		case SDLK_DOWN:
			if ( y_val_ + HEIGHT_MAIN_OBJECT / 4<= SCREEN_HEIGHT- HEIGHT_MAIN_OBJECT/3 )
				y_val_+= HEIGHT_MAIN_OBJECT/4;
				break;

		case SDLK_RIGHT:
			if ( x_val_ + WIDTH_MAIN_OBJECT/3 <= SCREEN_WIDTH - WIDTH_MAIN_OBJECT/3 )
				x_val_+= WIDTH_MAIN_OBJECT/3 ;
				break;

		case SDLK_LEFT:
			if (x_val_ + WIDTH_MAIN_OBJECT / 2 >= 0 )
				x_val_-= WIDTH_MAIN_OBJECT/3 ;
				break;

        case SDLK_SPACE:{
            Mix_PlayMusic(m_bullet,0);

            BulletObject* p_bulletblue= new BulletObject();
            BulletObject* p_bulletpink= new BulletObject();

            p_bulletblue->LoadImg("gameShooting/bluebullet.png",ren );
            p_bulletpink->LoadImg("gameShooting/pinkbullet.png",ren );

            p_bulletblue->SetRect(this->rect_.x + 93, this->rect_.y - 15 );
            p_bulletpink->SetRect( this->rect_.x +20, this->rect_.y -15 ) ;

            p_bulletblue->SetIsMove(true);
            p_bulletpink->SetIsMove(true);

            p_bullet_list_.push_back(p_bulletblue);
            p_bullet_list_.push_back(p_bulletpink);

            }
            break;

		}
		break;
	}
}

void MainObject::HandleMove() {
	rect_.x = x_val_;
	rect_.y = y_val_;
}

void MainObject::ControlBullet(SDL_Renderer* g_renderer)
{
    for (unsigned int i=0; i< p_bullet_list_.size(); i++ )
    {
            if( p_bullet_list_[i] ->GetIsMove() )
            {
                p_bullet_list_[i]->Show(g_renderer);
                p_bullet_list_[i]->HandleMove(0,0);
            } else {
                delete p_bullet_list_[i];
                p_bullet_list_.erase(p_bullet_list_.begin()+i);
                //Vcout<< "bullet list size = " << p_bullet_list_.size()<<endl;
            }
    }
}

void MainObject::ShowAnimation(SDL_Renderer* ren)
{
    SDL_RenderCopy(ren, full_object_, &rectTexture[frame], &rect_);
    SDL_RenderPresent(ren);
    frame = (frame+1)%7;
}

void MainObject::LoadDeathImg(string path, SDL_Renderer *ren)
{
    death_ = SDL_General::LoadImage(path.c_str(),ren);
    if (death_ == NULL) cout << " can't load main death ! " << endl;
} ;
void MainObject::ShowDeath(SDL_Renderer* ren, bool &is_quit)
{
    SDL_RenderCopy(ren, death_, &rect_death[frame_death], &rect_);
    SDL_RenderPresent(ren);
    frame_death++;
    if (frame_death >= 7) is_quit = true ;
} ;



