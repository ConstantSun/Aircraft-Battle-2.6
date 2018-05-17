#include "EnemyBullet.hpp"

EnemyBullet::EnemyBullet() {
    rect_.w = ENEMY_BULLET_WIDTH;
    rect_.h = ENEMY_BULLET_HEIGHT;
}
EnemyBullet::~EnemyBullet(){}


void EnemyBullet::HandleMove( int x_border, int y_border ) {
    switch(bullet_type_){
    case 0:  // this case bullet is straight forward
    {
        rect_.y+=20;
        if (rect_.y > y_border ) {
            is_move_ = false;
        }
    }
        break;

    case 2: // this case bullet is diagonal left
    {
        rect_.y+=20;
        rect_.x-=20;
        if (rect_.y > y_border ) {
            is_move_ = false;
        }
    }
        break;


    case 1: // this case bullet is diagonal right
    {
         rect_.y+=20;
        rect_.x+=20;
        if (rect_.y > y_border ) {
            is_move_ = false;
        }
    }
        break;

    default:
        break;

    }

}
