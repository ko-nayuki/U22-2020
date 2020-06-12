#include "DxLib.h"
#include "Struct.h"

/************************************************
**	U-22ゲーム（タイトル）
*************************************************/
//変更点
//トイレ
/***************************
*	グローバル変数の宣言
****************************/
int g_gameScene = 0;

/***************************
*	関数の宣言
****************************/

/***************************
* WinMain関数
****************************/

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_
	HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd) {

	// フルスクリーンにしないかどうか TRUE:しない FALSE:する
	ChangeWindowMode(TRUE);

	// ウィンドウ画面の大きさ
	SetGraphMode(1280, 768, 32);

	// DXライブラリの初期化
	if (DxLib_Init() == -1) return  -1;

	//ゲームメイン
	Main();

	// DXライブラリ終了
	DxLib_End();

	// 終了
	return 0;
}

int Main() {
	// 描画先を裏画面にセット
	SetDrawScreen(DX_SCREEN_BACK);

	// メインループ
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0) {
		// 画面のクリア
		ClearDrawScreen();

		// ゲームシーンの中を見て適当なゲーム画面を描画
		GameScene(g_gameScene);

		// 画面の更新
		ScreenFlip();
	}

	// 終了
	return 0;
}

// ゲームシーンの管理
void GameScene(int gameScene) {

	switch (gameScene) {

	}
}