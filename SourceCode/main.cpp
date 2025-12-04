#include"all.h"


ISCENE* scenes[SCENE_MAX] = { new SceneTitle,new SceneGame};


int APIENTRY wWinMain(HINSTANCE, HINSTANCE, LPWSTR, int)
{
	//ゲームライブラリの初期設定
	GameLib::init(L"呪祓", SCREEN_W, SCREEN_H,true);

	//乱数のシード
	srand((unsigned int)time(NULL));

	//オーディオの初期設定
	//audio_init();

	

	//ゲームループ
	while (GameLib::gameLoop())
	{
		//シーン切り替え処理
		if (ISCENE::curScene != ISCENE::nextScene)
		{
			//現在のシーンに応じた終了処理
			if(ISCENE::curScene>=0)
			scenes[ISCENE::curScene]->deinit();


			//次のシーンに応じた初期設定処理
			scenes[ISCENE::nextScene]->init();
			ISCENE::curScene = ISCENE::nextScene;
		}

		//入力を更新する
		input::update();

		//音楽の更新
		music::update();

		//現在のシーンに応じた更新・描画処理
		scenes[ISCENE::curScene]->update();
		scenes[ISCENE::curScene]->render();

		//デバッグ用文字列の表示
		debug::display(1, 1, 1, 1, 1);

		//画面を描画する
		GameLib::present(1, 0);
	}
	

	for (int i = 0;i < SCENE_MAX;i++)
	{
		scenes[i]->deleteSprite();
		delete scenes[i];
	}



	//音楽の開放
	//audio_deinit();

	//ゲームライブラリの終了処理
	GameLib::uninit();
	

	return 0;
}