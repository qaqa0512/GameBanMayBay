#include "Com_Func.h"
#include "FontText.h"

// ktra toa do cua mot diem voi rect da cho truoc
bool SDLCommonFunc::CheckFocusRect(const int& x, const int& y, const SDL_Rect& rect)
{
	if(x >= rect.x && x <= rect.x + rect.w && y >= rect.y && y <= rect.y + rect.h) // neu con chuot nam trong vung dc chi dinh thi se dc focus
	{
		return true;
	}
	return false;
}

// ham show Menu
int SDLCommonFunc::ShowMenu(SDL_Surface* des, TTF_Font* font)
{
	g_img_menu = LoadImage("menu.png");// load anh menu len man hinh
	if (g_img_menu == NULL) // ktra neu = Null thi sai
	{
		return 1;
	}

	const int MenuItemNum = 2; // khai bao 2 option cho game do la play game va exit
	int xm = 0;// Khai bao toa do cua con chuot
	int ym = 0;// Khai bao toa do cua con chuot
	SDL_Rect pos_arr[MenuItemNum]; // khai bao vi tri hien thi cua 2 option
	// vi tri cua option 1
	pos_arr[0].x = 480;
	pos_arr[0].y = 170;

	// vi tri cua option 2
	pos_arr[1].x = 520;
	pos_arr[1].y = 220;

	Font_Text text_menu[MenuItemNum]; // noi dung cua text
	//Option 1
	text_menu[0].SetText("Play Game"); // dat ten cho option 1
	text_menu[0].SetColor(Font_Text::ORANGE_TEXT);
	text_menu[0].SetRect(pos_arr[0].x, pos_arr[0].y); // vi tri hien thi

	//Option 2
	text_menu[1].SetText("Exit"); // dat ten cho option 2
	text_menu[1].SetColor(Font_Text::ORANGE_TEXT);
	text_menu[1].SetRect(pos_arr[1].x, pos_arr[1].y); // vi tri hien thi

	// ktra 2 trang thai focus duoc vao
	bool selected[MenuItemNum] = { 0,0 };// khong the focus vao
	
	SDL_Event m_event; // su kien di chuyen con chuot
	
	while (true)
	{
		// Cap nhat man hinh
		SDLCommonFunc::ApplySurface(g_img_menu, des, 0, 0);
		for (int i = 0; i < MenuItemNum; i++) 
		{
			text_menu[i].CreateGameText(font, des); // truyen tham so font vao des vao
		}

		// Su kien 
		while (SDL_PollEvent(&m_event))
		{
			switch (m_event.type)
			{
				//truong hop thoat
			case SDL_QUIT: // neu quit thi se tra ve 1 => exit 
				return 1;
				// truong hop di chuyen con chuot
			case SDL_MOUSEMOTION: // con chuot di chuyen tren man hinh
			{
				xm = m_event.motion.x; // lay toa do cua con chuot di chuyen tren man hinh
				ym = m_event.motion.y;// lay toa do cua con chuot di chuyen tren man hinh
				
				for(int i=0; i<MenuItemNum; i++)
				{
					if (CheckFocusRect(xm, ym, text_menu[i].GetRect())) 
					{
						if(selected[i] == false)
						{
							selected[i] = 1; // trang thai khi di chuyen chuot nam trong vung dc focus
							text_menu[i].SetColor(Font_Text::REDPINK_TEXT); // thi lap tuc se dc doi mau
						}
					}

					else
					{
						if (selected[i] == true) // nguoc lai neu = true thi se
						{
							selected[i] = 0; // trang thai khi di chuyen chuot nha ra ngay trong vung dc focus
							text_menu[i].SetColor(Font_Text::ORANGE_TEXT); // thi lap tuc tro ve mau ban dau
						}
					}
				}
			}
				break;
				// truong hop click chuot
			case SDL_MOUSEBUTTONDOWN:
			{
				xm = m_event.button.x; // lay toa do cua con chuot khi bam xuong
				ym = m_event.button.y;
				for (int i = 0; i < MenuItemNum; i++)
				{
					if (CheckFocusRect(xm, ym, text_menu[i].GetRect()))
					{
						return i; // item = 0
					}
				}
			}
			// Truong hop chua thuc hien gi nhung an exit thi sao
			case SDL_KEYDOWN:
				if(m_event.key.keysym.sym == SDLK_ESCAPE)
				{
					return 1; // exit chuong trinh
				}
			default:
				break;
			}
		}

		SDL_Flip(des);
	}

	
	return 1;
}

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
SDL_Rect SDLCommonFunc::ApplySurface(SDL_Surface* src, SDL_Surface* des, int x, int y)// co chuc nang load 1 surface nguon va dich
{
	SDL_Rect offset; 
	offset.x = x;
	offset.y = y;
	SDL_BlitSurface(src, NULL, des, &offset); // match lai voi nhau
	return offset;
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