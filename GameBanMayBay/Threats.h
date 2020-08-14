#pragma once

// Khoi tao cac doi tuong tro ngai

//Header Guard
#ifndef THREATS_OBJECT_H_
#define THREATS_OBJECT_H_
#include "Com_Func.h"
#include "BasicObject.h"
#include "AmoObject.h"
#include <vector>

//dinh nghia do rong
#define WIDTH_THREAT 80
#define HEIGHT_THREAT 33
const int UNDER_LIMIT_THREAT = 200;

class ThreatObject : public BaseObject 
{
public:
	ThreatObject();
	~ThreatObject();

	// Ham xu ly Move
	void HandleMove(const int& x_border, const int& y_border);
	void HandleInputAction(SDL_Event events);

	//Ham vi tri 
	void set_x_val(const int& val) { x_val_ = val; }
	void set_y_val(const int& val) { y_val_ = val; }
	int get_x_val() { return x_val_; }
	int get_y_val() { return y_val_; }

	void SetAmoList(std::vector<AmoObject*> amo_list_) { p_amo_list_ = amo_list_; }
	std::vector<AmoObject*>GetAmoList() const { return p_amo_list_; }

	void InitAmo(AmoObject* p_amo);
	void MakeAmo(SDL_Surface* des, const int& x_limit, const int& y_limit); //Ham ban dan duoc ban ra
																			// Gioi han cho phep dan duoc ban ra
private:
	int x_val_ ;
	int y_val_;

	std::vector<AmoObject*> p_amo_list_;

};








#endif // !THREATS_OBJECT_H_
