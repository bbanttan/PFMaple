#include "stdafx.h"
#include "charEffect.h"

HRESULT charEffect::init()
{
	EFFECTMANAGER->addEffect("왼쪽일반공격1", "이미지/이펙트/일반공격/왼쪽공격1.bmp", 44, 36, 44, 36, 1.0f, 0.1f, 2);
	EFFECTMANAGER->addEffect("왼쪽일반공격2", "이미지/이펙트/일반공격/왼쪽공격2.bmp", 45, 23, 45, 23, 1.0f, 0.1f, 2);
	EFFECTMANAGER->addEffect("왼쪽일반공격3", "이미지/이펙트/일반공격/왼쪽공격3.bmp", 49, 40, 49, 40, 1.0f, 0.1f, 2);

	EFFECTMANAGER->addEffect("오른쪽일반공격1", "이미지/이펙트/일반공격/오른쪽공격1.bmp", 44, 36, 44, 36, 1.0f, 0.1f, 2);
	EFFECTMANAGER->addEffect("오른쪽일반공격2", "이미지/이펙트/일반공격/오른쪽공격2.bmp", 45, 23, 45, 23, 1.0f, 0.1f, 2);
	EFFECTMANAGER->addEffect("오른쪽일반공격3", "이미지/이펙트/일반공격/오른쪽공격3.bmp", 49, 40, 49, 40, 1.0f, 0.1f, 2);

	EFFECTMANAGER->addEffect("슬래시블러스트", "이미지/이펙트/슬래시블러스트/슬러시블러스트.bmp", 1045, 233, 209, 233, 3.0f, 0.1f, 5);
	EFFECTMANAGER->addEffect("슬래시블러스트타격", "이미지/이펙트/슬래시블러스트/타격.bmp", 500, 105, 125, 105, 1.0f, 0.1f, 5);

	EFFECTMANAGER->addEffect("럭키세븐_1", "이미지/이펙트/럭키세븐/럭키세븐_1.bmp", 480, 100, 80, 100, 2.0f, 0.1f, 5);
	EFFECTMANAGER->addEffect("럭키세븐_2", "이미지/이펙트/럭키세븐/럭키세븐_2.bmp", 480, 100, 80, 100, 2.0f, 0.1f, 5);
	EFFECTMANAGER->addEffect("럭키세븐타격", "이미지/이펙트/럭키세븐/타격.bmp", 256, 79, 64, 79, 1.0f, 0.1f, 5);

	EFFECTMANAGER->addEffect("매직클로_1", "이미지/이펙트/매직클로/매직클로_1.bmp", 201, 67, 67, 67, 1.0f, 0.1f, 5);
	EFFECTMANAGER->addEffect("매직클로_2", "이미지/이펙트/매직클로/매직클로_2.bmp", 201, 67, 67, 67, 1.0f, 0.1f, 5);
	EFFECTMANAGER->addEffect("매직클로타격", "이미지/이펙트/매직클로/매직클로타격.bmp", 505, 95, 101, 95, 1.0f, 0.1f, 1);


	return S_OK;
}

void charEffect::release()
{

}

void charEffect::update()
{
	EFFECTMANAGER->update();
}

void charEffect::render()
{
	EFFECTMANAGER->render();
}
