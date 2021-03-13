#pragma once
#include "gameNode.h"

#define MAXNUM 200

class Item;
class Character;

class Inventory : public gameNode
{
private:
	struct tagItemSlot
	{
		Item* slot;
		RECT rect;
		int itemNum;
	};

	tagItemSlot islot[20];

	Character* c;

	bool _Visible, second_click;

	int first_click_cnt, select_slot;

	float x, y;

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void Inventory_Visible();

	bool Item_add(Item* _itemInfo, int _inum);
	void Double_Click();
	int getLeaveSlotCheck();
	int getLeaveSlotNumCheck();
	int getSameItemCheck(string _iname);
	bool getDAGGERItemCheck();
	bool getARROWItemCheck();
	void setMinusNum(string _iname, int _num);
	void setItemDelete(int _slotnum);
	void setCharacterAdress(Character* _c) { c = _c; };
	
};

