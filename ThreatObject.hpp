#ifndef THREATOBJECT_H_
#define THREATOBJECT_H_

#include"BaseObject.hpp"
#include"MainObject.hpp"
#include"EnemyBullet.hpp"
#include"GameText.hpp"
const int THREAT_OBJECT_WIDTH = 114;
const int THREAT_OBJECT_HEIGHT = 82;

class ThreatObject: public BaseObject
{
public:
    ThreatObject();
    ~ThreatObject();
    void HandleMove(const int x_border, const int y_border);

    void GenerateBullet(SDL_Renderer* ren );
    void ControlBulletAndKillMainObject(int x, int y,SDL_Renderer* ren, MainObject &main_object,Mix_Chunk* g_main_injured, GameText &Score );

    bool GetIsMove() {return is_move ;};
    std::vector <EnemyBullet*> GetBulletList() { return p_bullet_list; };
    void SetBulletList( std::vector <EnemyBullet*> bullet ){ p_bullet_list = bullet;  };
    void ShowAnimation(SDL_Renderer* ren);
private:
    bool is_move = 1;
    vector <EnemyBullet*> p_bullet_list;
    SDL_Rect rectTexture[4];
    int frame = 0;
};
#endif // THREATOBJECT_H_
