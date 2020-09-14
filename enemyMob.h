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

	float _chaseX;				// �Ѱ� �ִ� ��� ������ ��ġ 
	RECT _rec;					// ������ ��ġ �� �ǰ�����
	float _speed;
	int _minX, _maxX;			// ������ Ȱ�� ����
	int _frameIndex;
	int _frameCount;
	int _chaseCount;			// �Ѱ� �ִ��� �󸶳� ����� �ľ��ϱ� ����

	float _viewRange;			// Ž�� ����
	float _attackRange;			// ���� ����
	RECT _attackRc;
	RECT _rangeRc;

	image* _enemyimg;			//�� �̹���

	int _frameX;				//������X 
	int _frameY;				//������Y
	bool _isLeft;				//������Y
	bool _isCollsion;
	bool _attackRangeCollsion;

	string _imgkeyName;
	int _initX, _initY;			//�� �ʱ� ��ġ
	float _ptX;					//��ġ
	int _hp;					//�� hp
	int _atk;					//�� ���ݷ�
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

	//�����Լ�
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

