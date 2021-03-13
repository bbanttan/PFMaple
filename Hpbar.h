#pragma once
#include "gameNode.h"

class Hpbar : public gameNode
{
private:
	image* _hpfront;
	image* _hpbehind;

	int hp, mhp;
	float x, y;

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void setHP(int _hp, int _mhp, float _x, float _y) { hp = _hp; mhp = _mhp; x = _x; y = _y; }
	int getHP() { return hp; }
};