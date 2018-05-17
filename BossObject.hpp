#ifndef BOSSOBJECT_H_
#define BOSSOBJECT_H_

#include "BaseObject.hpp"
#include "General_Function.hpp"
#include"BossBullet.hpp"
#include"MainObject.hpp"
#include"GameText.hpp"
const int BOSS_OBJECT_WIDTH = 296*2/3;
const int BOSS_OBJECT_HEIGHT = 394*2/3;
const int BOSS_MAX_LIVES = 20 ;
class BossObject : public BaseObject
{
public:
    BossObject(SDL_Renderer *ren);
    //~BossObject();
    void HandleMove(const int x_border, const int y_border);

    void GenerateBullet(SDL_Renderer* ren );
    void ControlBulletAndKillMainObject(int x, int y,SDL_Renderer* ren, MainObject &main_object,
                                        Mix_Chunk* g_main_injured, GameText &Score );
    bool GetIsMove() {return is_move ;};
    void SetIsMove(bool x) { is_move = x ; } ;

    std::vector <BossBullet*> GetBulletList() { return p_bullet_list; };
    void SetBulletList( std::vector <BossBullet*> bullet ){ p_bullet_list = bullet;  };
    void ShowAnimation(SDL_Renderer* ren);
    void DecreaseLives() { lives--; } ;
    int GetLives() {return lives ;};
    void Fresh();
private:
    bool is_move = 0;
    int lives = BOSS_MAX_LIVES ;
    vector <BossBullet*> p_bullet_list;
    SDL_Rect rectTexture[6];
    int frame = 0;
};

#endif // BOSSOBJECT_H_

