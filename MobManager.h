#pragma once
#include "gameNode.h"
#include "HornyMushroom.h"
#include "ZombieMushroom.h"
#include "Junior.h"
#include "damage.h"
#include <vector>

class Map;
class Character;
class ItemManager;

class MobManager : public gameNode
{
private:
	Map* _map;
	damage* dmg;
	Character* cha;
	ItemManager* _itemM;

	vector<Mob*>			_vMob;
	vector<Mob*>::iterator	_viMob;

	string c_map;

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
	virtual void map_collision();

	void setMonster(string currentMap);
	void setMapAdress(Map* m) { _map = m; }
	void setCharAdress(Character* c) { cha = c; }
	void setItemManagerAdress(ItemManager* _iM) { _itemM = _iM; }

	vector<Mob*> _getvMob() { return _vMob; };
	vector<Mob*>::iterator _getviMob() { return _viMob; };
};

