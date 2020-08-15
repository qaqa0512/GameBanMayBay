#include "Com_Func.h"

// Ham LoadImage thuc hinh load cac anh
SDL_Surface* SDLCommonFunc::LoadImage(std::string file_path) // them namespace trong com_func.h vao
{
	SDL_Surface * load_image = NULL;
	SDL_Surface* optimize_image = NULL;
	load_image = IMG_Load(file_path.c_str());// thuc hien doc file anh 
	if (load_image != NULL)
	{
		optimize_image = SDL_DisplayFormat(load_image);// toi uu hoa load_image sao cho phu hop
		SDL_FreeSurface(load_image);// giai phong doi tuong

									// xoa vien background nhan vat
		if (optimize_image != NULL)
		{
			UINT32 color_key = SDL_MapRGB(optimize_image->format, 0, 0xFF, 0xFF); // SDL_MapRGB: dinh dang lai surface va truyen vao cac mau sac cua background de transparent di 
			SDL_SetColorKey(optimize_image, SDL_SRCCOLORKEY, color_key);
		}
	}
	return optimize_image;
}

//Ham ApplySurFace thuc hien load cac anh vao man hinh
void SDLCommonFunc::ApplySurface(SDL_Surface* src, SDL_Surface* des, int x, int y)// co chuc nang load 1 surface nguon va dich
{
	SDL_Rect offset;
	offset.x = x;
	offset.y = y;
	SDL_BlitSurface(src, NULL, des, &offset); // match lai voi nhau
}
void SDLCommonFunc::ApplySurfaceClip(SDL_Surface* src, SDL_Surface* des, SDL_Rect* clip, int x, int y)
{
	SDL_Rect offset;
	offset.x = x;
	offset.y = y;
	SDL_BlitSurface(src, clip , des, &offset); // match tat ca lai voi nhau
}

//Ham xu ly va cham
bool SDLCommonFunc::CheckCollision(const SDL_Rect& object_1, const SDL_Rect& object_2)
{
	int left_a = object_1.x; // khai bao bien ben trai
	int right_a = object_1.x + object_1.w; // khai bao bien ben phai
	int top_a = object_1.y; // khai bao bien ben tren
	int bottom_a = object_1.y + object_1.h; // khai bao bien ben duoi

	int left_b = object_2.x;
	int right_b = object_2.x + object_2.w;
	int top_b = object_2.y;
	int bottom_b = object_2.y + object_2.h;

	// Case 1: size object 1 < size object 2
	if (left_a > left_b && left_a < right_b)
	{
		if (top_a > top_b && top_a < bottom_b)
		{
			return true;
		}
	}

	if (left_a > left_b && left_a < right_b)
	{
		if (bottom_a > top_b && bottom_a < bottom_b)
		{
			return true;
		}
	}

	if (right_a > left_b && right_a < right_b)
	{
		if (top_a > top_b && top_a < bottom_b)
		{
			return true;
		}
	}

	if (right_a > left_b && right_a < right_b)
	{
		if (bottom_a > top_b && bottom_a < bottom_b)
		{
			return true;
		}
	}

	// Case 2: size object 1 < size object 2
	if (left_b > left_a && left_b < right_a)
	{
		if (top_b > top_a && top_b < bottom_a)
		{
			return true;
		}
	}

	if (left_b > left_a && left_b < right_a)
	{
		if (bottom_b > top_a && bottom_b < bottom_a)
		{
			return true;
		}
	}

	if (right_b > left_a && right_b < right_a)
	{
		if (top_b > top_a && top_b < bottom_a)
		{
			return true;
		}
	}

	if (right_b > left_a && right_b < right_a)
	{
		if (bottom_b > top_a && bottom_b < bottom_a)
		{
			return true;
		}
	}

	// Case 3: size object 1 = size object 2
	if (top_a == top_b && right_a == right_b && bottom_a == bottom_b)
	{
		return true;
	}

	return false;
}
// Ham giai phong vung nho kh can thiet
void SDLCommonFunc::CleanUp()
{
	SDL_FreeSurface(g_screen);
	SDL_FreeSurface(g_bkground);
}