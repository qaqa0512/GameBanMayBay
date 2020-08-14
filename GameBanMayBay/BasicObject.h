//Lop co so
#pragma once

//Heeader Guard
#ifndef BASE_OBJECT_H_
#define BASE_OBJECT_H_
#include "Com_Func.h"
//dinh nghia
class BaseObject
{
	public:
		BaseObject();// Ham constructor mac dinh
		~BaseObject();// Ham huy mac dinh
		void Show(SDL_Surface* des);// truyen doi tuong vao des
		bool LoadImg(const char* file_name);// duong dan de load anh

		void SetRect(const int& x, const int& y) { rect_.x = x, rect_.y = y; }
		SDL_Rect GetRect() const { return rect_; }// tranh hien tuong bi thay doi
		SDL_Surface* GetObject() { return p_object_; }; // tra lai doi tuong khi can
	protected://dat bien thanh vien
		SDL_Rect rect_;// phan biet su khac nhau giua local va global
		SDL_Surface* p_object_;
};



#endif // !BASE_OBJECT_H_
