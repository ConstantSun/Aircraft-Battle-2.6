#ifndef BASEOBJECT_H_
#define BASEOBJECT_H_
#include "General_Function.hpp"

class BaseObject
{
public:
	BaseObject();
	~BaseObject();

	bool LoadImg(string path, SDL_Renderer *ren);
	void SetRect(const int &x, const int &y) {  rect_.x = x; rect_.y = y; }
	void Show(SDL_Renderer* ren);
	SDL_Rect GetRect() { return rect_;	}
	SDL_Texture * GetObject() {  return p_object_; }
protected:
	SDL_Rect rect_;
	SDL_Texture* p_object_;
	SDL_Texture* full_object_;

};

#endif
