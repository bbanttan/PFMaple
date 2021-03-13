#include "stdafx.h"
#include "MobEffect.h"

HRESULT MobEffect::init()
{
	EFFECTMANAGER->addEffect("주발공격1_1", "이미지/이펙트/주발/이펙트1_1.bmp", 486, 112, 243, 112, 1.0f, 0.1f, 1);
	EFFECTMANAGER->addEffect("주발공격1_2", "이미지/이펙트/주발/이펙트1_2.bmp", 486, 112, 243, 112, 1.0f, 0.1f, 1);

	EFFECTMANAGER->addEffect("주발공격2_1", "이미지/이펙트/주발/이펙트2_1.bmp", 1374, 122, 229, 122, 1.0f, 0.1f, 1);	
	EFFECTMANAGER->addEffect("주발공격2_2", "이미지/이펙트/주발/이펙트2_2.bmp", 1374, 122, 229, 122, 1.0f, 0.1f, 1);

	EFFECTMANAGER->addEffect("주발공격3", "이미지/이펙트/주발/이펙트3.bmp", 684, 111, 114, 111, 2.0f, 0.1f, 1);

	EFFECTMANAGER->addEffect("파이어볼터짐", "이미지/이펙트/주발/파이어볼터짐.bmp", 424, 120, 106, 120, 1.0f, 0.1f, 3);

	return S_OK;
}

void MobEffect::release()
{

}

void MobEffect::update()
{
	EFFECTMANAGER->update();
}

void MobEffect::render()
{
	EFFECTMANAGER->render();
}
