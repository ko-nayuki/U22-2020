#include "DxLib.h"
#include "Gimmick.h"
#include "player.h"
#include "GamePlay.h"
#include "Map.h"
#include "Picture.h"

void gimmickDisp() {
	DrawGraph(g_gimmick[LIFT].x, g_gimmick[LIFT].y, g_img.door[int(g_gimmick[LIFT].anime)], TRUE);
	DrawGraph(g_gimmick[BOUND].x, g_gimmick[BOUND].y, g_img.spring[int(g_gimmick[BOUND].anime)], TRUE);
}

void gimmickMove() {
	
	//playerがアイテムを拾う処理
	if (g_player.itemNo < ITEM_MAX) {
		//上
		if (g_map.playStage[int(g_player.py / CHIPSIZE)][int(g_player.px / CHIPSIZE) + 1] == A) {
			g_player.item[g_player.itemNo++] = K_UE;
			g_map.playStage[int(g_player.py / CHIPSIZE)][int(g_player.px / CHIPSIZE) + 1] = 0;
		}
		//下
		if (g_map.playStage[int(g_player.py / CHIPSIZE)][int(g_player.px / CHIPSIZE) + 1] == B) {
			g_player.item[g_player.itemNo++] = K_SITA;
			g_map.playStage[int(g_player.py / CHIPSIZE)][int(g_player.px / CHIPSIZE) + 1] = 0;
		}
		//力
		if (g_map.playStage[int(g_player.py / CHIPSIZE)][int(g_player.px / CHIPSIZE) + 1] == C) {
			g_player.item[g_player.itemNo++] = K_TIKARA;
			g_map.playStage[int(g_player.py / CHIPSIZE)][int(g_player.px / CHIPSIZE) + 1] = 0;
		}
		//壊
		if (g_map.playStage[int(g_player.py / CHIPSIZE)][int(g_player.px / CHIPSIZE) + 1] == D) {
			g_player.item[g_player.itemNo++] = K_KAI;
			g_map.playStage[int(g_player.py / CHIPSIZE)][int(g_player.px / CHIPSIZE) + 1] = 0;
		}

		//アイテム欄左詰め
		for (int i = 0; i < g_player.itemNo; i++) {
			if (g_player.item[i] == K_NO) {
				g_player.item[i] = g_player.item[i + 1];
				g_player.item[i + 1] = K_NO;
			}
		}
	}

	//エレベーター処理
	if (g_map.playStage[int(g_player.py / CHIPSIZE)][int((g_player.px+32) / CHIPSIZE)] == GIM_1) {
		if (g_player.item[g_player.itemSelect] == K_UE || g_player.item[g_player.itemSelect] == K_SITA) {
			if (g_gimmick[LIFT].anime < 2.0F)g_gimmick[LIFT].anime += 0.1F;
		}
		if (g_gimmick[LIFT].y != CHIPSIZE) {//[上]を使う
			if (g_player.item[g_player.itemSelect] == K_UE && key[KEY_INPUT_SPACE] == 1
				&& g_gimmick[LIFT].moveFlg == false && g_gimmick[LIFT].moveFlg2 == false) {
				g_gimmick[LIFT].moveFlg = true;
				g_map.playStage[int(g_player.py / CHIPSIZE)][int(g_player.px / CHIPSIZE) + 1] = AIR;
				g_player.item[g_player.itemSelect] = K_NO;
				g_player.itemNo--;
			}
		}
		if (g_gimmick[LIFT].y != CHIPSIZE * 9) {//[下]を使う
			if (g_player.item[g_player.itemSelect] == K_SITA && key[KEY_INPUT_SPACE] == 1
				&& g_gimmick[LIFT].moveFlg == false && g_gimmick[LIFT].moveFlg2 == false) {
				g_gimmick[LIFT].moveFlg2 = true;
				g_map.playStage[int(g_player.py / CHIPSIZE)][int(g_player.px / CHIPSIZE) + 1] = AIR;
				g_player.item[g_player.itemSelect] = K_NO;
				g_player.itemNo--;
			}
		}
	}
	else {
		if (g_gimmick[LIFT].anime > 0.0F)g_gimmick[LIFT].anime -= 0.1F;
	}

	if (g_gimmick[LIFT].moveFlg == true) {//上昇の処理
		if (g_gimmick[LIFT].y == CHIPSIZE) {

			g_map.playStage[int(g_player.py / CHIPSIZE)][int(g_player.px / CHIPSIZE) + 1] = GIM_1;
			if (g_gimmick[LIFT].anime < 2.0F)g_gimmick[LIFT].anime += 0.1F;
			else g_gimmick[LIFT].moveFlg = false;

		} else if(g_gimmick[LIFT].y < CHIPSIZE){
			g_gimmick[LIFT].y++;

		} else {
			if (g_gimmick[LIFT].anime > 0.0F)g_gimmick[LIFT].anime -= 0.1F;
			else g_gimmick[LIFT].y -= 2, g_player.py = g_gimmick[LIFT].y;
		}
	}

	if (g_gimmick[LIFT].moveFlg2 == true) {//下降の処理
		if (g_player.py == CHIPSIZE * 9) {
			g_map.playStage[int(g_player.py / CHIPSIZE)][int(g_player.px / CHIPSIZE) + 1] = GIM_1;
			if (g_gimmick[LIFT].anime < 2.0F)g_gimmick[LIFT].anime += 0.1F;
			else g_gimmick[LIFT].moveFlg2 = false;
		} else if (g_gimmick[LIFT].y > CHIPSIZE * 9) {
			g_gimmick[LIFT].y--;
		} else {
			if (g_gimmick[LIFT].anime > 0.0F)g_gimmick[LIFT].anime -= 0.1F;
			else g_gimmick[LIFT].y += 2, g_player.py = g_gimmick[LIFT].y;
		}
	}

	//ジャンプ台処理
	if (g_map.playStage[int(g_player.py / CHIPSIZE) + 1][int(g_player.px / CHIPSIZE)] == GIM_2) {
		if (g_gimmick[BOUND].y != CHIPSIZE) {//[力]を使う
			if (g_player.item[g_player.itemSelect] == K_TIKARA && key[KEY_INPUT_SPACE] == 1 &&
				g_gimmick[BOUND].ONFlg == false) {
				g_gimmick[BOUND].ONFlg = true;
				g_player.item[g_player.itemSelect] = K_NO;
				g_player.itemNo--;
				
			}
		}
	}

	if (g_gimmick[BOUND].ONFlg == true) {
		if (g_gimmick[LIFT].moveFlg == false && g_gimmick[LIFT].moveFlg2 == false) {
			if (g_map.playStage[int(g_player.py / CHIPSIZE) + 1][int((g_player.px+32)/ CHIPSIZE)] == GIM_2) {
				g_player.fallSpeed = -JUMP_POWER;
				g_gimmick[BOUND].anime = 3;
			}

			//頭上にブロックがあったら
			if (g_map.playStage[int(g_player.py / CHIPSIZE)][int(g_player.px / CHIPSIZE) + 1] == BLOCK) {

				g_player.py = g_player.py + 1;
				g_player.fallSpeed = 0;

			}

		}

		if (g_gimmick[BOUND].anime > 0) g_gimmick[BOUND].anime -= 0.1F;
	}
	
	//破壊できる壁の処理
	if (g_map.gimmickData[int(g_player.py / CHIPSIZE)][int((g_player.px+4) / CHIPSIZE) + 1] == GIM_3 ||
		g_map.gimmickData[int(g_player.py / CHIPSIZE)][int((g_player.px-4) / CHIPSIZE)] == GIM_3 ) {
		if (g_player.item[g_player.itemSelect] == K_KAI && key[KEY_INPUT_SPACE] == 1) {
			g_gimmick[BREAK].ONFlg = true;
			g_player.item[g_player.itemSelect] = K_NO;
			g_player.itemNo--;
		}
	}
	if (g_gimmick[BREAK].ONFlg == true) {
		for (int i = 0; i < STAGE_HEIGHT; i++) {
			for (int j = 0; j < STAGE_WIDTH; j++) {
				if (g_map.gimmickData[i][j] == 7) {
					g_map.playStage[i][j] = AIR;
					g_map.gimmickData[i][j] = 0;
				}
			}
		}
		g_gimmick[BREAK].ONFlg = false;
	}

}

void gimmickInit() {
	for (int i = 0; i < GIMMICK_NUM; i++) {
		g_gimmick[i].ONFlg = false;
		g_gimmick[i].moveFlg = false;
		g_gimmick[i].moveFlg2 = false;
		g_gimmick[i].x = 0;
		g_gimmick[i].y = 0;
		g_gimmick[i].anime = 0;
	}
}