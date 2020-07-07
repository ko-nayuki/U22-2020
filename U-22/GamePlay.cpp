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
	DrawFormatString(0, 400, 0x000000, "%d", g_player.py / CHIPSIZE);
	DrawFormatString(0, 450, 0x000000, "%d", g_player.py );
	/*for (int i = 0; i < STAGE_HEIGHT; i++) {
		for (int j = 0; j < STAGE_WIDTH; j++) {
			DrawFormatString(j * CHIPSIZE, i * CHIPSIZE, 0xFF0000, "%d", g_map.playStage[i][j]);
		}
	}*/
	DrawFormatString(0, 600, 0x000000, "%d", g_player.itemNo);

	for (int i = 0; i < ITEM_MAX; i++) {
		if (i != g_player.itemSelect) {
			DrawGraph(96 + (CHIPSIZE + 32) * i, CHIPSIZE * 10 + 32, g_img.itemBox, TRUE);
		} else {
			SetDrawBright(255, 0, 0);
			DrawGraph(96 + (CHIPSIZE + 32) * i, CHIPSIZE * 10 + 32, g_img.itemBox, TRUE);
			SetDrawBright(255, 255, 255);
		}
		if (g_player.item[i] != 0) {
			DrawGraph(96 + (CHIPSIZE + 32) * i, CHIPSIZE * 10 + 32, g_img.kanzi[g_player.item[i] - 1], TRUE);
		}
	}

	if (g_KeyFlg & PAD_INPUT_RIGHT) {
		if (++g_player.itemSelect > ITEM_MAX - 1) g_player.itemSelect = 0;
	}
	if (g_KeyFlg & PAD_INPUT_LEFT) {
		if (--g_player.itemSelect < 0) g_player.itemSelect = ITEM_MAX - 1;
	}

}

void PlayMove() {
	gimmickMove();
	if(g_gimmick->moveFlg != true && g_gimmick->moveFlg2 != true) PlayerMove();

	if (g_map.playStage[int(g_player.py / CHIPSIZE)][int(g_player.px / CHIPSIZE) + 1] == 2) {
		g_gameScene = GAME_SELECT;
	}
}