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
#include <SDL_ttf.h>



#undef main
//Khai bao cac thong so cua screan
const int WIDTH_BG = 4800;
const int HEIGHT_BG = 600;
const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 600;
const int SCREEN_BPP = 32;


//Khai bao cac thong so cua main
const int POS_X_START_MAIN_OBJ = 100; // vi tri ban dau
const int POS_Y_START_MAIN_OBJ = 100; // vi tri ban dau

//Khai bao cac thong so cua threats
const int NUM_THREAT = 3; // khoi tao so luong cua doi tuong can tro




// Khai bao cac bien global quan ly man hinh
static SDL_Surface* g_screen = NULL;
static SDL_Surface* g_bkground = NULL;
static SDL_Surface* g_img_menu = NULL;
static SDL_Event g_even; //quản lý việc bấm sự kiện

namespace SDLCommonFunc // dat ten de tranh bi trung ten voi thu vien
{
	SDL_Surface* LoadImage(std::string file_path);
	SDL_Rect ApplySurface(SDL_Surface* src, SDL_Surface* des, int x, int y);// co chuc nang load 1 surface nguon va dich
	void ApplySurfaceClip(SDL_Surface* src, SDL_Surface* des, SDL_Rect* clip, int x, int y); 
	void CleanUp();
	bool CheckCollision(const SDL_Rect& object_1,const SDL_Rect& object_2); //khai bao ham Xu Ly Va Cham
	int ShowMenu(SDL_Surface* des, TTF_Font* font); // Khoi tao cho menu
	bool CheckFocusRect(const int& x, const int& y, const SDL_Rect& rect);// ktra toa do cua mot diem voi rect da cho truoc
}

#endif // !COM_FUNCTION_H_

