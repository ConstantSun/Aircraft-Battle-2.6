#include"EnemyDeath.hpp"

EnemyDeath::EnemyDeath(){
    rect_.w = 114;
    rect_.h = 128;

    rectTexture[0].x = 0;
    rectTexture[0].y = 0;
    rectTexture[0].w = 114;
    rectTexture[0].h = 128;

    rectTexture[1].x = 144;
    rectTexture[1].y = 0;
    rectTexture[1].w = 114;
    rectTexture[1].h = 128;

    rectTexture[2].x = 288 ;
    rectTexture[2].y = 0;
    rectTexture[2].w = 114;
    rectTexture[2].h = 128;

    rectTexture[3].x = 432;
    rectTexture[3].y = 0;
    rectTexture[3].w = 114;
    rectTexture[3].h = 128;

    rectTexture[4].x = 576 ;
    rectTexture[4].y = 0;
    rectTexture[4].w = 114;
    rectTexture[4].h = 128;

    rectTexture[5].x = 720 ;
    rectTexture[5].y = 0;
    rectTexture[5].w = 114;
    rectTexture[5].h = 128;

    rectTexture[6].x = 864;
    rectTexture[6].y = 0;
    rectTexture[6].w = 114;
    rectTexture[6].h = 128;

    rectTexture[7].x = 1008;
    rectTexture[7].y = 0;
    rectTexture[7].w = 114;
    rectTexture[7].h = 128;
}
void EnemyDeath::ShowAnimation(SDL_Renderer* ren){
    SDL_RenderCopy(ren, full_object_, &rectTexture[frame_count_], &rect_);
    SDL_RenderPresent(ren);
};
void EnemyDeath::HandleAnimation()
{
     frame_count_++;
     //cout << " frame = " << frame_count_ <<endl;
     if ( frame_count_==8 ){
        is_shown_ = 0;
     }
};
