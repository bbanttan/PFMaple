#pragma once
#include "Mob.h"
#include "MobEffect.h"
#include "Junior_fireball.h"

class Junior : public Mob
{
private:
	int rnd_attack1;
	int rnd_attack2;
	int rnd_attack3;
	int attackPattern;
	int addWidth;

	RECT AggroRECT;

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void Aggrow();

	void dead();

};

