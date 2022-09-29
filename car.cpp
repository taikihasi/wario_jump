#include "DxLib.h"
#include "game.h"
#include "car.h"
#include "player.h"
namespace
{
	// �҂�����
	constexpr int kWaitFrameMin = 60;
	constexpr int kWaitFrameMax = 180;
	// �Ԃ̑��x
	constexpr float kSpeed = -24.0f;
	// �W�����v��
	constexpr float kJumpAcc = -16.0f;
	// �d��
	constexpr float kGravity = 0.8f;
}

Car::Car()
{

	m_handle = -1;
	m_fieldY = 0.0f;
	m_moveType = 0;
	m_waitFrame = 0;
}

void Car::setGraphic(int handle)
{
	m_handle = handle;
	GetGraphSizeF(m_handle, &m_size.x, &m_size.y);
}

void Car::setup(float fieldY)
{
	m_fieldY = fieldY;
	m_pos.x = Game::kScreenWidth + 16.0f;
	m_pos.y = m_fieldY - m_size.y;

	m_vec.x = -16.0f;
	m_vec.y = 0.0f;

	// �����̃o���G�[�V������I��
	int randNum = GetRand(99);
	if (randNum < 38)
	{
		m_moveType = kMoveTypeNormal;
	}
	else if (randNum < 38 + 30)
	{
		m_moveType = kMoveTypeStop;
	}
	else if (randNum < 38 + 30 + 30)
	{
		m_moveType = kMoveTypeJump;
	}
	else
	{
		m_moveType = kMoveTypeReturn;
	}
	// �f�o�b�O�p�ɋ��������߂�
	

	// �����n�߂�܂ł̎��Ԃ�ݒ�	1�b����3�b�҂@60�t���[������180�t���[��
	m_waitFrame = GetRand(120) + 60;
}

void Car::update()
{
	if (m_waitFrame > 0)
	{
		m_waitFrame--;
		return;
	}

	switch (m_moveType)
	{
	case kMoveTypeNormal:
		updateNormal();
		break;
	case kMoveTypeStop:
		updateStop();
		break;
	case kMoveTypeJump:
		updateJump();
		break;
	case kMoveTypeReturn:
		updateReturn();
		break;
	default:
		updateNormal();
		break;
	}
}

void Car::draw()
{
	DrawGraphF(m_pos.x, m_pos.y, m_handle, true);
//	DrawFormatString(0, 0, GetColor(255,255,255), "wait:%d", m_waitFrame);
}

void Car::updateNormal()
{
	m_pos += m_vec;
}

void Car::updateStop()
{
}

void Car::updateJump()
{
}

void Car::updateReturn()
{
}



// �܂������i��
void updateNormal()
{
	
}
// �ꎞ��~�t�F�C���g
void updateStop() 
{
	updateNormal();// ��
}
// �W�����v����
void updateJump()
{
	updateNormal();// ��
}
// �r���ň����Ԃ��i�K�������j
void updateReturn()
{
	updateNormal();// ��
}