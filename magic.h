#pragma once
#include "gameNode.h"

class Character;
class MobManager;
class charEffect;
class Map;

class magic : public gameNode
{
private:
	int cnt, who, temp, need_hp, need_mp;

	Character* c;
	MobManager* mm;
	Map* m;
	charEffect* eft;

public:
	magic() { cnt = 0; who = -1; temp = 10000; need_hp = 0; need_mp = 20; };
	~magic() {};

	virtual void update();

	void Mob_Search(Character* _c, MobManager* _mm, Map* _map, charEffect* _eft);
	void Mob_Knock();
	void setCnt() { cnt = 20; }
	int getNeedHP() { return need_hp; }
	int getNeedMP() { return need_mp; }
};

