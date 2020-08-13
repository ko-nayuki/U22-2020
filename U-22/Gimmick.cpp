#include "DxLib.h"
#include "Gimmick.h"
#include "player.h"
#include "GamePlay.h"
#include "Map.h"
#include "Picture.h"

bool smokeFlg[7] = { false };


void gimmickDisp() {
	DrawGraph(g_gimmick[LIFT].x, g_gimmick[LIFT].y, g_img.door[int(g_gimmick[LIFT].anime)], TRUE);
	DrawGraph(g_gimmick[BOUND].x, g_gimmick[BOUND].y, g_img.spring[int(g_gimmick[BOUND].anime)], TRUE);
	//SetDrawBright(255, 0, 0);
	DrawGraph(g_gimmick[DROP].x, g_gimmick[DROP].y, g_img.itemBox, TRUE);
	DrawGraph(g_gimmick[BOMB].x, g_gimmick[BOMB].y, g_img.itemBox, TRUE);
	//SetDrawBright(255, 255, 255);
	DrawGraph(g_gimmick[WARP_A].x, g_gimmick[WARP_A].y, g_img.itemBox, TRUE);
	DrawGraph(g_gimmick[WARP_B].x, g_gimmick[WARP_B].y, g_img.itemBox, TRUE);
	//DrawFormatString(200, 550, 0x0000ff, "%d", g_gimmick[LIFT].h * CHIPSIZE);
	//DrawFormatString(200, 570, 0x0000ff, "%d", g_gimmick[LIFT].y);
}

void gimmickMove() {

	//playerがアイテムを拾う処理
	if (g_player.itemNo < ITEM_MAX) {
		//上
		if (g_map.playStage[int(g_player.py / CHIPSIZE)][int((g_player.px + 32) / CHIPSIZE)] == A) {
			g_player.item[g_player.itemNo++] = K_UE;
			g_map.playStage[int(g_player.py / CHIPSIZE)][int((g_player.px + 32) / CHIPSIZE)] = 0;
		}
		//下
		if (g_map.playStage[int(g_player.py / CHIPSIZE)][int((g_player.px + 32) / CHIPSIZE)] == B) {
			g_player.item[g_player.itemNo++] = K_SITA;
			g_map.playStage[int(g_player.py / CHIPSIZE)][int((g_player.px + 32) / CHIPSIZE)] = 0;
		}
		//力
		if (g_map.playStage[int(g_player.py / CHIPSIZE)][int((g_player.px + 32) / CHIPSIZE)] == C) {
			g_player.item[g_player.itemNo++] = K_TIKARA;
			g_map.playStage[int(g_player.py / CHIPSIZE)][int((g_player.px + 32) / CHIPSIZE)] = 0;
		}
		//破
		if (g_map.playStage[int(g_player.py / CHIPSIZE)][int((g_player.px + 32) / CHIPSIZE)] == D) {
			g_player.item[g_player.itemNo++] = K_HA;
			g_map.playStage[int(g_player.py / CHIPSIZE)][int((g_player.px + 32) / CHIPSIZE)] = 0;
		}
		//消
		if (g_map.playStage[int(g_player.py / CHIPSIZE)][int((g_player.px + 32) / CHIPSIZE)] == E) {
			g_player.item[g_player.itemNo++] = K_SHOU;
			g_map.playStage[int(g_player.py / CHIPSIZE)][int((g_player.px + 32) / CHIPSIZE)] = 0;
		}
		//動
		if (g_map.playStage[int(g_player.py / CHIPSIZE)][int((g_player.px + 32) / CHIPSIZE)] == F) {
			g_player.item[g_player.itemNo++] = K_DOU;
			g_map.playStage[int(g_player.py / CHIPSIZE)][int((g_player.px + 32) / CHIPSIZE)] = 0;
		}
		//爆
		/*if (g_map.playStage[int(g_player.py / CHIPSIZE)][int((g_player.px + 32) / CHIPSIZE)] == 26) {
			g_player.item[g_player.itemNo++] = K_BAKU;
			g_map.playStage[int(g_player.py / CHIPSIZE)][int((g_player.px + 32) / CHIPSIZE)] = 0;
		}*/

		//アイテム欄左詰め
		for (int i = 0; i < g_player.itemNo; i++) {
			if (g_player.item[i] == K_NO) {
				g_player.item[i] = g_player.item[i + 1];
				g_player.item[i + 1] = K_NO;
			}
		}
	}

	//漢字の重力
	for (int i = 0; i < STAGE_HEIGHT; i++) {
		for (int j = 0; j < STAGE_WIDTH; j++) {
			if (g_map.playStage[i][j] >= A) {
				if (g_map.playStage[i + 1][j] == AIR) {
					g_map.playStage[i + 1][j] = g_map.playStage[i][j];
					g_map.playStage[i][j] = AIR;
				}
			}
			if (g_map.playStage[i][j] == GIM_2) {//爆弾
				if (g_map.playStage[i - 1][j] == G) {
					g_map.playStage[i - 1][j] = AIR;
					g_map.gimmickData[i][j] = AIR;
					g_map.playStage[i][j] = GIM_7;
					g_gimmick[BOMB].x = j * CHIPSIZE;
					g_gimmick[BOMB].y = i * CHIPSIZE;
					g_gimmick[BOMB].ONFlg = true;
				}
			}
		}

	}

	if (key[KEY_INPUT_SPACE] == 1) mistake();

	liftMove();		//エレベーター
	boundMove();	//ジャンプ台
	breakMove();	//破壊できる壁
	dropMove();		//落下ギミック
	fireMove();		//炎
	warpMove();		//ワープ
	bombMove();		//爆弾

	cauldronMove();	//大釜
}

void liftMove() {
	//エレベーター処理
	if (g_map.playStage[int(g_player.py / CHIPSIZE)][int((g_player.px + 32) / CHIPSIZE)] == GIM_1) {
		if (g_player.item[g_player.itemSelect] == K_UE || g_player.item[g_player.itemSelect] == K_SITA &&
			g_gimmick[LIFT].moveFlg == false && g_gimmick[LIFT].moveFlg2 == false) {
			if (g_gimmick[LIFT].anime < 2.0F)g_gimmick[LIFT].anime += 0.1F;
			//DrawGraph(g_player.px, g_player.py - 32, g_img.marubatu[0], TRUE);
		}else {
			//DrawGraph(g_player.px, g_player.py - 32, g_img.marubatu[1], TRUE);
		}
		//if (g_gimmick[LIFT].y != CHIPSIZE) {//[上]を使う
		if (g_player.item[g_player.itemSelect] == K_UE && key[KEY_INPUT_SPACE] == 1
			&& g_gimmick[LIFT].moveFlg == false && g_gimmick[LIFT].moveFlg2 == false) {

			for (g_gimmick[LIFT].h = int(g_player.py / CHIPSIZE); g_gimmick[LIFT].h > 0; g_gimmick[LIFT].h--) {
				if (g_map.playStage[g_gimmick[LIFT].h][int(g_gimmick[LIFT].x / CHIPSIZE)] == BLOCK) {
					if (g_map.playStage[g_gimmick[LIFT].h - 1][int(g_gimmick[LIFT].x / CHIPSIZE)] == AIR) {
						g_gimmick[LIFT].h--;
						g_gimmick[LIFT].moveFlg = true;
						g_map.playStage[int(g_player.py / CHIPSIZE)][int((g_player.px + 32) / CHIPSIZE)] = AIR;
						g_player.item[g_player.itemSelect] = K_NO;
						g_player.itemNo--;
						smokeFlg[LIFT] = true;
						g_map.gimmickData[int(g_player.py / CHIPSIZE)][int((g_player.px + 32) / CHIPSIZE)] = AIR;
						break;

					}
				}
			}
		}
		//}
		//if (g_gimmick[LIFT].y != CHIPSIZE * 9) {//[下]を使う
		if (g_player.item[g_player.itemSelect] == K_SITA && key[KEY_INPUT_SPACE] == 1
			&& g_gimmick[LIFT].moveFlg == false && g_gimmick[LIFT].moveFlg2 == false) {

			for (g_gimmick[LIFT].h = int(g_player.py / CHIPSIZE); g_gimmick[LIFT].h < STAGE_HEIGHT; g_gimmick[LIFT].h++) {
				if (g_map.playStage[g_gimmick[LIFT].h][int(g_gimmick[LIFT].x / CHIPSIZE)] == BLOCK) {
					if (g_map.playStage[g_gimmick[LIFT].h - 1][int(g_gimmick[LIFT].x / CHIPSIZE)] == AIR) {

						g_gimmick[LIFT].h--;
						g_gimmick[LIFT].moveFlg2 = true;
						g_map.playStage[int(g_player.py / CHIPSIZE)][int((g_player.px + 32) / CHIPSIZE)] = AIR;
						g_player.item[g_player.itemSelect] = K_NO;
						g_player.itemNo--;
						smokeFlg[LIFT] = true;
						g_map.gimmickData[int(g_player.py / CHIPSIZE)][int((g_player.px + 32) / CHIPSIZE)] = AIR;
						break;
					}
				}
			}
		}
		//}
	}
	else {
		if (g_gimmick[LIFT].anime > 0.0F)g_gimmick[LIFT].anime -= 0.1F;
		if (g_gimmick[LIFT].moveFlg == false && g_gimmick[LIFT].moveFlg2 == false && g_gimmick[LIFT].anime <= 0.0F) {
			if (g_gimmick[LIFT].y != -CHIPSIZE) {
				g_map.gimmickData[int(g_gimmick[LIFT].y / CHIPSIZE)][int(g_gimmick[LIFT].x) / CHIPSIZE] = GIM_1;
			}
		}
	}

	if (g_gimmick[LIFT].moveFlg == true) {//上昇の処理
		if (smokeFlg[LIFT] == true) {//煙
			smoke(g_gimmick[LIFT].x, g_gimmick[LIFT].y);
		}

		//if (g_gimmick[LIFT].ONFlg == true) {
		if (g_gimmick[LIFT].y == g_gimmick[LIFT].h * CHIPSIZE) {
			g_map.playStage[int(g_player.py / CHIPSIZE)][int((g_player.px + 32) / CHIPSIZE)] = GIM_1;
			if (g_gimmick[LIFT].anime < 2.0F)g_gimmick[LIFT].anime += 0.1F;
			else g_gimmick[LIFT].moveFlg = false;

		}
		else if (g_gimmick[LIFT].y < g_gimmick[LIFT].h * CHIPSIZE) {
			g_gimmick[LIFT].y++, g_player.py = g_gimmick[LIFT].y;
		}
		else {
			if (g_gimmick[LIFT].anime > 0.0F)g_gimmick[LIFT].anime -= 0.1F;
			else g_gimmick[LIFT].y -= 2, g_player.py = g_gimmick[LIFT].y;
		}
		//}
	}

	if (g_gimmick[LIFT].moveFlg2 == true) {//下降の処理
		if (smokeFlg[LIFT] == true) {//煙
			smoke(g_gimmick[LIFT].x, g_gimmick[LIFT].y);
		}
		if (g_player.py == g_gimmick[LIFT].h * CHIPSIZE) {
			g_map.playStage[int(g_player.py / CHIPSIZE)][int((g_player.px + 32) / CHIPSIZE)] = GIM_1;
			if (g_gimmick[LIFT].anime < 2.0F)g_gimmick[LIFT].anime += 0.1F;
			else g_gimmick[LIFT].moveFlg2 = false;
		}
		else if (g_gimmick[LIFT].y > g_gimmick[LIFT].h * CHIPSIZE) {
			g_gimmick[LIFT].y--;
		}
		else {
			if (g_gimmick[LIFT].anime > 0.0F)g_gimmick[LIFT].anime -= 0.1F;
			else g_gimmick[LIFT].y += 2, g_player.py = g_gimmick[LIFT].y;
		}
	}

}
void boundMove() {
	//ジャンプ台処理
	if (g_map.playStage[int(g_player.py / CHIPSIZE) + 1][int((g_player.px + 32) / CHIPSIZE)] == GIM_2) {
		if (g_gimmick[BOUND].y != CHIPSIZE) {//[力]を使う
			if (g_player.item[g_player.itemSelect] == K_TIKARA && key[KEY_INPUT_SPACE] == 1 &&
				g_gimmick[BOUND].ONFlg == false) {
				g_gimmick[BOUND].ONFlg = true;
				g_player.item[g_player.itemSelect] = K_NO;
				g_player.itemNo--;
				smokeFlg[BOUND] = true;
				g_map.gimmickData[int(g_player.py / CHIPSIZE) + 1][int((g_player.px + 32) / CHIPSIZE)] = AIR;
				g_gimmick[BOUND].x = int((g_player.px + 32) / CHIPSIZE) * CHIPSIZE;
				g_gimmick[BOUND].y = (int(g_player.py / CHIPSIZE) + 1) * CHIPSIZE;
			}else if (g_player.item[g_player.itemSelect] == K_TIKARA && key[KEY_INPUT_SPACE] == 1 &&
				g_gimmick[BOUND].ONFlg == true) {
				g_map.gimmickData[g_gimmick[BOUND].y / CHIPSIZE][g_gimmick[BOUND].x / CHIPSIZE] = GIM_2;
				g_map.gimmickData[int(g_player.py / CHIPSIZE) + 1][int((g_player.px + 32) / CHIPSIZE)] = AIR;
				g_gimmick[BOUND].x = int((g_player.px + 32) / CHIPSIZE) * CHIPSIZE;
				g_gimmick[BOUND].y = (int(g_player.py / CHIPSIZE) + 1) * CHIPSIZE;
				smokeFlg[BOUND] = true;
			}
		}
		/*if (g_player.item[g_player.itemSelect] == K_TIKARA || g_player.item[g_player.itemSelect] == K_BAKU) {
			DrawGraph(g_player.px, g_player.py - 32, g_img.marubatu[0], TRUE);
		}
		else if(g_gimmick[BOUND].ONFlg == false){
			DrawGraph(g_player.px, g_player.py - 32, g_img.marubatu[1], TRUE);
		}*/
	}

	if (g_gimmick[BOUND].ONFlg == true) {
		if (smokeFlg[BOUND] == true) {//煙
			smoke(g_gimmick[BOUND].x, g_gimmick[BOUND].y);
		}
		if (g_gimmick[LIFT].moveFlg == false && g_gimmick[LIFT].moveFlg2 == false) {
			if (g_player.py + CHIPSIZE == g_gimmick[BOUND].y && (g_player.px + 32 >= g_gimmick[BOUND].x && g_player.px + 32 <= g_gimmick[BOUND].x + CHIPSIZE)) {
				g_player.fallSpeed = -JUMP_POWER;
				g_gimmick[BOUND].anime = 3;
			}

			//頭上にブロックがあったら
			/*if (g_map.playStage[int(g_player.py / CHIPSIZE)][int(g_player.px / CHIPSIZE) + 1] == BLOCK) {

				g_player.py = g_player.py + 1;
				g_player.fallSpeed = 0;

			}*/
			if (g_map.playStage[int(g_player.py / CHIPSIZE)][int(g_player.px / CHIPSIZE)] == BLOCK ||
				g_map.playStage[int((g_player.py - 8) / CHIPSIZE)][int((g_player.px + 64) / CHIPSIZE)] == BLOCK ||
				g_map.playStage[int(g_player.py / CHIPSIZE)][int(g_player.px / CHIPSIZE) + 1] == BLOCK ||
				g_player.py == 64) {

				g_player.py = g_player.py + 1;
				g_player.fallSpeed = 0;
			}

		}

		if (g_gimmick[BOUND].anime > 0) g_gimmick[BOUND].anime -= 0.1F;
	}

}
void breakMove() {
	//破壊できる壁の処理
	if (g_map.gimmickData[int(g_player.py / CHIPSIZE)][int((g_player.px + 4) / CHIPSIZE) + 1] == GIM_3 ||
		g_map.gimmickData[int(g_player.py / CHIPSIZE)][int((g_player.px - 4) / CHIPSIZE)] == GIM_3) {
		if (g_player.item[g_player.itemSelect] == K_HA && key[KEY_INPUT_SPACE] == 1) {
			g_gimmick[BREAK].ONFlg = true;
			g_player.item[g_player.itemSelect] = K_NO;
			g_player.itemNo--;
			smokeFlg[BREAK] = true;
		}
		/*if (g_player.item[g_player.itemSelect] == K_HA) {
			DrawGraph(g_player.px, g_player.py - 32, g_img.marubatu[0], TRUE);
		}
		else{
			DrawGraph(g_player.px, g_player.py - 32, g_img.marubatu[1], TRUE);
		}*/
	}
	if (g_gimmick[BREAK].ONFlg == true) {
		if (smokeFlg[BREAK] == true) {//煙
			smoke(g_player.px, g_player.py);
		}
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
void dropMove() {
	//落下ギミックの処理
	if (g_map.playStage[int(g_player.py / CHIPSIZE)][int((g_player.px + 32) / CHIPSIZE)] == GIM_402) {
		if (g_player.item[g_player.itemSelect] == K_SITA && key[KEY_INPUT_SPACE] == 1 && g_gimmick[DROP].ONFlg == false) {
			g_gimmick[DROP].ONFlg = true;
			g_player.item[g_player.itemSelect] = K_NO;
			g_player.itemNo--;
			smokeFlg[DROP] = true;
			g_map.gimmickData[int(g_player.py / CHIPSIZE)][int((g_player.px + 32) / CHIPSIZE)] = AIR;
			g_gimmick[DROP].x = int((g_player.px + 32) / CHIPSIZE) * CHIPSIZE;
			g_gimmick[DROP].y = int(g_player.py / CHIPSIZE) * CHIPSIZE;
		}
		/*if (g_player.item[g_player.itemSelect] == K_SITA) {
			DrawGraph(g_player.px, g_player.py - 32, g_img.marubatu[0], TRUE);
		}
		else{
			DrawGraph(g_player.px, g_player.py - 32, g_img.marubatu[1], TRUE);
		}*/
	}
	if (g_gimmick[DROP].ONFlg == true) {

		if (smokeFlg[DROP] == true) {//煙
			smoke(g_gimmick[DROP].x, g_gimmick[DROP].y);
		}
		for (int i = (g_gimmick[DROP].x / CHIPSIZE) + 1; i < STAGE_WIDTH; i++) {//右
			if (g_map.gimmickData[int(g_gimmick[DROP].y / CHIPSIZE) + 1][i] == 8) {
				g_map.playStage[int(g_gimmick[DROP].y / CHIPSIZE) + 1][i] = AIR;
			} else {
				break;
			}
		}
		for (int i = (g_gimmick[DROP].x / CHIPSIZE) - 1; i > 0; i--) {//左
			if (g_map.gimmickData[int(g_gimmick[DROP].y / CHIPSIZE) + 1][i] == 8) {
				g_map.playStage[int(g_gimmick[DROP].y / CHIPSIZE) + 1][i] = AIR;
			} else {
				break;
			}
		}
		for (int i = 0; i < STAGE_HEIGHT; i++) {//元に戻す
			for (int j = 0; j < STAGE_WIDTH; j++) {
				if (g_map.gimmickData[int(g_player.py / CHIPSIZE) - 1][int((g_player.px + 32) / CHIPSIZE)] == GIM_401) {
					if (g_map.gimmickData[i][j] == 8) {
						g_map.playStage[i][j] = BLOCK;
					}
					if (g_map.playStage[i][j] == GIM_402) {
						g_map.gimmickData[i][j] = GIM_402;
					}
					g_gimmick[DROP].ONFlg = false;
				}
			}
		}
	}
}
void fireMove() {
	//炎の処理
	if (g_map.gimmickData[int(g_player.py / CHIPSIZE)][int((g_player.px + 4) / CHIPSIZE) + 1] == GIM_5 ||
		g_map.gimmickData[int(g_player.py / CHIPSIZE)][int((g_player.px - 4) / CHIPSIZE)] == GIM_5) {
		if (g_player.item[g_player.itemSelect] == K_SHOU && key[KEY_INPUT_SPACE] == 1) {
			g_gimmick[FIRE].ONFlg = true;
			g_player.item[g_player.itemSelect] = K_NO;
			g_player.itemNo--;
			smokeFlg[FIRE] = true;
		}
		/*if (g_player.item[g_player.itemSelect] == K_SHOU) {
			DrawGraph(g_player.px, g_player.py - 32, g_img.marubatu[0], TRUE);
		}
		else{
			DrawGraph(g_player.px, g_player.py - 32, g_img.marubatu[1], TRUE);
		}*/
	}
	if (g_gimmick[FIRE].ONFlg == true) {
		if (smokeFlg[FIRE] == true) {//煙
			smoke(g_player.px, g_player.py);
		}
		for (int i = 0; i < STAGE_HEIGHT; i++) {
			for (int j = 0; j < STAGE_WIDTH; j++) {
				if (g_map.gimmickData[i][j] == 10) {
					g_map.playStage[i][j] = AIR;
					g_map.gimmickData[i][j] = 0;
				}
			}
		}
		g_gimmick[BREAK].ONFlg = false;
	}
}
void warpMove() {
	//ワープ処理
	if (g_map.playStage[int(g_player.py / CHIPSIZE)][int((g_player.px + 32) / CHIPSIZE)] == GIM_601 ||
		g_map.playStage[int(g_player.py / CHIPSIZE)][int((g_player.px + 32) / CHIPSIZE)] == GIM_602) {
		if (g_player.item[g_player.itemSelect] == K_DOU && key[KEY_INPUT_SPACE] == 1) {
			g_gimmick[WARP_A].ONFlg = true;
			g_gimmick[WARP_B].ONFlg = true;
			g_gimmick[WARP_A].moveFlg = true;
			g_gimmick[WARP_B].moveFlg = true;
			g_player.item[g_player.itemSelect] = K_NO;
			g_player.itemNo--;
			smokeFlg[WARP_A] = true;
		}
		/*if (g_player.item[g_player.itemSelect] == K_DOU) {
			DrawGraph(g_player.px, g_player.py - 32, g_img.marubatu[0], TRUE);
		}
		else if(g_gimmick[WARP_A].ONFlg == false){
			DrawGraph(g_player.px, g_player.py - 32, g_img.marubatu[1], TRUE);
		}*/
	}
	if (g_gimmick[WARP_A].ONFlg == true) {
		if (smokeFlg[WARP_A] == true) {//煙
			smoke(g_gimmick[WARP_A].x, g_gimmick[WARP_A].y);
			smoke(g_gimmick[WARP_B].x, g_gimmick[WARP_B].y);
		}
		if (g_gimmick[WARP_A].moveFlg == true) {
			if (g_map.playStage[int(g_player.py / CHIPSIZE)][int((g_player.px + 32) / CHIPSIZE)] == GIM_601) {
				g_gimmick[WARP_B].moveFlg = false;
				g_player.px = g_gimmick[WARP_B].x;
				g_player.py = g_gimmick[WARP_B].y;
			}
		}
		if (g_map.playStage[int(g_player.py / CHIPSIZE)][int((g_player.px + 32) / CHIPSIZE)] != GIM_602) {
			g_gimmick[WARP_B].moveFlg = true;
		}
	}
	if (g_gimmick[WARP_B].ONFlg == true) {
		if (g_gimmick[WARP_B].moveFlg == true) {
			if (g_map.playStage[int(g_player.py / CHIPSIZE)][int((g_player.px + 32) / CHIPSIZE)] == GIM_602) {
				g_gimmick[WARP_A].moveFlg = false;
				g_player.px = g_gimmick[WARP_A].x;
				g_player.py = g_gimmick[WARP_A].y;
			}
		}
		if (g_map.playStage[int(g_player.py / CHIPSIZE)][int((g_player.px + 32) / CHIPSIZE)] != GIM_601) {
			g_gimmick[WARP_A].moveFlg = true;
		}
	}
}
void bombMove() {
	//爆弾の処理
	if (g_map.playStage[int(g_player.py / CHIPSIZE) + 1][int((g_player.px + 32) / CHIPSIZE)] == GIM_2) {
		if (g_player.item[g_player.itemSelect] == K_BAKU && key[KEY_INPUT_SPACE] == 1 &&
			g_gimmick[BOMB].ONFlg == false) {//[爆]を使う
			g_gimmick[BOMB].ONFlg = true;
			g_player.item[g_player.itemSelect] = K_NO;
			g_player.itemNo--;
			smokeFlg[BOMB] = true;
			g_map.playStage[int(g_player.py / CHIPSIZE) + 1][int((g_player.px + 32) / CHIPSIZE)] = GIM_7;
			g_map.gimmickData[int(g_player.py / CHIPSIZE) + 1][int((g_player.px + 32) / CHIPSIZE)] = AIR;
			g_gimmick[BOMB].x = int((g_player.px + 32) / CHIPSIZE) * CHIPSIZE;
			g_gimmick[BOMB].y = (int(g_player.py / CHIPSIZE) + 1) * CHIPSIZE;
		}
	}
	if (g_gimmick[BOMB].ONFlg == true) {
		DrawFormatString(g_gimmick[BOMB].x, g_gimmick[BOMB].y + 20, 0x00ff00, "%f", g_gimmick[BOMB].anime);
		g_gimmick[BOMB].anime += 0.1F;
		if (g_gimmick[BOMB].anime > 10.0F) {
			g_map.playStage[g_gimmick[BOMB].y / CHIPSIZE][g_gimmick[BOMB].x / CHIPSIZE] = AIR;
			g_gimmick[BOMB].anime = 0;
			g_gimmick[BOMB].y = -CHIPSIZE;
			g_gimmick[BOMB].x = -CHIPSIZE;
			g_gimmick[BOMB].ONFlg = false;
		}
	}

}

void cauldronMove() {
	//大釜の処理
	if (g_map.playStage[int(g_player.py / CHIPSIZE)][int((g_player.px + 32) / CHIPSIZE)] == BOSS_G_1) {
		for (int i = 0; i < STAGE_HEIGHT; i++) {
			for (int j = 0; j < STAGE_WIDTH; j++) {
				if (g_map.playStage[i][j] == 3) {
					g_player.px = j * CHIPSIZE;
					g_player.py = i * CHIPSIZE;
				}
			}
		}
	}
}

void mistake() {
	//エレベータ
	if (g_map.playStage[int(g_player.py / CHIPSIZE)][int((g_player.px + 32) / CHIPSIZE)] == GIM_1) {
		if (g_player.item[g_player.itemSelect] != K_UE && g_player.item[g_player.itemSelect] != K_SITA) {
			DrawGraph(g_player.px, g_player.py - 32, g_img.marubatu[1], TRUE);
		}
	}
	//ジャンプ台
	if (g_map.playStage[int(g_player.py / CHIPSIZE) + 1][int((g_player.px + 32) / CHIPSIZE)] == GIM_2) {
		if (g_player.item[g_player.itemSelect] != K_TIKARA) {
			DrawGraph(g_player.px, g_player.py - 32, g_img.marubatu[1], TRUE);
		}
	}
	//破壊できる壁
	if (g_map.gimmickData[int(g_player.py / CHIPSIZE)][int((g_player.px + 4) / CHIPSIZE) + 1] == GIM_3 ||
		g_map.gimmickData[int(g_player.py / CHIPSIZE)][int((g_player.px - 4) / CHIPSIZE)] == GIM_3) {
		if (g_player.item[g_player.itemSelect] != K_HA) {
			DrawGraph(g_player.px, g_player.py - 32, g_img.marubatu[1], TRUE);
		}
	}
	//落下看板
	if (g_map.gimmickData[int(g_player.py / CHIPSIZE)][int((g_player.px + 32) / CHIPSIZE)] == GIM_402) {
		if (g_player.item[g_player.itemSelect] != K_SITA) {
			DrawGraph(g_player.px, g_player.py - 32, g_img.marubatu[1], TRUE);
		}
	}
	//炎
	if (g_map.gimmickData[int(g_player.py / CHIPSIZE)][int((g_player.px + 4) / CHIPSIZE) + 1] == GIM_5 ||
		g_map.gimmickData[int(g_player.py / CHIPSIZE)][int((g_player.px - 4) / CHIPSIZE)] == GIM_5) {
		if (g_player.item[g_player.itemSelect] != K_SHOU) {
			DrawGraph(g_player.px, g_player.py - 32, g_img.marubatu[1], TRUE);
		}
	}
	//ワープ
	if (g_map.playStage[int(g_player.py / CHIPSIZE)][int((g_player.px + 32) / CHIPSIZE)] == GIM_601 ||
		g_map.playStage[int(g_player.py / CHIPSIZE)][int((g_player.px + 32) / CHIPSIZE)] == GIM_602) {
		if (g_player.item[g_player.itemSelect] != K_DOU) {
			DrawGraph(g_player.px, g_player.py - 32, g_img.marubatu[1], TRUE);
		}
	}
}

void smoke(int smokeX, int smokeY) {

	static float anime = 0;

	DrawGraph(smokeX, smokeY, g_img.smoke[int(anime)], TRUE);

	if (anime < 7.0F) anime += 0.2F;
	else {
		anime = 0;
		for (int i = 0; i < 7; i++)smokeFlg[i] = false;
	}

}

void gimmickInit() {
	for (int i = 0; i < GIMMICK_NUM; i++) {
		g_gimmick[i].ONFlg = false;
		g_gimmick[i].moveFlg = false;
		g_gimmick[i].moveFlg2 = false;
		g_gimmick[i].x = -CHIPSIZE;
		g_gimmick[i].y = -CHIPSIZE;
		g_gimmick[i].w = 0;
		g_gimmick[i].h = 0;
		g_gimmick[i].anime = 0;
	}
}