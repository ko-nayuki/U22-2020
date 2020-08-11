#include "DxLib.h"
#include "GameScene.h"
#include "GamePlay.h"
#include "KeyControl.h"
#include "player.h"
#include "Gimmick.h"
#include "Picture.h"
#include "Map.h"
#include "yoshitaka.h"

float ItemAnime = 0;

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
	
	if (ItemAnime < 7.5) ItemAnime += 0.5F;

	for (int i = 0; i < ITEM_MAX; i++) {
		if (i != g_player.itemSelect) {
			DrawGraph(96 + (CHIPSIZE + 32) * i, CHIPSIZE * 10 + 32, g_img.itemBox, TRUE);
		} else {
			SetDrawBright(255, 0, 0);
			//DrawGraph(96 + (CHIPSIZE + 32) * i, CHIPSIZE * 10 + 32, g_img.itemBox, TRUE);
			DrawRotaGraph(128 + (CHIPSIZE + 32) * i, CHIPSIZE * 10 + 64, 1, -(ItemAnime / 3.14), g_img.itemBox, TRUE);
			SetDrawBright(255, 255, 255);
		}
		if (g_player.item[i] != 0) {
			DrawGraph(96 + (CHIPSIZE + 32) * i, CHIPSIZE * 10 + 32, g_img.kanzi[g_player.item[i] - 1], TRUE);
		}
	}

	if (g_KeyFlg & PAD_INPUT_Z) {
		if (++g_player.itemSelect > ITEM_MAX - 1) g_player.itemSelect = 0;
		ItemAnime = 0;
	}
	if (g_KeyFlg & PAD_INPUT_X) {
		if (--g_player.itemSelect < 0) g_player.itemSelect = ITEM_MAX - 1;
		ItemAnime = 0;
	}
}

void PlayMove() {
	gimmickMove();
	if(g_gimmick->moveFlg != true && g_gimmick->moveFlg2 != true) PlayerMove();

	if (g_map.playStage[int(g_player.py / CHIPSIZE)][int(g_player.px / CHIPSIZE) + 1] == 2) {
		//if ((g_map.select / 3) - 1 != 0){
		g_map.select++;
		g_gameScene = GAME_CLEAR;
		//}
		//else {
		//	g_gameScene = GAME_SELECT;
		//}
	}
}