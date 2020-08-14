#include "MainObject.h"

MainObject::MainObject() 
{
	rect_.x = 0;
	rect_.y = 0;
	rect_.w = WIDTH_MAIN_OBJECT;
	rect_.h = HEIGHT_MAIN_OBJECT;
	x_val_ = 0;
	y_val_ = 0;
}

MainObject::~MainObject() {
	;
}

void MainObject::HandleInputAction(SDL_Event events) {
	//Bat su kien ban phim
	if (events.type == SDL_KEYDOWN)// ktra nhung phim duoc an xuong
	{
		switch (events.key.keysym.sym)
		{
		case SDLK_UP:
			y_val_ -= HEIGHT_MAIN_OBJECT / 4; //di chuyen di xuong = chieu cao cua chinh doi tuong
			break;
		case SDLK_DOWN:
			y_val_ += HEIGHT_MAIN_OBJECT / 4;//di chuyen di len = chieu cao cua chinh doi tuong
			break;
		case SDLK_LEFT:
			x_val_ -= WIDTH_MAIN_OBJECT / 4;//di chuyen qua trai = chieu rong cua chinh doi tuong
			break;
		case SDLK_RIGHT:
			x_val_ += WIDTH_MAIN_OBJECT / 4;//di chuyen qua phai = chieu rong cua chinh doi tuong
			break;
		}
	}
	else if (events.type == SDL_KEYUP) // ktra nhung phim duoc tha ra
	{
		switch (events.key.keysym.sym)
		{
		case SDLK_UP:
			y_val_ += HEIGHT_MAIN_OBJECT / 4; //di chuyen di xuong = chieu cao cua chinh doi tuong
			break;
		case SDLK_DOWN:
			y_val_ -= HEIGHT_MAIN_OBJECT / 4;//di chuyen di len = chieu cao cua chinh doi tuong
			break;
		case SDLK_LEFT:
			x_val_ += WIDTH_MAIN_OBJECT / 4;//di chuyen qua trai = chieu rong cua chinh doi tuong
			break;
		case SDLK_RIGHT: 
			x_val_ -= WIDTH_MAIN_OBJECT / 4;//di chuyen qua phai = chieu rong cua chinh doi tuong
			break;
		}
	}
	else if (events.type == SDL_MOUSEBUTTONDOWN) // ktra khi chuot click vao
	{
		AmoObject* p_amo = new AmoObject();
		if (events.button.button == SDL_BUTTON_LEFT)
		{
			p_amo->SetWidthHeight(WIDTH_LASER,HEIGHT_LASER);// thiet lap chieu rong, cao
			p_amo->LoadImg("laser.png");// load anh vao
			p_amo->set_type(AmoObject::LASER);//Chon the loai
		}
		else if(events.button.button  == SDL_BUTTON_RIGHT) {
			p_amo->SetWidthHeight(WIDTH_SAPHERE, HEIGHT_SAPHERE);
			p_amo->LoadImg("sphere.png");
			p_amo->set_type(AmoObject::SAPHERE);
		}
		// cap nhat vi tri cho doi tuong
		p_amo->SetRect(this->rect_.x + this->rect_.w - 10, this->rect_.y + this->rect_.h*0.5);// thiet lap toa do cho dan
		p_amo->set_is_move(true);

		p_amo_list_.push_back(p_amo);
	}
	else if (events.type == SDL_MOUSEBUTTONUP) // ktra khi chuot tha ra
	{

	}
	else
	{
		rect_.x += x_val_;
		//Gioi han chieu rong
		if (rect_.x < 0 || rect_.x + WIDTH_MAIN_OBJECT > SCREEN_WIDTH)
		{
			rect_.x -= x_val_;
		}
		//Gioi han chieu cao
		rect_.y += y_val_;
		if (rect_.y < 0 || rect_.y + HEIGHT_MAIN_OBJECT > SCREEN_HEIGHT - 200) {
			rect_.y -= y_val_;
		}
	}

}
void MainObject::HandleMove() {
	//TODO
}