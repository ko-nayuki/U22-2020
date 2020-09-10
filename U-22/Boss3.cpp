#include "DxLib.h"
#include "Picture.h"
#include "Map.h"
#include "Boss.h"
#include "player.h"
#include "Gimmick.h"
#include "GameScene.h"
#include "KeyControl.h"
#include "Sounds.h"

#include <math.h>

void ColossusMove() {//boss3
	//0~2 左側の手  3~5 右側の手

	static int boss3_attack = 0; //攻撃
	static int Random = 0;

	static int head_Number = 0;     //ボスの顔
	static int UpDown_head = true;  //true:上下 false:上下しない
	static int UpDown_head_s = 0;
	static int UpDown_head_s2 = 0;
	static int UpDown_head_count = 50;
	static int UpDown_head_count2 = 0;

	static int UpDown_flg = 1;  // 0:上下しない 1:ずっと上下する
	static int UpDown_s = 0;
	static int UpDown_count = 0;

	static int search_LR = 1;  //0:オフ 1:オン
	static int search_count = 250;
	static int search_stop = 100;
	static int search_attack1 = 0;//0:オフ 1:オン

	static int attack1_Fall = 0;

	static int attck_count = 0;

	static int attck_start = 35;
	static int attck_end1 = true;
	static int attck_end2 = true;

	//DrawFormatString(500, 510, 0xFFFF00, "%d", g_boss[Random].attackFlg);
	//DrawFormatString(500, 530, 0xFFFF00, "%d", g_boss[Random].count);
	//DrawFormatString(500, 550, 0xFFFF00, "%d", attck_start);
	//DrawFormatString(500, 570, 0xFFFF00, "%d", g_boss[2].x);
	//if (g_KeyFlg & PAD_INPUT_Z) g_player.py -= 300;

	if (g_boss3head.anime == 0) {//ボス３頭の上下移動処理
		if (UpDown_head == true) {

			/*if (UpDown_head_s == 0) {
				g_boss3head[head_Number].x += 0.5;
				UpDown_head_count += 1;
				if (UpDown_head_count == 100) {
					UpDown_head_s = 1;
				}
			}
			if (UpDown_head_s == 1) {
				g_boss3head[head_Number].x -= 0.5;
				UpDown_head_count -= 1;
				if (UpDown_head_count == 0) {
					UpDown_head_s = 0;
				}
			}*/

			if (UpDown_head_s2 == 0) {
				g_boss3head.y += 0.5;
				UpDown_head_count2 += 1;
				if (UpDown_head_count2 == 50) {
					UpDown_head_s2 = 1;
				}
			}
			if (UpDown_head_s2 == 1) {
				g_boss3head.y -= 0.5;
				UpDown_head_count2 -= 1;
				if (UpDown_head_count2 == 0) {
					UpDown_head_s2 = 0;
				}
			}
		}
	}



	if (boss3_attack == 0 && (g_boss[2].hp > 0 || g_boss[3].hp > 0)) {
		if (g_boss[2].hp > 0 && g_boss[3].hp > 0) {
			Random = GetRand(1);
			Random += 2;
			boss3_attack = (GetRand(1) + 1);
			//boss3_attack += 1;
		}
		else if (g_boss[2].hp > 0 && g_boss[3].hp == 0) {
			Random = 2;
			boss3_attack = (GetRand(1) + 1);
			//boss3_attack = 1;
		}
		else
		{
			Random = 3;
			boss3_attack = (GetRand(1) + 1);
			//boss3_attack = 1;
		}
	}

	if (g_boss[Random].attackFlg == false) {   //攻撃するまでの時間
		g_boss[Random].count++;
		if (g_boss[Random].count > (150 * g_boss[Random].hp) / 2) {
			if (attck_start >= 0 && Random == 2) {
				g_boss[2].x -= 5;
				attck_start -= 1;
			}

			if (attck_start >= 0 && Random == 3)
			{
				g_boss[3].x += 5;
				attck_start -= 1;
			}

			if (g_boss[Random].count > 150 * g_boss[Random].hp) {
				g_boss[Random].attackFlg = true;
			}
		}
	}

	if (g_boss[Random].attackFlg == true) {
		if (boss3_attack == 1) {
			if (UpDown_flg == 1) { //上下移動処理
				if (UpDown_s == 0) {
					g_boss[Random].y += 0.5;
					UpDown_count += 1;
					if (UpDown_count == 50) {
						UpDown_s = 1;
					}
				}
				if (UpDown_s == 1) {
					g_boss[Random].y -= 0.5;
					UpDown_count -= 1;
					if (UpDown_count == 0) {
						UpDown_s = 0;
					}
				}
			}

			//拳骨攻撃
			if (search_LR == 1) {
				if (g_boss[Random].x <= g_player.px - 156) {
					g_boss[Random].x += 5;
					search_count -= 1;
				}

				if (g_boss[Random].x > g_player.px - 156) {
					g_boss[Random].x -= 5;
					search_count -= 1;
				}
			}
			if (search_count <= 0) {
				search_LR = 0;
				UpDown_flg = 0;
				search_stop -= 1;
				if (search_stop <= 0) {   //落下待機
					search_count = 250;
					search_attack1 = 1;
				}
			}

			if (search_attack1 == 1)  //振り下ろしモーション
			{
				boss_Hand();//bossのdamageFlg切り替え

				//手の右判定
				if (g_player.px + 64 > g_boss[Random].x + 54 && g_player.px + 64 < g_boss[Random].x + 330 && g_player.py + 64 >= g_boss[Random].y) {
					g_player.px -= 4;
				}
				//手の左判定
				if (g_player.px < g_boss[Random].x + 330 && g_player.px > g_boss[Random].x + 54 && g_player.py + 64 >= g_boss[Random].y) {
					g_player.px += 4;
				}
				//手の上判定
				if (g_player.py + 64 > g_boss[Random].y - 32 && g_player.px < g_boss[Random].x + 330 && g_player.px + 64 > g_boss[Random].x + 54) {
					g_player.fallSpeed = 0;
				}

				if ((g_map.playStage[(int(g_boss[Random].y) / CHIPSIZE) + 1][int(g_boss[Random].x) / CHIPSIZE] == AIR ||
					(g_map.playStage[(int(g_boss[Random].y) / CHIPSIZE) + 3][int(g_boss[Random].x) / CHIPSIZE]) == START) &&
					g_boss[Random].damageFlg == false) {

					if ((g_map.playStage[(int(g_boss[Random].y) / CHIPSIZE) + 3][int(g_boss[Random].x) / CHIPSIZE]) == AIR ||
						(g_map.playStage[(int(g_boss[Random].y) / CHIPSIZE) + 3][int(g_boss[Random].x) / CHIPSIZE]) == START) {
						g_boss[Random].y += CHIPSIZE;
						PlaySoundMem(g_sounds.Arm, DX_PLAYTYPE_BACK, TRUE);//移動音
						if (g_player.px <= g_boss[Random].x + 330 &&
							g_player.px + 64 >= g_boss[Random].x + 54 &&
							g_player.py <= g_boss[Random].y + 256 &&
							g_player.py + 64 >= g_boss[Random].y) {
							if (g_boss[Random].damageFlg == false && g_player.muteki == 0) {
								if (g_player.px + 34 < g_boss[Random].x + 256) {
									g_player.px -= 3 * CHIPSIZE;
									g_player.muteki = 1;
									g_player.life -= 1;
								}
								if (g_player.px + 34 > g_boss[Random].x + 256) {
									g_player.px += 3 * CHIPSIZE;
									g_player.muteki = 1;
									g_player.life -= 1;
								}
							}
						}
					}
					attack1_Fall += 1;
				}
			}

			if (attack1_Fall >= 400) {  //腕戻る
				search_attack1 = 0;
				search_count = 250;
				if (attck_end2 == true && g_boss[Random].y >= -192) {
					g_boss[Random].y -= 10;
				}

				if (Random == 3 && g_boss[3].y <= -192 && attck_end1 == true) {
					attck_end2 = false;
					g_boss[3].x = 20 * CHIPSIZE;
					g_boss[3].y = 2 * CHIPSIZE;
					attck_end1 = false;
				}

				if (Random == 2 && g_boss[2].y <= -192 && attck_end1 == true) {
					attck_end2 = false;
					g_boss[2].x = -5 * CHIPSIZE;
					g_boss[2].y = 2 * CHIPSIZE;
					attck_end1 = false;
				}

				if (attck_end1 == false) {
					if (g_boss[3].x > 17 * CHIPSIZE) {
						g_boss[3].x -= 5;
					}
					if (g_boss[2].x < -3 * CHIPSIZE) {
						g_boss[2].x += 5;
					}
					if ((Random == 2 && g_boss[2].x >= -3 * CHIPSIZE) || (Random == 3 && g_boss[3].x <= 17 * CHIPSIZE)) {
						search_stop = 100;
						boss3_attack = 0;
						search_LR = 1;
						UpDown_count = 0;
						attack1_Fall = 0;
						g_boss[Random].count = 0;
						g_boss[Random].attackFlg = false;
						UpDown_flg = 1;
						UpDown_s = 0;
						attck_start = 35;
						attck_end1 = true;
						attck_end2 = true;
					}
				}
			}

		}
	}



	if (g_boss[Random].attackFlg == true) {
		if (boss3_attack == 2) {    //薙ぎ払い
			if (attck_count == 0)
			{
				g_boss[Random].y = 7 * CHIPSIZE;
				attck_count = 1;
			}

			if (Random == 2) {
				g_boss[2].x += 6;
				if (g_boss[2].x >= CHIPSIZE * 6 - 32) {
					g_boss[2].y -= 7;
				}
				if (g_player.px <= g_boss[Random].x + 330 &&
					g_player.px + 64 >= g_boss[Random].x + 54 &&
					g_player.py <= g_boss[Random].y + 256 &&
					g_player.py + 64 >= g_boss[Random].y) {
					if (g_boss[Random].damageFlg == false && g_player.muteki == 0) {
						if (g_player.px + 34 < g_boss[Random].x + 256) {
							g_player.px -= 3 * CHIPSIZE;
							g_player.muteki = 1;
							g_player.life -= 1;
						}
						if (g_player.px + 34 > g_boss[Random].x + 256) {
							g_player.px += 3 * CHIPSIZE;
							g_player.muteki = 1;
							g_player.life -= 1;
						}
					}
				}
			}


			if (Random == 3) {
				g_boss[3].x -= 6;
				if (g_boss[3].x <= CHIPSIZE * 8 + 32) {
					g_boss[3].y -= 7;
				}
				if (g_player.px <= g_boss[Random].x + 330 &&
					g_player.px + 64 >= g_boss[Random].x + 54 &&
					g_player.py <= g_boss[Random].y + 256 &&
					g_player.py + 64 >= g_boss[Random].y) {
					if (g_boss[Random].damageFlg == false && g_player.muteki == 0) {
						if (g_player.px + 34 < g_boss[Random].x + 256) {
							g_player.px -= 3 * CHIPSIZE;
							g_player.muteki = 1;
							g_player.life -= 1;
						}
						if (g_player.px + 34 > g_boss[Random].x + 256) {
							g_player.px += 3 * CHIPSIZE;
							g_player.muteki = 1;
							g_player.life -= 1;
						}
					}
				}
			}

			if (Random == 3 && g_boss[3].y <= -192 && attck_end1 == true) {
				attck_end2 = false;
				g_boss[3].x = 20 * CHIPSIZE;
				g_boss[3].y = 2 * CHIPSIZE;
				attck_end1 = false;
			}

			if (Random == 2 && g_boss[2].y <= -192 && attck_end1 == true) {
				attck_end2 = false;
				g_boss[2].x = -5 * CHIPSIZE;
				g_boss[2].y = 2 * CHIPSIZE;
				attck_end1 = false;
			}

			if (attck_end1 == false) {
				if (g_boss[3].x > 17 * CHIPSIZE) {
					g_boss[3].x -= 5;
				}
				if (g_boss[2].x < -3 * CHIPSIZE) {
					g_boss[2].x += 5;
				}
				if ((Random == 2 && g_boss[2].x >= -3 * CHIPSIZE) || (Random == 3 && g_boss[3].x <= 17 * CHIPSIZE)) {
					search_stop = 100;
					boss3_attack = 0;
					search_LR = 1;
					UpDown_count = 0;
					attack1_Fall = 0;
					attck_count = 0;
					g_boss[Random].count = 0;
					g_boss[Random].attackFlg = false;
					UpDown_flg = 1;
					UpDown_s = 0;
					attck_start = 35;
					attck_end1 = true;
					attck_end2 = true;
				}
				//if (g_boss[Random].y <= -192) {    //初期化
				//	g_boss[2].x = -3 * CHIPSIZE;
				//	g_boss[3].x = 17 * CHIPSIZE;
				//	g_boss[Random].y = 2 * CHIPSIZE;
				//	attck_count = 0;
				//	g_boss[Random].count = 0;
				//	g_boss[Random].attackFlg = false;
				//	boss3_attack = 0;
				//	attck_start = 35;
				//}
			}
		}

		//bossダメージ
		if (g_boss[Random].damageFlg == true) {
			g_boss3head.anime = 1;
			attack1_Fall = 400;
			g_boss[Random].anime += 1;
			g_boss[Random].hp -= 1;
			g_map.playStage[9][9] = D;//[破]を再設置
			g_boss[Random].damageFlg = false;
		}
		if (g_boss3head.anime == 1)
		{
			if (head_Number >= 50) {
				head_Number = 0;
				g_boss3head.anime = 0;
			}
			else {
				head_Number += 1;
			}
		}
		if (g_boss[2].hp <= 0 && g_boss[3].hp <= 0) {
			g_boss3head.anime = 2;
			if ((g_map.playStage[(int(g_boss3head.y) / CHIPSIZE) + 3][int(g_boss3head.x) / CHIPSIZE]) == AIR ||
				(g_map.playStage[(int(g_boss3head.y) / CHIPSIZE) + 3][int(g_boss3head.x) / CHIPSIZE]) == START) {
				g_boss3head.y += CHIPSIZE / 2;
				g_map.playStage[int(g_boss3head.y / CHIPSIZE)][int((g_boss3head.x + 224) / CHIPSIZE)] = 2;//ゴール設置
			}
		}

		if (g_map.playStage[int((g_player.py - 1) / CHIPSIZE) + 1][int((g_player.px - 4) / CHIPSIZE)] == g_boss[Random].x + 330) {
			g_player.px -= 4 * g_player.move;
		}
	}
}