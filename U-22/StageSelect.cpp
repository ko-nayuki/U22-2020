#include "DxLib.h"
#include "KeyControl.h"
#include "GameScene.h"
#include "StageSelect.h"
#include "Map.h"
#include "player.h"
#include "Gimmick.h"

void StageSelect() {
	SelectDisp();
	SelectMove();
}

void SelectDisp() {
	BackStageDisp();
	SelectMAPDisp();
	DrawFormatString(600, 300, 0xFF00FF, "SPACE");
	DrawFormatString(0, 600, 0xFF00FF, "%d", g_map.select);
}
void SelectMove() {
	PlayerMove();
	if (g_KeyFlg & PAD_INPUT_RIGHT) {
		if (++g_map.select > STAGE - 1) g_map.select = 0;
	}
	if (g_KeyFlg & PAD_INPUT_LEFT) {
		if (--g_map.select < 0) g_map.select = STAGE - 1;
	}

	if (key[KEY_INPUT_SPACE] == 1) {
		gimmickInit();
		StageInit();
		g_player.px = 1 * CHIPSIZE;
		g_player.py = 9 * CHIPSIZE;
		for (int i = 0; i < ITEM_MAX; i++) {
			g_player.item[i] = K_NO;
		}

		g_gameScene = GAME_PLAY;
	}
}
