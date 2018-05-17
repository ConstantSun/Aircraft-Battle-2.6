#ifndef BOSSBULLET_H_
#define BOSSBULLET_H_
#include"BaseObject.hpp"
#include"General_Function.hpp"

const int BOSS_BULLET_WIDTH = 14 ;
const int BOSS_BULLET_HEIGHT = 55 ;

class BossBullet : public BaseObject
{
public:
	BossBullet();
	~BossBullet();
	void HandleMove( const int x_border, const int y_border );
	bool GetIsMove() { return is_move_; };
	void SetIsMove(bool x) { is_move_ = x; };
	void ShowAnimation(SDL_Renderer* ren);
private:
	bool is_move_=0 ;
    SDL_Rect rectTexture[4];
    int frame = 0;
};
#endif // BOSSBULLET_H_
