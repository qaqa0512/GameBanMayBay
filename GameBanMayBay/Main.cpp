﻿#include "Com_Func.h"
#include "MainObject.h"
#include "Threats.h"
#undef main


//Ham Init khoi tao cac thuoc tinh ban dau
bool Init()
{

	if(SDL_Init(SDL_INIT_EVERYTHING) == -1)
	{
		return false;
	}
	//Thiet lap man hinh
	g_screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);
	if (g_screen == NULL) {
		return false;
	}
	return true;
}


//Ham main
int main(int arc, char* argv[])
{
	// Khoi tao va ktra
	bool is_quit = false;

	if (Init() == false)
		return 0;

	// dua anh vao background
	g_bkground = SDLCommonFunc::LoadImage("bg2.png");
	if (g_bkground == NULL)
	{
		return 0;
	}
	
	// Khoi tao nhan vat chinh
	MainObject human_object;
	human_object.SetRect(100, 200);
	bool ret = human_object.LoadImg("plane80.png");
	if (!ret) {
		return 0;
	} 

	//Khoi tao nhan vat tro ngai
	ThreatObject* p_threats = new ThreatObject[NUM_THREAT]; // tao bien de qly so luong dt tro ngai
	for (int t = 0; t < NUM_THREAT; t++) 
	{
		ThreatObject* p_threat = (p_threats + t); // moi lan chay se khoi tao 1 doi tuong
		if (p_threat)
		{
			ret = p_threat->LoadImg("af1.png");
			if (ret == false)// neu anh load len bi loi
			{
				return 0;// sai 
			}
			//set doi tuong xuat hien ngau nhien
			int rand_y = rand() % 400;
			if (rand_y > SCREEN_HEIGHT - 200)
			{
				rand_y = SCREEN_HEIGHT*0.3;
			}

			p_threat->SetRect(SCREEN_WIDTH + t * 400, rand_y);
			p_threat->set_x_val(3);// toc do di chuyen

			AmoObject* p_amo = new AmoObject(); // tao bien quan ly dan ban
			p_threat->InitAmo(p_amo);
		}

	}

	// vong lap up lien tuc man hinh
	while (!is_quit)
	{
		while (SDL_PollEvent(&g_even))
		{
			if (g_even.type == SDL_QUIT)
			{
				is_quit = true;
				break;
			}
			// Doi tuong may bay
			human_object.HandleInputAction(g_even);

		}
		// Cap nhat lai vi tri moi
		SDLCommonFunc::ApplySurface(g_bkground, g_screen, 0, 0); // x=0, y=0 => offset: toa do day; de che do full man hinh
		human_object.Show(g_screen);
		human_object.HandleMove();

		for (int i = 0; i < human_object.GetAmoList().size(); i++)
		{
			std::vector<AmoObject*> amo_list = human_object.GetAmoList();
			AmoObject* p_amo = amo_list.at(i);
			if (p_amo != NULL) {
				if (p_amo->get_is_move())// ktra neu p_amo cho phep dan ban ra
				{
					p_amo->Show(g_screen);
					p_amo->HandleMove(SCREEN_WIDTH,SCREEN_HEIGHT);
				}
				else
				{
					if (p_amo != NULL) // ktra neu vuot gioi han thi
					{
						// xoa doi tuong di 
						amo_list.erase(amo_list.begin() + i);
						human_object.SetAmoList(amo_list);
						//vien dan nao vuot qua gioi han cho phep thi lap tuc se bi loai bo
						delete p_amo;
						p_amo = NULL;
					}
				}
			}
		}

		// Chay nhan vat tro ngai
		for (int tt = 0; tt < NUM_THREAT; tt++) 
		{
			ThreatObject* p_threat = (p_threats + tt); // moi lan chay se khoi tao 1 doi tuong 
			// ktra neu != Null thi cho phep chay tiep
			if (p_threat) 
			{
				p_threat->Show(g_screen);
				p_threat->HandleMove(SCREEN_WIDTH, SCREEN_HEIGHT);
				p_threat->MakeAmo(g_screen, SCREEN_WIDTH, SCREEN_HEIGHT);
			}
		}
		// SDL_lip refresh lai ung dung
		if (SDL_Flip(g_screen) == -1) 
			return 0;
	}

	delete[] p_threats;

	SDLCommonFunc::CleanUp();
	SDL_Quit();

	return 1;
}