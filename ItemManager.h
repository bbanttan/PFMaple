#pragma once
#include "gameNode.h"
#include "Item.h"
#include <vector>

class Map;
class Character;
class Inventory;

class ItemManager : public gameNode
{
private:
	Map* _map;
	Character* c;
	Inventory* _inven;

	vector<Item*>			_vItem;
	vector<Item*>::iterator	_viItem;

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void Item_all_clear();

	void itemDrop(string _iname, int _inum, float _x, float _y) 
	{
		Item* item;
		item = new Item;

		item->init(_iname, _inum, _x, _y, _map);

		_vItem.push_back(item);
	}
	void setMapAdress(Map* _m) { _map = _m; }
	void setCharacterAdress(Character* _c) { c = _c; }
	void setInventoryAdress(Inventory* _iv) { _inven = _iv; }
};

