#include "DxLib.h"
#include "Gimmick.h"
#include "player.h"
#include "GamePlay.h"
#include "Map.h"
#include "Picture.h"
#include "KeyControl.h"
#include "Sounds.h"
#include "enemy.h"

bool smokeFlg[GIMMICK_NUM] = { false };
bool use_Flg = false;
float goal_Anime = 0.0;

void gimmickDisp() {
	DrawGraph(g_gimmick[LIFT].x, g_gimmick[LIFT].y, g_img.door[int(g_gimmick[LIFT].anime)], TRUE);
	DrawGraph(g_gimmick[BOUND].x, g_gimmick[BOUND].y, g_img.spring[int(g_gimmick[BOUND].anime)], TRUE);
	//SetDrawBright(255, 0, 0);
	DrawGraph(g_gimmick[DROP].x, g_gimmick[DROP].y, g_img.drop, TRUE);
	//SetDrawBright(255, 255, 255);
	//DrawGraph(g_gimmick[WARP_A].x, g_gimmick[WARP_A].y, g_img.warp, TRUE);
	//DrawGraph(g_gimmick[WARP_B].x, g_gimmick[WARP_B].y, g_img.warp, TRUE);
	//DrawFormatString(200, 550, 0x0000ff, "%d", g_gimmick[LIFT].h * CHIPSIZE);
	//DrawFormatString(200, 570, 0x0000ff, "%d", g_gimmick[LIFT].y);
	//DrawFormatString(200, 590, 0xff00ff, "%d", g_gimmick[WARP_A].x / CHIPSIZE);
	//DrawFormatString(200, 610, 0xff00ff, "%d", g_gimmick[WARP_A].w / CHIPSIZE);

	for (int i = 0; i < STAGE_HEIGHT; i++) {//ゴールの描画
		for (int j = 0; j < STAGE_WIDTH; j++) {
			if (g_map.playStage[i][j] == 2 && g_map.playStage[i][j + 1] == 2 && g_map.playStage[i + 1][j] == 2) {
				DrawGraph(j * CHIPSIZE, i * CHIPSIZE, g_img.goal[int(goal_Anime)], TRUE);
			}
			if (g_map.gimmickData[i][j] == GIM_401) {
				if (g_map.playStage[i][j] == BLOCK) {
					DrawGraph(j * CHIPSIZE, i * CHIPSIZE, g_img.gear[0], TRUE);
				} else {
					DrawGraph(j * CHIPSIZE, i * CHIPSIZE, g_img.gear[1], TRUE);
				}
			}
			if (g_map.gimmickData[i][j] == GIM_5 && g_map.gimmickData[i][j + 1] == GIM_5 && g_map.gimmickData[i + 1][j] == GIM_5) {
				DrawGraph(j * CHIPSIZE, i * CHIPSIZE, g_img.fire[int(goal_Anime) % 2], TRUE);
			}
		}
	}
	if (goal_Anime < 4.0) goal_Anime += 0.1F;
	else goal_Anime = 0.0;
}

void gimmickMove() {

	//playerがアイテムを拾う処理
	if (g_player.itemNo < ITEM_MAX) {
		//上
		if (g_map.playStage[int(g_player.py / CHIPSIZE)][int((g_player.px + 32) / CHIPSIZE)] == A) {
			g_player.item[g_player.itemNo++] = K_UE;
			g_player.aab = 1;
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
			g_player.syo = 1;
			g_map.playStage[int(g_player.py / CHIPSIZE)][int((g_player.px + 32) / CHIPSIZE)] = 0;
		}
		//動
		if (g_map.playStage[int(g_player.py / CHIPSIZE)][int((g_player.px + 32) / CHIPSIZE)] == F) {
			g_player.item[g_player.itemNo++] = K_DOU;
			g_player.aaa = 1;
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
			if (g_map.playStage[i][j] == GIM_2 && g_map.gimmickData[i][j] == GIM_2) {//爆弾
				if (g_map.playStage[i - 1][j] == G) {
					g_map.playStage[i - 1][j] = AIR;
					//g_map.gimmickData[i][j] = AIR;
					//g_map.playStage[i][j] = GIM_7;
					g_map.gimmickData[i][j] = AIR;
					g_map.playStage[i][j] = BLOCK;
					g_gimmick[BOMB].x = j * CHIPSIZE;
					g_gimmick[BOMB].y = (i - 1) * CHIPSIZE;
					g_gimmick[BOMB].anime = 50;
					g_gimmick[BOMB].ONFlg = true;
				}
			}
		}

	}

	mistake();
	if (use_Flg == true) use_Effect(g_player.px, g_player.py - 40);

	liftMove();		//エレベーター
	boundMove();	//ジャンプ台
	breakMove();	//破壊できる壁
	dropMove();		//落下ギミック
	fireMove();		//炎
	warpMove();		//ワープ
	bombMove();		//爆弾

	cauldronMove();	//大釜
	if (g_map.select == 8) bigboundMove(); //横長ジャンプ台

	if (g_map.playStage[int((g_player.py + 32) / CHIPSIZE) + 1][int((g_player.px + 32) / CHIPSIZE)] == BLOCK) {
		if (g_player.py % CHIPSIZE != 0) g_player.py--;
	}

	for (int i = 1; i < ENEMY_MAX; i++) {//毒敵
		if (HitBoxPlayer3(&g_player, &g_enemy3[i]) == TRUE
			&& g_player.item[g_player.itemSelect] == K_SHOU) {
			PlaySoundMem(g_sounds.Fire, DX_PLAYTYPE_BACK, TRUE);//消毒音
			g_enemy3[i].ex3 = CHIPSIZE * -1, g_enemy3[i].ey3 = CHIPSIZE * -1;
			g_player.syo = 0;
			use_Flg = true;
		}
	}
}

void liftMove() {
	//エレベーター処理
	if (g_map.playStage[int(g_player.py / CHIPSIZE)][int((g_player.px + 32) / CHIPSIZE)] == GIM_1) {
		if (g_player.item[g_player.itemSelect] == K_UE || g_player.item[g_player.itemSelect] == K_SITA &&
			g_gimmick[LIFT].moveFlg == false && g_gimmick[LIFT].moveFlg2 == false) {
			if (g_gimmick[LIFT].anime < 2.0F)g_gimmick[LIFT].anime += 0.1F;
			//DrawGraph(g_player.px, g_player.py - 32, g_img.marubatu[0], TRUE);
		}
		else {
			//DrawGraph(g_player.px, g_player.py - 32, g_img.marubatu[1], TRUE);
		}
		//if (g_gimmick[LIFT].y != CHIPSIZE) {//[上]を使う
		if (g_player.item[g_player.itemSelect] == K_UE && (key[KEY_INPUT_SPACE] == 1 || g_KeyFlg & PAD_INPUT_2)
			&& g_gimmick[LIFT].moveFlg == false && g_gimmick[LIFT].moveFlg2 == false) {

			g_gimmick[LIFT].x = int((g_player.px + 32) / CHIPSIZE) * CHIPSIZE;
			g_gimmick[LIFT].y = int(g_player.py / CHIPSIZE) * CHIPSIZE;

			for (g_gimmick[LIFT].h = int(g_player.py / CHIPSIZE); g_gimmick[LIFT].h > 0; g_gimmick[LIFT].h--) {
				if (g_map.playStage[g_gimmick[LIFT].h][int(g_gimmick[LIFT].x / CHIPSIZE)] == BLOCK) {
					if (g_map.playStage[g_gimmick[LIFT].h - 1][int(g_gimmick[LIFT].x / CHIPSIZE)] == AIR) {
						g_gimmick[LIFT].h--;
						g_gimmick[LIFT].moveFlg = true;
						use_Flg = true;
						PlaySoundMem(g_sounds.Eleverter, DX_PLAYTYPE_BACK, TRUE);//エレベータ音
						g_map.playStage[int(g_player.py / CHIPSIZE)][int((g_player.px + 32) / CHIPSIZE)] = AIR;
						//g_player.item[g_player.itemSelect] = K_NO;
						//g_player.itemNo--;
						smokeFlg[LIFT] = true;
						g_map.gimmickData[int(g_player.py / CHIPSIZE)][int((g_player.px + 32) / CHIPSIZE)] = AIR;
						break;

					}
				}
			}
		}
		//}
		//if (g_gimmick[LIFT].y != CHIPSIZE * 9) {//[下]を使う
		if (g_player.item[g_player.itemSelect] == K_SITA && (key[KEY_INPUT_SPACE] == 1 || g_KeyFlg & PAD_INPUT_2)
			&& g_gimmick[LIFT].moveFlg == false && g_gimmick[LIFT].moveFlg2 == false) {

			g_gimmick[LIFT].x = int((g_player.px + 32) / CHIPSIZE) * CHIPSIZE;
			g_gimmick[LIFT].y = int(g_player.py / CHIPSIZE) * CHIPSIZE;

			for (g_gimmick[LIFT].h = int(g_player.py / CHIPSIZE); g_gimmick[LIFT].h < STAGE_HEIGHT; g_gimmick[LIFT].h++) {
				if (g_map.playStage[g_gimmick[LIFT].h][int(g_gimmick[LIFT].x / CHIPSIZE)] == BLOCK) {
					if (g_map.playStage[g_gimmick[LIFT].h - 1][int(g_gimmick[LIFT].x / CHIPSIZE)] == AIR) {

						g_gimmick[LIFT].h--;
						g_gimmick[LIFT].moveFlg2 = true;
						use_Flg = true;
						PlaySoundMem(g_sounds.Eleverter, DX_PLAYTYPE_BACK, TRUE);//エレベータ音
						g_map.playStage[int(g_player.py / CHIPSIZE)][int((g_player.px + 32) / CHIPSIZE)] = AIR;
						//g_player.item[g_player.itemSelect] = K_NO;
						//g_player.itemNo--;
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
			else {
				g_map.gimmickData[int(g_gimmick[LIFT].y / CHIPSIZE)][int(g_gimmick[LIFT].x / CHIPSIZE)] = GIM_1;
				g_gimmick[LIFT].moveFlg = false;
			}

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
			else {
				g_map.gimmickData[int(g_gimmick[LIFT].y / CHIPSIZE)][int(g_gimmick[LIFT].x / CHIPSIZE)] = GIM_1;
				g_gimmick[LIFT].moveFlg2 = false;
			}
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
	if (g_map.playStage[int(g_player.py / CHIPSIZE) + 1][int((g_player.px + 32) / CHIPSIZE)] == GIM_2 &&
		g_map.gimmickData[int(g_player.py / CHIPSIZE) + 1][int((g_player.px + 32) / CHIPSIZE)] == GIM_2) {
		if (g_gimmick[BOUND].y != CHIPSIZE) {//[力]を使う
			if (g_player.item[g_player.itemSelect] == K_TIKARA && (key[KEY_INPUT_SPACE] == 1 || g_KeyFlg & PAD_INPUT_2)) {
				use_Flg = true;
				//g_player.item[g_player.itemSelect] = K_NO;
				//g_player.itemNo--;
				smokeFlg[BOUND] = true;
				g_map.gimmickData[int(g_player.py / CHIPSIZE) + 1][int((g_player.px + 32) / CHIPSIZE)] = AIR;
				g_gimmick[BOUND].x = int((g_player.px + 32) / CHIPSIZE) * CHIPSIZE;
				g_gimmick[BOUND].y = (int(g_player.py / CHIPSIZE) + 1) * CHIPSIZE;
			}
		}
		/*if (g_player.item[g_player.itemSelect] == K_TIKARA || g_player.item[g_player.itemSelect] == K_BAKU) {
			DrawGraph(g_player.px, g_player.py - 32, g_img.marubatu[0], TRUE);
		}
		else if(g_gimmick[BOUND].ONFlg == false){
			DrawGraph(g_player.px, g_player.py - 32, g_img.marubatu[1], TRUE);
		}*/
	}

	if (smokeFlg[BOUND] == true) {//煙
		smoke(g_gimmick[BOUND].x, g_gimmick[BOUND].y);
	}

	if (g_gimmick[BOUND].ONFlg == true) {
		if (g_gimmick[LIFT].moveFlg == false && g_gimmick[LIFT].moveFlg2 == false) {
			if (g_player.py + CHIPSIZE == g_gimmick[BOUND].y && (g_player.px + 32 >= g_gimmick[BOUND].x && g_player.px + 32 <= g_gimmick[BOUND].x + CHIPSIZE)) {
				g_player.fallSpeed = -JUMP_POWER;
				g_gimmick[BOUND].anime = 3;
				g_gimmick[BOUND].ONFlg = false;
			}

			//頭上にブロックがあったら
			/*if (g_map.playStage[int(g_player.py / CHIPSIZE)][int(g_player.px / CHIPSIZE) + 1] == BLOCK) {

				g_player.py = g_player.py + 1;
				g_player.fallSpeed = 0;

			}*/
			/*if (g_map.playStage[int(g_player.py / CHIPSIZE)][int(g_player.px / CHIPSIZE)] == BLOCK ||
				g_map.playStage[int((g_player.py - 8) / CHIPSIZE)][int((g_player.px + 64) / CHIPSIZE)] == BLOCK ||
				g_map.playStage[int((g_player.py - 8) / CHIPSIZE)][int((g_player.px) / CHIPSIZE)] == BLOCK ||
				g_map.playStage[int(g_player.py / CHIPSIZE)][int(g_player.px / CHIPSIZE) + 1] == BLOCK ||
				g_player.py == 64) {

				g_player.py = g_player.py + 1;
				g_player.fallSpeed = 0;
			}*/
		}
	}

	if (g_gimmick[BOUND].anime > 0) g_gimmick[BOUND].anime -= 0.1F;
	if (g_map.playStage[int(g_player.py / CHIPSIZE) + 1][int((g_player.px + 32) / CHIPSIZE)] == GIM_2 &&
		g_map.gimmickData[int(g_player.py / CHIPSIZE) + 1][int((g_player.px + 32) / CHIPSIZE)] == AIR) {
		g_gimmick[BOUND].x = int((g_player.px + 32) / CHIPSIZE) * CHIPSIZE;
		g_gimmick[BOUND].y = (int(g_player.py / CHIPSIZE) + 1) * CHIPSIZE;
		g_gimmick[BOUND].ONFlg = true;
		PlaySoundMem(g_sounds.Spring, DX_PLAYTYPE_BACK, TRUE);//ばね音
	}
}
void breakMove() {
	//破壊できる壁の処理
	if ((g_map.gimmickData[int(g_player.py / CHIPSIZE)][int((g_player.px + 4) / CHIPSIZE) + 1] == GIM_3 ||
		g_map.gimmickData[int(g_player.py / CHIPSIZE)][int((g_player.px - 4) / CHIPSIZE)] == GIM_3) &&
		g_map.playStage[int(g_player.py / CHIPSIZE) + 1][int((g_player.px + 32) / CHIPSIZE)] != AIR) {
		if (g_player.item[g_player.itemSelect] == K_HA && (key[KEY_INPUT_SPACE] == 1 || g_KeyFlg & PAD_INPUT_2)) {
			g_gimmick[BREAK].ONFlg = true;
			use_Flg = true;
			//g_player.item[g_player.itemSelect] = K_NO;
			//g_player.itemNo--;
			smokeFlg[BREAK] = true;
			PlaySoundMem(g_sounds.Break, DX_PLAYTYPE_BACK, TRUE);//破壊音
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
		for (g_gimmick[BREAK].y = int(g_player.py / CHIPSIZE); ;) {
			for (g_gimmick[BREAK].x = int(g_player.px / CHIPSIZE) + 1; g_gimmick[BREAK].x < STAGE_WIDTH;) {
				if (g_map.gimmickData[g_gimmick[BREAK].y][g_gimmick[BREAK].x] == 7) {
					g_map.playStage[g_gimmick[BREAK].y][g_gimmick[BREAK].x] = AIR;
					g_map.gimmickData[g_gimmick[BREAK].y][g_gimmick[BREAK].x] = 0;
					g_gimmick[BREAK].y--;
				}
				else {
					g_gimmick[BREAK].y = int(g_player.py / CHIPSIZE);

					if (g_map.gimmickData[g_gimmick[BREAK].y][g_gimmick[BREAK].x + 1] == 7) {
						g_gimmick[BREAK].x++;
					}
					else {
						break;
					}
				}
			}
			break;
		}

		if (g_map.gimmickData[int(g_player.py / CHIPSIZE)][int((g_player.px - 4) / CHIPSIZE)] == GIM_3) {
			for (g_gimmick[BREAK].y = int(g_player.py / CHIPSIZE); ;) {
				for (g_gimmick[BREAK].x = int(g_player.px / CHIPSIZE) - 1; g_gimmick[BREAK].x > 0;) {
					if (g_map.gimmickData[g_gimmick[BREAK].y][g_gimmick[BREAK].x] == 7) {
						g_map.playStage[g_gimmick[BREAK].y][g_gimmick[BREAK].x] = AIR;
						g_map.gimmickData[g_gimmick[BREAK].y][g_gimmick[BREAK].x] = 0;
						g_gimmick[BREAK].y--;
					}
					else {
						g_gimmick[BREAK].y = int(g_player.py / CHIPSIZE);

						if (g_map.gimmickData[g_gimmick[BREAK].y][g_gimmick[BREAK].x - 1] == 7) {
							g_gimmick[BREAK].x--;
						}
						else {
							break;
						}
					}
				}
				break;
			}
		}
		g_gimmick[BREAK].ONFlg = false;
	}

}
void dropMove() {
	//落下ギミックの処理(落下)
	if (g_map.playStage[int(g_player.py / CHIPSIZE)][int((g_player.px + 32) / CHIPSIZE)] == GIM_402) {
		if (g_player.item[g_player.itemSelect] == K_SITA && (key[KEY_INPUT_SPACE] == 1 || g_KeyFlg & PAD_INPUT_2) && g_gimmick[DROP].ONFlg == false) {
			g_gimmick[DROP].ONFlg = true;
			g_gimmick[DROP].moveFlg = true;
			use_Flg = true;
			//g_player.item[g_player.itemSelect] = K_NO;
			//g_player.itemNo--;
			smokeFlg[DROP] = true;
			g_map.gimmickData[int(g_player.py / CHIPSIZE)][int((g_player.px + 32) / CHIPSIZE)] = AIR;
			g_gimmick[DROP].x = int((g_player.px + 32) / CHIPSIZE) * CHIPSIZE;
			g_gimmick[DROP].y = int(g_player.py / CHIPSIZE) * CHIPSIZE;
			PlaySoundMem(g_sounds.Fall, DX_PLAYTYPE_BACK, TRUE);//落下音
		}
		/*if (g_player.item[g_player.itemSelect] == K_SITA) {
			DrawGraph(g_player.px, g_player.py - 32, g_img.marubatu[0], TRUE);
		}
		else{
			DrawGraph(g_player.px, g_player.py - 32, g_img.marubatu[1], TRUE);
		}*/
	}
	//落下ギミックの処理(破損)
	if (g_map.playStage[int(g_player.py / CHIPSIZE)][int((g_player.px + 32) / CHIPSIZE)] == GIM_403) {
		if (g_player.item[g_player.itemSelect] == K_HA && (key[KEY_INPUT_SPACE] == 1 || g_KeyFlg & PAD_INPUT_2) && g_gimmick[DROP].ONFlg == false) {
			g_gimmick[DROP].ONFlg = true;
			g_gimmick[DROP].moveFlg2 = true;
			use_Flg = true;
			//g_player.item[g_player.itemSelect] = K_NO;
			//g_player.itemNo--;
			smokeFlg[DROP] = true;
			g_map.gimmickData[int(g_player.py / CHIPSIZE)][int((g_player.px + 32) / CHIPSIZE)] = AIR;
			g_gimmick[DROP].x = int((g_player.px + 32) / CHIPSIZE) * CHIPSIZE;
			g_gimmick[DROP].y = int(g_player.py / CHIPSIZE) * CHIPSIZE;
			PlaySoundMem(g_sounds.Fall, DX_PLAYTYPE_BACK, TRUE);//落下音
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
			if (g_gimmick[DROP].moveFlg == true) {
				if (g_map.gimmickData[int(g_gimmick[DROP].y / CHIPSIZE) + 1][i] == 8) {//(落下)
					g_map.playStage[int(g_gimmick[DROP].y / CHIPSIZE) + 1][i] = AIR;
				}
				else {
					break;
				}
			}
			if (g_gimmick[DROP].moveFlg2 == true) {
				if (g_map.gimmickData[int(g_gimmick[DROP].y / CHIPSIZE) + 1][i] == 7) {//(破損)
					g_map.playStage[int(g_gimmick[DROP].y / CHIPSIZE) + 1][i] = AIR;
					g_map.gimmickData[int(g_gimmick[DROP].y / CHIPSIZE) + 1][i] = AIR;
				}
				else {
					break;
				}
			}
		}
		for (int i = (g_gimmick[DROP].x / CHIPSIZE) - 1; i > 0; i--) {//左
			if (g_gimmick[DROP].moveFlg == true) {
				if (g_map.gimmickData[int(g_gimmick[DROP].y / CHIPSIZE) + 1][i] == 8) {//(落下)
					g_map.playStage[int(g_gimmick[DROP].y / CHIPSIZE) + 1][i] = AIR;
				}
				else {
					break;
				}
			}
			if (g_gimmick[DROP].moveFlg2 == true) {
				if (g_map.gimmickData[int(g_gimmick[DROP].y / CHIPSIZE) + 1][i] == 7) {//(破損)
					g_map.playStage[int(g_gimmick[DROP].y / CHIPSIZE) + 1][i] = AIR;
					g_map.gimmickData[int(g_gimmick[DROP].y / CHIPSIZE) + 1][i] = AIR;
				}
				else {
					g_map.playStage[int(g_gimmick[DROP].y / CHIPSIZE)][int(g_gimmick[DROP].x / CHIPSIZE)] = AIR;
					g_gimmick[DROP].moveFlg2 = false;
					g_gimmick[DROP].ONFlg = false;
					break;
				}
			}
		}
		for (int i = 0; i < STAGE_HEIGHT; i++) {//元に戻す
			for (int j = 0; j < STAGE_WIDTH; j++) {
				if (g_map.gimmickData[int(g_player.py / CHIPSIZE) - 1][int((g_player.px + 32) / CHIPSIZE)] == GIM_401 ||
					g_map.gimmickData[int((g_enemy3[1].ey3 + 64) / CHIPSIZE) - 1][int(g_enemy3[1].ex3 / CHIPSIZE)] == GIM_401 ||
					g_gimmick[BOMB].ONFlg == true) {
					if (g_map.gimmickData[i][j] == 8) {
						g_map.playStage[i][j] = BLOCK;
					}
					if (g_map.playStage[i][j] == GIM_402) {
						g_map.gimmickData[i][j] = GIM_402;
					}
					if (g_map.playStage[i][j] == GIM_403) {
						g_map.gimmickData[i][j] = GIM_403;
					}
					g_gimmick[DROP].moveFlg = false;
					g_gimmick[DROP].ONFlg = false;
				}
			}
		}
	}
}
void fireMove() {
	//炎の処理
	if ((g_map.gimmickData[int(g_player.py / CHIPSIZE)][int((g_player.px + 4) / CHIPSIZE) + 1] == GIM_5 ||
		g_map.gimmickData[int(g_player.py / CHIPSIZE)][int((g_player.px - 4) / CHIPSIZE)] == GIM_5) &&
		g_map.playStage[int(g_player.py / CHIPSIZE) + 1][int((g_player.px + 32) / CHIPSIZE)] != AIR) {
		if (g_player.item[g_player.itemSelect] == K_SHOU && (key[KEY_INPUT_SPACE] == 1 || g_KeyFlg & PAD_INPUT_2)) {
			g_gimmick[FIRE].ONFlg = true;
			use_Flg = true;
			//g_player.item[g_player.itemSelect] = K_NO;
			//g_player.itemNo--;
			smokeFlg[FIRE] = true;
			PlaySoundMem(g_sounds.Fire, DX_PLAYTYPE_BACK, TRUE);//消火音
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
		if (g_map.gimmickData[int(g_player.py / CHIPSIZE)][int((g_player.px + 4) / CHIPSIZE) + 1] == GIM_5) {
			g_map.playStage[int(g_player.py / CHIPSIZE)][int((g_player.px + 4) / CHIPSIZE) + 1] = AIR;
			g_map.playStage[int(g_player.py / CHIPSIZE)][int((g_player.px + 4) / CHIPSIZE) + 2] = AIR;
			g_map.playStage[int(g_player.py / CHIPSIZE) - 1][int((g_player.px + 4) / CHIPSIZE) + 1] = AIR;
			g_map.playStage[int(g_player.py / CHIPSIZE) - 1][int((g_player.px + 4) / CHIPSIZE) + 2] = AIR;
			g_map.gimmickData[int(g_player.py / CHIPSIZE)][int((g_player.px + 4) / CHIPSIZE) + 1] = 0;
			g_map.gimmickData[int(g_player.py / CHIPSIZE)][int((g_player.px + 4) / CHIPSIZE) + 2] = 0;
			g_map.gimmickData[int(g_player.py / CHIPSIZE) - 1][int((g_player.px + 4) / CHIPSIZE) + 1] = 0;
			g_map.gimmickData[int(g_player.py / CHIPSIZE) - 1][int((g_player.px + 4) / CHIPSIZE) + 2] = 0;
		}
		if (g_map.gimmickData[int(g_player.py / CHIPSIZE)][int((g_player.px - 4) / CHIPSIZE)] == GIM_5) {
			g_map.playStage[int(g_player.py / CHIPSIZE)][int((g_player.px + 4) / CHIPSIZE) - 1] = AIR;
			g_map.playStage[int(g_player.py / CHIPSIZE)][int((g_player.px + 4) / CHIPSIZE) - 2] = AIR;
			g_map.playStage[int(g_player.py / CHIPSIZE) - 1][int((g_player.px + 4) / CHIPSIZE) - 1] = AIR;
			g_map.playStage[int(g_player.py / CHIPSIZE) - 1][int((g_player.px + 4) / CHIPSIZE) - 2] = AIR;
			g_map.gimmickData[int(g_player.py / CHIPSIZE)][int((g_player.px + 4) / CHIPSIZE) - 1] = 0;
			g_map.gimmickData[int(g_player.py / CHIPSIZE)][int((g_player.px + 4) / CHIPSIZE) - 2] = 0;
			g_map.gimmickData[int(g_player.py / CHIPSIZE) - 1][int((g_player.px + 4) / CHIPSIZE) - 1] = 0;
			g_map.gimmickData[int(g_player.py / CHIPSIZE) - 1][int((g_player.px + 4) / CHIPSIZE) - 2] = 0;
		}
		g_gimmick[FIRE].ONFlg = false;
	}
}
void warpMove() {
	//ワープA処理
	{
		if (g_map.gimmickData[int(g_player.py / CHIPSIZE)][int((g_player.px + 32) / CHIPSIZE)] == GIM_601) {
			if (g_player.item[g_player.itemSelect] == K_DOU && (key[KEY_INPUT_SPACE] == 1 || g_KeyFlg & PAD_INPUT_2)) {

				for (int i = 0; i < STAGE_HEIGHT; i++) {
					for (int j = 0; j < STAGE_WIDTH; j++) {
						if (g_map.playStage[i][j] == GIM_601) {
							g_map.gimmickData[i][j] = AIR;
						}
					}
				}
				for (int i = 0; i < STAGE_HEIGHT; i++) {
					for (int j = 0; j < STAGE_WIDTH; j++) {
						if (g_map.playStage[i][j] == GIM_601) {
							if (i != int(g_player.py / CHIPSIZE) && j != int((g_player.px + 32) / CHIPSIZE)) {
								g_gimmick[WARP_A].x = j * CHIPSIZE;
								g_gimmick[WARP_A].y = i * CHIPSIZE;
							}
							else {
								g_gimmick[WARP_A].w = j * CHIPSIZE;
								g_gimmick[WARP_A].h = i * CHIPSIZE;
							}
						}
					}
				}
				g_gimmick[WARP_A].ONFlg = true;
				g_gimmick[WARP_A].moveFlg = true;
				use_Flg = true;
				//g_player.item[g_player.itemSelect] = K_NO;
				//g_player.itemNo--;
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
			}
			if (g_gimmick[WARP_A].moveFlg == true) {
				if (g_map.playStage[int(g_player.py / CHIPSIZE)][int((g_player.px + 32) / CHIPSIZE)] == GIM_601) {
					if (int(g_player.py / CHIPSIZE) == g_gimmick[WARP_A].y / CHIPSIZE && int((g_player.px + 32) / CHIPSIZE) == g_gimmick[WARP_A].x / CHIPSIZE) {
						g_player.px = g_gimmick[WARP_A].w;
						g_player.py = g_gimmick[WARP_A].h;
					}
					else {
						g_player.px = g_gimmick[WARP_A].x;
						g_player.py = g_gimmick[WARP_A].y;
					}
					PlaySoundMem(g_sounds.Warp, DX_PLAYTYPE_BACK, TRUE);//ワープ音
					g_gimmick[WARP_A].moveFlg = false;
				}
			}
			else {
				if (g_map.playStage[int(g_player.py / CHIPSIZE)][int((g_player.px + 32) / CHIPSIZE)] != GIM_601) {
					g_gimmick[WARP_A].moveFlg = true;
				}
			}
		}
	}
	//ワープB処理
	{
		if (g_map.gimmickData[int(g_player.py / CHIPSIZE)][int((g_player.px + 32) / CHIPSIZE)] == GIM_602) {
			if (g_player.item[g_player.itemSelect] == K_DOU && (key[KEY_INPUT_SPACE] == 1 || g_KeyFlg & PAD_INPUT_2)) {

				for (int i = 0; i < STAGE_HEIGHT; i++) {
					for (int j = 0; j < STAGE_WIDTH; j++) {
						if (g_map.playStage[i][j] == GIM_602) {
							g_map.gimmickData[i][j] = AIR;
						}
					}
				}
				for (int i = 0; i < STAGE_HEIGHT; i++) {
					for (int j = 0; j < STAGE_WIDTH; j++) {
						if (g_map.playStage[i][j] == GIM_602) {
							if (i != int(g_player.py / CHIPSIZE) && j != int((g_player.px + 32) / CHIPSIZE)) {
								g_gimmick[WARP_B].x = j * CHIPSIZE;
								g_gimmick[WARP_B].y = i * CHIPSIZE;
							}
							else {
								g_gimmick[WARP_B].w = j * CHIPSIZE;
								g_gimmick[WARP_B].h = i * CHIPSIZE;
							}
						}
					}
				}
				g_gimmick[WARP_B].ONFlg = true;
				g_gimmick[WARP_B].moveFlg = true;
				use_Flg = true;
				//g_player.item[g_player.itemSelect] = K_NO;
				//g_player.itemNo--;
				smokeFlg[WARP_B] = true;
			}
			/*if (g_player.item[g_player.itemSelect] == K_DOU) {
				DrawGraph(g_player.px, g_player.py - 32, g_img.marubatu[0], TRUE);
			}
			else if(g_gimmick[WARP_B].ONFlg == false){
				DrawGraph(g_player.px, g_player.py - 32, g_img.marubatu[1], TRUE);
			}*/
		}
		if (g_gimmick[WARP_B].ONFlg == true) {
			if (smokeFlg[WARP_B] == true) {//煙
				smoke(g_gimmick[WARP_B].x, g_gimmick[WARP_B].y);
			}
			if (g_gimmick[WARP_B].moveFlg == true) {
				if (g_map.playStage[int(g_player.py / CHIPSIZE)][int((g_player.px + 32) / CHIPSIZE)] == GIM_602) {
					if (int(g_player.py / CHIPSIZE) == g_gimmick[WARP_B].y / CHIPSIZE && int((g_player.px + 32) / CHIPSIZE) == g_gimmick[WARP_B].x / CHIPSIZE) {
						g_player.px = g_gimmick[WARP_B].w;
						g_player.py = g_gimmick[WARP_B].h;
					}
					else {
						g_player.px = g_gimmick[WARP_B].x;
						g_player.py = g_gimmick[WARP_B].y;
					}
					PlaySoundMem(g_sounds.Warp, DX_PLAYTYPE_BACK, TRUE);//ワープ音
					g_gimmick[WARP_B].moveFlg = false;
				}
			}
			else {
				if (g_map.playStage[int(g_player.py / CHIPSIZE)][int((g_player.px + 32) / CHIPSIZE)] != GIM_602) {
					g_gimmick[WARP_B].moveFlg = true;
				}
			}
		}
	}
	//ワープC処理
	{
		if (g_map.gimmickData[int(g_player.py / CHIPSIZE)][int((g_player.px + 32) / CHIPSIZE)] == GIM_603) {
			if (g_player.item[g_player.itemSelect] == K_DOU && (key[KEY_INPUT_SPACE] == 1 || g_KeyFlg & PAD_INPUT_2)) {

				for (int i = 0; i < STAGE_HEIGHT; i++) {
					for (int j = 0; j < STAGE_WIDTH; j++) {
						if (g_map.playStage[i][j] == GIM_603) {
							g_map.gimmickData[i][j] = AIR;
						}
					}
				}
				for (int i = 0; i < STAGE_HEIGHT; i++) {
					for (int j = 0; j < STAGE_WIDTH; j++) {
						if (g_map.playStage[i][j] == GIM_603) {
							if (i != int(g_player.py / CHIPSIZE) && j != int((g_player.px + 32) / CHIPSIZE)) {
								g_gimmick[WARP_C].x = j * CHIPSIZE;
								g_gimmick[WARP_C].y = i * CHIPSIZE;
							}
							else {
								g_gimmick[WARP_C].w = j * CHIPSIZE;
								g_gimmick[WARP_C].h = i * CHIPSIZE;
							}
						}
					}
				}
				g_gimmick[WARP_C].ONFlg = true;
				g_gimmick[WARP_C].moveFlg = true;
				use_Flg = true;
				//g_player.item[g_player.itemSelect] = K_NO;
				//g_player.itemNo--;
				smokeFlg[WARP_C] = true;
			}
			/*if (g_player.item[g_player.itemSelect] == K_DOU) {
				DrawGraph(g_player.px, g_player.py - 32, g_img.marubatu[0], TRUE);
			}
			else if(g_gimmick[WARP_C].ONFlg == false){
				DrawGraph(g_player.px, g_player.py - 32, g_img.marubatu[1], TRUE);
			}*/
		}
		if (g_gimmick[WARP_C].ONFlg == true) {
			if (smokeFlg[WARP_C] == true) {//煙
				smoke(g_gimmick[WARP_C].x, g_gimmick[WARP_C].y);
			}
			if (g_gimmick[WARP_C].moveFlg == true) {
				if (g_map.playStage[int(g_player.py / CHIPSIZE)][int((g_player.px + 32) / CHIPSIZE)] == GIM_603) {
					if (int(g_player.py / CHIPSIZE) == g_gimmick[WARP_C].y / CHIPSIZE && int((g_player.px + 32) / CHIPSIZE) == g_gimmick[WARP_C].x / CHIPSIZE) {
						g_player.px = g_gimmick[WARP_C].w;
						g_player.py = g_gimmick[WARP_C].h;
					}
					else {
						g_player.px = g_gimmick[WARP_C].x;
						g_player.py = g_gimmick[WARP_C].y;
					}
					PlaySoundMem(g_sounds.Warp, DX_PLAYTYPE_BACK, TRUE);//ワープ音
					g_gimmick[WARP_C].moveFlg = false;
				}
			}
			else {
				if (g_map.playStage[int(g_player.py / CHIPSIZE)][int((g_player.px + 32) / CHIPSIZE)] != GIM_603) {
					g_gimmick[WARP_C].moveFlg = true;
				}
			}
		}
	}
}
void bombMove() {
	//爆弾の処理
	/*if (g_map.playStage[int(g_player.py / CHIPSIZE) + 1][int((g_player.px + 32) / CHIPSIZE)] == GIM_2) {
		if (g_player.item[g_player.itemSelect] == K_BAKU && (key[KEY_INPUT_SPACE] == 1 || g_KeyFlg & PAD_INPUT_2) &&
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
	}*/
	if (g_gimmick[BOMB].ONFlg == true) {
		//DrawGraph(g_gimmick[BOMB].x, g_gimmick[BOMB].y, g_img.bomb, TRUE);
		DrawRotaGraph(g_gimmick[BOMB].x + 32, g_gimmick[BOMB].y + 32, 1 + ((50 - g_gimmick[BOMB].anime) * 0.01), 0, g_img.bomb, TRUE);//爆弾の描画
		DrawFormatString(g_gimmick[BOMB].x, g_gimmick[BOMB].y + 20, 0x00ff00, "%f", g_gimmick[BOMB].anime);
		g_gimmick[BOMB].anime;
		if (g_gimmick[BOMB].anime-- < 0) {
			PlaySoundMem(g_sounds.Break, DX_PLAYTYPE_BACK, TRUE);//爆発音
			DrawBox(g_gimmick[BOMB].x - 64, g_gimmick[BOMB].y - 64, g_gimmick[BOMB].x + 128, g_gimmick[BOMB].y + 64, 0xFF0000, true);//爆発範囲
			//g_map.playStage[g_gimmick[BOMB].y / CHIPSIZE][g_gimmick[BOMB].x / CHIPSIZE] = AIR;
			g_gimmick[BOMB].anime = 50;
			g_gimmick[BOMB].y = -CHIPSIZE;
			g_gimmick[BOMB].x = -CHIPSIZE;
			g_gimmick[BOMB].ONFlg = false;
		}
	}
	//ダメージ
	if (g_player.px < g_gimmick[BOMB].x + 128 &&
		g_player.px + 64 > g_gimmick[BOMB].x - 64 &&
		g_player.py < g_gimmick[BOMB].y + 64 &&
		g_player.py + 64 > g_gimmick[BOMB].y - 64) {
		if (g_gimmick[BOMB].anime <= 0) {
			g_player.life -= 1;
			g_player.py -= CHIPSIZE * 2;
		}
	}

}

void cauldronMove() {
	//大釜の処理
	if (g_map.playStage[int(g_player.py / CHIPSIZE)][int((g_player.px + 32) / CHIPSIZE)] == BOSS_G_1) {
		g_player.life--;//ダメージ
		g_player.muteki = 1;
		PlaySoundMem(g_sounds.Fire, DX_PLAYTYPE_BACK, TRUE);//消火音
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
void bigboundMove() {
	if (g_map.gimmickData[int(g_player.py / CHIPSIZE) + 1][int((g_player.px + 32) / CHIPSIZE)] == BOSS_G_2) {
		if (g_player.item[g_player.itemSelect] == K_TIKARA && (key[KEY_INPUT_SPACE] == 1 || g_KeyFlg & PAD_INPUT_2)) {

			g_map.gimmickData[int(g_player.py / CHIPSIZE) + 1][int((g_player.px + 32) / CHIPSIZE)] = BOSS_G_3;
			if (g_map.gimmickData[int(g_player.py / CHIPSIZE) + 1][int((g_player.px + 32) / CHIPSIZE) + 1] == BOSS_G_2) {
				g_map.gimmickData[int(g_player.py / CHIPSIZE) + 1][int((g_player.px + 32) / CHIPSIZE) + 1] = BOSS_G_3;
			}
			else {
				g_map.gimmickData[int(g_player.py / CHIPSIZE) + 1][int((g_player.px + 32) / CHIPSIZE) - 1] = BOSS_G_3;
			}

			use_Flg = true;
			PlaySoundMem(g_sounds.Spring, DX_PLAYTYPE_BACK, TRUE);//ばね音
			//g_player.item[g_player.itemSelect] = K_NO;
			//g_player.itemNo--;
			g_player.fallSpeed = -JUMP_POWER;
		}
	}
	if (g_map.playStage[int(g_player.py / CHIPSIZE)][int(g_player.px / CHIPSIZE)] == BLOCK ||
		g_map.playStage[int((g_player.py - 8) / CHIPSIZE)][int((g_player.px + 64) / CHIPSIZE)] == BLOCK ||
		g_map.playStage[int(g_player.py / CHIPSIZE)][int(g_player.px / CHIPSIZE) + 1] == BLOCK ||
		g_player.py == 64) {

		g_player.py = g_player.py + 1;
		g_player.fallSpeed = 0;
	}
}

void mistake() {
	if (/*key[KEY_INPUT_SPACE] == 1 ||*/ g_KeyFlg & PAD_INPUT_2) {
		if (g_player.item[g_player.itemSelect] != K_NO) {
			PlaySoundMem(g_sounds.Select, DX_PLAYTYPE_BACK, TRUE);
			//エレベータ
			if (g_map.playStage[int(g_player.py / CHIPSIZE)][int((g_player.px + 32) / CHIPSIZE)] == GIM_1) {
				if (g_player.item[g_player.itemSelect] != K_UE && g_player.item[g_player.itemSelect] != K_SITA) {
					DrawGraph(g_player.px, g_player.py - 32, g_img.marubatu[1], TRUE);
				}
			}
			//ジャンプ台
			if (g_map.gimmickData[int(g_player.py / CHIPSIZE) + 1][int((g_player.px + 32) / CHIPSIZE)] == GIM_2) {
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
			//破損看板
			if (g_map.gimmickData[int(g_player.py / CHIPSIZE)][int((g_player.px + 32) / CHIPSIZE)] == GIM_403) {
				if (g_player.item[g_player.itemSelect] != K_HA) {
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
			if (g_map.gimmickData[int(g_player.py / CHIPSIZE)][int((g_player.px + 32) / CHIPSIZE)] == GIM_601 ||
				g_map.gimmickData[int(g_player.py / CHIPSIZE)][int((g_player.px + 32) / CHIPSIZE)] == GIM_602 ||
				g_map.gimmickData[int(g_player.py / CHIPSIZE)][int((g_player.px + 32) / CHIPSIZE)] == GIM_603) {
				if (g_player.item[g_player.itemSelect] != K_DOU) {
					DrawGraph(g_player.px, g_player.py - 32, g_img.marubatu[1], TRUE);
				}
			}
			//横長ジャンプ台
			if (g_map.gimmickData[int(g_player.py / CHIPSIZE) + 1][int((g_player.px + 32) / CHIPSIZE)] == BOSS_G_2) {
				if (g_player.item[g_player.itemSelect] != K_TIKARA) {
					DrawGraph(g_player.px, g_player.py - 32, g_img.marubatu[1], TRUE);
				}
			}
		}
	}
	else {
		//エレベータ
		if (g_map.playStage[int(g_player.py / CHIPSIZE)][int((g_player.px + 32) / CHIPSIZE)] == GIM_1) {
			if (g_player.item[g_player.itemSelect] != K_NO) {
				DrawGraph(g_player.px, g_player.py - 40, g_img.Button, TRUE);
			}
		}
		//ジャンプ台
		if (g_map.gimmickData[int(g_player.py / CHIPSIZE) + 1][int((g_player.px + 32) / CHIPSIZE)] == GIM_2) {
			if (g_player.item[g_player.itemSelect] != K_NO) {
				DrawGraph(g_player.px, g_player.py - 40, g_img.Button, TRUE);
			}
		}
		//破壊できる壁
		if (g_map.gimmickData[int(g_player.py / CHIPSIZE)][int((g_player.px + 4) / CHIPSIZE) + 1] == GIM_3 ||
			g_map.gimmickData[int(g_player.py / CHIPSIZE)][int((g_player.px - 4) / CHIPSIZE)] == GIM_3) {
			if (g_player.item[g_player.itemSelect] != K_NO) {
				DrawGraph(g_player.px, g_player.py - 40, g_img.Button, TRUE);
			}
		}
		//落下看板
		if (g_map.gimmickData[int(g_player.py / CHIPSIZE)][int((g_player.px + 32) / CHIPSIZE)] == GIM_402) {
			if (g_player.item[g_player.itemSelect] != K_NO) {
				DrawGraph(g_player.px, g_player.py - 40, g_img.Button, TRUE);
			}
		}
		//破損看板
		if (g_map.gimmickData[int(g_player.py / CHIPSIZE)][int((g_player.px + 32) / CHIPSIZE)] == GIM_403) {
			if (g_player.item[g_player.itemSelect] != K_NO) {
				DrawGraph(g_player.px, g_player.py - 40, g_img.Button, TRUE);
			}
		}
		//炎
		if (g_map.gimmickData[int(g_player.py / CHIPSIZE)][int((g_player.px + 4) / CHIPSIZE) + 1] == GIM_5 ||
			g_map.gimmickData[int(g_player.py / CHIPSIZE)][int((g_player.px - 4) / CHIPSIZE)] == GIM_5) {
			if (g_player.item[g_player.itemSelect] != K_NO) {
				DrawGraph(g_player.px, g_player.py - 40, g_img.Button, TRUE);
			}
		}
		//ワープ
		if (g_map.gimmickData[int(g_player.py / CHIPSIZE)][int((g_player.px + 32) / CHIPSIZE)] == GIM_601 ||
			g_map.gimmickData[int(g_player.py / CHIPSIZE)][int((g_player.px + 32) / CHIPSIZE)] == GIM_602 ||
			g_map.gimmickData[int(g_player.py / CHIPSIZE)][int((g_player.px + 32) / CHIPSIZE)] == GIM_603) {
			if (g_player.item[g_player.itemSelect] != K_NO) {
				DrawGraph(g_player.px, g_player.py - 40, g_img.Button, TRUE);
			}
		}
		//ジャンプ台
		if (g_map.gimmickData[int(g_player.py / CHIPSIZE) + 1][int((g_player.px + 32) / CHIPSIZE)] == BOSS_G_2) {
			if (g_player.item[g_player.itemSelect] != K_NO) {
				DrawGraph(g_player.px, g_player.py - 40, g_img.Button, TRUE);
			}
		}
	}
}

void smoke(int smokeX, int smokeY) {

	static float anime = 0;

	DrawGraph(smokeX, smokeY, g_img.smoke[int(anime)], TRUE);

	if (anime < 7.0F) anime += 0.2F;
	else {
		anime = 0;
		for (int i = 0; i < GIMMICK_NUM; i++)smokeFlg[i] = false;
	}

}

void use_Effect(int effectX, int effectY) {//漢字を使ったときのエフェクト

	static int effect = 0;
	static int item = g_player.item[g_player.itemSelect] - 1;

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 - (effect * 15));
	DrawModiGraph((effectX) - effect, (effectY) - effect,
		(effectX + 64) + effect, (effectY) - effect,
		(effectX + 64) + effect, ((effectY + 64)) + effect,
		(effectX) - effect, ((effectY + 64)) + effect,
		g_img.kanzi[item], TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	if (effect == 0) {
		item = g_player.item[g_player.itemSelect] - 1;
		g_player.item[g_player.itemSelect] = K_NO;
		g_player.itemNo--;
	}
	if (effect++ > 17) {
		effect = 0;
		use_Flg = false;
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