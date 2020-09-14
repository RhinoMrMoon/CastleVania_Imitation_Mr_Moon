#pragma once
#include "gameNode.h"

#define ARMOREDKNIGHTMAX 9

//상호교류 전방선언
class mapManager;
class playerManager;

//참조 전방선언
class enemyMob;

class enemyManager :
	public gameNode
{
private:
	vector<enemyMob*>			_vEnemys;
	//vector<enemyMob>::iterator	_viEnemys;

	char _buffer1[100]; 

	mapManager* _mapMg;
	playerManager* _playerMg;

	int _frameCount;
	bool _isCollsion;
	bool _playerDamage;
	bool _enemyIsLeft;

	enemyMob* _armoredKnight[ARMOREDKNIGHTMAX];
public:
	HRESULT init();
	void release();
	void update();
	void render();

	int getFrameCount() { return _frameCount; }
	void setFrameCount(int frameCount) { _frameCount = frameCount; }

	void setEnemyMapManegerAddressLink(mapManager* _mapManager) { _mapMg = _mapManager; }
	void setEnemyPlayerManagerAddressLink(playerManager* _playerManager) { _playerMg = _playerManager; }

	void enemyPlayerCollsion();
	//void enemyPlayerAttackCollsion();
	bool getCollsion() { return _isCollsion; }

	//RECT getEnemyRect(int i) { return _vEnemys[i]->getEnemyAtkRect(); }
	bool getEnemyIsLeft();
	bool getPlayerDamage() { return _playerDamage; }
};

