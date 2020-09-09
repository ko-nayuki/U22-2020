#include "DxLib.h"
#include "GameScene.h"
#include "KeyControl.h"
#include "Gimmick.h"
#include "Map.h"
#include "player.h"
#include "GameClear.h"
#include "yoshitaka.h"
#include "Picture.h"
#include "enemy.h"
#include "Boss.h"
#include "yoshitaka.h"

void GameClear() {
	if (Fead.EndFlg == 0) {
		GameClearDisp();
		GameClearMove();
	}
	else {
		GameComplete();
		GameCompMove();
	}
}

void GameClearDisp() {
	BackStageDisp();
	gimmickDisp();
	StageDisp();

	//DrawExtendGraph(50, 50, 200, 200, g_img.itemBox, FALSE);

	DrawGraph(180, 100, g_img.ClearText, FALSE);

	DrawGraph(450, 450, g_img.NextText, FALSE);

	DrawFormatString(0, 650, 0x000000, "%d", g_map.select);


	//DrawFormatString(600, 300, 0xFFFFFF, "ステージクリア");
	//DrawFormatString(600, 400, 0xFFFFFF, "Dキーで次のステージへ");
}

void GameClearMove() {
	if (g_KeyFlg & PAD_INPUT_M || g_KeyFlg & PAD_INPUT_2) {
		if ((g_map.select + 1) % 3 != 0) {
			Fead.InfoStg = 4;
			Fead.ClearFlg = 0;
			FeadOut();

			gimmickInit();
			StageInit();
			EnemyInit();
			bossInit();
			PlayerInit();

			if (CheckHitKey(PAD_INPUT_1) == 1)
				g_KeyFlg = 0;
			//g_gameScene = GAME_PLAY;
		}
		else {
			PlayerInit();
			g_player.px = 128;
			g_player.py = 576;

			Fead.InfoStg = 4;
			Fead.ClearFlg = 1;
			if (g_Select.Checkkey == g_Select.CheckCorect) {
				++g_Select.CheckCorect;
				++g_Select.Key;
			}
			if (CheckHitKey(PAD_INPUT_1) == 1)
				g_KeyFlg = 0;
			//g_gameScene = GAME_SELECT;
			FeadOut();
		}
	}
}


void GameComplete() {
	DrawGraph(0, 0, g_img.End, FALSE);
	g_Select.Key = 4;

}

void GameCompMove() {
	if (g_KeyFlg & PAD_INPUT_2) {
		Fead.InfoStg = 4;
		Fead.ClearFlg = 2;
		FeadOut();
	}
}