#pragma once

// Hien thi ky tu len man hinh
#ifndef FONT_TEXT_H_
#define FONT_TEXT_H_

#include "BasicObject.h"
#include <string>
#include <SDL_ttf.h>

class Font_Text : public BaseObject
{
public:
	// tao 1 so mau mac dinh
	enum TextColor
	{
		RED_TEXT = 0,
		WHITE_TEXT = 1,
		ORANGE_TEXT = 2
	};

	Font_Text();
	~Font_Text();

	void SetText(const std::string& text) { str_val_ = text;} // noi dung text
	void SetColor(const int& type); // set mau cho chu
	void CreateGameText(TTF_Font* font, SDL_Surface* des); // ham text khi choi 
private:
	std::string str_val_; // noi dung text
	SDL_Color text_color_; // mau sac cua chu

};

#endif // !FONT_TEXT_H_
