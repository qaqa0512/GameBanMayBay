// Tất cả các hàm xử lý chung
#pragma once

//Header Guard
#ifndef COM_FUNCTION_H_ // dinh nghia ham chung
#define COM_FUNCTION_H_

// Cac ham xu ly chung
#include <Windows.h>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#undef main
//Khai bao cac thong so co dinh
const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 600;
const int SCREEN_BPP = 32;
const int NUM_THREAT = 3; // khoi tao so luong cua doi tuong can tro


// Khai bao cac bien global quan ly man hinh
static SDL_Surface* g_screen = NULL;
static SDL_Surface* g_bkground = NULL;
static SDL_Event g_even; //quản lý việc bấm sự kiện

namespace SDLCommonFunc // dat ten de tranh bi trung ten voi thu vien
{
	SDL_Surface* LoadImage(std::string file_path);
	void ApplySurface(SDL_Surface* src, SDL_Surface* des, int x, int y);// co chuc nang load 1 surface nguon va dich
	void CleanUp();
}







#endif // !COM_FUNCTION_H_

