#include "stdafx.h"
#include "playGround.h"

playGround::playGround()
{
}


playGround::~playGround()
{
}

HRESULT playGround::init()
{
	gameNode::init(true);

	IMAGEMANAGER->addImage("메뉴UI", "이미지/UI/메뉴게이지UI.bmp", 242, 221, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("체력바UI", "이미지/UI/체력바UI.bmp", 163, 16, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("마나바UI", "이미지/UI/마나바UI.bmp", 163, 16, false, RGB(255, 0, 255));

	map = new Map;
	map->init();

	c = new Character;
	c->init();

	Mm = new MobManager;
	Mm->init();

	dmg = new damage;
	dmg->init();

	_log = new login;
	_log->init();

	_itemM = new ItemManager;
	_itemM->init();

	_inven = new Inventory;
	_inven->init();

	c->getMyAdress(c);
	c->setMapAdress(map);
	c->setMapAdress(Mm);
	map->setCharacter(c);
	Mm->setMapAdress(map);
	Mm->setCharAdress(c);
	map->setMobManager(Mm);
	_itemM->setMapAdress(map);
	_itemM->setCharacterAdress(c);
	_itemM->setInventoryAdress(_inven);
	Mm->setItemManagerAdress(_itemM);
	map->setItemManagerAdress(_itemM);
	_inven->setCharacterAdress(c);
	c->setInventoryAdress(_inven);

	return S_OK;
}


void playGround::release()
{
	gameNode::release();
}

void playGround::update()
{
	gameNode::update();

	if (_log->getNext() != 2)
	{
		_log->update();
	}
	if (_log->getNext() == 2)
	{
		map->update();
		c->update();
		Mm->update();
		_itemM->update();
		_inven->update();

		CAMERA->cam(c->getX(), c->getY(), -60.0f, false, NULL, NULL, 0.0f, 0.0f);
	}
}


void playGround::render()
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//================ 위에 건들지 마라 ==============================

	if (_log->getNext() != 2)
	{
		_log->render();
	}
	if (_log->getNext() == 2)
	{
		map->render();
		c->render();
		Mm->render();
		_itemM->render();
		_inven->render();

		TIMEMANAGER->render(getMemDC());

		//메뉴UI
		IMAGEMANAGER->findImage("메뉴UI")->render(getMemDC(), CAMERA->getcamX(), CAMERA->getcamY() + 379);
		IMAGEMANAGER->findImage("체력바UI")->render(getMemDC(), CAMERA->getcamX() + 49, CAMERA->getcamY() + 550, 0, 0,
			(c->getHP() / c->getMHP()) * 163.0f, 16);
		IMAGEMANAGER->findImage("마나바UI")->render(getMemDC(), CAMERA->getcamX() + 49, CAMERA->getcamY() + 570, 0, 0,
			(c->getMP() / c->getMMP()) * 163.0f, 16);
	}
	//================= 아래도 건들지 마라 ==============================
	if (_log->getNext() != 2)
	{
		_backBuffer->render(getHDC(), 0, 0);
	}
	if (_log->getNext() == 2)
	{
		_backBuffer->render(getHDC(), 0, 0, CAMERA->getcamX(), CAMERA->getcamY(), WINSIZEX, WINSIZEY);
	}
}

