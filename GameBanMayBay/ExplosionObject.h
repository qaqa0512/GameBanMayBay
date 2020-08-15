#pragma once

// Xu ly vu no
#ifndef EXPLOSION_OBJECT_H_
#define EXPLOSION_OBJECT_H_

#include "BasicObject.h"
#include "Com_Func.h"

const int EXP_WIDTH = 165; // khai bao kich thuoc chieu rong cho explo
const int EXP_HEIGHT = 165; // khai bao kich thuoc chieu cao cho explo

class ExplosionObject : public BaseObject
{
public:
	ExplosionObject();
	~ExplosionObject();
	void set_clip(); // ham tao clip 
	void set_frame(const int& fr) { frame_ = fr; }// ham thiet lap frame
	void ShowExp(SDL_Surface* des); // ham show
private:
	int frame_;
	SDL_Rect clip_[4];
};



#endif // !EXPLOSION_OBJECT_H_
