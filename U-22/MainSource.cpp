#include "DxLib.h"
#include "Struct.h"
#include "yoshitaka.h"
#include "tubasa.h"
#include "yu-ki.h"
#include "issei.h"
#include "hiroaki.h"
#include "daiki.h"
#include "GameScene.h"
#include "GameTitle.h"
#include "StageSelect.h"
#include "GamePlay.h"
#include "GameClear.h"
#include "GameOver.h"

/************************************************
**	U-22ゲーム（タイトル）
*************************************************/
//変更点
//トイレ
/***************************
*	グローバル変数の宣言
****************************/
int g_gameScene = 0;
mouse g_mouseInfo;								// マウスの状態管理
int g_KeyFlg; //6.16 (key入力変数）
int g_OldKey;
int g_NowKey;
/***************************
*	関数の宣言
****************************/
int Main(void);					// ゲームのメイン処理
void GameScene(int gameScene);	// 画面のシーン管理

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
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0 && !(g_KeyFlg & PAD_INPUT_START)) {
		// 画面のクリア
		ClearDrawScreen();

		//デバッグ？マウス取得
		ControlInfo(&g_mouseInfo);

		//デバッグ前提座標
		DrawFormatString(0, 20, 0xFFFFFF, "mouseX = %d \n mouseY = %d", g_mouseInfo.mouseX, g_mouseInfo.mouseY);

		// ゲームシーンの中を見て適当なゲーム画面を描画
		GameScene(g_gameScene);

		//6.16 キー入力
		g_OldKey = g_NowKey;
		g_NowKey = GetJoypadInputState(DX_INPUT_KEY_PAD1);
		g_KeyFlg = g_NowKey & ~g_OldKey;


		// 画面の更新
		ScreenFlip();
	}

	// 終了
	return 0;
}

// ゲームシーンの管理
void GameScene(int gameScene) {

	switch (gameScene) {
		case GAME_TITLE:	GameTitle();	break;	 // ゲームタイトル
		case GAME_SELECT:	StageSelect();	break;	 // ゲームセレクト
		case GAME_PLAY:	    GamePlay();		break;	 // ゲームプレイ	
		case GAME_OVER:		GameOver();		break;	 // ゲームオーバー
		case GAME_CLEAR:	GameClear();	break;	 // ゲームクリア
	}
}
