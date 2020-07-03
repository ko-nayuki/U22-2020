#include "DxLib.h"
#include "Gimmick.h"
#include "player.h"
#include "GamePlay.h"
#include "Map.h"
#include "Picture.h"

void gimmickDisp() {
	DrawGraph(g_gimmick[LIFT].x, g_gimmick[LIFT].y, g_img.door[int(g_gimmick[LIFT].anime)], TRUE);
	DrawFormatString(0, 650, 0xFF00FF, "%d", g_player.item[0]);
	DrawFormatString(0, 670, 0xFF00FF, "%d", g_player.item[1]);
	DrawFormatString(0, 690, 0xFF00FF, "%d", g_player.item[2]);
	DrawFormatString(0, 710, 0xFF00FF, "%d", g_player.item[3]);
	DrawFormatString(0, 730, 0xFF00FF, "%d", g_player.item[4]);
}

void gimmickMove() {

	//player���A�C�e�����E������
	if (g_player.itemNo < ITEM_MAX) {
		//��
		if (g_map.playStage[int(g_player.py / CHIPSIZE)][int(g_player.px / CHIPSIZE) + 1] == 3) {
			g_player.item[g_player.itemNo++] = K_UE;
			g_map.playStage[int(g_player.py / CHIPSIZE)][int(g_player.px / CHIPSIZE) + 1] = 0;
		}

		//�A�C�e�������l��
		for (int i = 0; i < g_player.itemNo; i++) {
			if (g_player.item[i] == 0) {
				g_player.item[i] = g_player.item[i + 1];
				g_player.item[i + 1] = K_NO;
				g_player.itemNo--;
			}
		}
	}

	for (int i = 0; i < g_player.itemNo + 1; i++) {
		//�G���x�[�^�[����
		if (g_map.playStage[int(g_player.py / CHIPSIZE)][int(g_player.px / CHIPSIZE) + 1] == 4) {
			if (g_player.item[i] == K_UE) {
				g_gimmick[LIFT].moveFlg = true;
				g_map.playStage[int(g_player.py / CHIPSIZE)][int(g_player.px / CHIPSIZE) + 1] = 0;
				g_player.item[i] = K_NO;
			}
		}
		if (g_player.item[i] == 1) {
			if (g_gimmick[LIFT].anime < 2.0F)g_gimmick[LIFT].anime += 0.1F;
		}
		if (g_gimmick[LIFT].moveFlg == true) {
			if (g_player.py == CHIPSIZE) {
				g_map.playStage[int(g_player.py / CHIPSIZE) + 1][int(g_player.px / CHIPSIZE) + 1] = 1;
				if (g_gimmick[LIFT].anime < 2.0F)g_gimmick[LIFT].anime += 0.1F;
				else g_gimmick[LIFT].moveFlg = false;
			} else {
				if (g_gimmick[LIFT].anime > 0.0F)g_gimmick[LIFT].anime -= 0.1F;
				else g_player.py -= 2, g_gimmick[LIFT].y = g_player.py;
			}
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