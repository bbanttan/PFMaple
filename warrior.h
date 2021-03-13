#pragma once
#include "gameNode.h"

class Character;
class MobManager;
class Map;
class charEffect;

class warrior : public gameNode
{
private:
	int Who_Target_Mob[3];
	int Dis_Target_Mob[3];
	int tempWho, tempRich, r, s, cnt, add_attack_scale, need_mp, need_hp;

	Character* _c;
	MobManager* _mm;
	charEffect* eft;
	Map* _map;

public:
	warrior() { cnt = s = add_attack_scale = 0; need_mp = 10; need_hp = 0; };
	~warrior() {};

	virtual void update();
	virtual void render();

	void Mob_Search(Character* c, MobManager* mm, Map* map, charEffect* _eft);
	void Mob_Knock(Character* c, MobManager * mm, Map* map, int y);
	void setCnt() { cnt = 30; }
	int getNeedHP() { return need_hp; }
	int getNeedMP() { return need_mp; }
};

