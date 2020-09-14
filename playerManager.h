#pragma once
#include "gameNode.h"

#define PI 3.141592f
#define SHADOWMAX 10

class mapManager;
class enemyManager;

enum playerStatus
{
	IDLE,		//���
	WALK01,		//�̵����1
	WALK02,		//�̵����2
	ATTACK,		//����
	JUMP,		//����
	JUMPRIGHT,	//��������
	JUMPLEFT,	//������
	BACKDASH,	//��뽬
	DUCKING,	//����
	DOWNATTACK,	//�ɾƼ� ����
	FALLEN,		//�������� ����
	AIRATTACK,	//��������
	HELLFIRE,	//��ų
	HEART		//�ǰ�
};

struct tagPlayer
{
	image* _img;
	RECT _rc;

	playerStatus _status;
	playerStatus _lastStatus;

	float _width, _height;
	float _halfWidth, _halfHeight; //�ݹ�
	float _centerX, _centerY;
	float _x, _y;
	float _angle;

	int _frameX, _frameY;
	bool _isLeft;

	float _speed;
	int _rcWidth;

	//���ĺ��� ��
	int _alphaValue;


	//�ȼ� �浹��
	RECT _probeRc;
	float _dirX, _dirY;
	float _dirWidth, _dirHeight;
	float _probeY;

	RECT _testRect;

	//�÷��̾� ���� �浹�� ��Ʈ
	RECT _playerAttack;
};

class playerManager : public gameNode
{
private:
	tagPlayer _player;
	tagPlayer _shadow[SHADOWMAX];

	image* _playerImg;

	RECT _rcAttack;

	int _jumpCount;
	int _frameCount;
	int _shadowCount;
	int _walkCount01;
	int _walkCount02;

	float _gravity;
	bool _landing;
	//bool _isLeft;

	bool _jumpActive;

	char _buffer[100];
	char _buffer02[100];
	char _buffer03[100];
	char _buffer04[100];
	char _buffer05[100];
	char _buffer06[100];

	float _jumpHighestScore;
	float _jumpPower;

	float _playerPositionX;
	float _playerPositionY;

	bool _buleCollision;


	string _stageImg;

	mapManager* _mapMg;
	enemyManager* _enemyMg;

	const char* _stateToString[15] = {"IDLE", "WALK01", "WALK02", "ATTACK", "JUMP", "JUMPRIGHT", "JUMPLEFT", "BACKDASH", "DUCKING", "DOWNATTACK", "FALLEN", "AIRATTACK", "HELLFIRE", "HEART" };
public:
	
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void setStatus(tagPlayer &_player, playerStatus _playerStatus);
	playerStatus getPlayerState() { return _player._status; }

	void setPlayerMapManagerAddressLink(mapManager* _mapManager) { _mapMg = _mapManager; }
	void setPlayerEnemyManagerAddressLink(enemyManager* _enemyManager) { _enemyMg = _enemyManager; }

	virtual float getCenterX();
	virtual float getCenterY();

	virtual void setPlayerCenterX(float setX);
	virtual void setPlayerCenterY(float setY);
	void setPlayerAngle(float _angle) { _player._angle = _angle; }

	void setPlayerState(playerStatus _playerStatus) { _player._status = _playerStatus; }

	//�ǰ� �� Ž����? ��Ʈ
	virtual RECT getPlayerRect() { return _player._rc; }

	//���� ������ ��Ʈ
	virtual RECT getPlayerAttackRect() { return _rcAttack; }

	void setPlayerPosition(float x, float y);
};

