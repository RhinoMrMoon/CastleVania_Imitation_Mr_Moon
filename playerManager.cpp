#include "stdafx.h"
#include "playerManager.h"
#include "mapManager.h"
#include "enemyManager.h"

HRESULT playerManager::init()
{
	//이동모션
	IMAGEMANAGER->addFrameImage("AlucardWalk01", "Castlevania/Image/AlucardImage/State_Move_01.bmp", 4500, 600, 15, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("AlucardWalk02", "Castlevania/Image/AlucardImage/State_Move_02.bmp", 4800, 600, 16, 2, true, RGB(255, 0, 255));
	
	//대기
	_playerImg = IMAGEMANAGER->addFrameImage("AlucardIdle", "Castlevania/Image/AlucardImage/State_Idle.bmp", 5700, 600, 19, 2, true, RGB(255, 0, 255));
	
	//점프
	IMAGEMANAGER->addFrameImage("AlucardJump", "Castlevania/Image/AlucardImage/State_Jump.bmp", 3000, 600, 10, 2, true, RGB(255, 0, 255));
	
	//공격
	IMAGEMANAGER->addFrameImage("AlucardAttack", "Castlevania/Image/AlucardImage/State_Attack.bmp", 3300, 600, 11, 2, true, RGB(255,0,255));
	IMAGEMANAGER->addFrameImage("AlucardAttack01", "Castlevania/Image/AlucardImage/State_Attack_01.bmp", 3300, 600, 11, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("AlucardAttack02", "Castlevania/Image/AlucardImage/State_Attack_02.bmp", 3300, 600, 11, 2, true, RGB(255, 0, 255));
	
	//앉기
	IMAGEMANAGER->addFrameImage("AlucardDucking", "Castlevania/Image/AlucardImage/State_Ducking.bmp", 5100, 600, 17, 2, true, RGB(255, 0, 255));
	
	//백대쉬
	IMAGEMANAGER->addFrameImage("AlucardBackdash", "Castlevania/Image/AlucardImage/State_Backdash.bmp", 3900, 600, 13, 2, true, RGB(255, 0, 255));
	
	//공중공격
	IMAGEMANAGER->addFrameImage("AlucardAirAttack", "Castlevania/Image/AlucardImage/State_Attack_Air.bmp", 1200, 600, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("AlucardAirAttack01", "Castlevania/Image/AlucardImage/State_AttackInAir_01.bmp", 1200, 600, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("AlucardAirAttack02", "Castlevania/Image/AlucardImage/State_AttackInAir_02.bmp", 1200, 600, 4, 2, true, RGB(255, 0, 255));

	//앉아서 공격
	IMAGEMANAGER->addFrameImage("AlucardDuckingAttack", "Castlevania/Image/AlucardImage/State_Ducking_Attack.bmp", 3000, 600, 12, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("AlucardDuckingAttack01", "Castlevania/Image/AlucardImage/State_Ducking_Attack_01.bmp", 3000, 600, 12, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("AlucardDuckingAttack02", "Castlevania/Image/AlucardImage/State_Ducking_Attack_02.bmp", 3000, 600, 12, 2, true, RGB(255, 0, 255));

	//피격
	IMAGEMANAGER->addFrameImage("AlucardHeart", "Castlevania/Image/AlucardImage/State_Heart.bmp", 3900, 600, 13, 2, true, RGB(255, 0, 255));

	//스킬
	IMAGEMANAGER->addFrameImage("AlucardHellFire", "Castlevania/Image/AlucardImage/State_HellFire.bmp", 3600, 600, 12, 2, true, RGB(255, 0, 255));


	_player._frameX = 0;

	_player._frameY = 0;

	//_player._centerX = 400;
	//_player._centerY = 1800;

	_player._x = 400;
	_player._y = 200;

	_player._dirX = 400;
	_player._dirY = 200;

	_player._angle = PI / 2;
	_player._speed = 4;

	_player._status = IDLE;
	_player._lastStatus = IDLE;

	_player._rcWidth = 55;

	_jumpPower = 0;
	_gravity = 0;

	_frameCount = 0;
	_walkCount01 = 0;
	_walkCount02 = 0;
	_shadowCount = 0;


	_jumpCount = 0;

	_jumpActive = false;
	_buleCollision = false;

	for (int i = 0; i < SHADOWMAX; i++)
	{
		_shadow[i]._alphaValue = 255;
	}

	return S_OK;
}

void playerManager::release()
{

}

void playerManager::update()
{
	

	//중력
	_gravity += 0.2f;	//중력
	_player._centerY += _gravity;

	////플레이어 상태에 따른 키입력 처리
	switch (_player._status)
	{
		case IDLE: //가만히 있는 상태
		{
			//공격
			if (KEYMANAGER->isStayKeyDown('Z'))
			{
				setStatus(_player, ATTACK);
				break;
			}

			//점프
			/*if (KEYMANAGER->isOnceKeyDown(VK_SPACE) && _jumpActive == false)
			{
				_jumpPower = 10.0f;
				_jumpActive = true;
				break;
			}*/

			//길게 점프
			if (KEYMANAGER->isStayKeyDown(VK_SPACE) && _jumpActive == false)
			{
				_jumpActive = true;
				_player._speed = 7;
				_jumpPower += 3;
				setStatus(_player, JUMP);
				break;
			}

			//백대쉬
			if (KEYMANAGER->isStayKeyDown('D'))
			{
				setStatus(_player, BACKDASH);
				break;
			}

			//앉기
			if (KEYMANAGER->isStayKeyDown(VK_DOWN))
			{
				setStatus(_player, DUCKING);
				break;
			}

			//왼쪽으로 이동
			if (KEYMANAGER->isStayKeyDown(VK_LEFT))
			{
				if (!_player._isLeft)
				{
					_player._isLeft = true;
				}
				setStatus(_player, WALK01);
				_player._centerX -= 5;
				break;
			}

			//오른쪽으로 이동
			else if (KEYMANAGER->isStayKeyDown(VK_RIGHT)) 
			{
				if (_player._isLeft)
				{
					_player._isLeft = false;
				}
				setStatus(_player, WALK01);
				_player._centerX += 5;
				break;
			}
		}
		break;

		case WALK01:
		{
			//공격
			if (KEYMANAGER->isStayKeyDown('Z'))
			{
				setStatus(_player, ATTACK);
				break;
			}

			//점프
			/*if (KEYMANAGER->isOnceKeyDown(VK_SPACE) && _jumpActive == false)
			{
				_jumpPower = 10.0f;
				_jumpActive = true;
				break;
			}*/

			//길게 점프
			if (KEYMANAGER->isStayKeyDown(VK_SPACE) && _jumpActive == false)
			{
				_jumpActive = true;
				_player._speed = 7;
				_jumpPower += 3;
				setStatus(_player, JUMP);
				break;
			}

			//앉기
			if (KEYMANAGER->isStayKeyDown(VK_DOWN))
			{
				setStatus(_player, DUCKING);
				break;
			}

			//백대쉬
			if (KEYMANAGER->isStayKeyDown('D'))
			{
				setStatus(_player, BACKDASH);
				break;
			}

			//왼쪽으로 이동
			if (KEYMANAGER->isStayKeyDown(VK_LEFT))
			{
				if (!_player._isLeft)
				{
					_player._isLeft = true;
				}
				_player._centerX -= 5;
				break;
			}

			//오른쪽으로 이동
			else if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
			{
				if (_player._isLeft)
				{
					_player._isLeft = false;
				}
				_player._centerX += 5;
				break;
			}

			else
			{
				setStatus(_player, IDLE);
				break;
			}
		}
		break;

		case WALK02:
		{
			//공격
			if (KEYMANAGER->isStayKeyDown('Z'))
			{
				setStatus(_player, ATTACK);
				break;
			}

			//점프
			/*if (KEYMANAGER->isOnceKeyDown(VK_SPACE) && _jumpActive == false)
			{
				_jumpPower = 10.0f;
				_jumpActive = true;
				break;
			}*/

			//길게 점프
			if (KEYMANAGER->isStayKeyDown(VK_SPACE) && _jumpActive == false)
			{
				_jumpActive = true;
				_player._speed = 7;
				_jumpPower += 3;
				setStatus(_player, JUMP);
				break;
			}

			//앉기
			if (KEYMANAGER->isStayKeyDown(VK_DOWN))
			{
				setStatus(_player, DUCKING);
				break;
			}

			//백대쉬
			if (KEYMANAGER->isStayKeyDown('D'))
			{
				setStatus(_player, BACKDASH);
				break;
			}

			if (KEYMANAGER->isOnceKeyUp(VK_LEFT) || KEYMANAGER->isOnceKeyUp(VK_RIGHT))
			{
				setStatus(_player, IDLE);
				break;
			}

			//왼쪽으로 이동
			if (KEYMANAGER->isStayKeyDown(VK_LEFT))
			{
				if (!_player._isLeft)
				{
					_player._isLeft = true;
				}
				_player._centerX -= 5;
				break;
			}

			//오른쪽으로 이동
			else if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
			{
				if (_player._isLeft)
				{
					_player._isLeft = false;
				}
				_player._centerX += 5;
				break;
			}
			
			else
			{
				setStatus(_player, IDLE);
				break;
			}

			
		}
		break;

		case ATTACK:
		{

		}
		break;

		case DOWNATTACK:
		{
			if (KEYMANAGER->isOnceKeyUp(VK_DOWN))
			{
				setStatus(_player, IDLE);
			}
		}
		break;

		case AIRATTACK:
		{
			if (KEYMANAGER->isStayKeyDown(VK_LEFT))
			{
				if (!_player._isLeft)
				{
					_player._isLeft = true;
				}
				_player._centerX -= 5;
			}
			else if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
			{
				if (_player._isLeft)
				{
					_player._isLeft = false;
				}
				_player._centerX += 5;
			}
		}
		break;

		case JUMP:
		{
			if (KEYMANAGER->isStayKeyDown('Z'))
			{
				setStatus(_player, AIRATTACK);
				break;
			}

			if (KEYMANAGER->isOnceKeyUp(VK_SPACE))
			{
				_jumpPower = 0;
				break;
			}

			if (KEYMANAGER->isStayKeyDown(VK_LEFT))
			{
				//_player._angle -= 0.1f;
				if (!_player._isLeft)
				{
					_player._isLeft = true;
				}
				setStatus(_player, JUMPLEFT);
				_player._centerX -= 5;
				break;
			}
			else if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
			{
				//_player._angle += 0.1f;
				if (_player._isLeft)
				{
					_player._isLeft = false;
				}
				setStatus(_player, JUMPRIGHT);
				_player._centerX += 5;
				break;
			}
		}
		break;

		case JUMPLEFT:
		case JUMPRIGHT:
		{
			if (KEYMANAGER->isStayKeyDown('Z'))
			{
				setStatus(_player, AIRATTACK);
				break;
			}

			if (KEYMANAGER->isStayKeyDown(VK_LEFT))
			{
				//_player._angle -= 0.1f;
				if (!_player._isLeft)
				{
					_player._isLeft = true;
				}
				_player._centerX -= 5;
				break;
			}
			else if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
			{
				//_player._angle += 0.1f;
				if (_player._isLeft)
				{
					_player._isLeft = false;
				}
				_player._centerX += 5;
				break;
			}
		}
		break;

		case BACKDASH:
		{
			if (KEYMANAGER->isStayKeyDown(VK_DOWN))
			{
				setStatus(_player, DUCKING);
			}
		}
		break;

		case DUCKING: //앉은 상태
		{
			if (KEYMANAGER->isStayKeyDown('Z'))
			{
				setStatus(_player, DOWNATTACK);
				break;
			}

			if (KEYMANAGER->isOnceKeyDown(VK_SPACE)) //아래 점프
			{
				setStatus(_player, FALLEN);
				break;
			}

			if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
			{
				if (!_player._isLeft)
				{
					_player._isLeft = true;
				}
			}
			else if(KEYMANAGER->isOnceKeyDown(VK_RIGHT))
			{
				if (_player._isLeft)
				{
					_player._isLeft = false;
				}
			}


			if (KEYMANAGER->isOnceKeyUp(VK_DOWN))
			{
				setStatus(_player, IDLE);
				break;
			}
		}
		break;

		case FALLEN:
		{
			if (KEYMANAGER->isStayKeyDown('Z'))
			{
				setStatus(_player, AIRATTACK);
				break;
			}

			/*if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
			{
				setStatus(_player, JUMP);
				break;
			}*/
			//왼쪽으로 이동
			if (KEYMANAGER->isStayKeyDown(VK_LEFT))
			{
				//_player._angle -= 0.1f;
				_player._centerX -= 5;
				if (!_player._isLeft)
				{
					_player._isLeft = true;
				}
				break;
			}

			//오른쪽으로 이동
			else if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
			{
				//_player._angle += 0.1f;
				_player._centerX += 5;
				if (_player._isLeft)
				{
					_player._isLeft = false;
				}
				break;
			}
		}
		break;
	}

	//플레이어 데미지
	if (_enemyMg->getPlayerDamage() && _player._status != HEART)
	{
		setStatus(_player, HEART);
	}

	if (_jumpActive)
	{
		_player._centerY += -sinf(_player._angle) * _jumpPower - _player._speed;
		_jumpHighestScore = (-sinf(_player._angle) * _jumpPower - _player._speed) + _gravity;
	}

	_frameCount++;

	//애니메이션 처리
	switch (_player._status)
	{
		case IDLE:
		{
			_player._speed = 0;
			switch (_player._lastStatus)
			{
				case IDLE:
				{
					if (_frameCount == 7)
					{
						/*if (_player._frameX == 6)
						{
							_player._frameX + 9;
						}*/
						if (_player._frameX == 6)
						{
							_player._frameX += 9;
						}

						_player._frameX++;

						if (_player._frameX >= 18)
						{
							_player._frameX = 18;
						}


						_frameCount = 0;
					}
				}
				break;
				case WALK01:
				{
					if (_frameCount == 5)
					{
						_player._frameX++;
						_frameCount = 0;
						if (_player._frameX >= 14)
						{
							setStatus(_player, IDLE);
						}
					}
				}
				break;

				case WALK02:
				{
					setStatus(_player, IDLE);
				}
				break;

				case ATTACK:
				{
					if (_player._frameX >= 10)
					{
						setStatus(_player, IDLE);
					}
				}
				break;

				case BACKDASH:
				{
					if (_player._frameX >= 12)
					{
						setStatus(_player, IDLE);
					}
				}
				break;

				case DUCKING:
				{
					if (_frameCount == 5)
					{
						_player._frameX++;
						_frameCount = 0;
						if (_player._frameX >= 14)
						{
							setStatus(_player, IDLE);
						}
					}
				}
				break;

				case JUMP:
				case FALLEN:
				{
					if (_player._frameX >= 5)
					{
						setStatus(_player, IDLE);
					}
				}
				break;
			}
		}
		break;

		case HEART:
		{
			if (_frameCount == 3)
			{
				_frameCount = 0;
				_player._frameX++;
				/*if (_enemyMg->getEnemyIsLeft())
				{
					_player._angle = PI / 4;
				}
				if (!_enemyMg->getEnemyIsLeft())
				{
					_player._angle = PI * 0.75f;
				}*/
				
				_player._centerX += -sinf(_player._angle) * 20;
				//_player._centerY 
			
				if (_player._frameX >= 12)
				{
					setStatus(_player, DUCKING);
				}
			}
		}
		break;

		case WALK01:
		{
			if (_frameCount == 3)
			{
				_frameCount = 0;
				_player._frameX++;
				if (_player._frameX >= 14)
				{
					setStatus(_player, WALK02);
				}
			}
		}
		break;

		case WALK02:
		{
			if (_player._lastStatus == WALK01)
			{
				if (_frameCount == 4)
				{
					_player._frameX++;
					_frameCount = 0;

					if (_player._frameX >= 14)
					{
						_player._frameX = 0;
						//setStatus(_player, IDLE);
					}
				}
			}
			else
			{
				setStatus(_player, IDLE);
			}
		}
		break;

		case DUCKING:
		{
			if (_player._lastStatus == DOWNATTACK)
			{
				_player._frameX = 12;
			}
			else
			{
				if (_frameCount == 6)
				{
					_frameCount = 0;
					_player._frameX++;
					if (_player._frameX >= 12)
					{
						_player._frameX = 12;
					}
				}

			}
		}
		break;

		case ATTACK:
		{
			if (_frameCount == 5)
			{
				_frameCount = 0;
				_player._frameX++;
				if (_player._frameX >= 10)
				{
					setStatus(_player, IDLE);
				}
			}

			
		}
		break;

		case BACKDASH:
		{

			if (_player._isLeft)
			{
				_player._centerX += 5;
			}
			if (!_player._isLeft)
			{
				_player._centerX -= 5;
			}

			if (_frameCount == 3)
			{
				_player._frameX++;

				if (_player._frameX > 12)
				{
					setStatus(_player, IDLE);
				}
				_frameCount = 0;
			}
		}
		break;

		case JUMP:
		{
			if (_frameCount == 5)
			{
				_frameCount = 0;
				_player._frameX++;
				if (_player._frameX > 3)
				{
					if (_jumpHighestScore >= 0)
					{
						setStatus(_player, FALLEN);
					}
					_player._frameX = 3;

				}
			}
		}
		break;

		case JUMPRIGHT:
		case JUMPLEFT:
		{
			if (_frameCount == 5)
			{
				_frameCount = 0;
				_player._frameX++;
				if (_player._frameX > 9)
				{
					_player._frameX = 9;
					if (_jumpHighestScore >= 0)
					{
						setStatus(_player, FALLEN);
					}
				}
			}
		}
		break;

		case FALLEN:
		{
			if ((_player._lastStatus == JUMPLEFT) || (_player._lastStatus == JUMPRIGHT))
			{
				if (_frameCount == 5)
				{
					_frameCount = 0;
					_player._frameX--;
					if (_player._frameX <= 1)
					{
						_player._frameX = 1;
					}
				}
			}
			else
			{
				if (_frameCount == 5)
				{
					_frameCount = 0;
					_player._frameX++;
					if (_player._frameX >= 5)
					{
						_player._frameX = 5;
					}
				}
			}
		}
		break;

		case DOWNATTACK:
		{
			if (_frameCount == 5)
			{
				_frameCount = 0;
				_player._frameX++;
				if (_player._frameX >= 11)
				{
					setStatus(_player, DUCKING);
				}
			}
		}
		break;

		case AIRATTACK:
		{
			if (_player._lastStatus == JUMPLEFT)
			{
				if (_frameCount == 5)
				{
					_frameCount = 0;
					_player._frameX++;
					if (_player._frameX >= 3)
					{
						setStatus(_player, JUMPLEFT);
					}
				}
			}
			else if (_player._lastStatus == JUMPRIGHT)
			{
				if (_frameCount == 5)
				{
					_frameCount = 0;
					_player._frameX++;
					if (_player._frameX >= 3)
					{
						setStatus(_player, JUMPRIGHT);
					}
				}
			}
			else if (_frameCount == 5)
			{
				_frameCount = 0;
				_player._frameX++;
				if (_player._frameX >= 3)
				{
					setStatus(_player, FALLEN);
				}
			}
		}
		break;
	}

	if (_player._status == ATTACK || _player._status == AIRATTACK)
	{
		if (_player._isLeft)
		{
			_rcAttack = RectMake(_player._centerX - 150, _player._centerY - 60, 100, 35);
		}
		else if (!_player._isLeft)
		{
			_rcAttack = RectMake(_player._centerX + 50, _player._centerY - 60, 100, 35);
		}
	}
	

	if (_player._status == DOWNATTACK)
	{
		if (_player._isLeft)
		{
			_rcAttack = RectMake(_player._centerX - 150, _player._centerY - 10, 100, 35);
		}
		else if (!_player._isLeft)
		{
			_rcAttack = RectMake(_player._centerX + 50, _player._centerY - 10, 100, 35);
		}
	}
	


	//플레이어 그릴 렉트	
	_player._rc = RectMakeCenter(_player._centerX, _player._centerY, _player._rcWidth, 145);

	_player._probeY = _player._rc.bottom - _player._centerY;

	//픽셀 충돌 렉트
	_player._probeRc = RectMakeCenter(_player._centerX, _player._centerY + _player._probeY, 20, 25);

	//int _dirCenterX = (_player._dirRc.right + _player._dirRc.left) / 2;
	int _dirCenterY = (_player._probeRc.top + _player._probeRc.bottom) / 2;

	//바닥충돌
	for (int i = _player._rc.bottom - 10; i < _player._rc.bottom + 5; ++i)
	{
		COLORREF floorColor01 = GetPixel(IMAGEMANAGER->findImage(_mapMg->getPixelMapName())->getMemDC(), _player._centerX, i);
		//COLORREF floorColor02 = GetPixel(IMAGEMANAGER->findImage(_mapMg->getPixelMapName())->getMemDC(), _player._rc.left, i);

		int r01 = GetRValue(floorColor01);
		int g01 = GetGValue(floorColor01);
		int b01 = GetBValue(floorColor01);

		if ((r01 == 0 && g01 == 42 && b01 == 254))
		{
			_player._centerY = i - 70;
			
			_buleCollision = true;
			_jumpActive = false;
			_landing = false;
			if (_player._status == FALLEN || _player._status == JUMP || _player._status == JUMPLEFT || _player._status == JUMPRIGHT)
			{
				_player._angle = PI / 2;
				_jumpPower = 0;
				setStatus(_player, IDLE);
			}
			_gravity = 0;
			break;
		}
		else if ((r01 == 150 && g01 == 254 && b01 == 0))
		{
			_player._centerY = i - 70;

			_buleCollision = true;
			_jumpActive = false;
			_landing = false;
			if (_player._status == FALLEN || _player._status == JUMP || _player._status == JUMPLEFT || _player._status == JUMPRIGHT)
			{
				_player._angle = PI / 2;
				_jumpPower = 0;
				setStatus(_player, IDLE);
			}

			_gravity = 0;

			break;
		}
		else if ((r01 == 255 && g01 == 255 && b01 == 255))
		{
			_buleCollision = false;
			_landing = true;
		}
	/*	else
		{
			setStatus(_player, FALLEN);
		}*/
	}

	//천장 충돌
	COLORREF floorColor = GetPixel(IMAGEMANAGER->findImage(_mapMg->getPixelMapName())->getMemDC(), _player._centerX, _player._rc.top);

	int r = GetRValue(floorColor);
	int g = GetGValue(floorColor);
	int b = GetBValue(floorColor);

	if ((r == 246 && g == 14 && b == 14) && _buleCollision == false)
	{
		_jumpActive = false;
		_jumpPower = 0;
		_player._centerY = _player._rc.top + 79;
		setStatus(_player, FALLEN);
	}
	else if ((r == 150 && g == 254 && b == 0))
	{
		_jumpActive = false;
		_jumpPower = 0;
		_player._centerY = _player._rc.top + 79;
		//setStatus(_player, FALLEN);
	}

	//위 충돌
	/*for (int i = _player._rc.top - 10; i < _player._rc.top; i++)
	{
		COLORREF floorColor = GetPixel(IMAGEMANAGER->findImage(_mapMg->getPixelMapName())->getMemDC(), _player._centerX, i);

		int r = GetRValue(floorColor);
		int g = GetGValue(floorColor);
		int b = GetBValue(floorColor);

		if ((r == 246 && g == 14 && b == 14))
		{
			_player._centerY = i + 90;
			break;
		}
	}*/
	
	if (_player._status != JUMP || _player._status != FALLEN)
	{
		//왼쪽 충돌
		for (int i = _player._rc.left; i < _player._rc.left + 3; ++i)
		{
			COLORREF floorColor = GetPixel(IMAGEMANAGER->findImage(_mapMg->getPixelMapName())->getMemDC(), i, _player._centerY);

			int r = GetRValue(floorColor);
			int g = GetGValue(floorColor);
			int b = GetBValue(floorColor);

			if ((r == 150 && g == 254 && b == 0))
			{
				_player._centerX = i + 32;
				break;
			}
		}

		//오른쪽 충돌
		for (int i = _player._rc.right; i < _player._rc.right + 10; i++)
		{
			COLORREF floorColor = GetPixel(IMAGEMANAGER->findImage(_mapMg->getPixelMapName())->getMemDC(), i, _player._centerY);

			int r = GetRValue(floorColor);
			int g = GetGValue(floorColor);
			int b = GetBValue(floorColor);

			if ((r == 150 && g == 254 && b == 0))
			{
				_player._centerX = i - 40;
				break;
			}
		}
	}

	//점프 상태일때 충돌
	else if (_player._status == JUMP || _player._status == FALLEN)
	{
		//왼쪽 충돌
		for (int i = _player._rc.left; i < _player._rc.left + 10; ++i)
		{
			COLORREF floorColor = GetPixel(IMAGEMANAGER->findImage(_mapMg->getPixelMapName())->getMemDC(), i, _player._centerY);

			int r = GetRValue(floorColor);
			int g = GetGValue(floorColor);
			int b = GetBValue(floorColor);

			if ((r == 150 && g == 254 && b == 0))
			{
				_player._centerX = i + 34;
				break;
			}
			else if (r == 246 && g == 14 && b == 14)
			{
				_player._centerX = i + 40;
				break;
			}
		}

		//오른쪽 충돌
		for (int i = _player._rc.right; i < _player._rc.right + 10; i++)
		{
			COLORREF floorColor = GetPixel(IMAGEMANAGER->findImage(_mapMg->getPixelMapName())->getMemDC(), i, _player._centerY);

			int r = GetRValue(floorColor);
			int g = GetGValue(floorColor);
			int b = GetBValue(floorColor);

			if ((r == 150 && g == 254 && b == 0))
			{
				_player._centerX = i - 38;
				break;
			}
			else if (r == 246 && g == 14 && b == 14)
			{
				_player._centerX = i - 44;
				break;
			}
		}
	}
	//CAMERA->setX(_player._centerX - 400);
	//CAMERA->setY(_player._centerY - 300);

	sprintf_s(_buffer, "current gravity : %f", _gravity);
	sprintf_s(_buffer02, "current frameX %d", _player._frameX);

	//if (_frameCount % 20 == 0)
	//{
	//	_playerPositionX = _player._centerX - 150;
	//	_playerPositionY = _player._centerY - 227;
	//}

	_shadowCount++;

	if (!(_player._status == IDLE) || !(_player._status == WALK01))
	{
		for (int i = 0; i < SHADOWMAX; i++)
		{
			_shadow[i]._alphaValue -= 3;
			if (_shadow[i]._alphaValue <= 0)
			{
				_shadow[i]._img = nullptr;
			}
		}
	}

	_player._img = _playerImg;
	_player._frameY = _player._isLeft;

	if (_player._status == WALK01 || _player._status == JUMPLEFT || _player._status == JUMPRIGHT)
	{
		if (_player._isLeft)
		{
			if (_shadowCount % 10 == 6)
			{
				_shadow[0]._alphaValue = 255;

				_shadow[0]._centerX = _player._centerX - 120;
				_shadow[0]._centerY = _player._centerY - 227;
				_shadow[0]._frameX = _player._frameX;
				_shadow[0]._frameY = _player._frameY;
				_shadow[0]._img = _player._img;
			}
			else if (_shadowCount % 10 == 5)
			{
				_shadow[1]._alphaValue = 210;

				_shadow[1]._centerX = _player._centerX - 120;
				_shadow[1]._centerY = _player._centerY - 227;
				_shadow[1]._frameX = _player._frameX;
				_shadow[1]._frameY = _player._frameY;
				_shadow[1]._img = _player._img;
			}

			else if (_shadowCount % 10 == 4)
			{
				_shadow[2]._alphaValue = 175;

				_shadow[2]._centerX = _player._centerX - 120;
				_shadow[2]._centerY = _player._centerY - 227;
				_shadow[2]._frameX = _player._frameX;
				_shadow[2]._frameY = _player._frameY;
				_shadow[2]._img = _player._img;
			}

			else if (_shadowCount % 10 == 3)
			{
				_shadow[3]._alphaValue = 130;

				_shadow[3]._centerX = _player._centerX - 120;
				_shadow[3]._centerY = _player._centerY - 227;
				_shadow[3]._frameX = _player._frameX;
				_shadow[3]._frameY = _player._frameY;
				_shadow[3]._img = _player._img;
			}

			else if (_shadowCount % 10 == 2)
			{
				_shadow[4]._alphaValue = 85;

				_shadow[4]._centerX = _player._centerX - 120;
				_shadow[4]._centerY = _player._centerY - 227;
				_shadow[4]._frameX = _player._frameX;
				_shadow[4]._frameY = _player._frameY;
				_shadow[4]._img = _player._img;
			}

			else if (_shadowCount % 10 == 1)
			{
				_shadow[5]._alphaValue = 40;

				_shadow[5]._centerX = _player._centerX - 120;
				_shadow[5]._centerY = _player._centerY - 227;
				_shadow[5]._frameX = _player._frameX;
				_shadow[5]._frameY = _player._frameY;
				_shadow[5]._img = _player._img;
			}

			else if (_shadowCount % 10 == 0)
			{
				_shadow[6]._alphaValue = 5;

				_shadow[6]._centerX = _player._centerX - 120;
				_shadow[6]._centerY = _player._centerY - 227;
				_shadow[6]._frameX = _player._frameX;
				_shadow[6]._frameY = _player._frameY;
				_shadow[6]._img = _player._img;
			}
		}

		if (!_player._isLeft)
		{
			if (_shadowCount % 10 == 6)
			{
				_shadow[0]._alphaValue = 255;


				_shadow[0]._centerX = _player._centerX - 170;
				_shadow[0]._centerY = _player._centerY - 227;
				_shadow[0]._frameX = _player._frameX;
				_shadow[0]._frameY = _player._frameY;
				_shadow[0]._img = _player._img;
			}
			else if (_shadowCount % 10 == 5)
			{
				_shadow[1]._alphaValue = 210;


				_shadow[1]._centerX = _player._centerX - 170;
				_shadow[1]._centerY = _player._centerY - 227;
				_shadow[1]._frameX = _player._frameX;
				_shadow[1]._frameY = _player._frameY;
				_shadow[1]._img = _player._img;
			}
			else if (_shadowCount % 10 == 4)
			{
				_shadow[2]._alphaValue = 168;


				_shadow[2]._centerX = _player._centerX - 170;
				_shadow[2]._centerY = _player._centerY - 227;
				_shadow[2]._frameX = _player._frameX;
				_shadow[2]._frameY = _player._frameY;
				_shadow[2]._img = _player._img;
			}

			else if (_shadowCount % 10 == 3)
			{
				_shadow[3]._alphaValue = 124;


				_shadow[3]._centerX = _player._centerX - 170;
				_shadow[3]._centerY = _player._centerY - 227;
				_shadow[3]._frameX = _player._frameX;
				_shadow[3]._frameY = _player._frameY;
				_shadow[3]._img = _player._img;
			}
			else if (_shadowCount % 10 == 2)
			{
				_shadow[4]._alphaValue = 80;

				_shadow[4]._centerX = _player._centerX - 170;
				_shadow[4]._centerY = _player._centerY - 227;
				_shadow[4]._frameX = _player._frameX;
				_shadow[4]._frameY = _player._frameY;
				_shadow[4]._img = _player._img;
			}

			else if (_shadowCount % 10 == 1)
			{
				_shadow[5]._alphaValue = 40;

				_shadow[5]._centerX = _player._centerX - 170;
				_shadow[5]._centerY = _player._centerY - 227;
				_shadow[5]._frameX = _player._frameX;
				_shadow[5]._frameY = _player._frameY;
				_shadow[5]._img = _player._img;
			}

			else if (_shadowCount % 10 == 0)
			{
				_shadow[6]._alphaValue = 5;

				_shadow[6]._centerX = _player._centerX - 170;
				_shadow[6]._centerY = _player._centerY - 227;
				_shadow[6]._frameX = _player._frameX;
				_shadow[6]._frameY = _player._frameY;
				_shadow[6]._img = _player._img;
			}
		}
	}
	
	//백대쉬 잔상
	if (_player._status == BACKDASH)
	{
		if (_player._isLeft)
		{
			if (_shadowCount % 10 == 6)
			{
				_shadow[0]._alphaValue = 255;

				_shadow[0]._centerX = _player._centerX - 170;
				_shadow[0]._centerY = _player._centerY - 227;
				_shadow[0]._frameX = _player._frameX;
				_shadow[0]._frameY = _player._frameY;
				_shadow[0]._img = _player._img;
			}
			if (_shadowCount % 10 == 5)
			{
				_shadow[1]._alphaValue = 210;

				_shadow[1]._centerX = _player._centerX - 170;
				_shadow[1]._centerY = _player._centerY - 227;
				_shadow[1]._frameX = _player._frameX;
				_shadow[1]._frameY = _player._frameY;
				_shadow[1]._img = _player._img;
			}

			if (_shadowCount % 10 == 4)
			{
				_shadow[2]._alphaValue = 175;

				_shadow[2]._centerX = _player._centerX - 170;
				_shadow[2]._centerY = _player._centerY - 227;
				_shadow[2]._frameX = _player._frameX;
				_shadow[2]._frameY = _player._frameY;
				_shadow[2]._img = _player._img;
			}

			if (_shadowCount % 10 == 3)
			{
				_shadow[3]._alphaValue = 130;

				_shadow[3]._centerX = _player._centerX - 170;
				_shadow[3]._centerY = _player._centerY - 227;
				_shadow[3]._frameX = _player._frameX;
				_shadow[3]._frameY = _player._frameY;
				_shadow[3]._img = _player._img;
			}

			if (_shadowCount % 10 == 2)
			{
				_shadow[4]._alphaValue = 85;

				_shadow[4]._centerX = _player._centerX - 170;
				_shadow[4]._centerY = _player._centerY - 227;
				_shadow[4]._frameX = _player._frameX;
				_shadow[4]._frameY = _player._frameY;
				_shadow[4]._img = _player._img;
			}

			if (_shadowCount % 10 == 1)
			{
				_shadow[5]._alphaValue = 40;

				_shadow[5]._centerX = _player._centerX - 170;
				_shadow[5]._centerY = _player._centerY - 227;
				_shadow[5]._frameX = _player._frameX;
				_shadow[5]._frameY = _player._frameY;
				_shadow[5]._img = _player._img;
			}

			if (_shadowCount % 10 == 0)
			{
				_shadow[6]._alphaValue = 5;

				_shadow[6]._centerX = _player._centerX - 170;
				_shadow[6]._centerY = _player._centerY - 227;
				_shadow[6]._frameX = _player._frameX;
				_shadow[6]._frameY = _player._frameY;
				_shadow[6]._img = _player._img;
			}
		}

		if (!_player._isLeft)
		{
			if (_shadowCount % 10 == 6)
			{
				_shadow[0]._alphaValue = 255;

				_shadow[0]._centerX = _player._centerX - 100;
				_shadow[0]._centerY = _player._centerY - 227;
				_shadow[0]._frameX = _player._frameX;
				_shadow[0]._frameY = _player._frameY;
				_shadow[0]._img = _player._img;
			}
			if (_shadowCount % 10 == 5)
			{
				_shadow[1]._alphaValue = 210;


				_shadow[1]._centerX = _player._centerX - 100;
				_shadow[1]._centerY = _player._centerY - 227;
				_shadow[1]._frameX = _player._frameX;
				_shadow[1]._frameY = _player._frameY;
				_shadow[1]._img = _player._img;
			}
			if (_shadowCount % 10 == 4)
			{
				_shadow[2]._alphaValue = 168;


				_shadow[2]._centerX = _player._centerX - 100;
				_shadow[2]._centerY = _player._centerY - 227;
				_shadow[2]._frameX = _player._frameX;
				_shadow[2]._frameY = _player._frameY;
				_shadow[2]._img = _player._img;
			}

			if (_shadowCount % 10 == 3)
			{
				_shadow[3]._alphaValue = 124;


				_shadow[3]._centerX = _player._centerX - 100;
				_shadow[3]._centerY = _player._centerY - 227;
				_shadow[3]._frameX = _player._frameX;
				_shadow[3]._frameY = _player._frameY;
				_shadow[3]._img = _player._img;
			}
			if (_shadowCount % 10 == 2)
			{
				_shadow[4]._alphaValue = 80;

				_shadow[4]._centerX = _player._centerX - 100;
				_shadow[4]._centerY = _player._centerY - 227;
				_shadow[4]._frameX = _player._frameX;
				_shadow[4]._frameY = _player._frameY;
				_shadow[4]._img = _player._img;
			}

			if (_shadowCount % 10 == 1)
			{
				_shadow[5]._alphaValue = 40;

				_shadow[5]._centerX = _player._centerX - 100;
				_shadow[5]._centerY = _player._centerY - 227;
				_shadow[5]._frameX = _player._frameX;
				_shadow[5]._frameY = _player._frameY;
				_shadow[5]._img = _player._img;
			}

			if (_shadowCount % 10 == 0)
			{
				_shadow[6]._alphaValue = 5;

				_shadow[6]._centerX = _player._centerX - 100;
				_shadow[6]._centerY = _player._centerY - 227;
				_shadow[6]._frameX = _player._frameX;
				_shadow[6]._frameY = _player._frameY;
				_shadow[6]._img = _player._img;
			}
		}
	}


	//점프 잔상
	if (_player._status == JUMP || _player._status == FALLEN)
	{
		if (_shadowCount % 20 == 16)
		{
			_shadow[0]._alphaValue = 255;

			_shadow[0]._centerX = _player._centerX - 150;
			_shadow[0]._centerY = _player._centerY - 227;
			_shadow[0]._frameX = _player._frameX;
			_shadow[0]._frameY = _player._frameY;
			_shadow[0]._img = _player._img;
		}

		else if (_shadowCount % 20 == 12)
		{
			_shadow[1]._alphaValue = 200;

			_shadow[1]._centerX = _player._centerX - 150;
			_shadow[1]._centerY = _player._centerY - 227;
			_shadow[1]._frameX = _player._frameX;
			_shadow[1]._frameY = _player._frameY;
			_shadow[1]._img = _player._img;
		}

		else if (_shadowCount % 20 == 8)
		{
			_shadow[2]._alphaValue = 145;

			_shadow[2]._centerX = _player._centerX - 150;
			_shadow[2]._centerY = _player._centerY - 227;
			_shadow[2]._frameX = _player._frameX;
			_shadow[2]._frameY = _player._frameY;
			_shadow[2]._img = _player._img;
		}

		else if (_shadowCount % 20 == 4)
		{
			_shadow[3]._alphaValue = 95;

			_shadow[3]._centerX = _player._centerX - 150;
			_shadow[3]._centerY = _player._centerY - 227;
			_shadow[3]._frameX = _player._frameX;
			_shadow[3]._frameY = _player._frameY;
			_shadow[3]._img = _player._img;
		}

		else if (_shadowCount % 20 == 0)
		{
			_shadow[4]._alphaValue = 40;

			_shadow[4]._centerX = _player._centerX - 150;
			_shadow[4]._centerY = _player._centerY - 227;
			_shadow[4]._frameX = _player._frameX;
			_shadow[4]._frameY = _player._frameY;
			_shadow[4]._img = _player._img;
		}
	}

	//_player._img = _playerImg;

	//혹시 모를 오류를 대비해
	if (_shadowCount >= 1000)
	{
		_shadowCount = 0;
	}
}

void playerManager::render()
{
	MYRECT rc;
	
	if (!_player._isLeft && _player._status == WALK02 || (!_player._isLeft && _player._status == WALK01) || (!_player._isLeft && _player._status == DUCKING) || (!_player._isLeft && _player._status == DOWNATTACK))
	{
		rc = { static_cast<float>(_player._rc.left + 20),
		static_cast<float>(_player._rc.top),
		static_cast<float>(_player._rc.right + 20),
		static_cast<float>(_player._rc.bottom) };
	}
	else if (_player._isLeft && _player._status == DUCKING)
	{
		rc = { static_cast<float>(_player._rc.left - 20),
		static_cast<float>(_player._rc.top),
		static_cast<float>(_player._rc.right - 20),
		static_cast<float>(_player._rc.bottom) };
	}
	else if (_player._status == DOWNATTACK)
	{
		rc = { static_cast<float>(_player._rc.left - 20),
		   static_cast<float>(_player._rc.top),
		   static_cast<float>(_player._rc.right - 20),
		   static_cast<float>(_player._rc.bottom) };

	}
	else
	{
		rc = { static_cast<float>(_player._rc.left),
		static_cast<float>(_player._rc.top),
		static_cast<float>(_player._rc.right),
		static_cast<float>(_player._rc.bottom) };
	}

	MYRECT dirRc = { static_cast<float>(_player._probeRc.left),
	static_cast<float>(_player._probeRc.top),
	static_cast<float>(_player._probeRc.right),
	static_cast<float>(_player._probeRc.bottom) };

	MYRECT testRc = { static_cast<float>(_player._testRect.left),
	static_cast<float>(_player._testRect.top),
	static_cast<float>(_player._testRect.right),
	static_cast<float>(_player._testRect.bottom) };

	MYRECT rcAttack = { static_cast<float>(_rcAttack.left),
	static_cast<float>(_rcAttack.top),
	static_cast<float>(_rcAttack.right),
	static_cast<float>(_rcAttack.bottom) };

	//플레이어 충돌용 렉트
	//CAMERA->rectangle(getMemDC(), rc);
	
	//Rectangle(getMemDC(), _player._rc);
	//CAMERA->rectangle(getMemDC(), dirRc);


	//잔상 그리기
	for (int i = 0; i < 4; i++)
	{
		if (_shadow[i]._img == nullptr) break;
		else
		{
			CAMERA->alphaFrameRender(getMemDC(), _shadow[i]._img, _shadow[i]._centerX, _shadow[i]._centerY, _shadow[i]._frameX, _shadow[i]._frameY, _shadow[i]._alphaValue);
		}
	}	

	//공격 렉트
	if (_player._status == ATTACK || _player._status == AIRATTACK || _player._status == DOWNATTACK)
	{
		CAMERA->rectangle(getMemDC(), rcAttack);
	}

	if (_player._status != DOWNATTACK)
	{
		//플레이어
		if (!_player._isLeft)
		{
			CAMERA->frameRender(getMemDC(), _playerImg, _player._rc.left - 123, _player._rc.top - 157, _player._frameX, _player._isLeft);
		}
		if ((_player._isLeft && _player._status == WALK01) || (_player._isLeft && _player._status == WALK02))
		{
			CAMERA->frameRender(getMemDC(), _playerImg, _player._rc.left - 100, _player._rc.top - 157, _player._frameX, _player._isLeft);
		}
		else
		{
			CAMERA->frameRender(getMemDC(), _playerImg, _player._rc.left - 123, _player._rc.top - 157, _player._frameX, _player._isLeft);
		}
	}
	else if (_player._isLeft && _player._status == DOWNATTACK)
	{
		CAMERA->frameRender(getMemDC(), _playerImg, _player._rc.left - 120, _player._rc.top - 157, _player._frameX, _player._isLeft);
	}
	else if (!_player._isLeft && _player._status == DOWNATTACK)
	{
		CAMERA->frameRender(getMemDC(), _playerImg, _player._rc.left - 78, _player._rc.top - 157, _player._frameX, _player._isLeft);
	}

	//TIMEMANAGER->render(getMemDC());
	//TextOut(getMemDC(), 10, 10, _buffer, strlen(_buffer));
	//TextOut(getMemDC(), 10, 50, _buffer02, strlen(_buffer02));

	sprintf_s(_buffer03, "state : %s", _stateToString[_player._status]);
	//TextOut(getMemDC(), 10, 70, _buffer03, strlen(_buffer03));

	sprintf_s(_buffer04, "last state : %s", _stateToString[_player._lastStatus]);

	//TextOut(getMemDC(), 10, 90, _buffer04, strlen(_buffer04));

	sprintf_s(_buffer05, "current angle : %f", _player._angle);
	//TextOut(getMemDC(), 10, 105, _buffer05, strlen(_buffer05));

	sprintf_s(_buffer06, "current centerX : %f", _player._centerX);
	//TextOut(getMemDC(), 10, 120, _buffer06, strlen(_buffer06));

	sprintf_s(_buffer06, "current jumpHighestScore : %f", _jumpHighestScore);
	//TextOut(getMemDC(), 10, 140, _buffer06, strlen(_buffer06));

}

void playerManager::setStatus(tagPlayer & _player, playerStatus _playerStatus)
{
	_player._lastStatus = _player._status;
	_player._status = _playerStatus;
	if (_player._lastStatus != _player._status)
	{
		_frameCount = 0;
	}

	switch (_playerStatus)
	{
		case IDLE:
		{
			switch (_player._lastStatus)
			{
				case WALK01:
				{
					_playerImg = IMAGEMANAGER->findImage("AlucardWalk01");
					_player._frameX = 14;
				}
				break;

				case WALK02:
				{
					_playerImg = IMAGEMANAGER->findImage("AlucardWalk02");
					//_playerImg = IMAGEMANAGER->findImage("AlucardIdle");
					_player._frameX = 0;
				}
				break;

				case ATTACK:
				{
					_playerImg = IMAGEMANAGER->findImage("AlucardAttack");
					_player._frameX = 10;
				}
				break;

				case BACKDASH:
				{
					_playerImg = IMAGEMANAGER->findImage("AlucardBackdash");
					_player._frameX = 12;
				}
				break;

				case DUCKING:
				{
					_playerImg = IMAGEMANAGER->findImage("AlucardDucking");
					//_playerImg = IMAGEMANAGER->findImage("AlucardIdle");

					_player._frameX = 16;
				}
				break;

				case JUMP:
				{
					_playerImg = IMAGEMANAGER->findImage("AlucardJump");
					_player._frameX = 4;
				}
				break;

				case FALLEN:
				{
					_playerImg = IMAGEMANAGER->findImage("AlucardJump");
					_player._frameX = 6;
				}
				break;

				default:
				{
					_playerImg = IMAGEMANAGER->findImage("AlucardIdle");
					_player._frameX = 0;
				}
				break;
			}
		}
		break;

		case HEART:
		{
			_playerImg = IMAGEMANAGER->findImage("AlucardHeart");
			_player._frameX = 0;
		}
		break;

		case WALK01:
		{
			_playerImg = IMAGEMANAGER->findImage("AlucardWalk01");
			_player._frameX = 0;
		}
		break;
			
		case WALK02:
		{
			switch (_player._lastStatus)
			{
				/*case WALK01:
				{
					_playerImg = IMAGEMANAGER->findImage("AlucardWalk01");
					_player._frameX = 14;
				}
				break;*/

				default:
				{
					_playerImg = IMAGEMANAGER->findImage("AlucardWalk02");
					_player._frameX = 0;
				}
				break;
			}
		}
		break;

		case ATTACK:
		{
			_playerImg = IMAGEMANAGER->findImage("AlucardAttack01");
			_player._frameX = 0;
		}
		break;

		case DOWNATTACK:
		{
			_playerImg = IMAGEMANAGER->findImage("AlucardDuckingAttack02");
			_player._frameX = 0;
		}
		break;

		case AIRATTACK:
		{
			_playerImg = IMAGEMANAGER->findImage("AlucardAirAttack01");
			_player._frameX = 0;
		}
		break;

		case FALLEN:
		{
			
			switch (_player._lastStatus)
			{
				case JUMPLEFT:
				case JUMPRIGHT:
				{
					_playerImg = IMAGEMANAGER->findImage("AlucardWalk01");
					_player._frameX = 6;
				}
				break;

				case JUMP:
				case FALLEN:
				case AIRATTACK:
				{
					_playerImg = IMAGEMANAGER->findImage("AlucardJump");
					_player._frameX = 5;
				}
				break;
			}
		}
		break;

		case JUMP:
		{
			_playerImg = IMAGEMANAGER->findImage("AlucardJump");
			_player._frameX = 0;
		}
		break;

		case JUMPLEFT:
		case JUMPRIGHT:
		{
			_playerImg = IMAGEMANAGER->findImage("AlucardJump");
			_player._frameX = 6;
		}
		break;

		case BACKDASH:
		{
			_playerImg = IMAGEMANAGER->findImage("AlucardBackdash");
			_player._frameX = 3;
		}
		break;

		case DUCKING:
		{
			switch (_player._lastStatus)
			{
				case DOWNATTACK:
				{
					_playerImg = IMAGEMANAGER->findImage("AlucardDuckingAttack");
					_player._frameX = 11;
				}
				break;

				default:
				{
					_playerImg = IMAGEMANAGER->findImage("AlucardDucking");
					_player._frameX = 0;
				}
				break;
			}
			//_playerImg = IMAGEMANAGER->findImage("AlucardIdle");
			_playerImg = IMAGEMANAGER->findImage("AlucardDucking");
			_player._frameX = 0;
		}
		break;

	}
}

float playerManager::getCenterX()
{
	return _player._centerX;
}

float playerManager::getCenterY()
{
	return _player._centerY;
}

void playerManager::setPlayerCenterX(float setX)
{
	_player._centerX = setX;
}

void playerManager::setPlayerCenterY(float setY)
{
	_player._centerY = setY;
}

void playerManager::setPlayerPosition(float x, float y)
{
}
