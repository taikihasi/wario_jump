#include "DxLib.h"
#include "game.h"
#include "car.h"
#include "player.h"
namespace
{
	// 待ち時間
	constexpr int kWaitFrameMin = 60;
	constexpr int kWaitFrameMax = 180;
	// 車の速度
	constexpr float kSpeed = -24.0f;
	// ジャンプ力
	constexpr float kJumpAcc = -16.0f;
	// 重力
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

	// 動きのバリエーションを選択
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
	// デバッグ用に挙動を決める
	

	// 動き始めるまでの時間を設定	1秒から3秒待つ　60フレームから180フレーム
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



// まっすぐ進む
void updateNormal()
{
	
}
// 一時停止フェイント
void updateStop() 
{
	updateNormal();// 仮
}
// ジャンプする
void updateJump()
{
	updateNormal();// 仮
}
// 途中で引き返す（必ず成功）
void updateReturn()
{
	updateNormal();// 仮
}