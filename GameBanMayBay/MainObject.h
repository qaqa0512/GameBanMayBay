#pragma once

//Header Guard
#ifndef MAIN_OBJECT_H_
#define MAIN_OBJECT_H_

#include "AmoObject.h"
#include "Com_Func.h"
#include "BasicObject.h"
// su dung vector
#include <vector>
// kich thuoc cua doi tuong
#define WIDTH_MAIN_OBJECT 80
#define HEIGHT_MAIN_OBJECT 46

// lop ke thua
class MainObject :public BaseObject
{
public:
	//Ham constructor
	MainObject();
	~MainObject();

	void HandleInputAction(SDL_Event events);// ham quan ly cac hanh dong
	void HandleMove();
	void SetAmoList(std::vector<AmoObject*> amo_list_) { p_amo_list_ = amo_list_; }
	std::vector<AmoObject*>GetAmoList() const { return p_amo_list_; }
	void MainObject::MakeAmo(SDL_Surface* des);
	// dinh nghia cac truong
private:
	int x_val_;
	int y_val_;

	std::vector<AmoObject*> p_amo_list_;

};
#endif // !MAIN_OBJECT_H_
