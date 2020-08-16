#pragma once


// Hien thi so mang cua nhan vat
#ifndef POWER_OBJECT_H_
#define POWER_OBJECT_H_
#include "BasicObject.h"
#include <vector>


class PlayerPower : public BaseObject
{
public:
	PlayerPower();
	~PlayerPower();
	void SetNumber(const int& num) { number_ = num; } // ham thiet lap so mang cho nhan van
	void AddPos(const int& xpos); // ham de add cac danh sach cua vi tri
	void Render(SDL_Surface* des); // Ham show
	void Init();
	void Decrease(); // Ham giam mang moi khi bi va cham
private:
	int number_; // dai dien cho so mang cua nhan vat
	std::vector<int> pos_list_; // vi tri cua mang

};
#endif // !POWER_OBJECT_H_
