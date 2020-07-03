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
	/*for (int i = 0; i < STAGE_HEIGHT; i++) {
		for (int j = 0; j < STAGE_WIDTH; j++) {
			DrawFormatString(j * CHIPSIZE, i * CHIPSIZE, 0xFF0000, "%d", g_map.playStage[i][j]);
		}
	}*/
	DrawFormatString(0, 650, 0xFF00FF, "%d", g_player.item[0]);
	DrawFormatString(0, 670, 0xFF00FF, "%d", g_player.item[1]);
	DrawFormatString(0, 690, 0xFF00FF, "%d", g_player.item[2]);
}

void PlayMove() {
	gimmickMove();
	if(g_gimmick->moveFlg != true && g_gimmick->moveFlg2 != true) PlayerMove();

	if (g_map.playStage[int(g_player.py / CHIPSIZE)][int(g_player.px / CHIPSIZE) + 1] == 2) {
		g_gameScene = GAME_SELECT;
	}
}