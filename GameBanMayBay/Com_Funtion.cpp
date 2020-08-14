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

// Ham giai phong vung nho kh can thiet
void SDLCommonFunc::CleanUp()
{
	SDL_FreeSurface(g_screen);
	SDL_FreeSurface(g_bkground);
}