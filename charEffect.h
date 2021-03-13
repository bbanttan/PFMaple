#pragma once
#include "gameNode.h"

class charEffect : public gameNode
{

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void normal_r_1(float _x, float _y) { EFFECTMANAGER->play("오른쪽일반공격1", _x, _y); };
	void normal_l_1(float _x, float _y) { EFFECTMANAGER->play("왼쪽일반공격1", _x, _y); };

	void normal_r_2(float _x, float _y) { EFFECTMANAGER->play("오른쪽일반공격2", _x, _y); };
	void normal_l_2(float _x, float _y) { EFFECTMANAGER->play("왼쪽일반공격2", _x, _y); };

	void normal_r_3(float _x, float _y) { EFFECTMANAGER->play("오른쪽일반공격3", _x, _y); };
	void normal_l_3(float _x, float _y) { EFFECTMANAGER->play("왼쪽일반공격3", _x, _y); };

	void blust(float _x, float _y) { EFFECTMANAGER->play("슬래시블러스트", _x, _y); };
	void blust_blow(float _x, float _y) { EFFECTMANAGER->play("슬래시블러스트타격", _x, _y); };

	void seven_1(float _x, float _y) { EFFECTMANAGER->play("럭키세븐_1", _x, _y); };
	void seven_2(float _x, float _y) { EFFECTMANAGER->play("럭키세븐_2", _x, _y); };
	void seven_blow(float _x, float _y) { EFFECTMANAGER->play("럭키세븐타격", _x, _y); };

	void clo_1(float _x, float _y) { EFFECTMANAGER->play("매직클로_1", _x, _y); };
	void clo_2(float _x, float _y) { EFFECTMANAGER->play("매직클로_2", _x, _y); };
	void clo_blow(float _x, float _y) { EFFECTMANAGER->play("매직클로타격", _x, _y); };
};