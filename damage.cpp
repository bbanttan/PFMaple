#include "stdafx.h"
#include "damage.h"

HRESULT damage::init()
{
	IMAGEMANAGER->addFrameImage("데미지", "이미지/데미지/데미지.bmp", 1078, 38, 11, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("피격데미지", "이미지/데미지/피격데미지.bmp", 1078, 38, 11, 1, true, RGB(255, 0, 255));

	return S_OK;
}

void damage::release()
{
}

void damage::update()
{
	for (_viDmg = _vDmg.begin(); _viDmg != _vDmg.end(); )
	{
		if (_viDmg->alpha <= 0)
		{
			_viDmg = _vDmg.erase(_viDmg);
		}
		else
		{
			_viDmg->y--;
			_viDmg->alpha-=2;
			++_viDmg;
		}
	}
}

void damage::render()
{
	for (_viDmg = _vDmg.begin(); _viDmg != _vDmg.end(); ++_viDmg )
	{
		if (_viDmg->alpha >= 0)
		{
			_viDmg->damage_img->alpha_frameRender(getMemDC(), _viDmg->x, _viDmg->y, _viDmg->frame, 0, _viDmg->alpha);
		}
	}
}

void damage::create_damage(float x, float y, int dmg, bool monster)
{
	int a_dmg[4] = { 0 };

	a_dmg[0] = dmg / 1000;
	a_dmg[1] = (dmg % 1000) / 100;
	a_dmg[2] = ((dmg % 1000) % 100) / 10;
	a_dmg[3] = (((dmg % 1000) % 100) % 10) / 1;

	int To, sit = 0;

	if ((a_dmg[0] + a_dmg[1] + a_dmg[2] + a_dmg[3]) <= 0)
	{
		tagDamage tDmg;
		monster ? tDmg.damage_img = IMAGEMANAGER->findImage("데미지") : tDmg.damage_img = IMAGEMANAGER->findImage("피격데미지");
		tDmg.frame = 10;
		tDmg.damage_img->setFrameX(tDmg.frame);
		tDmg.damage_img->setFrameY(0);
		tDmg.x = x;
		tDmg.y = y;
		tDmg.alpha = 255;
		_vDmg.push_back(tDmg);
		return;
	}

	for (int i = 0; i < 4; i++)
	{
		if (a_dmg[i] != 0)
		{
			To = i;
			break;
		}
	}

	for (int i = To; i < 4; i++)
	{
		tagDamage tDmg;
		monster ? tDmg.damage_img = IMAGEMANAGER->findImage("데미지") : tDmg.damage_img = IMAGEMANAGER->findImage("피격데미지");
		tDmg.frame = a_dmg[i];
		tDmg.damage_img->setFrameX(tDmg.frame);
		tDmg.damage_img->setFrameY(0);
		tDmg.x = x - (((4 - To)*(40)) / 2) + (25 * sit);
		tDmg.y = y;
		tDmg.alpha = 255;
		sit++;
		_vDmg.push_back(tDmg);
	}
}