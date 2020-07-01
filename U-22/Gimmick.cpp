#include "DxLib.h"
#include "Gimmick.h"
#include "player.h"
#include "GamePlay.h"
#include "Map.h"
#include "Picture.h"

void gimmickDisp() {
	DrawGraph(g_gimmick[LIFT].x, g_gimmick[LIFT].y, g_img.door[int(g_gimmick[LIFT].anime)], TRUE);
	DrawFormatString(0, 600, 0xFF00FF, "%d", g_player.item[0]);
}

void gimmickMove() {

	//playerがアイテムを拾う処理
	if (g_player.itemNo < ITEM_MAX) {
		//上
		if (g_map.playStage[int(g_player.py / CHIPSIZE)][int(g_player.px / CHIPSIZE) + 1] == 3) {
			g_player.item[g_player.itemNo++] = K_UE;
			g_map.playStage[int(g_player.py / CHIPSIZE)][int(g_player.px / CHIPSIZE) + 1] = 0;
		}
	}

	//エレベーター処理
	if (g_map.playStage[int(g_player.py /CHIPSIZE)][int(g_player.px / CHIPSIZE) + 1] == 4) {
		if (*g_player.item == K_UE) {
			*g_player.item = 0;
			g_gimmick[LIFT].moveFlg = true;
			g_map.playStage[int(g_player.py / CHIPSIZE)][int(g_player.px / CHIPSIZE) + 1] = 0;
		}
	}else {
		if (*g_player.item == 1) {
			if (g_gimmick[LIFT].anime < 2.0F)g_gimmick[LIFT].anime += 0.1F;
		} else {
			if (g_gimmick[LIFT].anime > 0.0F)g_gimmick[LIFT].anime -= 0.1F;
		}
	}

	if (g_gimmick[LIFT].moveFlg == true) {
		if (g_player.py == CHIPSIZE) {
			g_map.playStage[int(g_player.py / CHIPSIZE) + 1][int(g_player.px / CHIPSIZE) + 1] = 1;
			if (g_gimmick[LIFT].anime < 2.0F)g_gimmick[LIFT].anime += 0.2F;
			else g_gimmick[LIFT].moveFlg = false;
		} else {
			g_player.py -= 2;
			g_gimmick[LIFT].y = g_player.py;
		}
	}

}

void gimmickInit() {
	for (int i = 0; i < GIMMICK_NUM; i++) {
		g_gimmick[i].moveFlg = false;
		g_gimmick[i].x = 0;
		g_gimmick[i].y = 0;
		g_gimmick[i].anime = 0;
	}
}