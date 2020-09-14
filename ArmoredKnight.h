#pragma once
#include "enemyMob.h"


class ArmoredKnight : public enemyMob
{	
private:
	char _buffer[128];
	int _idleCount;
	mapManager* _mapMg;
public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	virtual int getEnemyFrameX() { return _enemy._frameX; }
	virtual void setEnemyState(tagEnemyState _enemyState);
	RECT getEnemyAttackRect() { return _enemy._attackRc; }
	RECT getEnemyRect() { return _enemy._rec; }
	bool getEnemyIsLeft() { return _enemy._isLeft; }
};

