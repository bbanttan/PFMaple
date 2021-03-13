#include "stdafx.h"
#include "ZombieMushroom.h"
#include "ItemManager.h"

#define UPDATE_RAND 20
#define STAND_RAND 10
#define RIGHT_RAND 40
#define LEFT_RAND 40
#define JUMP_RAND 10

HRESULT ZombieMushroom::init()
{
	
	return S_OK;
}

void ZombieMushroom::release()
{
}

void ZombieMushroom::update()
{
	if (hp > 0)
	{
		_hpbar->setHP(hp, mhp, x - Mobimage->getFrameWidth() / 2, y - Mobimage->getFrameHeight());
		if (knockback == 0.0f)
		{
			if (ani_update)	//어떠한 동작의 프레임 마지막일때
			{
				if (RND->getInt(100) < rnd_update)	//새로운 동작을 할 확률
				{
					int pro[] = { rnd_right, rnd_left, rnd_stand , rnd_jump };
					int end = 0, start = 0;
					int rnd = RND->getInt(100);

					for (int i = 0; i < 4; i++)
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
							else if (i == 2)
							{
								cnt = frameX = frameY = spd = 0;
								M_smja = M_STANDING;
							}
							else if (i == 3)
							{
								cnt = frameX = frameY = 0;
								M_smja = M_JUMP;
								jump_power = 6.0f;
								maxX = 0.0f;
								minX = 0.0f;
							}
							break;
						}
						start += pro[i];
					}
				}
			}

			ani_update = false;

			if (!aggro && (rnd_stand != STAND_RAND || rnd_right != RIGHT_RAND || rnd_left != LEFT_RAND || rnd_update != UPDATE_RAND || rnd_jump != JUMP_RAND))
			{
				rnd_stand = STAND_RAND;
				rnd_right = RIGHT_RAND;
				rnd_left = LEFT_RAND;
				rnd_update = UPDATE_RAND;
				rnd_jump = JUMP_RAND;
			}

			switch (M_smja)
			{
			case M_STANDING:
				if (M_rl == M_RIGHT)
				{
					if (cnt == 0 || cnt == 10 || cnt == 18 || cnt == 26)
					{
						if (cnt == 18) { ani_update = true; cnt = frameX = 0; break; }
						Mobimage->setFrameY(frameY = 5);
						Mobimage->setFrameX(frameX);
						frameX++;
						if (frameX >= 2) frameX = 0;
					}
				}
				else if (M_rl == M_LEFT)
				{
					if (cnt == 0 || cnt == 10 || cnt == 18 || cnt == 26)
					{
						if (cnt == 18) { ani_update = true; cnt = frameX = 0; break; }
						Mobimage->setFrameY(frameY = 0);
						Mobimage->setFrameX(frameX);
						frameX++;
						if (frameX >= 2) frameX = 0;
					}
				}
				break;

			case M_MOVE:
				if (M_rl == M_RIGHT)
				{
					if (cnt == 0 || cnt == 9 || cnt == 20 || cnt == 26 || cnt == 34)
					{
						if (cnt == 34) { ani_update = true; cnt = frameX = 0; break; }
						Mobimage->setFrameY(frameY = 6);
						Mobimage->setFrameX(frameX);
						frameX++;
						if (frameX >= 4) frameX = 0;
					}
				}
				else if (M_rl == M_LEFT)
				{
					if (cnt == 0 || cnt == 9 || cnt == 20 || cnt == 26 || cnt == 34)
					{
						if (cnt == 34) { ani_update = true; cnt = frameX = 0; break; }
						Mobimage->setFrameY(frameY = 1);
						Mobimage->setFrameX(frameX);
						frameX++;
						if (frameX >= 4) frameX = 0;
					}
				}
				break;

			case M_JUMP:
				if (M_rl == M_RIGHT)
				{
					frameY = 7;
				}
				else if (M_rl == M_LEFT)
				{
					frameY = 2;
				}
				break;
			}
		}
		if (knockback != 0.0f)
		{
			if (knockback > 0.0f)
			{
				knockback -= 0.2f;
				if (knockback <= 0.0f)
				{
					ani_update = true;
					knockback = 0.0f;
				}
			}
			else if (knockback < 0.0f)
			{
				knockback += 0.2f;
				if (knockback >= 0.0f)
				{
					ani_update = true;
					knockback = 0.0f;
				}
			}
		}

		aggro <= 0 ? aggro = 0 : aggro--;

		cnt++;

		gra += 0.2f;
		y += gra - jump_power;
		spdKnockback = spd + knockback;
		x += spdKnockback;

		//못지나감
		if (x > maxX - 3.0f && maxX != 0.0f)
		{
			x = maxX - 3.0f;
			setRL(M_LEFT);
		}
		if (x < minX + 3.0f && minX != 0.0f)
		{
			x = minX + 3.0f;
			setRL(M_RIGHT);
		}

		MobRect = RectMakeCenter(x, y - 25, 40, 40);
	}
	else
	{
		M_smja = M_DEAD;
		if (cnt > 0)
		{
			cnt = frameX = 0;
		}
		_hpbarVisible = false;
		dead();
	}
}

void ZombieMushroom::render()
{
	Mobimage->alpha_frameRender(getMemDC(), x - IMAGEMANAGER->findImage(mobName)->getFrameWidth() / 2, y - 78, frameX, frameY, alpha);

	if (KEYMANAGER->isToggleKey('1'))
	{
		HPEN Pen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
		HPEN oPen = (HPEN)SelectObject(getMemDC(), Pen);
		Rectangle(getMemDC(), MobRect);
		SelectObject(getMemDC(), oPen);
		DeleteObject(Pen);
	}
	if (_hpbarVisible) _hpbar->render();
}

void ZombieMushroom::dead()
{
	hp = -100;

	string ItemDrop_NameList[] = { "죽부", "고목나무스태프", "가니어", "왕푸", "워보우", "파란포션"};
	int ItemDrop_ProList[] = { 50, 10, 10, 10, 10, 100 };
	int ItemDrop_addList[] = { 1, 200 , 200, 200, 200, 1};

	if (M_rl == M_RIGHT)
	{
		if (cnt == 0 || cnt == -9 || cnt == -18)
		{
			if (cnt == 0) //아이템뿌리기
			{
				for (int i = 0; i < sizeof(ItemDrop_ProList) / sizeof(ItemDrop_ProList[0]); i++)
				{
					if (RND->getInt(100) < ItemDrop_ProList[i])
					{
						_itemManager->itemDrop(ItemDrop_NameList[i], ItemDrop_addList[i], x, y);
					}
				}
			}
			Mobimage->setFrameY(frameY = 9);
			Mobimage->setFrameX(frameX);
			frameX++;
			if (frameX >= 2) frameX = 2;
		}
	}
	else if (M_rl == M_LEFT)
	{
		if (cnt == 0 || cnt == -9 || cnt == -18)
		{
			if (cnt == 0) //아이템뿌리기
			{
				for (int i = 0; i < sizeof(ItemDrop_ProList) / sizeof(ItemDrop_ProList[0]); i++)
				{
					if (RND->getInt(100) < ItemDrop_ProList[i])
					{
						_itemManager->itemDrop(ItemDrop_NameList[i], ItemDrop_addList[i], x, y);
					}
				}
			}
			Mobimage->setFrameY(frameY = 4);
			Mobimage->setFrameX(frameX);
			frameX++;
			if (frameX >= 2) frameX = 2;
		}
	}
	if (frameX >= 2 && alpha > 0 && dead_cnt == 0)
	{
		alpha -= 5;
	}
	if (alpha <= 0)
	{
		dead_cnt++;
	}
	if (dead_cnt >= 600)
	{
		x = spawnX;
		y = spawnY;
		frameX = frameY = 0;
		alpha += 5;
	}
	if (alpha >= 255 && dead_cnt >= 600)
	{
		dead_cnt = cnt = aggro = 0;
		alpha = 255;
		hp = 600;
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
		return;
	}
	cnt--;
}