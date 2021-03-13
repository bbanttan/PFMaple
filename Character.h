#pragma once
#include "gameNode.h"
#include "damage.h"
#include "Item.h"

//전직업 공격스킬헤더
#include "chobo.h"
#include "warrior.h"
#include "thief.h"
#include "archer.h"
#include "magic.h"

#include "Bullet.h"

#include "charEffect.h"

#define ACCNACC 0.2f	//가감속상수
#define JUMPACC 0.2f	//점프가감속상수
#define MAXSPD 2.0f		//최대속력상수
#define GRAVITY 0.4f	//중력상수
#define JUMP_POWER 8.0f //점프력
#define C_WIDTH 12.0f	//캐릭터 폭길이
#define C_HEIGHT 29.0f	//캐릭터 높이

class Map;
class MobManager;
class Character;
class Inventory;

//상태패턴
enum CharacterState
{
	RIGHT,		//오른쪽방향일때
	LEFT,		//왼쪽방향일때
	WALK ,		//걷는중일때
	JUMP,		//점프중일때
	ATTACK,		//공격중일때
	STANDING,	//가만히있을때
	LADDERROPE,	//메달려있을때
	DEAD		//죽을때
};

class Character : public gameNode
{
private:
	/*               변수선언부                */

	float
		x,				//캐릭터 x축
		y,				//캐릭터 y축
		hp,				//캐릭터 hp
		mp,				//캐릭터 mp
		mhp,			//캐릭터 맥스 hp
		mmp,			//캐릭터 맥스 hp
		spd,			//캐릭터 가감속
		gravity,		//캐릭터 중력
		error_hp,		//캐릭터 hp 비례제어 변수
		error_mp,		//캐릭터 mp 비례제어 변수
		jump_power,		//캐릭터 점프력
		correctionX,	//캐릭터 머리 보정값
		correctionY;	//캐릭터 머리 보정값
		 
	int 
		cnt,			//애니메이션 인터발
		STR,			//캐릭터힘
		who,			//어떤 몬스터를 타격했느냐 변수
		temp,			//가장가까운 몬스터의 거리를 담는 변수
		alpha,			//캐릭터 알파값
		frame,			//캐릭터 애니메이션 프레임
		hitcnt,			//피격했을때 얼마나 무적상태인가 인터벌
		attackPattern;	//랜덤 공격모션 3가지

	bool 
		hit,				//몬스터에게 피격받은 관련 변수1						
		loop,				//애니메이션 루프(ex, 서있을때 0-1-2-1-0)
		knock,				//몬스터에게 피격받은 관련 변수2
		medal,				//메달려있는가 변수
		collision_portal,	//포탈과 닿았는가 변수
		left_isOnceKeyUp,	//왼쪽키 눌렀다 때는거 체크
		right_isOnceKeyUp,	//오른키 눌렀다 때는거 체크
		left_isOnceKeyDown,	//왼쪽키 누른거 한번만체크
		left_isStayKeyDown,	//왼쪽키 계속누르는거 체크	
		right_isOnceKeyDown,//오른키 누른거 한번만체크
		right_isStayKeyDown //오른키 계속누르는거 체크		
		;

	/*------------변수 선언부 끝-------------*/

	/*          렉트 선언부          */

	RECT
		head,						//렉트 머리
		body,						//렉트 캐릭터 몸
		collision_ropeladder;		//캐릭터와 닿은 사다리 렉트

	/*--------렉트 선언부 끝----------*/


	/*          클래스 선언부        */

	Map* map;						//맵 클래스 선언	 (전방선언 되어있음)
	damage* dmg;					//데미지 띄우는 데미지클래스	
	Character* c;					//자기자신 선언 (전방선언 되어있음)
	chobo* _chobo;					//직업 : 초보 선언
	thief* _thief;					//직업 : 도적 선언
	magic* _magic;					//직업 : 마법사 선언	
	MobManager* MM;					//몹매니저 선언 (전방선언 되어있음)
	charEffect* eft;				//캐릭터 스킬이펙트
	Bullet* _bullet;				//표창, 화살관련 클래스 선언
	archer* _archer;				//직업 : 궁수 선언
	warrior* _warrior;				//직업 : 전사 선언
	Inventory* _inven;
	Item* CurrentEquit;				//현재무기
	image* character_img;			//캐릭터 몸통이미지
	image* character_head;			//캐릭터 머리이미지	

	/*--------클래스 선언부 끝------*/

	string _job;
	
	/*          캐릭터 상태관련 enum 선언부         */

	CharacterState RL;		//방향의 상태를 저장하는 이넘문
	CharacterState WJASL;	//행위의 상태를 저장하는 이넘문

	/*--------캐릭터 상태관련 enum 선언부 끝---------*/

public:

	Character() {};
	~Character() {};

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void accNacc();				//가감속함수
	virtual void Landing();				//땅벽 함수
	virtual void anime();				//캐릭터 애니메이션 함수
	virtual void aggro();				//캐릭터에대한 몬스터 어그로함수
	virtual void blow();				//캐릭터가 타격받았을때 함수

	
	/*              get 함수모음               */

	float getX() { return x; }
	float getY() { return y; }
	int getSTR() { return STR; }
	int getWho() { return who; }
	int getTemp() { return temp; }
	float getMHP() { return mhp; }
	float getMMP() { return mmp; }
	RECT getRECT() { return body; }
	string getJob() { return _job; }
	void setCx(float cx) { x = cx; }
	void setCy(float cy) { y = cy; }
	float getHP() { return error_hp; }
	float getMP() { return error_mp; }
	CharacterState getRL() { return RL; }
	Item* getEquit() { return CurrentEquit; }
	void getMyAdress(Character* _c) { c = _c; }
	CharacterState getWJASL() { return WJASL; }	

	/*-------------get 함수모음 끝-------------*/

	/*              set 함수모음               */

	void setHIT() { knock = true; }
	void setWho(int _who) { who = _who; }
	void setCharacterImage(string _wname);
	void setTemp(int _temp) { temp = _temp; }
	void setSTR(int _setSTR) { STR = _setSTR; }
	void setMapAdress(Map* _map) { map = _map; }
	void setMapAdress(MobManager* _mm) { MM = _mm; }
	void setEquit(Item* _item) { CurrentEquit = _item; }
	void setPortal_Collision() { collision_portal = true; } //포탈과 밧줄이 맞닿아있을때 맵을변경할때 캐릭터위치가 이상해 지는거 방지
	void setInventoryAdress(Inventory* inven) { _inven = inven; }
	void setLadderRope(RECT rect) { collision_ropeladder = rect; }
	void setAddHpMp(int _addHP, int _addMP) { hp += _addHP; mp += _addMP; }
	
	/*-------------set 함수모음 끝-------------*/
};

