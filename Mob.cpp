#include "stdafx.h"
#include "Mob.h"
#include "Character.h"
#include "ItemManager.h"

HRESULT Mob::init(const char* imageName, POINT pos)
{
	mobName = imageName;

	eft = new MobEffect;
	eft->init();

	junior_fire = new Junior_fireball;
	junior_fire->init();

	Mobimage = IMAGEMANAGER->findImage(imageName);

	x = pos.x;
	y = pos.y;
	
	spd = 0;
	cnt = 0;
	frameX = frameY = 0;
	type = NORMAL;
	aggro = 0;

	plusDamageY = 0.0f;

	spawnX = pos.x;

	alpha = 255;

	hit = _hpbarVisible = isExist = false;

	_hpbar = new Hpbar;
	_hpbar->init();

	if (mobName == "»Ô¹ö¼¸")
	{
		hp = mhp = 300;
		jump_ok = false;
		knockback = 0.0f;
		minX = maxX = 0.0f;
		M_rl = M_LEFT;
		M_smja = M_STANDING;
		rnd_update = 20;
		rnd_stand = 20;
		rnd_right = 40;
		rnd_left = 40;
		gra = jump_power = knockback = 0.0f;
	}
	else if (mobName == "Á»ºñ¹ö¼¸")
	{
		hp = mhp = 600;
		jump_ok = true;
		M_rl = M_LEFT;
		minX = maxX = 0.0f;
		M_smja = M_STANDING;
		rnd_update = 20;
		rnd_stand = 20;
		rnd_right = 30;
		rnd_left = 30;
		rnd_jump = 20;
		gra = jump_power = knockback = 0.0f;
	}
	else if (mobName == "ÁÖ´Ï¾î¹ß·Ï")
	{
		hp = mhp = 900;
		type = BOSS;
		jump_ok = false;
		M_rl = M_LEFT;
		M_smja = M_MOVE;
		minX = 92.0f;
		maxX = 1439.0f;
		rnd_update = 100;
		rnd_right = 0;
		rnd_left = 100;
		ani_update = true;
		gra = jump_power = knockback = 0.0f;
	}
	spdKnockback = spd + knockback;
	return S_OK;
}

void Mob::release()
{

}

void Mob::update()
{

}

void Mob::render()
{

}

void Mob::setRL(MobState setrl) {
	if (setrl == M_LEFT)
	{
		if (jump_ok == false)
		{
			rnd_left = 100;
			rnd_right = 0;
			rnd_stand = 0;
		}
		else if (jump_ok == true)
		{
			rnd_left = 100;
			rnd_right = 0;
			rnd_stand = 0;
			rnd_jump = 0;
		}
	}
	if (setrl == M_RIGHT)
	{
		if (jump_ok == false)
		{
			rnd_left = 0;
			rnd_right = 100;
			rnd_stand = 0;
		}
		else if (jump_ok == true)
		{
			rnd_left = 0;
			rnd_right = 100;
			rnd_stand = 0;
			rnd_jump = 0;
		}
	}
	rnd_update = 100;
	ani_update = true;
}
void Mob::setHIT(MobState direction, float _plusDamgeY, int _damage)
{
	aggro = 600;

	damage = _damage;

	hit = true;

	if (jump_ok == true)
	{
		setGRA();
		setJP();
	}
	plusDamageY = _plusDamgeY;
	if (direction == M_LEFT)
	{
		knockback = -3.0f;
		
		if (M_smja != M_ATTACK)
		{
			frameX = cnt = spd = 0;
			frameY = (mobName == "»Ô¹ö¼¸") * 6 + (mobName == "Á»ºñ¹ö¼¸") * 8 + (mobName == "ÁÖ´Ï¾î¹ß·Ï") * 10;
		}
	}
	else if (direction == M_RIGHT)
	{
		knockback = 3.0f;
		
		if (M_smja != M_ATTACK)
		{
			frameX = cnt = spd = 0;
			frameY = (mobName == "»Ô¹ö¼¸") * 2 + (mobName == "Á»ºñ¹ö¼¸") * 3 + (mobName == "ÁÖ´Ï¾î¹ß·Ï") * 4;
		}
	}
	_hpbarVisible = true;

	hp -= _damage;

}

void Mob::setRnd(float infoX, float infoY)	//¸÷ÀÌ ¾î±×·Î¿¡ ²ø·ÈÀ»¶§ Ä³¸¯ÅÍ À§Ä¡¿¡µû¶ó ¹æÇâÈ®·ü
{
	if (infoX < x)	//¸÷ÀÌ ¿À¸¥ÂÊ¿¡ÀÖÀ»¶§
	{
		if (jump_ok == false)
		{
			rnd_update = 100;
			rnd_left = 90;
			rnd_right = 5;
			rnd_stand = 5;
		}
		else if (jump_ok == true)
		{
			float Ydistance;
			y > infoY ? Ydistance = sqrtf((y - infoY) * (y - infoY)) : Ydistance = 0.0f;

			rnd_update = 100;
			rnd_left = ((Ydistance >= 60.0f) * 50) + ((Ydistance < 60.0f) * 85);
			rnd_right = ((Ydistance >= 60.0f) * 0) + ((Ydistance < 60.0f) * 5);
			rnd_stand = ((Ydistance >= 60.0f) * 0) + ((Ydistance < 60.0f) * 5);
			rnd_jump = ((Ydistance >= 60.0f) * 50) + ((Ydistance < 60.0f) * 5);
		}
	}
	else if (infoX > x)	//¸÷ÀÌ ¿ÞÂÊ¿¡ÀÖÀ»¶§
	{
		if (jump_ok == false)
		{
			rnd_update = 100;
			rnd_left = 5;
			rnd_right = 90;
			rnd_stand = 5;
		}
		else if (jump_ok == true)
		{
			float Ydistance;
			y > infoY ? Ydistance = sqrtf((y - infoY) * (y - infoY)) : Ydistance = 0.0f;

			rnd_update = 100;
			rnd_left = ((Ydistance >= 60.0f) * 0) + ((Ydistance < 60.0f) * 5);
			rnd_right = ((Ydistance >= 60.0f) * 50) + ((Ydistance < 60.0f) * 85);
			rnd_stand = ((Ydistance >= 60.0f) * 0) + ((Ydistance < 60.0f) * 5);
			rnd_jump = ((Ydistance >= 60.0f) * 50) + ((Ydistance < 60.0f) * 5);
		}
	}
}
