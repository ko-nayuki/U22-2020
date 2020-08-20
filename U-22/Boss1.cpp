#include "DxLib.h"
#include "Picture.h"
#include "Map.h"
#include "Boss.h"
#include "player.h"
#include "Gimmick.h"
#include "GameScene.h"
#include "enemy.h"

#include <math.h>

void wolfMove() {// boss1
	static int next_Action = 0;					// 1~3:ジャンプ  4:風
	static int jump_x = 10 * CHIPSIZE + 32;		//ジャンプの着地地点
	static int jump_num = 0;					//0:前進 1:後退 2:その場
	static float fallSpeed = 0.0;
	static int wind_time = 200;					//風の時間
	static bool jumpFlg = false;
	static int gimmick_time = 100;				//落下ギミックが元に戻る時間

	//DrawFormatString(500, 450, 0x00FFFF, "%d", jump_x);
	//DrawFormatString(500, 420, 0x00FFFF, "%d", next_Action);

	//足場が消えたときに落下
	if (g_map.playStage[(int(g_boss[0].y) / CHIPSIZE) + 1][int(g_boss[0].x) / CHIPSIZE] == AIR &&
		g_map.gimmickData[(int(g_boss[0].y) / CHIPSIZE) + 1][int(g_boss[0].x) / CHIPSIZE] == GIM_401 &&
		g_boss[0].damageFlg == false) {
		g_boss[0].attackFlg = false;
		g_boss[0].damageFlg = true;
		g_boss[0].hp--;
		g_boss[0].count = 0;
		jumpFlg = false;
	}

	if (g_boss[0].damageFlg == false) {

		//次の行動までの時間
		if (g_boss[0].attackFlg == false) g_boss[0].count++, g_boss[0].anime -= 0.1;
		if (g_boss[0].anime < 3.0) g_boss[0].anime = 6;

		if (g_boss[0].count > 50 * g_boss[0].hp) {
			next_Action++;
			if (next_Action == 4 && g_boss[0].x != 15 * CHIPSIZE + 32) next_Action--;
			if (next_Action > 4) next_Action = 1;
			else jump_x = ((GetRand(2) + 1) * 5) * CHIPSIZE + 32;

			if (g_boss[0].x > jump_x) jump_num = 0;
			if (g_boss[0].x < jump_x) jump_num = 1;
			if (g_boss[0].x == jump_x) jump_num = 2;

			fallSpeed = (g_boss[0].x + jump_x) / 2;
			g_boss[0].count = 0;
			g_boss[0].attackFlg = true;
		}
	}

	//ジャンプ
	if ((next_Action >= 1 && next_Action < 4) && g_boss[0].attackFlg == true) {

		if (jump_num == 0) {//前進
			g_boss[0].anime = 2;
			g_boss[0].x -= 10 * cos(45);
			if (g_boss[0].x > fallSpeed) g_boss[0].y -= 5;
			else g_boss[0].y += 5;

			if (g_boss[0].x <= jump_x) {
				g_boss[0].x = jump_x;
				g_boss[0].y = 6 * CHIPSIZE;
				g_boss[0].attackFlg = false;
			}
		}
		if (jump_num == 1) {//後退
			g_boss[0].anime = 1;
			g_boss[0].x += 10 * cos(45);
			if (g_boss[0].x > fallSpeed) g_boss[0].y += 5;
			else g_boss[0].y -= 5;

			if (g_boss[0].x >= jump_x) {
				g_boss[0].x = jump_x;
				g_boss[0].y = 6 * CHIPSIZE;
				g_boss[0].attackFlg = false;
			}

		}
		if (jump_num == 2) {//その場ジャンプ
			g_boss[0].anime = 2;
			if (jumpFlg == false)g_boss[0].y -= 8;
			else g_boss[0].y += 8;
			if (g_boss[0].y < 2 * CHIPSIZE) jumpFlg = true;
			if (g_boss[0].y - 1 > 6 * CHIPSIZE) {
				jumpFlg = false;
				g_boss[0].y = 6 * CHIPSIZE;
				g_boss[0].attackFlg = false;
			}
		}
	}

	//風
	if (next_Action == 4 && g_boss[0].attackFlg == true) {

		g_boss[0].anime = 0;
		if (g_player.px < g_boss[0].x) g_player.px -= (wind_time * 0.01) + (4.5 - float(g_boss[0].hp));

		if (wind_time-- <= 0) {
			wind_time = 200;
			g_boss[0].attackFlg = false;
		}
		for (int i = 1; i < ENEMY_MAX; i++) {
			//当たり判定
			if (HitBoxPlayer3(&g_player, &g_enemy3[i]) == TRUE) {
				wind_time = 200;
				g_boss[0].attackFlg = false;
			}
		}
	}

	//落下ギミックを時間で元に戻す
	if (g_gimmick[DROP].ONFlg == true && g_boss[0].damageFlg == false) {
		if (gimmick_time-- < 0) {
			g_gimmick[DROP].ONFlg = false;
			g_gimmick[DROP].x = -CHIPSIZE;
			g_gimmick[DROP].y = -CHIPSIZE;
			gimmick_time = 100;
			g_map.playStage[6][18] = B;
			for (int i = 0; i < STAGE_HEIGHT; i++) {
				for (int j = 0; j < STAGE_WIDTH; j++) {
					if (g_map.gimmickData[i][j] == 8) {
						g_map.playStage[i][j] = BLOCK;
					}
					if (g_map.playStage[i][j] == GIM_402 && g_map.gimmickData[i][j] == AIR) {
						g_map.gimmickData[i][j] = GIM_402;
					}
				}
			}
		}
	}

	//ダメージをもらったら
	if (g_boss[0].damageFlg == true) {

		SetDrawBright(255, 255 - g_boss[0].count * (5 - g_boss[0].hp), 255);
		DrawGraph(g_boss[0].x, g_boss[0].y - CHIPSIZE, g_img.wolf[int(g_boss[0].anime)], TRUE);
		SetDrawBright(255, 255, 255);

		if (g_boss[0].y < 9 * CHIPSIZE && g_boss[0].count == 0) {
			g_boss[0].anime = 1;
			g_boss[0].y += 8;
		}
		else {
			g_boss[0].count++;
			if (g_boss[0].count > 50) {

				g_gimmick[DROP].ONFlg = false;
				g_gimmick[DROP].x = -CHIPSIZE;
				g_gimmick[DROP].y = -CHIPSIZE;
				for (int i = 0; i < STAGE_HEIGHT; i++) {
					for (int j = 0; j < STAGE_WIDTH; j++) {
						if (g_map.gimmickData[i][j] == 8) {
							g_map.playStage[i][j] = BLOCK;
						}
						if (g_map.playStage[i][j] == GIM_402 && g_map.gimmickData[i][j] == AIR) {
							g_map.playStage[i][j] = AIR;
						}
					}
				}

				if (g_boss[0].hp <= 0) {//HPが0になったら
					g_boss[0].anime = 2;
					next_Action = 0;
					wind_time = 200;
					gimmick_time = 100;
					jumpFlg = false;
					if (g_boss[0].y > 10 * CHIPSIZE - 16) {
						g_map.select++;
						g_gameScene = GAME_CLEAR;
					}
					else g_boss[0].y += 0.2F;
				}
				else {//HPがまだ残っているなら
					if (jumpFlg == false) g_boss[0].y -= 8, g_boss[0].anime = 2;
					else {
						g_boss[0].y += 8;
						if (g_boss[0].y >= 6 * CHIPSIZE) {
							g_boss[0].y = 6 * CHIPSIZE;
							g_map.playStage[6][18] = B;
							g_boss[0].damageFlg = false;
							g_boss[0].count = 0;
							next_Action = 0;
							wind_time = 200;
							jumpFlg = false;
						}
					}
					if (g_boss[0].y < 3 * CHIPSIZE) jumpFlg = true;
				}
			}
			else {
				g_boss[0].y += 0.3F;
				if (g_boss[0].count % 9 == 0) g_boss[0].anime = 1;
				if (g_boss[0].count % 9 == 5) g_boss[0].anime = 2;
			}
		}
	}

	if (g_player.py > 9 * CHIPSIZE) {//playerが下に落ちたら
		g_map.playStage[6][18] = B;
	}

	//playerダメージ
	if (g_player.px < g_boss[0].x + 44 &&
		g_player.px + 64 > g_boss[0].x + 20 &&
		g_player.py < g_boss[0].y + 44 &&
		g_player.py + 64 > g_boss[0].y + 20) {
		if (g_boss[0].damageFlg == false) {
			if (g_player.px + 64 < g_boss[0].x + 44) {
				g_player.px -= CHIPSIZE;
				g_player.life -= 1;
			}
			else if (g_player.px > g_boss[0].x) {
				g_player.px += CHIPSIZE;
				g_player.life -= 1;
			}
		}
		//DrawBox(g_boss[0].x + 20, g_boss[0].y + 20, g_boss[0].x + 44, g_boss[0].y + 44,0xFF0000,true);
	}

}
