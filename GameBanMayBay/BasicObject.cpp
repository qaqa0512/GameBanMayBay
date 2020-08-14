// su dung cac lop chung
#include "BasicObject.h" 

// Goi ham constructor
BaseObject::BaseObject()
{
	rect_.x = 0;
	rect_.y = 0;
	p_object_ = NULL;
}
BaseObject::~BaseObject() // Ham nay co the delete con tro 
{
	if (p_object_ != NULL) {
		SDL_FreeSurface(p_object_);// giai phong doi tuong
	}
}

bool BaseObject::LoadImg(const char* file_name) {
	p_object_ = SDLCommonFunc::LoadImage(file_name);
	if (p_object_ == NULL)
		return false;
	return true;
}
void BaseObject::Show(SDL_Surface* des) { //Hien thi cac thanh phan can thiet
	if (p_object_ != NULL) {
		SDLCommonFunc::ApplySurface(p_object_, des, rect_.x, rect_.y);
	}
}