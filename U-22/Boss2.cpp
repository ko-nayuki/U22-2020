#include "DxLib.h"
#include "Picture.h"
#include "Map.h"
#include "Boss.h"
#include "player.h"
#include "Gimmick.h"
#include "GameScene.h"
#include "enemy.h"
#include "Sounds.h"

#include <math.h>

//0:左待機 1~3:左攻撃 4:右待機 5~7:右攻撃 8~15:左からワープ 16~23:右からワープ

int motion_attack = 0;		//攻撃加算値
int motion_y = 0;			//移動時の高さ
bool warpFlg = false;		//移動フラグ
int warp_num = 0;			//0:移動開始 1:反対側へ 2:移動完了

//攻撃の爆弾用
int Bomb_X[3] = { -CHIPSIZE, -CHIPSIZE, -CHIPSIZE };
int Bomb_Y[3] = { -CHIPSIZE, -CHIPSIZE, -CHIPSIZE };
int Bomb_speed[3] = { 0 };
bool Bomb_Flg[3] = { false, false, false };
bool Bomb_Flg2[3] = { false, false, false };//跳ね返った爆弾
int Bomb_count[3] = { 0 };
int bomb_num = 0;

void thiefMove() {//boss2
	//モーション加算値

	//DrawFormatString(500, 420, 0x00FFFF, "%d", Bomb_X[0]);
	//DrawFormatString(500, 450, 0x00FFFF, "%d", Bomb_X[1]);
	//DrawFormatString(500, 480, 0x00FFFF, "%d", Bomb_X[2]);

	//DrawFormatString(500, 510, 0xFFFF00, "%d", g_boss[1].hp); 
	//DrawFormatString(500, 530, 0xFFFF00, "%d", g_player.life);

	if (g_boss[1].hp > 0) {
		//playerがいる方向とは逆方向にワープ
		if (g_boss[1].x == 17 * CHIPSIZE + 32) DrawGraph(1 * CHIPSIZE + 32, g_boss[1].y + 21 - motion_y, g_img.thief[15], TRUE);
		if (g_boss[1].x == 1 * CHIPSIZE + 32) DrawGraph(17 * CHIPSIZE + 32, g_boss[1].y + 21 - motion_y, g_img.thief[23], TRUE);

		if (g_player.px > 10 * CHIPSIZE + 32 && g_boss[1].x == 17 * CHIPSIZE + 32) {
			if (warpFlg == false) {//playerが右に移動
				g_boss[1].anime = 16;
				g_boss[1].count = 0;
				g_boss[1].attackFlg = false;
				warp_num = 0;
				warpFlg = true;
			}
		}
		else if (g_player.px < 8 * CHIPSIZE + 32 && g_boss[1].x == 1 * CHIPSIZE + 32) {
			if (warpFlg == false) {//playerが左に移動
				g_boss[1].anime = 8;
				g_boss[1].count = 0;
				g_boss[1].attackFlg = false;
				warp_num = 0;
				warpFlg = true;
			}
		}

		if (warpFlg == true) {
			if (warp_num == 0) {//移動開始
				PlaySoundMem(g_sounds.Warp, DX_PLAYTYPE_BACK, TRUE);//移動音
				if (motion_y < 85) {
					motion_y++;
					if (motion_y < 80) {
						g_boss[1].anime += 0.1;
					}
					else {
						if (g_boss[1].x == 17 * CHIPSIZE + 32) {
							g_boss[1].x = 1 * CHIPSIZE + 32;
							g_boss[1].anime = 15;
							warp_num = 1;
						}
						else if (g_boss[1].x == 1 * CHIPSIZE + 32) {
							g_boss[1].x = 17 * CHIPSIZE + 32;
							g_boss[1].anime = 23;
							warp_num = 1;
						}
					}
				}
			}
			else if (warp_num == 1) {//反対側へ
				if (motion_y > 0) {
					motion_y--;
					if (motion_y <= 80 && motion_y > 10) {
						g_boss[1].anime -= 0.1;
					}
				}
				else {
					if (g_boss[1].x == 1 * CHIPSIZE + 32) g_boss[1].anime = 0;
					if (g_boss[1].x == 17 * CHIPSIZE + 32) g_boss[1].anime = 4;
					warp_num = 2;//移動完了
					warpFlg = false;
				}
			}
		}
	}
	if (warpFlg == false && g_boss[1].attackFlg == false && g_boss[1].damageFlg == false) {//攻撃待機
		//すべての爆弾が爆発したらcount開始
		if (Bomb_Flg[0] == false && Bomb_Flg[1] == false && Bomb_Flg[2] == false
			&& Bomb_Flg2[0] == false && Bomb_Flg2[1] == false && Bomb_Flg2[2] == false) g_boss[1].count++;

		if (g_boss[1].count > 50 * g_boss[1].hp) {
			g_boss[1].count = 0;
			motion_attack = g_boss[1].anime + 3;
			g_boss[1].attackFlg = true;
		}
	}
	if (warpFlg == false && g_boss[1].attackFlg == true) {//攻撃
		if (g_boss[1].anime < motion_attack) g_boss[1].anime += 0.1;
		else {
			for (int i = 0; i < 4 - g_boss[1].hp;) {//爆弾の座標指定
				Bomb_Flg[i] = true;
				Bomb_count[i] = 50;
				Bomb_Y[i] = -CHIPSIZE;
				Bomb_X[i] = ((GetRand(4) + 1) * 3) * CHIPSIZE;
				Bomb_speed[i] = 4 * (GetRand(2) + 1);
				if (i == 0) i++;
				if (i == 1) if (Bomb_X[0] != Bomb_X[i] && Bomb_X[i] != -CHIPSIZE) i++;
				if (i == 2) if (Bomb_X[0] != Bomb_X[i] && Bomb_X[1] != Bomb_X[i] && Bomb_X[i] != -CHIPSIZE) i++;

			}

			g_boss[1].attackFlg = false;
			g_boss[1].anime = g_boss[1].anime - 3;

		}
	}

	//爆弾の処理
	if (Bomb_Flg[0] == true) {//1つ目
		if (Bomb_Y[0] <= 9 * CHIPSIZE) {//投下
			DrawGraph(Bomb_X[0] + 32, Bomb_Y[0], g_img.kanzi[6], TRUE);//[爆]の描画
			Bomb_Y[0] += Bomb_speed[0];
		}
		else {
			if (g_map.gimmickData[(Bomb_Y[0] / CHIPSIZE) + 1][Bomb_X[0] / CHIPSIZE] == BOSS_G_3) {//弾力なら跳ね返す
				g_boss[1].damageFlg = true;
				Bomb_Flg2[0] = true;
				Bomb_Flg[0] = false;
				PlaySoundMem(g_sounds.Spring, DX_PLAYTYPE_BACK, TRUE);//ばね音
			}
			else {//着弾
				if (Bomb_count[0]-- > 0) {//爆破カウント
					DrawRotaGraph(Bomb_X[0] + 64, Bomb_Y[0] + 32, 1 + ((50 - Bomb_count[0]) * 0.01), 0, g_img.bomb, TRUE);//爆弾の描画
					g_map.gimmickData[(Bomb_Y[0] / CHIPSIZE) + 1][Bomb_X[0] / CHIPSIZE] = 0;
					g_map.gimmickData[(Bomb_Y[0] / CHIPSIZE) + 1][(Bomb_X[0] / CHIPSIZE) + 1] = 0;
				}
				else {//爆破
					//DrawBox(Bomb_X[0] - 32, Bomb_Y[0] - 64, Bomb_X[0] + 160, Bomb_Y[0] + 64, 0xFF0000, true);//爆発範囲
					DrawExtendGraph(Bomb_X[0] - 32, Bomb_Y[0] - 64, Bomb_X[0] + 160, Bomb_Y[0] + 64, g_img.BombEff, TRUE);//爆発範囲
					g_map.gimmickData[(Bomb_Y[0] / CHIPSIZE) + 1][Bomb_X[0] / CHIPSIZE] = BOSS_G_2;
					g_map.gimmickData[(Bomb_Y[0] / CHIPSIZE) + 1][(Bomb_X[0] / CHIPSIZE) + 1] = BOSS_G_2;
					Bomb_Flg[0] = false;
					Bomb_Y[0] = -CHIPSIZE;
					Bomb_X[0] = -CHIPSIZE;
					Bomb_count[0] = 0;
					PlaySoundMem(g_sounds.Break, DX_PLAYTYPE_BACK, TRUE);//爆破音
				}
			}
		}
	}
	if (Bomb_Flg[1] == true) {//2つ目
		if (Bomb_Y[1] <= 9 * CHIPSIZE) {
			DrawGraph(Bomb_X[1] + 32, Bomb_Y[1], g_img.kanzi[6], TRUE);//[爆]の描画
			Bomb_Y[1] += Bomb_speed[1];
		}
		else {
			if (g_map.gimmickData[(Bomb_Y[1] / CHIPSIZE) + 1][Bomb_X[1] / CHIPSIZE] == BOSS_G_3) {
				g_boss[1].damageFlg = true;
				Bomb_Flg2[1] = true;
				Bomb_Flg[1] = false;
				PlaySoundMem(g_sounds.Spring, DX_PLAYTYPE_BACK, TRUE);//ばね音
			}
			else {
				if (Bomb_count[1]-- > 0) {
					DrawRotaGraph(Bomb_X[1] + 64, Bomb_Y[1] + 32, 1 + ((50 - Bomb_count[1]) * 0.01), 0, g_img.bomb, TRUE);//爆弾の描画
					g_map.gimmickData[(Bomb_Y[1] / CHIPSIZE) + 1][Bomb_X[1] / CHIPSIZE] = 0;
					g_map.gimmickData[(Bomb_Y[1] / CHIPSIZE) + 1][(Bomb_X[1] / CHIPSIZE) + 1] = 0;
				}
				else {
					//DrawBox(Bomb_X[1] - 32, Bomb_Y[1] - 64, Bomb_X[1] + 160, Bomb_Y[1] + 64, 0xFF0000, true);//爆発範囲
					DrawExtendGraph(Bomb_X[1] - 32, Bomb_Y[1] - 64, Bomb_X[1] + 160, Bomb_Y[1] + 64, g_img.BombEff, TRUE);//爆発範囲
					g_map.gimmickData[(Bomb_Y[1] / CHIPSIZE) + 1][Bomb_X[1] / CHIPSIZE] = BOSS_G_2;
					g_map.gimmickData[(Bomb_Y[1] / CHIPSIZE) + 1][(Bomb_X[1] / CHIPSIZE) + 1] = BOSS_G_2;
					Bomb_Flg[1] = false;
					Bomb_Y[1] = -CHIPSIZE;
					Bomb_X[1] = -CHIPSIZE;
					Bomb_count[1] = 0;
					PlaySoundMem(g_sounds.Break, DX_PLAYTYPE_BACK, TRUE);//爆破音
				}
			}
		}
	}
	if (Bomb_Flg[2] == true) {//3つ目
		if (Bomb_Y[2] <= 9 * CHIPSIZE) {
			DrawGraph(Bomb_X[2] + 32, Bomb_Y[2], g_img.kanzi[6], TRUE);//[爆]の描画
			Bomb_Y[2] += Bomb_speed[2];
		}
		else {
			if (g_map.gimmickData[(Bomb_Y[2] / CHIPSIZE) + 1][Bomb_X[2] / CHIPSIZE] == BOSS_G_3) {
				g_boss[1].damageFlg = true;
				Bomb_Flg2[2] = true;
				Bomb_Flg[2] = false;
				PlaySoundMem(g_sounds.Spring, DX_PLAYTYPE_BACK, TRUE);//ばね音
			}
			else {
				if (Bomb_count[2]-- > 0) {
					DrawRotaGraph(Bomb_X[2] + 64, Bomb_Y[2] + 32, 1 + ((50 - Bomb_count[2]) * 0.01), 0, g_img.bomb, TRUE);//爆弾の描画
					g_map.gimmickData[(Bomb_Y[2] / CHIPSIZE) + 1][Bomb_X[2] / CHIPSIZE] = 0;
					g_map.gimmickData[(Bomb_Y[2] / CHIPSIZE) + 1][(Bomb_X[2] / CHIPSIZE) + 1] = 0;
				}
				else {
					//DrawBox(Bomb_X[2] - 32, Bomb_Y[2] - 64, Bomb_X[2] + 160, Bomb_Y[2] + 64, 0xFF0000, true);//爆発範囲
					DrawExtendGraph(Bomb_X[2] - 32, Bomb_Y[2] - 64, Bomb_X[2] + 160, Bomb_Y[2] + 64, g_img.BombEff, TRUE);//爆発範囲
					g_map.gimmickData[(Bomb_Y[2] / CHIPSIZE) + 1][Bomb_X[2] / CHIPSIZE] = BOSS_G_2;
					g_map.gimmickData[(Bomb_Y[2] / CHIPSIZE) + 1][(Bomb_X[2] / CHIPSIZE) + 1] = BOSS_G_2;
					Bomb_Flg[2] = false;
					Bomb_Y[2] = -CHIPSIZE;
					Bomb_X[2] = -CHIPSIZE;
					Bomb_count[2] = 0;
					PlaySoundMem(g_sounds.Break, DX_PLAYTYPE_BACK, TRUE);//爆破音
				}
			}
		}
	}

	//ダメージを受ける
	if (g_boss[1].damageFlg == true) {
		for (bomb_num = 0; bomb_num < 3; bomb_num++) {
			if (Bomb_Flg2[bomb_num] == true) {//3つのうちどの爆弾が跳ね返されたか
				break;
			}
		}
		if (Bomb_X[bomb_num] != 1 * CHIPSIZE && Bomb_X[bomb_num] != 17 * CHIPSIZE) {//爆弾上昇
			DrawGraph(Bomb_X[bomb_num] + 32, Bomb_Y[bomb_num], g_img.kanzi[6], TRUE);//[爆]の描画
			if (Bomb_Y[bomb_num] > -CHIPSIZE) Bomb_Y[bomb_num] -= 8;
			else Bomb_X[bomb_num] = g_boss[1].x - 32;
		}
		else {
			if (Bomb_Y[bomb_num] < 3 * CHIPSIZE) {//爆弾降下
				DrawGraph(Bomb_X[bomb_num] + 32, Bomb_Y[bomb_num], g_img.kanzi[6], TRUE);//[爆]の描画
				Bomb_Y[bomb_num] += 4;
			}
			else {
				if (Bomb_count[bomb_num]-- > 0) {
					g_boss[1].count = 0;
					DrawRotaGraph(Bomb_X[bomb_num] + 64, Bomb_Y[bomb_num] + 32, 1 + ((50 - Bomb_count[bomb_num]) * 0.01), 0, g_img.bomb, TRUE);//爆弾の描画
					g_map.gimmickData[(Bomb_Y[bomb_num] / CHIPSIZE) + 1][Bomb_X[bomb_num] / CHIPSIZE] = 0;
					g_map.gimmickData[(Bomb_Y[bomb_num] / CHIPSIZE) + 1][(Bomb_X[bomb_num] / CHIPSIZE) + 1] = 0;
				}
				else {
					if (g_boss[1].count == 0) {
						PlaySoundMem(g_sounds.Break, DX_PLAYTYPE_BACK, TRUE);//爆破音
						//DrawBox(Bomb_X[bomb_num] - 32, Bomb_Y[bomb_num] - 64, Bomb_X[bomb_num] + 160, Bomb_Y[bomb_num] + 64, 0xFF0000, true);//爆発範囲
						DrawExtendGraph(Bomb_X[bomb_num] - 32, Bomb_Y[bomb_num] - 64, Bomb_X[bomb_num] + 160, Bomb_Y[bomb_num] + 64, g_img.BombEff, TRUE);//爆発範囲
						g_map.gimmickData[(Bomb_Y[bomb_num] / CHIPSIZE) + 1][Bomb_X[bomb_num] / CHIPSIZE] = BOSS_G_2;
						g_map.gimmickData[(Bomb_Y[bomb_num] / CHIPSIZE) + 1][(Bomb_X[bomb_num] / CHIPSIZE) + 1] = BOSS_G_2;
					}

					// ５回のうち２回表示する
					g_boss[1].count++;
					if (g_boss[1].count % 10 == 0) {
						//表示
						if (Bomb_X[bomb_num] == int(g_boss[1].x) - 32) {
							SetDrawBright(255, 0, 0);
							DrawGraph(g_boss[1].x, g_boss[1].y - CHIPSIZE, g_img.thief[int(g_boss[1].anime)], TRUE);
							SetDrawBright(255, 255, 255);
						}
					}
					if (g_boss[1].count >= 40) {
						g_boss[1].damageFlg = false;
						g_boss[1].count = 0;
						Bomb_Flg[bomb_num] = false;
						Bomb_Flg2[bomb_num] = false;
						Bomb_count[bomb_num] = 0;
						if (Bomb_X[bomb_num] == int(g_boss[1].x) - 32) g_boss[1].hp--;
						Bomb_Y[bomb_num] = -CHIPSIZE;
						Bomb_X[bomb_num] = -CHIPSIZE;
					}
				}
			}
		}
	}

	if (g_boss[1].hp <= 0) {//HPが0になったら
		if (g_boss[1].x == 17 * CHIPSIZE + 32) g_boss[1].anime = 15;
		if (g_boss[1].x == 1 * CHIPSIZE + 32) g_boss[1].anime = 23;
		//g_map.select++;
		if (g_boss[1].y < 3 * CHIPSIZE + 85) g_boss[1].y++;
		else {
			if (motion_y++ > 100) {
				motion_attack = 0;
				motion_y = 0;
				warp_num = 0;
				g_gameScene = GAME_CLEAR;
			}

		}
	}


	static int sx = -64;
	static int sy = -64;
	static bool smokeFlg = false;
	if (g_player.py == 9 * CHIPSIZE) {//playerが地面に着地したら
		if (g_boss[1].x == 1 * CHIPSIZE + 32) {
			if (g_player.item[0] == K_NO && g_map.playStage[9][18] == 0 && g_map.playStage[9][1] == 0) {
				g_map.playStage[9][1] = C;
			}
		}
		if (g_boss[1].x == 17 * CHIPSIZE + 32) {
			if (g_player.item[0] == K_NO && g_map.playStage[9][1] == 0 && g_map.playStage[9][18] == 0) {
				g_map.playStage[9][18] = C;
			}
		}

		for (int i = 0; i < STAGE_HEIGHT; i++) {
			for (int j = 0; j < STAGE_WIDTH; j++) {
				if (g_map.gimmickData[i][j] == BOSS_G_3) {
					g_map.gimmickData[i][j] = BOSS_G_2;
					sx = j * CHIPSIZE;
					sy = i * CHIPSIZE;
					smokeFlg = true;
				}
			}
		}
	}

	if (smokeFlg == true) {
		static float anime = 0;

		DrawGraph(sx, sy, g_img.smoke[int(anime)], TRUE);
		DrawGraph(sx - 64, sy, g_img.smoke[int(anime)], TRUE);

		if (anime < 7.0F) anime += 0.2F;
		else {
			anime = 0;
			sx = -64;
			sy = -64;
			smokeFlg = false;
		}
	}

	//playerダメージ
	for (int i = 0; i < 3; i++) {
		if (g_player.px < Bomb_X[i] + 160 &&
			g_player.px + 64 > Bomb_X[i] - 32 &&
			g_player.py < Bomb_Y[i] + 64 &&
			g_player.py + 64 > Bomb_Y[i] - 64) {
			if (Bomb_count[i] <= 0) {
				PlaySoundMem(g_sounds.Damage, DX_PLAYTYPE_BACK, TRUE);
				g_player.muteki = 1;
				g_player.life -= 1;
				g_player.py -= CHIPSIZE * 2;
			}
		}
	}
	//プレイヤーのライフが０なったら
	//if (g_player.life == 0) {
	//	g_gameScene = GAME_OVER;
	//	//g_player.px = CHIPSIZE * 1, g_player.py = CHIPSIZE * 9;
	//}
}

void boss2_Init(){

	motion_attack = 0;		//攻撃加算値
	motion_y = 0;			//移動時の高さ
	warpFlg = false;		//移動フラグ
	warp_num = 0;			//0:移動開始 1:反対側へ 2:移動完了

	//攻撃の爆弾用
	for (int i = 0; i < 3; i++) {
		Bomb_X[i] = -CHIPSIZE;
		Bomb_Y[i] = -CHIPSIZE;
		Bomb_speed[i] = 0;
		Bomb_Flg[i] = false;
		Bomb_Flg2[i] = false;//跳ね返った爆弾
		Bomb_count[i] = 0;
	}
	bomb_num = 0;
}