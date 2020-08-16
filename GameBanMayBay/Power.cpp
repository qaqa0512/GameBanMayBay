#include "Power.h"

PlayerPower::PlayerPower()
{

}
PlayerPower::~PlayerPower()
{

}
void PlayerPower::AddPos(const int& xpos)
{
	pos_list_.push_back(xpos); // moi khi goi ham deu phai luu vao list pos 
}

// ham show
void PlayerPower::Render(SDL_Surface* des)
{
	if (number_ == pos_list_.size()) // dam bao rang 3 mang se = dung 3 vi tri 
	{
		for (int i = 0; i < pos_list_.size(); i++) 
		{
			rect_.x = pos_list_.at(i);
			Show(des); // ham show nay duoc ke thua tu lop base
		}
	}
}

// Khoi tao
void PlayerPower::Init()
{
	LoadImg("change.png"); // khi load anh len thi lap tuc se dc ton tai trong baseobject
	number_ = 3; // o day se gan co dinh 3 mang
	if (pos_list_.size() > 0) // phai dam bao pos_list nay luc nao cung phai = 0
	{
		pos_list_.clear(); // xoa di nhung pos_list con ton tai truoc do
	}

	AddPos(20);
	AddPos(60);
	AddPos(100);
}

// Ham giam mang
void PlayerPower::Decrease()
{ 
	number_--;
	pos_list_.pop_back();
}