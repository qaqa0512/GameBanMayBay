#include "Com_Func.h"
#include "MainObject.h"
#include "Threats.h"
#include "ExplosionObject.h"
#include "Power.h"
#include "FontText.h"
#undef main

// Nguyen Quoc Anh_1711061484
// Nguyen Hoang Cong Duy_1711061525
// Lop 17DTHA6


// Khai bao Font 
TTF_Font* g_font_text = NULL;


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

	// Khoi tao font text
	if (TTF_Init() == -1)
	{
		return false;
	}

	// load file font chu len
	g_font_text = TTF_OpenFont("UVNBanhMi.ttf", 30); // 20 la font_size
	if (g_font_text == NULL) 
	{
		return false;
	}

	return true;
}


//Ham main
int main(int arc, char* argv[])
{
	bool is_run_screen = true; // quan ly viec dung hay la chay
	int bg_x = 0; // khai bao bien bg
	// Khoi tao va ktra
	bool is_quit = false;

	if (Init() == false)
		return 0;

	// dua anh vao background
	g_bkground = SDLCommonFunc::LoadImage("bg9.png");
	if (g_bkground == NULL)
	{
		return 0;
	}
	
	// Khoi tao so mang
	PlayerPower player_power;
	player_power.Init();

	// Khoi tao diem
	Font_Text point; // khai bao bien point
	point.SetColor(Font_Text::ORANGE_TEXT); // set cho diem la mau cam


	// Khoi tao nhan vat chinh
	MainObject human_object; // khai bao bien human_object
	human_object.SetRect(100, 200);
	bool ret = human_object.LoadImg("2.gif");
	if (!ret) {
		return 0;
	} 

	//Khoi tao doi tuong vu no
	ExplosionObject exp_main;
	ret = exp_main.LoadImg("exp_main.png");
	exp_main.set_clip(); // 
	if (!ret)
	{
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

	unsigned int die_number = 0; // khai bao bien so lan chet
	unsigned int point_value = 0; // khai bao bien cho gia tri diem

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
		// Cap nhat background
		//bg_x -= 2; // background di chuyen
		//SDLCommonFunc::ApplySurface(g_bkground, g_screen, bg_x, 0); // x=0, y=0 => offset: toa do day; de che do full man hinh
		//SDLCommonFunc::ApplySurface(g_bkground, g_screen, bg_x + SCREEN_WIDTH, 0);
		//if (bg_x <= -SCREEN_WIDTH) 
		//{
		//	bg_x = 0;
		//}

		
		// neu = true thi cho phep chay
		if(is_run_screen == true)
		{
			bg_x -= 2;
			if (bg_x <= -(WIDTH_BG - SCREEN_WIDTH)) 
			{
				is_run_screen = false;
			}
			else
			{
				SDLCommonFunc::ApplySurface(g_bkground, g_screen, bg_x, 0); //cap nhat background da dc di chuyen
			}
		}
		else
		{
			// giu nguyen trang thai cua bg kh cho chay nua
			SDLCommonFunc::ApplySurface(g_bkground, g_screen, bg_x, 0); //cap nhat background da dc di chuyen
		}

		// Hien thi mang 
		player_power.Render(g_screen);

		//thuc hien nhan vat chinh
		human_object.HandleMove(); // nhan vat chinh di chuyen
		human_object.Show(g_screen);// show hinh anh nhan vat len man hinh window
		human_object.MakeAmo(g_screen); //show hinh anh nhan vat len man hinh window
		

		// thuc thi doi tuong tro ngai
		for (int tt = 0; tt < NUM_THREAT; tt++) 
		{
			ThreatObject* p_threat = (p_threats + tt); // moi lan chay se khoi tao 1 doi tuong 
			// ktra neu != Null thi cho phep chay tiep
			if (p_threat) 
			{
				
				p_threat->HandleMove(SCREEN_WIDTH, SCREEN_HEIGHT);
				p_threat->Show(g_screen);
				p_threat->MakeAmo(g_screen, SCREEN_WIDTH, SCREEN_HEIGHT);
				

				//Xu ly va cham giua dan ban cua threat voi humanmain
				bool is_col1 = false;
				std::vector<AmoObject*> amo_arr = p_threat->GetAmoList();
				for (int am = 0; am < amo_arr.size(); am++) 
				{
					AmoObject* p_amo = amo_arr.at(am);
					if(p_amo)
					{
						is_col1 = SDLCommonFunc::CheckCollision(p_amo->GetRect(), human_object.GetRect());
						if(is_col1 == true)
						{
							p_threat->ResetAmo(p_amo);
							break;
						}
					}
				}
			
				// Sau khi vien dan di chuyen xong thi se kiem tra su va cham giua nhan vat chinh va doi tuong tro ngai
				bool is_col = SDLCommonFunc::CheckCollision(human_object.GetRect(), p_threat->GetRect());
				if(is_col1 || is_col)// neu va cham voi nhau thi tro choi se keu thuc
				{
					// Khi va cham thanh cong thi vu no se xay ra
					for (int exp = 0; exp < 4; exp++)
					{
						int x_pos = (human_object.GetRect().x + human_object.GetRect().w*0.2)-EXP_WIDTH*0.2; //vi tri cua pos se = vi tri ngay mep cua nv + 1/2 chieu chieu rong cua nv - 1/2 chieu rong cua vu no ==> Vi tri se nam o ngay tam 
						int y_pos = (human_object.GetRect().y + human_object.GetRect().h*0.3) - EXP_HEIGHT*0.3; //vi tri cua pos se = vi tri ngay mep cua nv + 1/2 chieu cao cua nv - 1/2 chieu cao cua vu no ==> Vi tri se nam o ngay tam 
						
						exp_main.set_frame(exp); // set frame cho explosion
						exp_main.SetRect(x_pos, y_pos);// set vi tri cho explosion
						exp_main.ShowExp(g_screen);
						/*SDL_Delay(100);*/

						// Cap nhat lai man hinh
						if (SDL_Flip(g_screen) == -1)
							return 0;
					}

					die_number++;// khi chet lan thu 1 thi ctrinh van chay
					if (die_number <= 2) 
					{
						SDL_Delay(700); // do tre sau sau khi hoi sinh
						human_object.SetRect(POS_X_START_MAIN_OBJ, POS_Y_START_MAIN_OBJ); //set lai vi tri ban dau
						player_power.Decrease(); // giam mang di
						player_power.Render(g_screen); // show anh len

													   // Cap nhat lai man hinh
						if (SDL_Flip(g_screen) == -1) 
						{
							delete[] p_threats;
							SDLCommonFunc::CleanUp();
							SDL_Quit();
							return 0;
						}	
					}
					else
					{
						if (MessageBox(NULL, L"Thua rồi bạn ơi!!!", L"Tin Buồn", MB_OK) == IDOK) //Hien thi thong bao ban da thua va khi click vao thi ctrinh se ket thuc
						{
							delete[] p_threats; // xoa doi tuong can tro di
							SDLCommonFunc::CleanUp();
							SDL_Quit();
							return 1;
						}
					}
				}

				// Sau khi vien dan di chuyen xong thi se kiem tra su va cham giua dan ban cua nhan vat chinh va doi tuong tro ngai
				std::vector<AmoObject*> amo_list = human_object.GetAmoList();
				for (int im = 0; im < amo_list.size(); im++)
				{
					AmoObject* p_amo = amo_list.at(im);
					if (p_amo != NULL) // ktra con tro
					{
						bool ret_col = SDLCommonFunc::CheckCollision(p_amo->GetRect(), p_threat->GetRect());// khai bao ham ktra neu dan ban trung doi tuong tro ngai thi se bien mat
						if(ret_col) // ktra khi ma dan ban trung vao doi tuong can tro thi
						{	

							point_value++; // la moi khi ban se tu cong len 1 diem
							for (int exp = 0; exp < 4; exp++)
							{
								// Xu ly vu no cua doi tuong tro ngai
								int x_pos = (p_threat->GetRect().x + p_threat->GetRect().w*0.5) - EXP_WIDTH*0.5; //vi tri cua pos se = vi tri ngay mep cua nv + 1/2 chieu chieu rong cua nv - 1/2 chieu rong cua vu no ==> Vi tri se nam o ngay tam 
								int y_pos = (p_threat->GetRect().y + p_threat->GetRect().h*0.5) - EXP_HEIGHT*0.5; //vi tri cua pos se = vi tri ngay mep cua nv + 1/2 chieu cao cua nv - 1/2 chieu cao cua vu no ==> Vi tri se nam o ngay tam 

								exp_main.set_frame(exp); // set frame cho explosion
								exp_main.SetRect(x_pos, y_pos);// set vi tri cho explosion
								exp_main.ShowExp(g_screen);
								/*SDL_Delay(100);*/

								//Cap nhat lai man hinh
								if (SDL_Flip(g_screen) == -1)
									return 0;

							}	
							p_threat->Reset(SCREEN_WIDTH + tt * 400); // doi tuong se duoc reset lai vi tri ban dau
							human_object.RemoveAmo(im); // khi nv chinh ban trung dt can tro thi vien dan se bien mat
						}
					}
				}
			}
		}

		//Show point_value len man hinh window
		std::string val_str_point = std::to_string(point_value); // chuyen doi tu so sang dang chuoi
		std::string strPoint("Point: "); // Dat ten cho point
		strPoint += val_str_point; // Dc gia tri cua so diem VD: 1...2...3...4...5

		point.SetText(strPoint); // dua noi dung hien thi text vao
		point.CreateGameText(g_font_text, g_screen);




		// Cap nhat lai man hinh
		if (SDL_Flip(g_screen) == -1) 
			return 0;
	}

	delete[] p_threats;

	SDLCommonFunc::CleanUp();
	SDL_Quit();

	return 1;
}