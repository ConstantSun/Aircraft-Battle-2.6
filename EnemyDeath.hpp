#ifndef ENEMY_DEATH_H_
#define ENEMY_DEATH_H_
#include "BaseObject.hpp"

class EnemyDeath : public BaseObject
{
public:
    EnemyDeath();
    //~EnemyDeath();
    bool GetIsShown(){return is_shown_;};
    void SetIsShown(bool x) { is_shown_ = x ; } ;

    void ShowAnimation (SDL_Renderer* ren);
    void HandleAnimation() ;
private:
    bool is_shown_ = 1;
    SDL_Rect rectTexture[8];
    int frame_count_ = 0;
};

#endif // ENEMY_DEATH_H_
