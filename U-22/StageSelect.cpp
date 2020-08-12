#include "DxLib.h"
#include "KeyControl.h"
#include "GameScene.h"
#include "StageSelect.h"
#include "Map.h"
#include "player.h"
#include "Gimmick.h"
#include "yoshitaka.h"
#include "Boss.h"

void StageSelect() {
	g_gimmick[BOUND].tikara = 0;
	SelectDisp();
	SelectMove();
	if (Fead.FeadFlg == 0) FeadIn();

}

void SelectDisp() {
	BackStageDisp();
	SelectMAPDisp();
	DrawFormatString(600, 300, 0x000000, "SPACE");
	DrawFormatString(0, 650, 0x000000, "%d", g_map.select);
}
void SelectMove() {

	if (g_map.playStage[int(g_player.py /CHIPSIZE) + 1][int(g_player.px / CHIPSIZE)] != 1) {
		g_player.py += 16;
	}

	PlayerMove();

	if (g_KeyFlg & PAD_INPUT_RIGHT) {
		if (++g_map.select > STAGE - 1) g_map.select = 0;
	}
	if (g_KeyFlg & PAD_INPUT_LEFT) {
		if (--g_map.select < 0) g_map.select = STAGE - 1;
	}

	if (g_KeyFlg & PAD_INPUT_M) {
		Fead.InfoStg = 2;
		FeadOut();
		gimmickInit();
		StageInit();
		bossInit();
		for (int i = 0; i < ITEM_MAX; i++) {
			g_player.item[i] = K_NO;
		}
		g_player.itemNo = 0;
		
		//g_gameScene = GAME_PLAY;
	}
}
