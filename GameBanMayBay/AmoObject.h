#pragma once
// co che xu ly dan ban
// header guard
#ifndef AMO_OBJECT_H_
#define AMO_OBJECT_H_
#include "BasicObject.h"

#define WIDTH_LASER 35
#define HEIGHT_LASER 5

#define WIDTH_SAPHERE 10
#define HEIGHT_SAPHERE 10
class AmoObject : public BaseObject
{
	//phuong thuc
public:
	// thiet lap chieu rong va chieu cao cho doi tuong
	enum AmoType
	{
		NONE = 0,
		LASER = 1,
		SAPHERE =2
	};
	AmoObject();
	~AmoObject();
	void HandInputAction(SDL_Event events);
	void HandleMove(const int& x_border, const int& y_border);
	void HandleMoveRight();

	int get_type() const { return amo_type_; }
	void set_type(const int &type) { amo_type_ = type; }

	bool get_is_move() const { return is_move_;}
	void set_is_move(bool is_move) { is_move_ = is_move; }
	void SetWidthHeight(const int& width, const int& height) { rect_.w = width, rect_.h = height; };
	// tao ra bien thanh vien
private:
	int x_val_;
	int y_val_;
	bool is_move_;
	int amo_type_;
};

#endif // !AMO_OBJECT_H_