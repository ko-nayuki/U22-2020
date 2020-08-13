#include "DxLib.h"
#include "GameScene.h"
#include "KeyControl.h"
#include "Gimmick.h"
#include "Map.h"
#include "player.h"
#include "GameClear.h"
#include "yoshitaka.h"
#include "Picture.h"
#include "Boss.h"

void GameClear() {
	GameClearDisp();
	GameClearMove();
}

void GameClearDisp() {
	BackStageDisp();
	gimmickDisp();
	StageDisp();

	DrawExtendGraph(50, 50, 200, 200, g_img.itemBox, FALSE);

	DrawFormatString(600, 300, 0xFFFFFF, "ステージクリア");
	//DrawFormatString(600, 400, 0xFFFFFF, "Dキーで次のステージへ");
}

void GameClearMove() {
	if (g_KeyFlg & PAD_INPUT_M) {
		if(g_map.select < STAGE - 1) g_map.select++;

		if ((g_map.select % 3) != 0) {
			Fead.InfoStg = 4;
			Fead.ClearFlg = 0;
			FeadOut();
			
			gimmickInit();
			StageInit();
			bossInit();
			for (int i = 0; i < ITEM_MAX; i++) {
				g_player.item[i] = K_NO;
			}
			g_player.itemNo = 0;

			if (CheckHitKey(KEY_INPUT_SPACE) == 1)
				g_KeyFlg = 0;
			//g_gameScene = GAME_PLAY;
		}
		else {
			Fead.InfoStg = 4;
			Fead.ClearFlg = 1;
			if (CheckHitKey(KEY_INPUT_SPACE) == 1)
				g_KeyFlg = 0;
			//g_gameScene = GAME_SELECT;
			FeadOut();
		}
	}
}