#include "FontText.h"

Font_Text::Font_Text() 
{
	rect_.x = 500;
	rect_.y = 10;
	text_color_.r = 255; 
	text_color_.g = 255;
	text_color_.b = 255;
}
Font_Text::~Font_Text()
{

}
void Font_Text::SetColor(const int& type) 
{
	if(type == RED_TEXT) // dinh mau san cho font chu
	{
		SDL_Color color = { 255,0,0 }; // mau do
		text_color_ = color;
	}
	else if (type == WHITE_TEXT)
	{
		SDL_Color color = { 255,255,255 }; // mau trang
		text_color_ = color;
	}
	else if (type == REDPINK_TEXT)
	{
		SDL_Color color = { 255,0,121 }; // mau trang
		text_color_ = color;
	}
	else
	{
		SDL_Color color = { 255,128,0 }; // mau cam
		text_color_ = color;
	}
}

void Font_Text::CreateGameText(TTF_Font* font, SDL_Surface* des)
{
	// Nhiem vu cua TTF_Render_Solid la tao ra 1 doi tuong surface tu ky tu cho vao, mau sac cho phep, font 
	p_object_ = TTF_RenderText_Solid(font, str_val_.c_str(), text_color_);
	Show(des);
}