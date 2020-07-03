#include "DxLib.h"
#include "GameScene.h"
#include "GamePlay.h"
#include "KeyControl.h"
#include "player.h"
#include "Gimmick.h"
#include "Picture.h"
#include "Map.h"

void GamePlay() {
	PlayDisp();
	PlayMove();
}

void PlayDisp() {
	BackStageDisp();
	gimmickDisp();
	StageDisp();
	DrawFormatString(0, 400, 0xFF00FF, "%d", g_player.px / CHIPSIZE);
	DrawFormatString(0, 450, 0xFF00FF, "%d", g_player.py / CHIPSIZE);
}

void PlayMove() {
	gimmickMove();
	if(g_gimmick->moveFlg != true) PlayerMove();

	if (g_map.playStage[int(g_player.py / CHIPSIZE)][int(g_player.px / CHIPSIZE) + 1] == 2) {
		g_gameScene = GAME_SELECT;
	}
}