#pragma once
#include "gameNode.h"
#include "mapManager.h"
#include "playerManager.h"
#include "enemyManager.h"

class playGround : public gameNode
{
private:
	mapManager* _map;
	playerManager* _player;
	enemyManager* _enemy;

	bool _collisionTrue;

public:
	playGround();
	~playGround();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	bool getCollision() { return _collisionTrue; }
};

