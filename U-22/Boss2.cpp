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

void thiefMove() {//boss2
	//ÉÇÅ[ÉVÉáÉìâ¡éZíl
	//0:ç∂ë“ã@ 1~3:ç∂çUåÇ 4:âEë“ã@ 5~7:âEçUåÇ 8~15:ç∂Ç©ÇÁÉèÅ[Év 16~23:âEÇ©ÇÁÉèÅ[Év

	static int motion_attack = 0;		//çUåÇâ¡éZíl
	static int motion_y = 0;			//à⁄ìÆéûÇÃçÇÇ≥
	static bool warpFlg = false;		//à⁄ìÆÉtÉâÉO
	static int warp_num = 0;			//0:à⁄ìÆäJén 1:îΩëŒë§Ç÷ 2:à⁄ìÆäÆóπ

	//çUåÇÇÃîöíeóp
	static int Bomb_X[3] = { -CHIPSIZE, -CHIPSIZE, -CHIPSIZE };
	static int Bomb_Y[3] = { -CHIPSIZE, -CHIPSIZE, -CHIPSIZE };
	static int Bomb_speed[3] = { 0 };
	static bool Bomb_Flg[3] = { false, false, false };
	static bool Bomb_Flg2[3] = { false, false, false };//íµÇÀï‘Ç¡ÇΩîöíe
	static int Bomb_count[3] = { 0 };
	static int bomb_num = 0;

	//DrawFormatString(500, 420, 0x00FFFF, "%d", Bomb_X[0]);
	//DrawFormatString(500, 450, 0x00FFFF, "%d", Bomb_X[1]);
	//DrawFormatString(500, 480, 0x00FFFF, "%d", Bomb_X[2]);

	//DrawFormatString(500, 510, 0xFFFF00, "%d", g_boss[1].hp); 
	//DrawFormatString(500, 530, 0xFFFF00, "%d", g_player.life);

	//playerÇ™Ç¢ÇÈï˚å¸Ç∆ÇÕãtï˚å¸Ç…ÉèÅ[Év
	if (g_boss[1].x == 17 * CHIPSIZE + 32) DrawGraph(1 * CHIPSIZE + 32, g_boss[1].y + 21 - motion_y, g_img.thief[15], TRUE);
	if (g_boss[1].x == 1 * CHIPSIZE + 32) DrawGraph(17 * CHIPSIZE + 32, g_boss[1].y + 21 - motion_y, g_img.thief[23], TRUE);

	if (g_player.px > 10 * CHIPSIZE + 32 && g_boss[1].x == 17 * CHIPSIZE + 32) {
		if (warpFlg == false) {//playerÇ™âEÇ…à⁄ìÆ
			g_boss[1].anime = 16;
			g_boss[1].count = 0;
			g_boss[1].attackFlg = false;
			warp_num = 0;
			warpFlg = true;
		}
	}
	else if (g_player.px < 8 * CHIPSIZE + 32 && g_boss[1].x == 1 * CHIPSIZE + 32) {
		if (warpFlg == false) {//playerÇ™ç∂Ç…à⁄ìÆ
			g_boss[1].anime = 8;
			g_boss[1].count = 0;
			g_boss[1].attackFlg = false;
			warp_num = 0;
			warpFlg = true;
		}
	}

	if (warpFlg == true) {
		if (warp_num == 0) {//à⁄ìÆäJén
			PlaySoundMem(g_sounds.Warp, DX_PLAYTYPE_BACK, TRUE);//à⁄ìÆâπ
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
		else if (warp_num == 1) {//îΩëŒë§Ç÷
			if (motion_y > 0) {
				motion_y--;
				if (motion_y <= 80 && motion_y > 10) {
					g_boss[1].anime -= 0.1;
				}
			}
			else {
				if (g_boss[1].x == 1 * CHIPSIZE + 32) g_boss[1].anime = 0;
				if (g_boss[1].x == 17 * CHIPSIZE + 32) g_boss[1].anime = 4;
				warp_num = 2;//à⁄ìÆäÆóπ
				warpFlg = false;
			}
		}
	}

	if (warpFlg == false && g_boss[1].attackFlg == false && g_boss[1].damageFlg == false) {//çUåÇë“ã@
		//Ç∑Ç◊ÇƒÇÃîöíeÇ™îöî≠ÇµÇΩÇÁcountäJén
		if(Bomb_Flg[0] == false && Bomb_Flg[1] == false && Bomb_Flg[2] == false
			&& Bomb_Flg2[0] == false && Bomb_Flg2[1] == false && Bomb_Flg2[2] == false) g_boss[1].count++;

		if (g_boss[1].count > 50 * g_boss[1].hp) {
			g_boss[1].count = 0;
			motion_attack = g_boss[1].anime + 3;
			g_boss[1].attackFlg = true;
		}
	}
	if (warpFlg == false && g_boss[1].attackFlg == true) {//çUåÇ
		if (g_boss[1].anime < motion_attack) g_boss[1].anime += 0.1;
		else {
			for (int i = 0; i < 4 - g_boss[1].hp;) {//îöíeÇÃç¿ïWéwíË
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

	//îöíeÇÃèàóù
	if (Bomb_Flg[0] == true) {//1Ç¬ñ⁄
		if (Bomb_Y[0] <= 9 * CHIPSIZE) {//ìäâ∫
			DrawGraph(Bomb_X[0] + 32, Bomb_Y[0], g_img.kanzi[6], TRUE);//[îö]ÇÃï`âÊ
			Bomb_Y[0] += Bomb_speed[0];
		} else {
			if (g_map.gimmickData[(Bomb_Y[0] / CHIPSIZE) + 1][Bomb_X[0] / CHIPSIZE] == BOSS_G_3) {//íeóÕÇ»ÇÁíµÇÀï‘Ç∑
				g_boss[1].damageFlg = true;
				Bomb_Flg2[0] = true;
				Bomb_Flg[0] = false;
				PlaySoundMem(g_sounds.Spring, DX_PLAYTYPE_BACK, TRUE);//ÇŒÇÀâπ
			}
			else {//íÖíe
				if (Bomb_count[0]-- > 0) {//îöîjÉJÉEÉìÉg
					DrawRotaGraph(Bomb_X[0] + 64, Bomb_Y[0] + 32, 1 + ((50 - Bomb_count[0]) * 0.01), 0, g_img.bomb, TRUE);//îöíeÇÃï`âÊ
					g_map.gimmickData[(Bomb_Y[0] / CHIPSIZE) + 1][Bomb_X[0] / CHIPSIZE] = 0;
					g_map.gimmickData[(Bomb_Y[0] / CHIPSIZE) + 1][(Bomb_X[0] / CHIPSIZE) + 1] = 0;
				} else {//îöîj
					DrawBox(Bomb_X[0] - 32, Bomb_Y[0] - 64, Bomb_X[0] + 160, Bomb_Y[0] + 64, 0xFF0000, true);//îöî≠îÕàÕ
					g_map.gimmickData[(Bomb_Y[0] / CHIPSIZE) + 1][Bomb_X[0] / CHIPSIZE] = BOSS_G_2;
					g_map.gimmickData[(Bomb_Y[0] / CHIPSIZE) + 1][(Bomb_X[0] / CHIPSIZE) + 1] = BOSS_G_2;
					Bomb_Flg[0] = false;
					Bomb_Y[0] = -CHIPSIZE;
					Bomb_X[0] = -CHIPSIZE;
					Bomb_count[0] = 0;
					PlaySoundMem(g_sounds.Break, DX_PLAYTYPE_BACK, TRUE);//îöîjâπ
				}
			}
		}
	}
	if (Bomb_Flg[1] == true) {//2Ç¬ñ⁄
		if (Bomb_Y[1] <= 9 * CHIPSIZE) {
			DrawGraph(Bomb_X[1] + 32, Bomb_Y[1], g_img.kanzi[6], TRUE);//[îö]ÇÃï`âÊ
			Bomb_Y[1] += Bomb_speed[1];
		}
		else {
			if (g_map.gimmickData[(Bomb_Y[1] / CHIPSIZE) + 1][Bomb_X[1] / CHIPSIZE] == BOSS_G_3) {
				g_boss[1].damageFlg = true;
				Bomb_Flg2[1] = true;
				Bomb_Flg[1] = false;
				PlaySoundMem(g_sounds.Spring, DX_PLAYTYPE_BACK, TRUE);//ÇŒÇÀâπ
			}
			else {
				if (Bomb_count[1]-- > 0) {
					DrawRotaGraph(Bomb_X[1] + 64, Bomb_Y[1] + 32, 1 + ((50 - Bomb_count[1]) * 0.01), 0, g_img.bomb, TRUE);//îöíeÇÃï`âÊ
					g_map.gimmickData[(Bomb_Y[1] / CHIPSIZE) + 1][Bomb_X[1] / CHIPSIZE] = 0;
					g_map.gimmickData[(Bomb_Y[1] / CHIPSIZE) + 1][(Bomb_X[1] / CHIPSIZE) + 1] = 0;
				}
				else {
					DrawBox(Bomb_X[1] - 32, Bomb_Y[1] - 64, Bomb_X[1] + 160, Bomb_Y[1] + 64, 0xFF0000, true);//îöî≠îÕàÕ
					g_map.gimmickData[(Bomb_Y[1] / CHIPSIZE) + 1][Bomb_X[1] / CHIPSIZE] = BOSS_G_2;
					g_map.gimmickData[(Bomb_Y[1] / CHIPSIZE) + 1][(Bomb_X[1] / CHIPSIZE) + 1] = BOSS_G_2;
					Bomb_Flg[1] = false;
					Bomb_Y[1] = -CHIPSIZE;
					Bomb_X[1] = -CHIPSIZE;
					Bomb_count[1] = 0;
					PlaySoundMem(g_sounds.Break, DX_PLAYTYPE_BACK, TRUE);//îöîjâπ
				}
			}
		}
	}
	if (Bomb_Flg[2] == true) {//3Ç¬ñ⁄
		if (Bomb_Y[2] <= 9 * CHIPSIZE) {
			DrawGraph(Bomb_X[2] + 32, Bomb_Y[2], g_img.kanzi[6], TRUE);//[îö]ÇÃï`âÊ
			Bomb_Y[2] += Bomb_speed[2];
		}
		else {
			if (g_map.gimmickData[(Bomb_Y[2] / CHIPSIZE) + 1][Bomb_X[2] / CHIPSIZE] == BOSS_G_3) {
				g_boss[1].damageFlg = true;
				Bomb_Flg2[2] = true;
				Bomb_Flg[2] = false;
				PlaySoundMem(g_sounds.Spring, DX_PLAYTYPE_BACK, TRUE);//ÇŒÇÀâπ
			}
			else {
				if (Bomb_count[2]-- > 0) {
					DrawRotaGraph(Bomb_X[2] + 64, Bomb_Y[2] + 32, 1 + ((50 - Bomb_count[2]) * 0.01), 0, g_img.bomb, TRUE);//îöíeÇÃï`âÊ
					g_map.gimmickData[(Bomb_Y[2] / CHIPSIZE) + 1][Bomb_X[2] / CHIPSIZE] = 0;
					g_map.gimmickData[(Bomb_Y[2] / CHIPSIZE) + 1][(Bomb_X[2] / CHIPSIZE) + 1] = 0;
				}
				else {
					DrawBox(Bomb_X[2] - 32, Bomb_Y[2] - 64, Bomb_X[2] + 160, Bomb_Y[2] + 64, 0xFF0000, true);//îöî≠îÕàÕ
					g_map.gimmickData[(Bomb_Y[2] / CHIPSIZE) + 1][Bomb_X[2] / CHIPSIZE] = BOSS_G_2;
					g_map.gimmickData[(Bomb_Y[2] / CHIPSIZE) + 1][(Bomb_X[2] / CHIPSIZE) + 1] = BOSS_G_2;
					Bomb_Flg[2] = false;
					Bomb_Y[2] = -CHIPSIZE;
					Bomb_X[2] = -CHIPSIZE;
					Bomb_count[2] = 0;
					PlaySoundMem(g_sounds.Break, DX_PLAYTYPE_BACK, TRUE);//îöîjâπ
				}
			}
		}
	}

	//É_ÉÅÅ[ÉWÇéÛÇØÇÈ
	if (g_boss[1].damageFlg == true) {
		for (bomb_num = 0; bomb_num < 3; bomb_num++) {
			if (Bomb_Flg2[bomb_num] == true) {//3Ç¬ÇÃÇ§ÇøÇ«ÇÃîöíeÇ™íµÇÀï‘Ç≥ÇÍÇΩÇ©
				break;
			}
		}
		if (Bomb_X[bomb_num] != 1 * CHIPSIZE && Bomb_X[bomb_num] != 17 * CHIPSIZE) {//îöíeè„è∏
			DrawGraph(Bomb_X[bomb_num] + 32, Bomb_Y[bomb_num], g_img.kanzi[6], TRUE);//[îö]ÇÃï`âÊ
			if (Bomb_Y[bomb_num] > -CHIPSIZE) Bomb_Y[bomb_num] -= 8;
			else Bomb_X[bomb_num] = g_boss[1].x - 32;
		}
		else {
			if (Bomb_Y[bomb_num] < 3 * CHIPSIZE) {//îöíeç~â∫
				DrawGraph(Bomb_X[bomb_num] + 32, Bomb_Y[bomb_num], g_img.kanzi[6], TRUE);//[îö]ÇÃï`âÊ
				Bomb_Y[bomb_num] += 4;
			}
			else {
				if (Bomb_count[bomb_num]-- > 0) {
					g_boss[1].count = 0;
					DrawRotaGraph(Bomb_X[bomb_num] + 64, Bomb_Y[bomb_num] + 32, 1 + ((50 - Bomb_count[bomb_num]) * 0.01), 0, g_img.bomb, TRUE);//îöíeÇÃï`âÊ
					g_map.gimmickData[(Bomb_Y[bomb_num] / CHIPSIZE) + 1][Bomb_X[bomb_num] / CHIPSIZE] = 0;
					g_map.gimmickData[(Bomb_Y[bomb_num] / CHIPSIZE) + 1][(Bomb_X[bomb_num] / CHIPSIZE) + 1] = 0;
				}
				else {
					if (g_boss[1].count == 0) {
						PlaySoundMem(g_sounds.Break, DX_PLAYTYPE_BACK, TRUE);//îöîjâπ
						DrawBox(Bomb_X[bomb_num] - 32, Bomb_Y[bomb_num] - 64, Bomb_X[bomb_num] + 160, Bomb_Y[bomb_num] + 64, 0xFF0000, true);//îöî≠îÕàÕ
						g_map.gimmickData[(Bomb_Y[bomb_num] / CHIPSIZE) + 1][Bomb_X[bomb_num] / CHIPSIZE] = BOSS_G_2;
						g_map.gimmickData[(Bomb_Y[bomb_num] / CHIPSIZE) + 1][(Bomb_X[bomb_num] / CHIPSIZE) + 1] = BOSS_G_2;
					}

					// ÇTâÒÇÃÇ§ÇøÇQâÒï\é¶Ç∑ÇÈ
					g_boss[1].count++;
					if (g_boss[1].count % 10 == 0) {
						//ï\é¶
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

	if (g_boss[1].hp <= 0) {//HPÇ™0Ç…Ç»Ç¡ÇΩÇÁ
		//g_map.select++;
		g_gameScene = GAME_CLEAR;
	}


	if (g_player.py == 9 * CHIPSIZE) {//playerÇ™ínñ Ç…íÖínÇµÇΩÇÁ
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
				}
			}
		}
	}

	//playerÉ_ÉÅÅ[ÉW
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
	//ÉvÉåÉCÉÑÅ[ÇÃÉâÉCÉtÇ™ÇOÇ»Ç¡ÇΩÇÁ
	//if (g_player.life == 0) {
	//	g_gameScene = GAME_OVER;
	//	//g_player.px = CHIPSIZE * 1, g_player.py = CHIPSIZE * 9;
	//}
}
