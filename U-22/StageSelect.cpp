#include "DxLib.h"
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
}
void SelectMove() {
	PlayerMove();
	if (key[KEY_INPUT_SPACE] == 1) {
		g_gameScene = GAME_PLAY;
		gimmickInit();
		StageInit();
		g_player.px = 1 * CHIPSIZE;
		g_player.py = 9 * CHIPSIZE;
	}
}
