#include "DxLib.h"
#include "Gimmick.h"
#include "player.h"
#include "GamePlay.h"
#include "Map.h"
#include "Picture.h"

void gimmickDisp() {
	DrawGraph(g_gimmick[LIFT].x, g_gimmick[LIFT].y, g_img.door[0], TRUE);
}

void gimmickMove() {
	//エレベーター処理
	if (g_map.playStage[int(g_player.py / 64)][int(g_player.px / 64) + 1] == 2) {
		g_gimmick[LIFT].moveFlg = true;
		g_map.playStage[int(g_player.py / 64)][int(g_player.px / 64) + 1] = 0;
	}

	if (g_gimmick[LIFT].moveFlg == true) {
		g_player.py -= 2;
		g_gimmick[LIFT].y = g_player.py;
		if (g_player.py / 64 <= 0) {
			g_map.playStage[int(g_player.py / 64) + 2][int(g_player.px / 64) + 1] = 9;
			g_gimmick[LIFT].moveFlg = false;
		}
	}
}

void gimmickInit() {
	for (int i = 0; i < GIMMICK_NUM; i++) {
		g_gimmick[i].moveFlg = false;
		g_gimmick[i].x = 0;
		g_gimmick[i].y = 0;
	}
}