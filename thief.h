#pragma once
#include "gameNode.h"

class Character;
class MobManager;
class charEffect;

class thief : public gameNode
{
private:
	int need_hp, need_mp;
	float sx, sy;

	charEffect* eft;
public:
	thief() { sx = sy = 0; need_hp = 0; need_mp = 15; };
	~thief() {};

	void Mob_Search(Character* c, MobManager* mm, charEffect* _eft);
	void setSx(float _sx) { sx = _sx; }
	void setSy(float _sy) { sy = _sy; }
	float getSx() { return sx; }
	float getSy() { return sy; }
	int getNeedHP() { return need_hp; }
	int getNeedMP() { return need_mp; }
};