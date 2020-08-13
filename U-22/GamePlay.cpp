#include "DxLib.h"
#include "GameScene.h"
#include "GamePlay.h"
#include "KeyControl.h"
#include "player.h"
#include "Gimmick.h"
#include "Picture.h"
#include "Map.h"
#include "yoshitaka.h"
#include "Boss.h"
#include "UI.h"

void GamePlay() {
	PlayDisp();
	PlayMove();
	if (Fead.FeadFlg == 0) FeadIn();
	DrawFormatString(0, 650, 0x000000, "%d", g_map.select);

}

void PlayDisp() {
	BackStageDisp();
	gimmickDisp();
	StageDisp();
	
	/*for (int i = 0; i < STAGE_HEIGHT; i++) {
		for (int j = 0; j < STAGE_WIDTH; j++) {
			DrawFormatString(j * CHIPSIZE, i * CHIPSIZE, 0xFF0000, "%d", g_map.playStage[i][j]);
			DrawFormatString(j * CHIPSIZE + 20, i * CHIPSIZE, 0x0000FF, "%d", g_map.gimmickData[i][j]);
		}
	}*/
	
}

void PlayMove() {
	bossMove();
	gimmickMove();
	if(g_gimmick->moveFlg != true && g_gimmick->moveFlg2 != true) PlayerMove();

	for (int i = 0; i < STAGE_HEIGHT; i++) {
		for (int j = 0; j < STAGE_WIDTH; j++) {//playerより手前のマップの描画
			if (g_map.playStage[i][j] == BOSS_G_1 && g_map.playStage[i][j + 1] == BOSS_G_1) {
				if (g_player.py / CHIPSIZE != i + 1) {
					DrawRectGraph(j * CHIPSIZE, i * CHIPSIZE + 10, 0, 10, 128, 128, g_img.Cauldron, TRUE, FALSE);
				}
			}
		}
	}

	item_Box();

	if (g_map.playStage[int(g_player.py / CHIPSIZE)][int(g_player.px / CHIPSIZE) + 1] == 2) {
		//if ((g_map.select / 3) - 1 != 0){
		//g_map.select++;
		g_gameScene = GAME_CLEAR;
		//}
		//else {
		//	g_gameScene = GAME_SELECT;
		//}
	}
}