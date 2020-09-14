#pragma once
#include "gameNode.h"
#include "enemyManager.h"
#include "playerManager.h"

enum tagEnemyState
{
	ENEMY_STAY,
	ENEMY_PATROL,
	ENEMY_ATTACK,
	ENEMY_ATTACK02,
	ENEMY_CHASE,
	ENEMY_DEAD,
	ENEMY_NONACTIVE,
	ENEMY_JUMPENEMY,
	ENEMY_DELAY
};

struct tagEnemy
{
	tagEnemyState _enemyState;
	tagEnemyState _enemyLastState;

	float _chaseX;				// 쫓고 있는 대상 마지막 위치 
	RECT _rec;					// 몬스터의 위치 및 피격판정
	float _speed;
	int _minX, _maxX;			// 몬스터의 활동 범위
	int _frameIndex;
	int _frameCount;
	int _chaseCount;			// 쫓고 있는지 얼마나 됬는지 파악하기 위함

	float _viewRange;			// 탐색 범위
	float _attackRange;			// 공격 범위
	RECT _attackRc;
	RECT _rangeRc;

	image* _enemyimg;			//적 이미지

	int _frameX;				//프레임X 
	int _frameY;				//프레임Y
	bool _isLeft;				//프레임Y
	bool _isCollsion;
	bool _attackRangeCollsion;

	string _imgkeyName;
	int _initX, _initY;			//적 초기 위치
	float _ptX;					//위치
	int _hp;					//적 hp
	int _atk;					//적 공격력
};

class enemyMob :
	public gameNode
{
private:

protected:
	tagEnemy _enemy;
	enemyManager* _enemyMg;
	playerManager* _playerMg;
public:
	const char*		_enemyStateToString[8] = { "ENEMY_IDLE", "ENEMY_PATROL", "ENEMY_ATTACK", "ENEMY_CHASE", "ENEMY_DEAD", "ENEMY_NONACTIVE", "ENEMY_JUMPENEMY" };

	virtual HRESULT init() { return S_OK; }
	virtual void release() {};
	virtual void update() {};
	virtual void render() {};

	virtual void idle() {};
	virtual void chase() {};

	//가상함수
	virtual void setIsCollsion(bool _collsion) { _enemy._isCollsion = _collsion; }
	virtual void setIsAttackCollsion(bool _atkCollsion) { _enemy._attackRangeCollsion = _atkCollsion; }
	virtual bool getIsAttackCollsion() { return _enemy._attackRangeCollsion; }
	virtual void setInitPosition(float _x, float _y, bool _isLeft) { _enemy._initX = _x, _enemy._initY = _y, _enemy._isLeft = _isLeft; }
	virtual RECT getEnemyRect() { return _enemy._rec; }
	virtual RECT getEnemyRangeRect() { return _enemy._rangeRc; }
	virtual RECT getEnemyAtkRect() { return _enemy._attackRc; }

	virtual tagEnemyState getEnemyState() { return _enemy._enemyState; }
	virtual void setEnemyState(tagEnemyState _enemyState) { _enemy._enemyState = _enemyState; }
	bool getEnemyIsLeft() { return _enemy._isLeft; }
};

