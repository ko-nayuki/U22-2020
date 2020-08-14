#include "DxLib.h"
#include "yoshitaka.h"
#include "GameScene.h"
#include "Map.h"
#include "player.h"
#include "Picture.h"
#include "StageSelect.h"
#include "GamePlay.h"
#include "Gimmick.h"
#include "GameClear.h"

static int num = 0;


void FeadOut() {
	num = 0;
	Fead.FeadFlg = 0;
	//フェードアウト
	while(num<255) {
		SetDrawBright(255 - num, 255 - num, 255 - num);

		//ステージ描画
		if (Fead.InfoStg == 1) {
			BackStageDisp();
			TitleMAPDisp();
			PlayerMove();
		}
		//セレクトステージ描画
		if (Fead.InfoStg == 2) {
			SelectDisp();
		}
		//ゲームクリア描画
		if (Fead.InfoStg == 4) {
			GameClearDisp();
		}

		num += 2;

		//画面を再表示
		ScreenFlip();
	}

	//FeadIn();
	if (Fead.InfoStg == 1) {
		g_gameScene = GAME_SELECT;
		Fead.InfoStg = 2;
	}
	else if (Fead.InfoStg == 2) {
		g_gameScene = GAME_PLAY;
		Fead.InfoStg = 3;
	}
	else if(Fead.InfoStg == 4 && Fead.ClearFlg == 0) {
		Fead.InfoStg = 3;
		g_gameScene = GAME_PLAY;
	}
	else if(Fead.InfoStg == 4 && Fead.ClearFlg == 1)
	{
		Fead.InfoStg = 2;
		g_gameScene = GAME_SELECT;
	}
	//if (InfoStg == 3) {
	//	g_gameScene = GAME_CLEAR;
	//	//InfoStg = 4;
	//}
}

void FeadIn() {
	num = 0;
	Fead.FeadFlg = 1;
	//フェードイン
	while (num < 255) {
		SetDrawBright(num,num,num);

		//タイトルステージ描画
		if (Fead.InfoStg == 1) {
			BackStageDisp();
			TitleMAPDisp();
			PlayerMove();
		}
		//セレクトステージ描画
		if (Fead.InfoStg == 2) {
			SelectDisp();
		}
		//ゲームプレイ描画
		if (Fead.InfoStg == 3) {
			PlayDisp();
		}
		num += 2;

		//画面を再表示
		ScreenFlip();
	}
}