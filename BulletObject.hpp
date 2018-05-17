#ifndef BULLET_OBJECT_H_
#define BULLET_OBJECT_H_
#include "BaseObject.hpp"

const int PINK_BULLET_WIDTH = 18;
const int PINK_BULLET_HEIGHT= 18;

const int BLUE_BULLET_HEIGHT =28;
const int BLUE_BULLET_WIDTH =18;

class BulletObject : public BaseObject {
public:
	BulletObject();
	~BulletObject();
	void HandleInputAction(SDL_Event events, SDL_Renderer *ren);
	void HandleMove( const int x_border, const int y_border );

	void SetIsMove(bool is_move) { is_move_ = is_move; };
	bool GetIsMove() { return is_move_; };

private:
	int x_val_;
	int y_val_;
	bool is_move_;
};

#endif // BULLET_OBJECT_H_

