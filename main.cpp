#include "DxLib.h"
#include "game.h"

#include "SceneMain.h"

namespace
{
	// �n�ʂ̍���
	constexpr int kFieldY = Game::kScreenHeight - 64;
}

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// window���[�h�ݒ�
	ChangeWindowMode(Game::kWindowMode);
	// �E�C���h�E���ݒ�
	SetMainWindowText(Game::kTitleText);
	// ��ʃT�C�Y�̐ݒ�
	SetGraphMode(Game::kScreenWidth, Game::kScreenHeight, Game::kColorDepth);

	if (DxLib_Init() == -1)		// �c�w���C�u��������������
	{
		return -1;			// �G���[���N�����璼���ɏI��
	}

	int hPlayer = LoadGraph("data/player.png");
	int hCar = LoadGraph("data/car.png");

	Player player;
	player.setGraphic(hPlayer);
	player.setup(kFieldY);

	Car car;
	car.setGraphic(hCar);
	car.setup(kFieldY);

	// �_�u���o�b�t�@���[�h
	SetDrawScreen(DX_SCREEN_BACK);

	// ���݂̃V�[���ԍ�	0:Title 1:Main 2:Test
	int sceneNo = 0;

	SceneMain sceneMain;
	SceneTitle sceneTitle;
	swich(sceneNo)
	{
	case 0:
		sceneTitle.init();
		vreak;
	case 1:
		sceneMain.init();
		vreak;
	}

	
	while (ProcessMessage() == 0)
	{
		LONGLONG  time = GetNowHiPerformanceCount();
		// ��ʂ̃N���A
		ClearDrawScreen();

		// �V�[���ύX�t���O
		bool  isChange = false;
		switch (sceneNo)
		{
		case 0:
			isChange = sceneTitle.update();
			sceneTitle.draw();
			if (isChange)
			{
				sceneTitle.end();

				sceneMain.init();
				sceneNo = 1;
			}
		}



		player.update();
		car.update();

		// �����蔻��
		if (player.isCol(car))
		{
			player.setDead(true);
		}

		// �n�ʂ̕`��
		DrawLine(0, kFieldY, Game::kScreenWidth, kFieldY, GetColor(255, 255, 255));
		player.draw();
		car.draw();

		//����ʂ�\��ʂ����ւ���
		ScreenFlip();

		// esc�L�[����������I������
		if (CheckHitKey(KEY_INPUT_ESCAPE))	break;

		// fps��60�ɌŒ�
		while (GetNowHiPerformanceCount() - time < 16667)
		{
		}
	}

	DeleteGraph(hPlayer);
	DeleteGraph(hCar);

	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return 0;				// �\�t�g�̏I�� 
}