#include "stdafx.h"
#include "Junior.h"
#include "Character.h"
#include "ItemManager.h"

#define UPDATE_RAND 10
#define RIGHT_RAND 50
#define LEFT_RAND 50

#define ATT1_RAND 34
#define ATT2_RAND 33
#define ATT3_RAND 33

HRESULT Junior::init()
{

	return S_OK;
}

void Junior::release()
{

}

void Junior::update()
{

	if (hp > 0)
	{
		if (knockback == 0.0f)
		{
			if (ani_update)	//어떠한 동작의 프레임 마지막일때
			{
				if (RND->getInt(100) < rnd_update)	//새로운 동작을 할 확률
				{

					int pro[] = { rnd_right, rnd_left, rnd_attack1, rnd_attack2, rnd_attack3 };
					int end = 0, start = 0;
					int rnd = RND->getInt(100);

					for (int i = 0; i < 5; i++)
					{
						end += pro[i];
						if (start < rnd && rnd <= end)
						{
							if (i == 0)
							{
								cnt = frameX = frameY = 0;
								spd = 1;
								M_rl = M_RIGHT;
								M_smja = M_MOVE;
							}
							else if (i == 1)
							{
								cnt = frameX = frameY = 0;
								spd = -1;
								M_rl = M_LEFT;
								M_smja = M_MOVE;
							}
							else if (i == 2)	//공격1
							{
								attackPattern = 1;
								cnt = frameX = frameY = spd = 0;
								M_smja = M_ATTACK;
							}
							else if (i == 3)	//공격2
							{
								attackPattern = 2;
								cnt = frameX = frameY = spd = 0;
								M_smja = M_ATTACK;
							}
							else if (i == 4)	//공격3
							{
								attackPattern = 3;
								cnt = frameX = frameY = spd = 0;
								M_smja = M_ATTACK;
							}
							break;
						}
						start += pro[i];
					}
				}
			}
			ani_update = false;
		}
			switch (M_smja)
			{
			case M_MOVE:
				if (M_rl == M_RIGHT)
				{
					if (cnt == 0 || cnt == 9 || cnt == 18 || cnt == 27 || cnt == 36 || cnt == 44)
					{
						if (cnt == 44) { ani_update = true; cnt = frameX = 0; break; }
						Mobimage->setFrameY(frameY = 6);
						Mobimage->setFrameX(frameX);
						frameX++;
						if (frameX >= 5) frameX = 0;
					}
				}
				else if (M_rl == M_LEFT)
				{
					if (cnt == 0 || cnt == 9 || cnt == 18 || cnt == 27 || cnt == 36 || cnt == 44)
					{
						if (cnt == 44) { ani_update = true; cnt = frameX = 0; break; }
						Mobimage->setFrameY(frameY = 0);
						Mobimage->setFrameX(frameX);
						frameX++;
						if (frameX >= 5) frameX = 0;
					}
				}
				break;
			case M_ATTACK:
				if (M_rl == M_RIGHT)
				{
					if (attackPattern == 1)
					{
						if (cnt == 0 || cnt == 21 || cnt == 26 || cnt == 46 || cnt == 50)
						{
							if (cnt == 0) { eft->Junior2_2(x + 30, y + 90); }
							if (cnt == 46) { junior_fire->fireball(x + 30, y + 90, getAngle(x + 30, y + 90, cha->getX(), cha->getY()), 1, cha);}
							if (cnt == 50) { ani_update = true; cnt = frameX = 0; break; }
							Mobimage->setFrameY(frameY = 8);
							Mobimage->setFrameX(frameX);
							frameX++;
							if (frameX >= 4) frameX = 0;
						}
					}
					else if (attackPattern == 2)
					{
						if (cnt == 0 || cnt == 6 || cnt == 11 || cnt == 26 || cnt == 50)
						{
							if (cnt == 26) { addWidth = 180; eft->Junior1_2(x + 30, y + 90); }
							if (cnt == 50) 
							{ ani_update = true; cnt = frameX = 0; break; }
							Mobimage->setFrameY(frameY = 7);
							Mobimage->setFrameX(frameX);
							frameX++;
							if (frameX >= 4) frameX = 0;
						}
					}
					else if (attackPattern == 3)
					{
						if (cnt == 0 || cnt == 6 || cnt == 11 || cnt == 16 || cnt == 22 || cnt == 27 || cnt == 43 || cnt == 69 || cnt == 104 || cnt == 116)
						{
							if (cnt == 43) { eft->Junior3(x + 30, y + 90); }
							if (cnt == 116) { ani_update = true; cnt = frameX = 0; break; }
							Mobimage->setFrameY(frameY = 9);
							Mobimage->setFrameX(frameX);
							frameX++;
							if (frameX >= 9) frameX = 0;
						}
					}
				}
				else if (M_rl == M_LEFT)
				{
					if (attackPattern == 1)
					{
						if (cnt == 0 || cnt == 21 || cnt == 26 || cnt == 46 || cnt == 50)
						{
							if (cnt == 0) { eft->Junior2_1(x - 30, y + 90); }
							if (cnt == 46) { junior_fire->fireball(x - 50, y + 90, getAngle(x - 50, y + 107, cha->getX(), cha->getY()), -1, cha); }
							if (cnt == 50) { ani_update = true; cnt = frameX = 0; break; }
							Mobimage->setFrameY(frameY = 2);
							Mobimage->setFrameX(frameX);
							frameX++;
							if (frameX >= 4) frameX = 0;
						}
					}
					else if (attackPattern == 2)
					{
						if (cnt == 0 || cnt == 6 || cnt == 11 || cnt == 26 || cnt == 50)
						{
							if (cnt == 26) {addWidth = 180; eft->Junior1_1(x - 30, y + 90); } 
							if (cnt == 50) { ani_update = true; cnt = frameX = 0; break; }
							Mobimage->setFrameY(frameY = 1);
							Mobimage->setFrameX(frameX);
							frameX++;
							if (frameX >= 4) frameX = 0;
						}
					}
					else if (attackPattern == 3)
					{
						if (cnt == 0 || cnt == 6 || cnt == 11 || cnt == 16 || cnt == 22 || cnt == 26 || cnt == 43 || cnt == 69 || cnt == 104 || cnt == 116)
						{
							if (cnt == 43) { eft->Junior3(x - 30, y + 90); }
							if (cnt == 116) { ani_update = true; cnt = frameX = 0; break; }
							Mobimage->setFrameY(frameY = 3);
							Mobimage->setFrameX(frameX);
							frameX++;
							if (frameX >= 9) frameX = 0;
						}
					}
				}
				break;
			}
		

		Aggrow();

		//공격범위
		int rich = getDistance(x, y + 150, cha->getX(), cha->getY());

		if (rich < 170)
		{
			rnd_right = rnd_left = 0;
			rnd_update = 100;
			rnd_attack1 = ATT1_RAND;
			rnd_attack2 = ATT2_RAND;
			rnd_attack3 = ATT3_RAND;
			cha->getX() > x ? M_rl = M_RIGHT : M_rl = M_LEFT;
		}
		else
		{
			//만약 어그로범위안에 캐릭터가 있을때
			RECT temp;
			if (IntersectRect(&temp, &cha->getRECT(), &AggroRECT))
			{
				if (RND->getInt(100) < 30)
				{
					if ((cha->getX() > x && M_rl == M_RIGHT) || (cha->getX() < x && M_rl == M_LEFT))
					{
						rnd_update = 100;
						rnd_right = 0;
						rnd_left = 0;
						rnd_attack1 = 100;
						rnd_attack2 = 0;
						rnd_attack3 = 0;
					}
				}
				else
				{
					if (aggro <= 2) aggro = 2;
				}
			}
			else
			{
				if (!aggro && (rnd_right != RIGHT_RAND || rnd_left != LEFT_RAND || rnd_update != UPDATE_RAND))
				{
					rnd_right = RIGHT_RAND;
					rnd_left = LEFT_RAND;
					M_smja == M_ATTACK ? rnd_update = 100 : rnd_update = UPDATE_RAND;
					rnd_attack1 = 0;
					rnd_attack2 = 0;
					rnd_attack3 = 0;
				}
			}
		}

		if (knockback != 0.0f)
		{
			if (knockback > 0.0f)
			{
				knockback -= 0.2f;
				if (knockback <= 0.0f)
				{
					if (M_smja != M_ATTACK) ani_update = true;
					knockback = 0.0f;
				}
			}
			else if (knockback < 0.0f)
			{
				knockback += 0.2f;
				if (knockback >= 0.0f)
				{
					if(M_smja != M_ATTACK) ani_update = true;
					knockback = 0.0f;
				}
			}
		}

		aggro <= 0 ? aggro = 0 : aggro--;

		cnt++;
		gra += 0.2f;
		x += spd + knockback;

		//못지나감
		if (x > maxX && maxX != 0.0f)
		{
			x = maxX;
			setRL(M_LEFT);
		}
		if (x < minX && minX != 0.0f)
		{
			x = minX;
			setRL(M_RIGHT);
		}

		MobRect = RectMakeCenter(x, y + 95, 126 + addWidth, 154);
		AggroRECT = RectMakeCenter(x, y + 95, 800, 149.8);

		addWidth = 0;
	}
	else
	{
		
		if (cnt > 0 && M_smja != M_DEAD)
		{
			cnt = frameX = 0;
		}
		M_smja = M_DEAD;
		_hpbarVisible = false;
		dead();
	}
	eft->update();	//이펙트
	junior_fire->update(); //파이어볼
}

void Junior::render()
{
	if (KEYMANAGER->isToggleKey('1'))
	{
		HPEN Pen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
		HPEN oPen = (HPEN)SelectObject(getMemDC(), Pen);
		Rectangle(getMemDC(), MobRect);
		Rectangle(getMemDC(), AggroRECT);
		SelectObject(getMemDC(), oPen);
		DeleteObject(Pen);
	}
	Mobimage->alpha_frameRender(getMemDC(), x - IMAGEMANAGER->findImage(mobName)->getFrameWidth() / 2, y-22, frameX, frameY, alpha);
	eft->render();
	junior_fire->render();

}

void Junior::Aggrow()
{
	if (aggro != 0)
	{
		if (cha->getX() > x)
		{
			rnd_update = 100;
			rnd_right = 95;
			rnd_left = 5;
			rnd_attack1 = 0;
			rnd_attack2 = 0;
			rnd_attack3 = 0;
		}
		else if (cha->getX() < x)
		{
			rnd_update = 100;
			rnd_left = 95;
			rnd_right = 5;
			rnd_attack1 = 0;
			rnd_attack2 = 0;
			rnd_attack3 = 0;
		}
	}
}

void Junior::dead()
{
	hp = -100;

	if (M_rl == M_RIGHT)
	{
		if (cnt == 0 || cnt == 11 || cnt == 22)
		{
			Mobimage->setFrameY(frameY = 11);
			Mobimage->setFrameX(frameX);
			frameX++;
			if (frameX >= 3) frameX = 3;
		}
	}
	else if (M_rl == M_LEFT)
	{
		if (cnt == 0 || cnt == 11 || cnt == 22)
		{
			Mobimage->setFrameY(frameY = 5);
			Mobimage->setFrameX(frameX);
			frameX++;
			if (frameX >= 3) frameX = 3;
		}
	}
	if (cnt >= 22)
	{
		alpha -= 5;
	}
	if (alpha <= 0)
	{
		return;
	}
	cnt++;
}