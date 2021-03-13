#include "stdafx.h"
#include "Character.h"
#include "Map.h"
#include "MobManager.h"
#include "Inventory.h"

HRESULT Character::init()
{
	_chobo = new chobo;
	_warrior = new warrior;
	_thief = new thief;
	_archer = new archer;
	_magic = new magic;

	eft = new charEffect;
	eft->init();

	_bullet = new Bullet;
	_bullet->init();

	dmg = new damage;
	dmg->init();

	//캐릭터 체력, 마나, 체력마나 비례제어 변수선언
	hp = mhp = error_hp = 50.0f;
	mp = mmp = error_mp = 200.0f;

	//애니메이션 인터발
	cnt = hitcnt = correctionX = correctionY = attackPattern = 0;

	//애니메이션 루프
	loop = knock = false;

	//캐릭터 최초 게임실행시 좌표지정
	x = 214.1;
	y = 1026.7;

	//
	temp = 10000;
	who = -1;

	alpha = 255;

	//중력과 점프할때 점프력 0으로 초기화
	gravity = jump_power = 0.0f;

	//상태패턴초기화
	RL = RIGHT;
	WJASL = STANDING;

	//캐릭터 이미지불러오기
	character_img = new image;
	character_img->init("이미지/캐릭터/초보자캐릭터.bmp", 456, 1460, 4, 20, true, RGB(0, 255, 0));
	character_img->setFrameY(10);
	
	IMAGEMANAGER->addFrameImage("전사", "이미지/캐릭터/전사캐릭터.bmp", 456, 1460, 4, 20, true, RGB(0, 255, 0));
	IMAGEMANAGER->addFrameImage("도적", "이미지/캐릭터/도적캐릭터.bmp", 456, 1460, 4, 20, true, RGB(0, 255, 0));
	IMAGEMANAGER->addFrameImage("궁수", "이미지/캐릭터/궁수캐릭터.bmp", 456, 1460, 4, 20, true, RGB(0, 255, 0));
	IMAGEMANAGER->addFrameImage("마법사", "이미지/캐릭터/마법사캐릭터.bmp", 456, 1460, 4, 20, true, RGB(0, 255, 0));
	IMAGEMANAGER->addFrameImage("초보자", "이미지/캐릭터/초보자캐릭터.bmp", 456, 1460, 4, 20, true, RGB(0, 255, 0));

	character_head = new image;
	character_head->init("이미지/캐릭터/머가리들.bmp", 320, 138, 5, 3, true, RGB(0, 255, 0));
	character_head->setFrameY(0);
	character_head->setFrameX(0);

	CurrentEquit = new Item;
	CurrentEquit->init("검");

	STR = CurrentEquit->getSTR();

	_job = "초보자";

	return S_OK;
}

void Character::release()
{

}

void Character::update()
{
	left_isOnceKeyDown  = KEYMANAGER->isOnceKeyDown(VK_LEFT);
	left_isStayKeyDown  = KEYMANAGER->isStayKeyDown(VK_LEFT);
	left_isOnceKeyUp    = KEYMANAGER->isOnceKeyUp(VK_LEFT);
	right_isOnceKeyDown = KEYMANAGER->isOnceKeyDown(VK_RIGHT);
	right_isStayKeyDown = KEYMANAGER->isStayKeyDown(VK_RIGHT);
	right_isOnceKeyUp   = KEYMANAGER->isOnceKeyUp(VK_RIGHT);

	if (error_hp != hp)
	{
		error_hp += (hp - error_hp) * 0.2f;
	}
	if (error_mp != mp)
	{
		error_mp += (mp - error_mp) * 0.2f;
	}
	if (hp >= mhp) hp = mhp;
	if (hp <= 0)   hp = 0;
	if (mp >= mmp) mp = mmp;
	if (mp <= 0)   mp = 0;

	if(WJASL != ATTACK)
	{
		if (right_isOnceKeyDown && medal == false)					//오른쪽키 한번만 누름체크가 ㄹㅇ일때
		{		
			RL = RIGHT;												//방향상태를 RIGHT
			cnt = 0;												//애니메이션 인터발 0
			frame = 0;												//애니메이션 프레임 0
			loop = false;											//애니메이션 자동반복 FALSE
		}
		if (left_isOnceKeyDown && medal == false)					//왼쪽키 한번만 누름체크가 ㄹㅇ일때
		{		
			RL = LEFT;												//방향상태를 RIGHT
			cnt = 0;												//애니메이션 인터발 0
			frame = 0;												//애니메이션 프레임 0
			loop = false;											//애니메이션 자동반복 FALSE
		}

		if (right_isStayKeyDown)								    //오른쪽키
		{												
			if (WJASL != JUMP && medal == false)	WJASL = WALK;
		}
		if (left_isStayKeyDown)										//왼쪽키
		{												
			if (WJASL != JUMP && medal == false)	WJASL = WALK;
		}

		//스탠딩이 되는 조건들
		if ((right_isOnceKeyUp || left_isOnceKeyUp) && medal == false)
		{

			if (left_isStayKeyDown || right_isStayKeyDown)
			{
				if (left_isStayKeyDown)  RL = LEFT;
				if (right_isStayKeyDown) RL = RIGHT;
				WJASL = WALK;
			}
			else
			{
				cnt = 0;
				frame = 0;
				loop = false;
				WJASL = STANDING;
			}
		}

		//로프 사다리(캐릭터와 닿은 사다리의 렉트)와 닿았을때
		if ((body.right > collision_ropeladder.left && body.left < collision_ropeladder.right &&
			body.top < collision_ropeladder.bottom && body.bottom > collision_ropeladder.top)&&
			collision_portal == false)
		{
			//땅은 계속 작용하는데 만약 올라가다가 땅과 만나면 거기서 막히기때문에
			//사다리의 렉트 top으로 부터 렉트전체길이의 0.2배 정도되는 길이를 더한 그 y축에 도달했을때
			//땅에 닿지않게하기위한 변수
			float downkey_possible = 
				collision_ropeladder.top + (collision_ropeladder.bottom - collision_ropeladder.top) * 0.2f;
			
			//메달려있음이 참일때
			if (medal)
			{
				//땅에 닿는조건인 gravity >= jump_power, downkey_possible < y 캐릭터y축이 저 변수보다 클때 즉, 아래에있을떄
				//는 땅에 닿게하기위해 gravity = 0.0f 으로 하고
				//반대로는 땅에 닿게하지 않기위해 gravity = -1.0f 으로함
				if (downkey_possible < y)		gravity = 0.0f;	 
				else if (downkey_possible > y)  gravity = -1.0f;

				if (KEYMANAGER->isStayKeyDown(VK_UP))
				{
					y -= 2;
					cnt++;	//애니메이션 인터발
				}
				else if (KEYMANAGER->isStayKeyDown(VK_DOWN))
				{
					y += 2;
					cnt++;
				}
				if (KEYMANAGER->isOnceKeyDown(VK_SPACE))	//사다리에서 점프하고자 할때
				{
					if (left_isStayKeyDown)
					{
						spd = -MAXSPD;
						RL = LEFT;
						medal = false;
						jump_power = 3.0f;
					}
					if (right_isStayKeyDown)
					{
						spd = MAXSPD;
						RL = RIGHT;
						medal = false;
						jump_power = 3.0f;
					}
				}
			}

			//메달려있음이 거짓일때 윗키나 아랫키를 눌렀을때
			if (((KEYMANAGER->isStayKeyDown(VK_UP) && downkey_possible < y) || (KEYMANAGER->isStayKeyDown(VK_DOWN) && downkey_possible > y)) && medal == false)
			{
				medal = true;				//메달림을 true로 만든다.
				spd = jump_power = 0.0f;	//가속, 점프력 0으로 초기화
				gravity = -1.0f;			//땅 안닿게하려고
				cnt = frame = 0;			//인터벌, 프레임 0
				x = collision_ropeladder.left + ((collision_ropeladder.right - collision_ropeladder.left)/2);
				//사다리가운데에 캐릭터의 x축을 고정시킨다.
			}	
		}
		else
		{
			medal = false;
		}

		//점프
		if (KEYMANAGER->isStayKeyDown(VK_SPACE) && WJASL != JUMP && jump_power == 0.0f && medal == false)
		{
			jump_power = JUMP_POWER;
		}

		//gravity가 0보다 커질때 상태를 점프상태로 바꾼다.
		if (gravity > 0.0f)
		{
			WJASL = JUMP;
		}
	}
	//공격(Z키)
	if (KEYMANAGER->isStayKeyDown(0x5A) && WJASL != ATTACK && medal == false)
	{	
		if ((_job == "전사" && mp > _warrior->getNeedMP()) || (_job == "마법사" && mp > _magic->getNeedMP()) ||
			(_job == "도적" && mp > _thief->getNeedMP()) || (_job == "궁수" && mp > _archer->getNeedMP()) || (_job == "초보자"))
		{
			WJASL = ATTACK;
			attackPattern = RND->getInt(3) + 1;
			cnt = frame = 0;

			if (_job == "초보자") _chobo->Mob_Search(c, MM);
			if (_job == "전사") _warrior->Mob_Search(c, MM, map, eft);
			if (_job == "마법사") _magic->Mob_Search(c, MM, map, eft);
			if (_job == "도적")
			{
				_thief->setSx(x);
				_thief->setSy(y - 20);
				_thief->Mob_Search(c, MM, eft);
			}
			else if (_job == "궁수")
			{
				_archer->setSx(x);
				_archer->setSy(y - 20);
				_archer->Mob_Search(c, MM);
			}
		}
	}

	//감속함수
	accNacc();

	x += spd;
	if(medal == false) gravity += GRAVITY;

	//중력 종단속도 설정해주는 구문
	if ((gravity - jump_power) >= 7.0f) { gravity = 7.0f; jump_power = 0.0f; }

	//투명땅 함수
	Landing();

	//모든 애니메이션
	anime();

	//몹이 캐릭터 따라옴
	aggro();

	//피격데미지띄우는거
	blow();

	eft->update();

	//슬래시블러스트
	if (_job == "전사") _warrior->update();

	//매직클로
	if (_job == "마법사") _magic->update();

	//럭키세븐
	if(_job == "도적" || _job == "궁수") _bullet->update();

	hitcnt != 0 ? hitcnt-- : hit = false;
	hitcnt != 0 ? alpha = 150 : alpha = 255;

	//데미지업데이트
	dmg->update();

	y += (gravity - jump_power)*(medal == false);

	body = RectMakeCenter(x, y, C_WIDTH, C_HEIGHT);

	if (collision_portal == true) collision_portal = false;
}

void Character::render()
{
	if (KEYMANAGER->isToggleKey('1'))
	{
		HPEN Pen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
		HPEN oPen = (HPEN)SelectObject(getMemDC(), Pen);

		Rectangle(getMemDC(), body);
		RectangleMakeCenter(getMemDC(), x, y - 37, 39, 37);

		SelectObject(getMemDC(), oPen);
		DeleteObject(Pen);
	}
	
	if ((WJASL == JUMP || WJASL == ATTACK) && medal == false)
	{
		character_head->alpha_frameRender(getMemDC(),
			x - (character_head->getFrameWidth() / 2) + ((RL==LEFT) * -(3.0f)) + ((RL == RIGHT) * (3.0f)) + correctionX,
			y - 62 + correctionY, alpha);
	}
	character_img->alpha_frameRender(getMemDC(), x - (character_img->getFrameWidth()/2), y - 49, alpha);
	if (WJASL == STANDING || WJASL == WALK || medal == true)
	{
		character_head->alpha_frameRender(getMemDC(),
			x - (character_head->getFrameWidth() / 2) + ((RL == LEFT) * -(3.0f) * ((medal==false) + (medal)*0)) + ((RL == RIGHT) * (3.0f) * ((medal==false) + (medal) * 0)),
			y - 60 + correctionY, alpha);
	}
	dmg->render();
	if(_job == "전사") _warrior->render();
	if(_job == "도적" || _job == "궁수") _bullet->render();
	eft->render();
}

//감속 함수
void Character::accNacc()
{
	if (RL == RIGHT && right_isStayKeyDown && medal == false)
	{
		spd += ACCNACC * (((gravity > 0.0f) * JUMPACC) + ((gravity == 0.0f) * 1.0f));
		if (spd >= MAXSPD) spd = MAXSPD;
	}
	if (RL == LEFT && left_isStayKeyDown && medal == false)
	{
		spd -= ACCNACC * (((gravity > 0.0f) * JUMPACC) + ((gravity == 0.0f) * 1.0f));
		if (spd <= -MAXSPD) spd = -MAXSPD;
	}
	if (spd != 0.0f && WJASL != WALK && WJASL != JUMP)
	{
		if (spd > 0.0f)
		{
			spd -= ACCNACC * (((gravity > 0.0f) * JUMPACC) + ((gravity == 0.0f) * 2.0f));
			if (spd <= 0.0f) spd = 0.0f;
		}
		else if (spd < 0.0f)
		{
			spd += ACCNACC * (((gravity > 0.0f) * JUMPACC) + ((gravity == 0.0f) * 2.0f));
			if (spd >= 0.0f) spd = 0.0f;
		}
	}
}

//땅닿음 함수
void Character::Landing()
{
	char str[128];
	sprintf_s(str, "%s투명땅", map->getCurrentMap());

	//-2 +2 는 점프력보다 작아야함. 안그럼 점프가 안됨
	if (jump_power <= gravity)
	{
		for (int i = ((int)y + (C_HEIGHT / 2)) - 4; i < ((int)y + (C_HEIGHT / 2)) + 4; ++i)
		{
			COLORREF landColor = GetPixel(IMAGEMANAGER->findImage(str)->getMemDC(), x, i);

			int r = GetRValue(landColor);
			int g = GetGValue(landColor);
			int b = GetBValue(landColor);

			if (r == 255 && g == 0 && b == 255)
			{
				if (gravity > GRAVITY)
				{
					if (WJASL != ATTACK) WJASL = STANDING;
					jump_power = 0.0f;
				}
				if (medal)	//메달려있다가 딱 땅에 이제막 닿은경우
				{
					if (right_isStayKeyDown)	 RL = RIGHT;
					else if (left_isStayKeyDown) RL = LEFT;
					WJASL = STANDING;
					cnt = frame = 0;
					loop = false;
				}

				medal = false;
				gravity = 0.0f;
				y = (float)i - (C_HEIGHT / 2);

				break;
			}
		}
	}
	//벽
	COLORREF wallColor = GetPixel(IMAGEMANAGER->findImage(str)->getMemDC(), x + ((RL == RIGHT)*(C_WIDTH/2)) + ((RL == LEFT)*(-C_WIDTH / 2)), y);

	if (GetRValue(wallColor) == 0 && GetGValue(wallColor) == 0 && GetBValue(wallColor) == 255)
	{
		spd = 0.0f;
		x = x + ((RL == RIGHT)*(-1)) + (RL == LEFT);
	}
}

//애니메이션
void Character::anime()
{
	if (RL == RIGHT && medal == false)
	{
		character_head->setFrameY(0);
		//오른쪽 스탠딩 이미지
		if (WJASL == STANDING)
		{
			character_img->setFrameY(10);

			correctionY = 0;		 //머리 보정값

			if (!(cnt % 40))
			{
				cnt = 0;
				character_img->setFrameX(frame);
				frame = frame + (loop == false) + ((loop == true) * -1);
				if (frame >= 2 || frame == 0)
				{
					loop = !loop;
				}
			}
		}
		if (WJASL == WALK)	//오른쪽 걷는 이미지
		{
			character_img->setFrameY(12);

			if (!(cnt % 9))
			{
				cnt = 0;
				character_img->setFrameX(frame);

				if (frame == 0)correctionY = -1;	 //머리 보정값
				if (frame == 1)correctionY = 0;		 //머리 보정값
				if (frame == 2)correctionY = -1;	 //머리 보정값
				if (frame == 3)correctionY = 0;		 //머리 보정값

				frame++;
				
				if (frame >= 4)
				{
					frame = 0;
				}
			}
		}
		if (WJASL == JUMP) //오른쪽 점프이미지
		{
			correctionY = 0;
			correctionX = 0;
			character_img->setFrameY(18);
			character_img->setFrameX(0);
		}
		if (WJASL == ATTACK)	//오른쪽 공격이미지
		{
			if (cnt == 0 || cnt == 15 || cnt == 23 || cnt == 41)
			{
				if(cnt == 23)
				{
					//만약 for문을 다 돌았고 몬스터가 사정권내에 있을때 힛트를 활성화
					if (_job == "초보자") _chobo->Mob_Knock(c, MM, map);
					if (_job == "전사")  _warrior->setCnt(); 
					if (_job == "마법사")  _magic->setCnt();
					if (_job == "도적")
					{
						float angle;
						for (int i = 0; i < 2; i++)
						{
							if (who != -1)
								angle = getAngle(_thief->getSx(), _thief->getSy() + 20, MM->_getvMob()[who]->getX(), MM->_getvMob()[who]->getY());
							else
								angle = 0.0f;
							angle = angle + ((-0.5 * (PI / 180)) * i);

							_bullet->Throw(_thief->getSx() - (i * 50), _thief->getSy(), angle, 1, who, c, MM, -15.0f*((1 - i) - i), _job, eft);
						}
						who = -1;
						temp = 10000;
					}
					if (_job == "궁수")
					{
						float angle;
						for (int i = 0; i < 2; i++)
						{
							if (who != -1)
								angle = getAngle(_archer->getSx(), _archer->getSy() + 20, MM->_getvMob()[who]->getX(), MM->_getvMob()[who]->getY());
							else
								angle = 0.0f;
							angle = angle + ((-0.5 * (PI / 180)) * i);

							_bullet->Throw(_archer->getSx() - (i * 50), _archer->getSy(), angle, 1, who, c, MM, -15.0f*((1 - i) - i), _job, eft);
						}
						who = -1;
						temp = 10000;
					}
				}
				if (cnt >= 41)
				{
					WJASL = STANDING;
					if (right_isStayKeyDown) RL = RIGHT;
					if (left_isStayKeyDown)  RL = LEFT;
					loop = false;
					attackPattern = frame = cnt = correctionX = correctionY = 0;			
					return;
				}

				if (attackPattern == 1)
				{
					character_img->setFrameY(13);
					if (frame == 0 && _job != "궁수") { correctionX = 6.5f; correctionY = 5.8f; }
					if (frame == 1 && _job != "궁수") { correctionX = 3.5f; correctionY = 1.2f; }
					if (frame == 2 && _job != "궁수") { eft->normal_r_1(x + (body.right-body.left)*2 + 10, y - (body.bottom - body.top) / 2 - 10); correctionX = 27.5f; correctionY = 6.8f; }

					if (frame == 0 && _job == "궁수") { correctionY = 0.0f; }
					if (frame == 1 && _job == "궁수") { correctionY = 3.0f; }
					if (frame == 2 && _job == "궁수") { correctionY = 3.0f; }
				}
				else if (attackPattern == 2)
				{
					character_img->setFrameY(14);
					if (frame == 0 && _job != "궁수") { correctionX = 3.3f; correctionY = 5.0f; }
					if (frame == 1 && _job != "궁수") { correctionX = 9.3f; correctionY = 4.0f; }
					if (frame == 2 && _job != "궁수") { eft->normal_r_2(x + (body.right - body.left) * 2 + 10, y - (body.bottom - body.top) / 2 + 5); correctionX = 5.3f; correctionY = 7.0f; }

					if (frame == 0 && _job == "궁수") { correctionY = 0.0f; }
					if (frame == 1 && _job == "궁수") { correctionY = 3.0f; }
					if (frame == 2 && _job == "궁수") { correctionY = 3.0f; }
				}
				else if (attackPattern == 3)
				{
					character_img->setFrameY(15);
					if (frame == 0 && _job != "궁수") { correctionX = -1.7f; correctionY = 0.0f; }
					if (frame == 1 && _job != "궁수") { correctionX = 2.3f; correctionY = 2.0f; }
					if (frame == 2 && _job != "궁수") { eft->normal_r_3(x + (body.right - body.left) * 2, y - (body.bottom - body.top) / 2 + 10); correctionX = 4.3f; correctionY = 5.0f; }

					if (frame == 0 && _job == "궁수") { correctionY = 0.0f; }
					if (frame == 1 && _job == "궁수") { correctionY = 3.0f; }
					if (frame == 2 && _job == "궁수") { correctionY = 3.0f; }
				}

				character_img->setFrameX(frame);
				frame++;
			}
		}
	}
	else if (RL == LEFT && medal == false)	///////////////////왼쪽
	{
		character_head->setFrameY(1);
		if (WJASL == STANDING)	//왼쪽 스탠딩 이미지
		{
			character_img->setFrameY(0);

			correctionY = 0;

			if (!(cnt % 40))
			{
				cnt = 0;
				character_img->setFrameX(frame);
				frame = frame + (loop == false) + ((loop == true) * -1);
				if (frame >= 2 || frame == 0)
				{
					loop = !loop;
				}
			}
		}
		if (WJASL == WALK)	//왼쪽 걷는 이미지
		{
			character_img->setFrameY(2);

			if (!(cnt % 9))
			{
				cnt = 0;
				character_img->setFrameX(frame);

				if (frame == 0)correctionY = -1;	 //머리 보정값
				if (frame == 1)correctionY = 0;		 //머리 보정값
				if (frame == 2)correctionY = -1;	 //머리 보정값
				if (frame == 3)correctionY = 0;		 //머리 보정값

				frame++;
				if (frame >= 4)
				{
					frame = 0;
				}
			}
		}
		if (WJASL == JUMP)	//왼쪽 점프 이미지
		{
			correctionY = 0;
			correctionX = 0;
			character_img->setFrameY(8);
			character_img->setFrameX(0);
		}
		if (WJASL == ATTACK)	//왼쪽 공격이미지
		{
			if (cnt == 0 || cnt == 15 || cnt == 23 || cnt == 41)
			{
				if (cnt == 23)
				{
					//만약 for문을 다 돌았고 몬스터가 사정권내에 있을때 힛트를 활성화
					if (_job == "초보자") _chobo->Mob_Knock(c, MM, map);
					if (_job == "전사") _warrior->setCnt();
					if (_job == "마법사") _magic->setCnt();
					if (_job == "도적" )
					{
						float angle;
						for (int i = 0; i < 2; i++)
						{
							if (who != -1)
								angle = getAngle(_thief->getSx(), _thief->getSy() + 20, MM->_getvMob()[who]->getX(), MM->_getvMob()[who]->getY());
							else
								angle = -180 * (PI / 180);
							angle = angle + ((-0.5 * (PI / 180)) * i);

							_bullet->Throw(_thief->getSx() + (i * 50), _thief->getSy(), angle, -1, who, c, MM, -15.0f*((1 - i) - i), _job, eft);
						}
						who = -1;
						temp = 10000;
					}
					if ( _job == "궁수")
					{
						float angle;
						for (int i = 0; i < 2; i++)
						{
							if (who != -1)
								angle = getAngle(_archer->getSx(), _archer->getSy() + 20, MM->_getvMob()[who]->getX(), MM->_getvMob()[who]->getY());
							else
								angle = -180 * (PI / 180);
							angle = angle + ((-0.5 * (PI / 180)) * i);

							_bullet->Throw(_archer->getSx() + (i * 50), _archer->getSy(), angle, -1, who, c, MM, -15.0f*((1 - i) - i), _job, eft);
						}
						who = -1;
						temp = 10000;
					}
					
				}
				if (cnt >= 41)
				{
					WJASL = STANDING;
					if (right_isStayKeyDown) RL = RIGHT;
					if (left_isStayKeyDown)  RL = LEFT;
					loop = false;
					attackPattern = frame = cnt = correctionX = correctionY = 0;
					return;
				}

				if (attackPattern == 1)
				{
					character_img->setFrameY(3);
					if (frame == 0 && _job != "궁수") { correctionX = -6.5f; correctionY = 5.8f; }
					if (frame == 1 && _job != "궁수") { correctionX = -3.5f; correctionY = 1.2f; }
					if (frame == 2 && _job != "궁수") { eft->normal_l_1(x - (body.right - body.left) * 2 - 10, y - (body.bottom - body.top) / 2 - 10); correctionX = -27.5f; correctionY = 6.8f; }

					if (frame == 0 && _job == "궁수") { correctionY = 0.0f; }
					if (frame == 1 && _job == "궁수") { correctionY = 3.0f; }
					if (frame == 2 && _job == "궁수") { correctionY = 3.0f; }
				}
				else if (attackPattern == 2)
				{
					character_img->setFrameY(4);
					if (frame == 0 && _job != "궁수") { correctionX = -3.3f; correctionY = 5.0f; }
					if (frame == 1 && _job != "궁수") { correctionX = -9.3f; correctionY = 4.0f; }
					if (frame == 2 && _job != "궁수") { eft->normal_l_2(x - (body.right - body.left) * 2 - 10, y - (body.bottom - body.top) / 2 + 5); correctionX = -5.3f; correctionY = 7.0f; }

					if (frame == 0 && _job == "궁수") { correctionY = 0.0f; }
					if (frame == 1 && _job == "궁수") { correctionY = 3.0f; }
					if (frame == 2 && _job == "궁수") { correctionY = 3.0f; }
				}
				else if (attackPattern == 3)
				{
					character_img->setFrameY(5);
					if (frame == 0 && _job != "궁수") { correctionX = 1.7f; correctionY = 0.0f; }
					if (frame == 1 && _job != "궁수") { correctionX = -2.3f; correctionY = 2.0f; }
					if (frame == 2 && _job != "궁수") { eft->normal_l_3(x - (body.right - body.left) * 2, y - (body.bottom - body.top) / 2 + 10); correctionX = -4.3f; correctionY = 5.0f; }

					if (frame == 0 && _job == "궁수") { correctionY = 0.0f; }
					if (frame == 1 && _job == "궁수") { correctionY = 3.0f; }
					if (frame == 2 && _job == "궁수") { correctionY = 3.0f; }
				}

				character_img->setFrameX(frame);
				frame++;
			}
		}
	}
	if (medal)	//메달려있을때
	{
		if ((collision_ropeladder.right - collision_ropeladder.left) >= 36.0f) character_img->setFrameY(6);
		if ((collision_ropeladder.right - collision_ropeladder.left) <= 15.0f) character_img->setFrameY(7);
		
		character_head->setFrameY(2);
		if (RL == RIGHT) correctionX = -4.0f;
		else if (RL == LEFT) correctionX = 4.0f;
		if(cnt>=15) cnt = 0;
		if (!cnt)
		{		
			character_img->setFrameX(frame);
			frame++;
			if (frame >= 2) frame = 0;	
		}	
	}
	if(medal == false) cnt++;
}

//디스오더
void Character::aggro()
{
	for (int i = 0; i < MM->_getvMob().size(); ++i)
	{
		if (MM->_getvMob()[i]->getAggro() == 0 || MM->_getvMob()[i]->getType() == BOSS) continue;

		//몹이 캐릭터보다 오른쪽에 있을때 즉, 몹이 왼쪽으로 이동해야할때, 왼쪽으로 이동하니까 minX(최소 이동반경 범위)
		//이 아직 정해지지 않았을땐 일단 그대로 따라오고, 가다가 gra(중력값)에 변화가생기면 그때 minX의 값이 정해진다
		//그렇다면 이 조건에선 (MM->_getvMob()[i]->getminX() == 0.0f || 이 성립되지않는다.
		//그렇다면 그 옆에있는 조건이 발동되는데 현재 minX이 0.0이 아니고 현재 몹의 x축이 최소반경보다 클때 참으로 한다.
		//이렇게하면 만약 x축이 최소반경보다 작아질때 (넘어설때) 거짓이 되므로 몹이 어그로가 끌려있고 캐릭터가 아직 왼쪽에있을떄
		//몹이 땅끝에서 박혀있는 현상을 없앨수있다.(핵심 사실 이것땜에 ..)
		if (MM->_getvMob()[i]->getX() > x && (MM->_getvMob()[i]->getminX() == 0.0f || (MM->_getvMob()[i]->getminX()!=0.0f && MM->_getvMob()[i]->getX() > MM->_getvMob()[i]->getminX()+3.0f)))
		{
			MM->_getvMob()[i]->setRnd(x, y);
		}
		else if (MM->_getvMob()[i]->getX() < x && (MM->_getvMob()[i]->getmaxX() == 0.0f || (MM->_getvMob()[i]->getmaxX()!=0.0f && MM->_getvMob()[i]->getX() < MM->_getvMob()[i]->getmaxX()-3.0f)))
		{
			MM->_getvMob()[i]->setRnd(x, y);
		}
	}
}

void Character::blow()
{
	if (hit == false)
	{
		for (int i = 0; i < MM->_getvMob().size(); ++i)
		{
			if (MM->_getvMob()[i]->getHP() <= 0) continue;
			RECT temp;
			if ((IntersectRect(&temp, &body, &MM->_getvMob()[i]->getRECT())) || knock)
			{
				dmg->create_damage(x, y, 30, false);
				(MM->_getvMob()[i]->getX() > x) ? spd = -3.0f : spd = 3.0f;
				
				hp -= 3;
				knock = false;
				jump_power = 3.0f;
				hitcnt = 100;
				hit = true;
				break;
			}
		}
	}
	else
	{
		knock = false;
	}
}

void Character::setCharacterImage(string _wname)
{
	_job = _wname;
	character_img = IMAGEMANAGER->findImage(_wname);
	if (_wname == "초보자") character_head->setFrameX(0);
	else if (_wname == "전사") character_head->setFrameX(4);
	else if (_wname == "도적") character_head->setFrameX(2);
	else if (_wname == "궁수") character_head->setFrameX(3);
	else if (_wname == "마법사") character_head->setFrameX(1);
}
