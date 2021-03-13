#pragma once
#include "gameNode.h"
#include <vector>

struct tagDamage
{
	image* damage_img;
	int frame, alpha;
	float x, y;
};

class damage : public gameNode
{
private:
	
	vector<tagDamage>				_vDmg;
	vector<tagDamage>::iterator		_viDmg;

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void create_damage(float x, float y, int dmg, bool monster);

};

