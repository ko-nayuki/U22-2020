#include "DxLib.h"
#include "KeyControl.h"
#include "GameScene.h"
#include "StageSelect.h"
#include "Map.h"
#include "player.h"
#include "enemy.h"
#include "Gimmick.h"
#include "yoshitaka.h"
#include "Boss.h"


void StageSelect() {
	PlayerInit();
	SelectDisp();
	SelectMove();
	if (Fead.FeadFlg == 0) FeadIn();

}

void SelectDisp() {
	BackStageDisp();
	SelectMAPDisp();
	DrawFormatString(600, 300, 0x000000, "SPACE");
	DrawFormatString(0, 650, 0x000000, "%d", g_map.select);
	DrawFormatString(0, 670, 0x000000, "%d", g_Select.Key);

}
void SelectMove() {

	//if (g_map.playStage[int(g_player.py /CHIPSIZE) + 1][int(g_player.px / CHIPSIZE)] != 1) {
	//	g_player.py += 16;
	//}

	PlayerMove();

	//DrawBox(g_Select.stage3x, 0, g_Select.stage3x + 128, g_Select.stage1y, 0xFFFFFF, FALSE);

	if (g_Select.stage1x < g_player.px + 64 && g_Select.stage1x + 128 > g_player.px) {
		DrawString(0, 650, "ステージ１", 0x000000);
	}
	if (g_Select.stage2x < g_player.px + 64 && g_Select.stage2x + 128 > g_player.px) {
		DrawString(0, 650, "ステージ２", 0x000000);
	}
	if (g_Select.stage3x < g_player.px + 64 && g_Select.stage3x + 128 > g_player.px) {
		DrawString(0, 650, "ステージ３", 0x000000);
	}
	if (g_Select.stage4x < g_player.px + 64 && g_Select.stage4x + 128 > g_player.px) {
		DrawString(0, 650, "ステージ4", 0x000000);
	}

	/*if (g_KeyFlg & PAD_INPUT_RIGHT) {
		if (++g_map.select > STAGE - 1) g_map.select = 0;
	}
	if (g_KeyFlg & PAD_INPUT_LEFT) {
		if (--g_map.select < 0) g_map.select = STAGE - 1;
	}*/

	if (g_KeyFlg & PAD_INPUT_M || g_KeyFlg & PAD_INPUT_2) {
		/*Fead.InfoStg = 2;
		FeadOut();
		gimmickInit();
		StageInit();
		EnemyInit();
		bossInit();
		for (int i = 0; i < ITEM_MAX; i++) {
			g_player.item[i] = K_NO;
		}
		g_player.itemNo = 0;

		g_gameScene = GAME_PLAY;*/
			if (g_Select.stage1x < g_player.px + 64 && g_Select.stage1x + 128 > g_player.px) {
				g_map.select = 0;
				g_Select.Checkkey = 0;
				Fead.InfoStg = 2;
				FeadOut();
				gimmickInit();
				StageInit();
				EnemyInit();
				bossInit();
				for (int i = 0; i < ITEM_MAX; i++) {
					g_player.item[i] = K_NO;
				}
				g_player.itemNo = 0;
				//g_gameScene = GAME_PLAY;
			}
			if ((g_Select.stage2x < g_player.px + 64 && g_Select.stage2x + 128 > g_player.px) && g_Select.Key >= 1) {
				g_map.select = 3;
				g_Select.Checkkey = 1;
				Fead.InfoStg = 2;
				FeadOut();
				gimmickInit();
				StageInit();
				EnemyInit();
				bossInit();
				for (int i = 0; i < ITEM_MAX; i++) {
					g_player.item[i] = K_NO;
				}
				g_player.itemNo = 0;
			}
			if ((g_Select.stage3x < g_player.px + 64 && g_Select.stage3x + 128 > g_player.px) && g_Select.Key >= 2) {
				g_map.select = 6;
				g_Select.Checkkey = 2;
				Fead.InfoStg = 2;
				FeadOut();
				gimmickInit();
				StageInit();
				EnemyInit();
				bossInit();
				for (int i = 0; i < ITEM_MAX; i++) {
					g_player.item[i] = K_NO;
				}
				g_player.itemNo = 0;
			}
			if ((g_Select.stage4x < g_player.px + 64 && g_Select.stage4x + 128 > g_player.px) && g_Select.Key >= 3) {
				g_map.select = 9;
				g_Select.Checkkey = 3;
				Fead.InfoStg = 2;
				FeadOut();
				gimmickInit();
				StageInit();
				EnemyInit();
				bossInit();
				for (int i = 0; i < ITEM_MAX; i++) {
					g_player.item[i] = K_NO;
				}
				g_player.itemNo = 0;
			}
	}
}
