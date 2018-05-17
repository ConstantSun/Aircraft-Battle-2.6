#include"BossObject.hpp"

BossObject::BossObject(SDL_Renderer *ren)
{
    rect_.y = - rand() % 50 - BOSS_OBJECT_HEIGHT ;
    rect_.x = rand()% SCREEN_WIDTH;
    rect_.w = BOSS_OBJECT_WIDTH;
    rect_.h = BOSS_OBJECT_HEIGHT;

    rectTexture[0].x=0;
    rectTexture[0].y=0;
    rectTexture[0].w=296;
    rectTexture[0].h=394;

    rectTexture[1].x=325;
    rectTexture[1].y=0;
    rectTexture[1].w=296;
    rectTexture[1].h=394;

    rectTexture[2].x=325*2;
    rectTexture[2].y=0;
    rectTexture[2].w=296;
    rectTexture[2].h=394;

    rectTexture[3].x=325*3;
    rectTexture[3].y=0;
    rectTexture[3].w=296;
    rectTexture[3].h=394;

    rectTexture[4].x=325*4;
    rectTexture[4].y=0;
    rectTexture[4].w=296;
    rectTexture[4].h=394;

    rectTexture[5].x=325*5;
    rectTexture[5].y=0;
    rectTexture[5].w=296;
    rectTexture[5].h=394;

    for (int i=0;i<10;i++)
    {
         p_bullet_list.push_back(new BossBullet);
         p_bullet_list[p_bullet_list.size()-1]->LoadImg("gameShooting/bossbullet.png",ren);
    }

}
void BossObject::Fresh()
{
    SetRect( rand()%SCREEN_WIDTH, -rand()%50- BOSS_OBJECT_HEIGHT );
    is_move = true;
    lives = BOSS_MAX_LIVES ;
    for (int i=0;i<10;i++)
    {
         p_bullet_list[i]->SetIsMove(false);
    }
//    p_bullet_list.clear();
//    p_bullet_list.shrink_to_fit();
}

void BossObject::GenerateBullet(SDL_Renderer* ren)
{
    for(int i=0;i<p_bullet_list.size();i++)
    {
        if (!p_bullet_list[i]->GetIsMove())
        {
            p_bullet_list[i]->SetIsMove(true);
            p_bullet_list[i]->SetRect( rect_.x + BOSS_OBJECT_WIDTH/2-BOSS_BULLET_WIDTH/2,
                                       rect_.y + int(BOSS_OBJECT_HEIGHT*4/5) );
            p_bullet_list[i]->ShowAnimation(ren);
            break;
        }
    }
}

void BossObject::ControlBulletAndKillMainObject(int x, int y, SDL_Renderer* ren,
                                                  MainObject &main_object,Mix_Chunk* g_main_injured , GameText &Score) {

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

                p_bullet_list[i]->SetIsMove(false);
            }
            else
            {
                p_bullet_list[i]->ShowAnimation(ren);
                p_bullet_list[i]->HandleMove(x,y );
            }
        }
    }
}

void BossObject::HandleMove(const int x_border, const int y_border) {
    if ( rect_.y > y_border ) {
        is_move = false;
//        p_bullet_list.clear();
//        p_bullet_list.shrink_to_fit();
        return ;
    }
    rect_.y+= BOSS_OBJECT_HEIGHT/15; // boss only moves straight forward !!!

}
void BossObject::ShowAnimation(SDL_Renderer* ren)
{
    SDL_RenderCopy(ren, full_object_, &rectTexture[frame], &rect_);
    SDL_RenderPresent(ren);
    frame = (frame+1)%6;
}




