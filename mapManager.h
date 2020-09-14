#pragma once
#include "gameNode.h"

class playerManager;
class enemyManager;

enum tagMap
{
	MAP01 = 1,
	MAP02,
	MAP03,
	MAP04,
	MAP05
};

class mapManager : public gameNode
{
private:

	string _mapStr;
	string _mapPixelStr;
	

	tagMap _stage;

	playerManager* _player;
	enemyManager* _enemy;

	int _lightningCount;
	int _lightningAlphaValue;
public:

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	string getPixelMapName() { return _mapPixelStr; }

	void setMapPlayerAddressLink(playerManager* _playerMg) { _player = _playerMg; }
	void setMapEnemyAddressLink(enemyManager* _enemyMg) { _enemy = _enemyMg; }

	void setStage(tagMap _map, float _initPositionX, float _initPositionY);
	tagMap getStage() { return _stage; }
};

