#include "AmoObject.h"

AmoObject::AmoObject()
{
	rect_.x = 0;
	rect_.y = 0;
	x_val_ = 0;
	y_val_ = 0;
	is_move_ = false;
	amo_type_ = NONE;// dinh cho dan kh co gi o thoi diem ban dau
}
AmoObject::~AmoObject()
{

}
// Ham xu ly dan ban cua nhan vat chinh
void AmoObject::HandleMove(const int& x_border, const int& y_border)
{
	rect_.x += 20;// toc do dan ban tu phia ben tri
	if (rect_.x > x_border) {
		is_move_ = false;// khong cho xuat hien nua
	}
}
// Ham xu ly dan ban cua doi tuong can tro
void AmoObject::HandleMoveRight()
{
	rect_.x -= 8; // toc do dan ban tu phia ben phai
	if (rect_.x < 0)
	{
		is_move_ = false;
	}
}
void AmoObject::HandInputAction(SDL_Event events)
{

}
