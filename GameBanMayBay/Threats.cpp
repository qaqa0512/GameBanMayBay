#include "Threats.h"

ThreatObject::ThreatObject() 
{
	// vi tri ban dau doi tuong tro ngai xuat hien
	rect_.x = SCREEN_WIDTH;
	rect_.y = SCREEN_HEIGHT*0.5;
	rect_.w = WIDTH_THREAT;
	rect_.h = HEIGHT_THREAT;

	x_val_ = 0;
	y_val_ = 0;
}

ThreatObject::~ThreatObject() 
{
	// giai phong cac vung nho
	if(p_amo_list_.size() > 0)
	{
		for (int i = 0; i < p_amo_list_.size(); i++) 
		{
			AmoObject* p_amo = p_amo_list_.at(i);
			if (p_amo != NULL) 
			{
				delete p_amo;
				p_amo = NULL;
			}
		}
		p_amo_list_.clear();
	}
}

//Khoi tao cac doi tuong amo cho threat
void ThreatObject::InitAmo(AmoObject* p_amo) 
{
	if (p_amo != NULL) // p_amo khac Null thi se dc phep load anh len
	{
		bool ret = p_amo->LoadImg("sphere.png");
		//ktra neu truong hop thanh cong thi
		if(ret)
		{ 
			p_amo->set_is_move(true); // cho phep vien dan di chuyen
			p_amo->SetWidthHeight(WIDTH_LASER,HEIGHT_LASER);// kich thuoc cua vien dan
			p_amo->set_type(AmoObject::LASER);// thiet lap loai dan ban
			p_amo->SetRect(rect_.x, rect_.y + rect_.h*0.5); // vi tri cua vien dan
			p_amo->set_x_val(8);
			p_amo_list_.push_back(p_amo); // hang loat doi tuong xuat hien 
		}
	}
}
// Ham xu ly dan ban ra
void ThreatObject::MakeAmo(SDL_Surface* des, const int& x_limit, const int& y_limit)
{
	for(int i=0;i<p_amo_list_.size();i++) // dan duoc ban lien tuc
	{
		AmoObject* p_amo = p_amo_list_.at(i);
		if (p_amo)
		{
			if(p_amo->get_is_move()) //ktr neu doi tuong dc cho phep move
			{
				p_amo->Show(des); 
				p_amo->HandleMoveRight();
			}
			else
			{
				p_amo->set_is_move(true); // vien dan dc ban lai
				p_amo->SetRect(rect_.x, rect_.y + rect_.h*0.5); //set lai vi tri ban dau cua dan
			}
		}
	}
}
void ThreatObject::HandleMove(const int& x_border, const int& y_border)
{
	rect_.x -= x_val_;
	// neu bi vuot qua gioi han
	if (rect_.x < 0) 
	{
		rect_.x = SCREEN_WIDTH;
		//set doi tuong xuat hien ngau nhien
		int rand_y = rand() % 400;
		if (rand_y > SCREEN_HEIGHT - UNDER_LIMIT_THREAT)
		{
			rand_y = SCREEN_HEIGHT*0.3;
		}
		rect_.y = rand_y;
	}
}
void ThreatObject::HandleInputAction(SDL_Event events)
{

}

// Ham reset doi tuong can tro
void ThreatObject::Reset(const int& xborder)
{
	rect_.x = xborder; // vi tri xuat hien ban dau nam ngay mep bia cua man hinhs
	//set doi tuong xuat hien ngau nhien
	int rand_y = rand() % 400;
	if (rand_y > SCREEN_HEIGHT - UNDER_LIMIT_THREAT)
	{
		rand_y = SCREEN_HEIGHT*0.3;
	}
	rect_.y = rand_y;

	// reset lai vi tri cua vien dan
	for (int i = 0; i < p_amo_list_.size(); i++) 
	{
		AmoObject* p_amo = p_amo_list_.at(i);
		if (p_amo != NULL)  // ktra con tro
		{
			ResetAmo(p_amo);
		}
	}
}
void ThreatObject::ResetAmo(AmoObject* p_amo)
{
	p_amo->SetRect(rect_.x, rect_.y + rect_.h*0.5); // vi tri cua vien dan
}