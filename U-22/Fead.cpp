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
#include "GameOver.h"
#include "Boss.h"
#include "enemy.h"

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
		//ゲームプレイ描画
		if (Fead.InfoStg == 3) {
			PlayDisp();
		}
		//ゲームクリア描画
		if (Fead.InfoStg == 4 && Fead.EndFlg == 0) {
			GameClearDisp();
		}
		//ゲームエンド描画
		if (Fead.InfoStg == 4 && Fead.EndFlg == 1) {
			GameComplete();
		}
		//ゲームオーバー描画
		if (Fead.InfoStg == 5) {
			GameOverDisp();
		}


		num += 2;

		//画面を再表示
		ScreenFlip();
	}

	//FeadIn();
	if (num >= 255 && g_gameScene == GAME_CLEAR && Fead.ClearFlg == 0) {
		if (g_map.select < STAGE - 1) g_map.select++;
	}

	if (Fead.InfoStg == 1) {
		g_gameScene = GAME_SELECT;
		Fead.InfoStg = 2;
	}
	else if (Fead.InfoStg == 2) {
		g_gameScene = GAME_PLAY;
		Fead.InfoStg = 3;
	}
	else if (Fead.InfoStg == 3 && Fead.EndFlg == 1) {
		Fead.InfoStg = 4;
		g_gameScene = GAME_CLEAR;
	}
	else if (Fead.InfoStg == 3) {
		Fead.InfoStg = 3;
		gimmickInit();
		StageInit();
		EnemyInit();
		bossInit();
		for (int i = 0; i < ITEM_MAX; i++) {
			g_player.item[i] = K_NO;
		}
		g_player.itemNo = 0;
		PlayerInit();
		g_gameScene = GAME_PLAY;
	}
	else if(Fead.InfoStg == 4 && Fead.ClearFlg == 0) {
		Fead.InfoStg = 3;
		//g_map.select++;
		g_gameScene = GAME_PLAY;
	}
	else if(Fead.InfoStg == 4 && Fead.ClearFlg == 1)
	{
		Fead.InfoStg = 2;
		g_gameScene = GAME_SELECT;
	}
	else if (Fead.InfoStg == 4 && Fead.ClearFlg == 2)
	{
		Fead.InfoStg = 1;
		g_gameScene = GAME_TITLE;
	}
	else if (Fead.InfoStg == 5 && Fead.OverFlg == 0)
	{
		Fead.InfoStg = 3;
		gimmickInit();
		StageInit();
		EnemyInit();
		bossInit();
		for (int i = 0; i < ITEM_MAX; i++) {
			g_player.item[i] = K_NO;
		}
		g_player.itemNo = 0;
		PlayerInit();
		g_gameScene = GAME_PLAY;
	}
	else if (Fead.InfoStg == 5 && Fead.OverFlg == 1)
	{
		Fead.InfoStg = 1;
		g_gameScene = GAME_TITLE;
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
		//エンド
		if (Fead.InfoStg == 4) {
			GameComplete();
		}
		num += 2;

		//画面を再表示
		ScreenFlip();
	}
}