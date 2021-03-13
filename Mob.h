#pragma once
#include "gameNode.h"
#include "Hpbar.h"
#include "MobEffect.h"
#include "Junior_fireball.h"

class Character;
class ItemManager;

enum MobType
{
	NORMAL,
	BOSS
};

enum MobState
{
	M_RIGHT,
	M_LEFT,
	M_STANDING,
	M_MOVE,
	M_JUMP,
	M_HIT,
	M_ATTACK,
	M_DEAD
};

class Mob : public gameNode
{
protected:

	MobEffect* eft;
	Junior_fireball* junior_fire;

	Character* cha;

	ItemManager* _itemManager;

	image* Mobimage;

	Hpbar* _hpbar;

	float x, y;			//몹의 x,y 축
	float spawnX, spawnY;
	string mobName;
	int hp, mhp;		//체력
	int spd;			//몹 이동속도
	int cnt;			//애니메이션 인터벌
	int random_state;	//랜덤상태
	int frameX, frameY;	//애니메이션 프레임
	int dead_cnt;		//몹이죽었을때 다시 리스폰되는 인터벌
	int alpha;			//몹알파값
	MobType type;		//일반몹, 보스몹
	int aggro;			//캐릭터가 때렸을때 어그로 (일반몹에서만)
	bool jump_ok;		//점프여부
	bool ani_update;	//애니메이션 프레임이 끝부분이라는 신호
	bool hit;
	bool _hpbarVisible;
	bool pause;
	float gra;			//점프하는 몹만 중력on
	float jump_power;	//점프하는 몹만 on
	float knockback;	//몹 넉백
	float minX, maxX;	//최소로 이동가능한 X반경과 최대 X반경	
	float plusDamageY;	
	float spdKnockback;

	int rnd_update;		//새로운동작이 될 확률
	int rnd_stand;		//가만히있을 확률
	int rnd_right;		//오른쪽으로 갈 확률
	int rnd_left;		//왼쪽으로 갈 확률
	int rnd_jump;		//점프할 확률
	int damage;
	int isExist;

	float TEST;

	RECT MobRect;

	MobState M_rl;		//몹이 보는방향상태
	MobState M_smja;	//몹의 행위상태

public:
	Mob() {};
	~Mob() {};

	virtual HRESULT init(const char* imageName, POINT pos);
	virtual void release();
	virtual void update();
	virtual void render();

	float getX() { return x; }
	float getY() { return y; }
	void setX(float setx) { x = setx; }
	void setY(float sety) { y = sety; }
	void setSpawnY(float sety) { spawnY = sety; }
	void setGRA() { gra = 0.0f; }
	MobState getRL() { return M_rl; }
	MobState getSMJA() { return M_smja; }
	MobType getType() { return type; }
	float getGRA() { return gra; }
	int getAggro() { return aggro; }
	float getminX() { return minX; }
	float getmaxX() { return maxX; }
	void setminX() { minX = x; }
	void setmaxX() { maxX = x; }
	void set_aniUpdate() { ani_update = true; rnd_update = 100; }
	float getJP() { return jump_power; }
	void setJP() { jump_power = 0.0f; cnt = frameX = 0; }
	void setRnd(float infoX, float infoY);
	void setRL(MobState setrl);
	void setHIT(MobState direction, float _plusDamgeY, int _damage);
	bool getHit() { return hit; }
	int getHP() { return hp; }
	void setFalseHit() { hit = false; }
	RECT getRECT() { return MobRect; }
	image* getImage() { return Mobimage; }
	bool getJumpOk() { return jump_ok; }
	float getPlusDamageY() { return plusDamageY; }
	void setPlusDamageY(float _setY) { plusDamageY = _setY; }
	void setCharAdress(Character* c) { cha = c; }
	void setItemManagerAdress(ItemManager* _iM) { _itemManager = _iM; }
	int getDMG() { return damage; }
	float getspdKnockback() { return spdKnockback; }
	void setExist(bool _set) { isExist = _set; }
	bool getExist() { return isExist; }
};

