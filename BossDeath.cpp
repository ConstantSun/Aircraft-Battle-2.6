
#include"BossDeath.hpp"
#include"BossObject.hpp"
BossDeath::BossDeath(){
    rect_.w = BOSS_OBJECT_WIDTH;
    rect_.h = BOSS_OBJECT_HEIGHT;

    rectTexture[0].x = 0;
    rectTexture[0].y = 0;
    rectTexture[0].w = 195;
    rectTexture[0].h = 324;

    rectTexture[1].x = 213;
    rectTexture[1].y = 0;
    rectTexture[1].w = 195;
    rectTexture[1].h = 324;

    rectTexture[2].x = 427 ;
    rectTexture[2].y = 0;
    rectTexture[2].w = 195;
    rectTexture[2].h = 324;

    rectTexture[3].x = 640;
    rectTexture[3].y = 0;
    rectTexture[3].w = 961-640;
    rectTexture[3].h = 324;

    rectTexture[4].x = 961 ;
    rectTexture[4].y = 0;
    rectTexture[4].w = 1290-961;
    rectTexture[4].h = 324;

    rectTexture[5].x = 1290 ;
    rectTexture[5].y = 0;
    rectTexture[5].w = 1630-1290;
    rectTexture[5].h = 324;

    rectTexture[6].x = 1630 ;
    rectTexture[6].y = 0;
    rectTexture[6].w = 1920-1630;
    rectTexture[6].h = 324;
}
void BossDeath::ShowAnimation(SDL_Renderer* ren){
    SDL_RenderCopy(ren, full_object_, &rectTexture[frame_count_], &rect_);
    SDL_RenderPresent(ren);
};
bool BossDeath::ShowEnough() {
    return (frame_count_ >= 5) ;
}
void BossDeath::HandleAnimation()
{
     frame_count_++;
     if ( frame_count_== 6 ){
        is_shown_ = 0 ;
        frame_count_ = 0;
     }
};
