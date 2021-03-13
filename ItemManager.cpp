#include "stdafx.h"
#include "ItemManager.h"
#include "Map.h"
#include "Character.h"
#include "Inventory.h"

HRESULT ItemManager::init()
{
	//기타
	IMAGEMANAGER->addImage("죽부", "이미지/아이템/좀비버섯/죽부.bmp", 26, 26, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("뿔버섯의갓", "이미지/아이템/뿔버섯/뿔버섯의갓.bmp", 30, 27, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("메소", "이미지/아이템/공용/메소.bmp", 25, 24, true, RGB(255, 0, 255));

	//무기
	IMAGEMANAGER->addImage("검", "이미지/아이템/초보자/검.bmp", 31, 29, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("왕푸", "이미지/아이템/전사/왕푸.bmp", 34, 31, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("가니어", "이미지/아이템/도적/가니어.bmp", 26, 25, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("워보우", "이미지/아이템/궁수/워보우.bmp", 30, 31, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("고목나무스태프", "이미지/아이템/마법사/고목나무스태프.bmp", 33, 32, true, RGB(255, 0, 255));

	//표창, 화살
	IMAGEMANAGER->addImage("뇌전수리검", "이미지/아이템/도적/뇌전.bmp", 25, 29, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("좋은화살", "이미지/아이템/궁수/화살.bmp", 32, 32, true, RGB(255, 0, 255));

	//포션
	IMAGEMANAGER->addImage("파란포션", "이미지/아이템/포션/파란포션.bmp", 27, 27, true, RGB(255, 0, 255));

	return S_OK;
}

void ItemManager::release()
{

}

void ItemManager::update()
{
	for (_viItem = _vItem.begin(); _viItem != _vItem.end(); )
	{
		if ((*_viItem)->EatSign())
		{
			_viItem = _vItem.erase(_viItem);
		}
		else
		{
			(*_viItem)->update();

			if (KEYMANAGER->isOnceKeyDown('A') && (*_viItem)->getLanding() == false && (*_viItem)->returnEat() == false)
			{
				if (_inven->getLeaveSlotNumCheck() > (*_viItem)->getNum())
				{
					RECT temp;
					if (IntersectRect(&temp, &c->getRECT(), &(*_viItem)->getRECT()))
					{
						(*_viItem)->Eat();	//먹었다는 신호를 아이템클래스에게 쏴줌
						_inven->Item_add((*_viItem), (*_viItem)->getNum());
					}
				}
			}
			if ((*_viItem)->returnEat())
			{
				(*_viItem)->setX((*_viItem)->getX() + ((c->getX() - (*_viItem)->getX())) * 0.05f);
				(*_viItem)->setY((*_viItem)->getY() + ((c->getY() - (*_viItem)->getY())) * 0.05f);
			}
			++_viItem;
		}
	}
}

void ItemManager::render()
{
	for (int i = 0; i < _vItem.size(); i++)
	{
		_vItem[i]->render();
	}
}

void ItemManager::Item_all_clear()
{
	_vItem.clear();
}
