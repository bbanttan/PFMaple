#pragma once
#include "gameNode.h"
#include "Character.h"
#include "Map.h"
#include "MobManager.h"
#include "ItemManager.h"
#include "Inventory.h"
#include "login.h"

class playGround : public gameNode
{
private:
	Map* map;
	Character* c;
	MobManager* Mm;
	damage* dmg;
	ItemManager* _itemM;
	Inventory* _inven;
	login* _log;

	RECT m;

public:
	playGround();
	~playGround();

	virtual HRESULT init();	//초기화 전용 함수
	virtual void release();	//메모리 해제 함수
	virtual void update();	//연산 전용
	virtual void render();	//그리기 전용

};