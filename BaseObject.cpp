#include "BaseObject.hpp"

BaseObject::BaseObject()
{
	rect_.x = 0;
	rect_.y = 0;
	p_object_ = NULL;
	full_object_= NULL;

}

BaseObject::~BaseObject()
{
}

bool BaseObject::LoadImg(string path, SDL_Renderer *ren) {

	p_object_= SDL_General::LoadImage(path.c_str(), ren)  ;
	if (p_object_ == NULL)
			return false;

    full_object_ = SDL_General::LoadImage(path.c_str(),ren);
    if (full_object_ == NULL)
    {
        return false;
    }
	return true;
}

void BaseObject::Show(SDL_Renderer *ren) {
	SDL_General::ApplySurface(ren, p_object_, rect_.x, rect_.y, rect_.w, rect_.h);
}
