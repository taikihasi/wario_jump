#include "DxLib.h"
#include "game.h"

#include "SceneMain.h"

namespace
{
	// 地面の高さ
	constexpr int kFieldY = Game::kScreenHeight - 64;
}

// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// windowモード設定
	ChangeWindowMode(Game::kWindowMode);
	// ウインドウ名設定
	SetMainWindowText(Game::kTitleText);
	// 画面サイズの設定
	SetGraphMode(Game::kScreenWidth, Game::kScreenHeight, Game::kColorDepth);

	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}

	int hPlayer = LoadGraph("data/player.png");
	int hCar = LoadGraph("data/car.png");

	Player player;
	player.setGraphic(hPlayer);
	player.setup(kFieldY);

	Car car;
	car.setGraphic(hCar);
	car.setup(kFieldY);

	// ダブルバッファモード
	SetDrawScreen(DX_SCREEN_BACK);

	// 現在のシーン番号	0:Title 1:Main 2:Test
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
		// 画面のクリア
		ClearDrawScreen();

		// シーン変更フラグ
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

		// 当たり判定
		if (player.isCol(car))
		{
			player.setDead(true);
		}

		// 地面の描画
		DrawLine(0, kFieldY, Game::kScreenWidth, kFieldY, GetColor(255, 255, 255));
		player.draw();
		car.draw();

		//裏画面を表画面を入れ替える
		ScreenFlip();

		// escキーを押したら終了する
		if (CheckHitKey(KEY_INPUT_ESCAPE))	break;

		// fpsを60に固定
		while (GetNowHiPerformanceCount() - time < 16667)
		{
		}
	}

	DeleteGraph(hPlayer);
	DeleteGraph(hCar);

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}