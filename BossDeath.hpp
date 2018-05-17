#ifndef BOSSDEATH_H_
#define BOSSDEATH_H_
#include"BaseObject.hpp"

class BossDeath: public BaseObject
{
public:
    BossDeath();

    bool GetIsShown(){return is_shown_;};
    void SetIsShown(bool x) { is_shown_ = x ; } ;

    void ShowAnimation (SDL_Renderer* ren);
    void HandleAnimation() ;
    bool ShowEnough();
private:
    bool is_shown_ = 0;
    SDL_Rect rectTexture[7];
    int frame_count_ = 0;
};

#endif // BOSSDEATH_H_
