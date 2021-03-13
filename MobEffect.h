#pragma once
#include "gameNode.h"

class MobEffect : public gameNode
{

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void Junior1_1(float _x, float _y) { EFFECTMANAGER->play("주발공격1_1", _x, _y); };
	void Junior1_2(float _x, float _y) { EFFECTMANAGER->play("주발공격1_2", _x, _y); };
	void Junior2_1(float _x, float _y) { EFFECTMANAGER->play("주발공격2_1", _x, _y); };
	void Junior2_2(float _x, float _y) { EFFECTMANAGER->play("주발공격2_2", _x, _y); };
	void Junior3(float _x, float _y) { EFFECTMANAGER->play("주발공격3", _x, _y); };
	void JuniorBomb(float _x, float _y) { EFFECTMANAGER->play("파이어볼터짐", _x, _y); };
};

