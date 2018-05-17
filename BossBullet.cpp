#include "BossBullet.hpp"

BossBullet::BossBullet()
{
    rect_.w = BOSS_BULLET_WIDTH;
    rect_.h = BOSS_BULLET_HEIGHT;
    rect_.x = rect_.y = 0;
    rectTexture[0].x=0;
    rectTexture[0].y=0;
    rectTexture[0].w=28;
    rectTexture[0].h=110;

    rectTexture[1].x=56;
    rectTexture[1].y=0;
    rectTexture[1].w=84-56;
    rectTexture[1].h=110;

    rectTexture[2].x=114;
    rectTexture[2].y=0;
    rectTexture[2].w=150-114;
    rectTexture[2].h=110;

    rectTexture[3].x=180;
    rectTexture[3].y=0;
    rectTexture[3].w=208-180;
    rectTexture[3].h=110;

}
BossBullet::~BossBullet(){}


void BossBullet::HandleMove( int x_border, int y_border )
{
    rect_.y+=BOSS_BULLET_HEIGHT/3; // Bullet only moves forward.
    if (rect_.y> SCREEN_HEIGHT)
        is_move_ = false;
}

void BossBullet::ShowAnimation(SDL_Renderer* ren)
{
    SDL_RenderCopy(ren, full_object_, &rectTexture[frame], &rect_);
    SDL_RenderPresent(ren);
    frame = (frame+1)%4;
}
