#include"ThreatObject.hpp"

ThreatObject::ThreatObject(){
    rect_.y = - rand() % 50 ;
    rect_.x = rand()% SCREEN_WIDTH;
    rect_.w = THREAT_OBJECT_WIDTH;
    rect_.h = THREAT_OBJECT_HEIGHT;

    rectTexture[0].x=0;
    rectTexture[0].y=0;
    rectTexture[0].w=114;
    rectTexture[0].h=82;

    rectTexture[1].x=144;
    rectTexture[1].y=0;
    rectTexture[1].w=114;
    rectTexture[1].h=82;

    rectTexture[2].x=288;
    rectTexture[2].y=0;
    rectTexture[2].w=114;
    rectTexture[2].h=82;

    rectTexture[3].x=432;
    rectTexture[3].y=0;
    rectTexture[3].w=114;
    rectTexture[3].h=82;

}
ThreatObject::~ThreatObject(){
}

void ThreatObject::GenerateBullet(SDL_Renderer* ren)
{
    EnemyBullet* enemy_bullet = new EnemyBullet();
    enemy_bullet->LoadImg("gameShooting/enemybullet.png",ren);
    enemy_bullet->SetRect( rect_.x + 52, rect_.y + THREAT_OBJECT_HEIGHT );
    enemy_bullet->SetBulletType( rand()%3 );
    p_bullet_list.push_back(enemy_bullet);
}

void ThreatObject::ControlBulletAndKillMainObject(int x, int y, SDL_Renderer* ren,
                                                  MainObject &main_object,Mix_Chunk* g_main_injured , GameText &Score)
{
    for (int i=0;i <p_bullet_list.size();i++ ) {
        if (p_bullet_list[i]->GetIsMove())
        {
            if (SDL_General::Do_two_objects_overlap( p_bullet_list[i]->GetRect(), main_object.GetRect() ) )
            {
                // update score
                Score.IncreaseValue(GET_INJURED_SCORE) ;
                // Play main_injured music.
                Mix_PlayChannel(-1,g_main_injured,0);

                main_object.SetIsShownInjured(true) ;
                main_object.ShowInjured(ren);
                main_object.DecreaseLives();

                delete p_bullet_list[i];
                p_bullet_list.erase( p_bullet_list.begin()+i );
            }
            else
            {
                p_bullet_list[i]->Show(ren);
                p_bullet_list[i]->HandleMove(x,y );
            }

        }
        else {
            delete p_bullet_list[i];
            p_bullet_list.erase( p_bullet_list.begin()+i );
            cout << p_bullet_list.size()<< endl ;
        }
    }

}

void ThreatObject::HandleMove(const int x_border, const int y_border) {
    if ( rect_.y > y_border ) {
        is_move = false;
        return ;
    }
    rect_.y+= THREAT_OBJECT_HEIGHT/15;
    int num = rand() % 5 ;
    switch(num)
    {
        case 0 :
             rect_.y+= THREAT_OBJECT_HEIGHT/15;
        break;

        case 1 :
            rect_.y+= THREAT_OBJECT_HEIGHT/7;
            rect_.x+= THREAT_OBJECT_WIDTH/4;
        break;

        case 2:
            rect_.y+= THREAT_OBJECT_HEIGHT/7;
            rect_.x-= THREAT_OBJECT_WIDTH/4;
        break;

        case 3:
            rect_.x-= THREAT_OBJECT_WIDTH/4;
        break;

        case 4:
            rect_.x+= THREAT_OBJECT_WIDTH/4;
        break;

    }

}
void ThreatObject::ShowAnimation(SDL_Renderer* ren)
{
    SDL_RenderCopy(ren, full_object_, &rectTexture[frame], &rect_);
    SDL_RenderPresent(ren);
    frame = (frame+1)%4;
}




