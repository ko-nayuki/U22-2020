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

int next_Action = 0;					// 1~3:�W�����v  4:��
int jump_x = 10 * CHIPSIZE + 32;		//�W�����v�̒��n�n�_
int jump_num = 0;					//0:�O�i 1:��� 2:���̏�
float fallSpeed = 0.0;
int wind_time = 200;					//���̎���
bool windFlg = false;
bool jumpFlg = false;
int gimmick_time = 100;				//�����M�~�b�N�����ɖ߂鎞��

void wolfMove() {// boss1

	//DrawFormatString(500, 450, 0x00FFFF, "%d", jump_x);
	//DrawFormatString(500, 420, 0x00FFFF, "%d", next_Action);

	//���ꂪ�������Ƃ��ɗ���
	if (g_map.playStage[(int(g_boss[0].y) / CHIPSIZE) + 1][int(g_boss[0].x) / CHIPSIZE] == AIR &&
		g_map.gimmickData[(int(g_boss[0].y) / CHIPSIZE) + 1][int(g_boss[0].x) / CHIPSIZE] == GIM_401 &&
		g_boss[0].damageFlg == false) {
		g_boss[0].attackFlg = false;
		g_boss[0].damageFlg = true;
		g_boss[0].hp--;
		g_boss[0].count = 0;
		jumpFlg = false;
		windFlg = false;
	}

	if (g_boss[0].damageFlg == false) {

		//���̍s���܂ł̎���
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
			if (next_Action == 4) g_boss[0].anime = 8.9;

			fallSpeed = (g_boss[0].x + jump_x) / 2;
			g_boss[0].count = 0;
			g_boss[0].attackFlg = true;
		}
	}

	//�W�����v
	if ((next_Action >= 1 && next_Action < 4) && g_boss[0].attackFlg == true) {

		if (jump_num == 0) {//�O�i
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
		if (jump_num == 1) {//���
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
		if (jump_num == 2) {//���̏�W�����v
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

	//��
	if (next_Action == 4 && g_boss[0].attackFlg == true) {
		if (g_boss[0].anime >= 8.0) {
			g_boss[0].anime -= 0.02F;

			if (windFlg == true) {
				g_boss[0].x += 0.5F;
				if (g_boss[0].x >= 15 * CHIPSIZE + 33) windFlg = false;
			}
			if (windFlg == false) {
				g_boss[0].x -= 0.5F;
				if (g_boss[0].x <= 15 * CHIPSIZE + 31) windFlg = true;
			}
		}
		else {
			g_boss[0].x = 15 * CHIPSIZE + 32;
			if (g_boss[0].anime >= 7.0) g_boss[0].anime -= 0.1F;
			else g_boss[0].anime = 0;
		}

		if (g_boss[0].anime == 0) {
			PlaySoundMem(g_sounds.Breath, DX_PLAYTYPE_BACK, TRUE);
			if (g_player.px < g_boss[0].x) g_player.px -= (wind_time * 0.01) + (4.5 - float(g_boss[0].hp));
			//SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150);
			//DrawBox(0, 384 + (wind_time / 10 - 20), g_boss[0].x, 384 - (wind_time / 10 - 20), 0x8888ff, true);
			//SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			DrawGraph(-300 + wind_time * 9, 6 * CHIPSIZE, g_img.wind, TRUE);
			DrawGraph(-350 + wind_time * 9, 6 * CHIPSIZE - 32, g_img.wind, TRUE);
			DrawGraph(-400 + wind_time * 9, 6 * CHIPSIZE + 32, g_img.wind, TRUE);
			if (wind_time-- <= 0) {
				wind_time = 200;
				g_boss[0].attackFlg = false;
			}
			if (g_player.px + 32 <= CHIPSIZE) {
				wind_time = 200;
				g_boss[0].attackFlg = false;
				g_player.px = CHIPSIZE;
			}
		}
	}

	//�����M�~�b�N�����ԂŌ��ɖ߂�
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

	//�_���[�W�����������
	if (g_boss[0].damageFlg == true) {

		SetDrawBright(255, 255 - g_boss[0].count * (5 - g_boss[0].hp), 255);
		DrawGraph(g_boss[0].x, g_boss[0].y - CHIPSIZE, g_img.wolf[int(g_boss[0].anime)], TRUE);
		SetDrawBright(255, 255, 255);

		if (g_boss[0].y < 9 * CHIPSIZE && g_boss[0].count == 0) {//����
			g_boss[0].anime = 1;
			g_boss[0].y += 8;
		}
		else {
			g_boss[0].count++;
			if (g_boss[0].count > 50) {//��������ǂ�

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

				if (g_boss[0].hp <= 0) {//HP��0�ɂȂ�����
					g_boss[0].anime = 2;
					next_Action = 0;
					wind_time = 200;
					gimmick_time = 100;
					jumpFlg = false;
					windFlg = false;
					if (g_boss[0].y > 10 * CHIPSIZE - 16) {
						//g_map.select++;
						g_gameScene = GAME_CLEAR;
					}
					else g_boss[0].y += 0.2F;
				}
				else {//HP���܂��c���Ă���Ȃ�
					if (jumpFlg == false) g_boss[0].y -= 8, g_boss[0].anime = 2;
					else {//��ɕ��A
						g_boss[0].y += 8;
						if (g_boss[0].y >= 6 * CHIPSIZE) {
							g_boss[0].y = 6 * CHIPSIZE;
							g_map.playStage[6][18] = B;
							g_boss[0].damageFlg = false;
							g_boss[0].count = 0;
							next_Action = 0;
							wind_time = 200;
							jumpFlg = false;
							windFlg = false;
						}
					}
					if (g_boss[0].y < 3 * CHIPSIZE) jumpFlg = true;
				}
			}
			else {//���Ŗ\���
				PlaySoundMem(g_sounds.Fire, DX_PLAYTYPE_BACK, TRUE);//�Ă��鉹
				g_boss[0].y += 0.3F;
				if (g_boss[0].count % 9 == 0) g_boss[0].anime = 1;
				if (g_boss[0].count % 9 == 5) g_boss[0].anime = 2;
			}
		}
	}

	if (g_player.py > 9 * CHIPSIZE) {//player�����ɗ�������
		g_map.playStage[6][18] = B;
	}

	//player�_���[�W
	if (g_player.px < g_boss[0].x + 44 &&
		g_player.px + 64 > g_boss[0].x + 20 &&
		g_player.py < g_boss[0].y + 44 &&
		g_player.py + 64 > g_boss[0].y + 20) {
		if (g_boss[0].damageFlg == false && g_player.muteki == 0) {
			if (g_player.px + 64 < g_boss[0].x + 44) {
				PlaySoundMem(g_sounds.Damage, DX_PLAYTYPE_BACK, TRUE);
				g_player.muteki = 1;
				g_player.life -= 1;
			}
			else if (g_player.px > g_boss[0].x) {
				PlaySoundMem(g_sounds.Damage, DX_PLAYTYPE_BACK, TRUE);
				g_player.muteki = 1;
				g_player.life -= 1;
			}
		}
		//DrawBox(g_boss[0].x + 20, g_boss[0].y + 20, g_boss[0].x + 44, g_boss[0].y + 44,0xFF0000,true);
	}
	//�v���C���[�̃��C�t���O�Ȃ�����
	//if (g_player.life == 0) {
	//	g_gameScene = GAME_OVER;
	//}

}

void boss1_Init() {

	next_Action = 0;					// 1~3:�W�����v  4:��
	jump_x = 10 * CHIPSIZE + 32;		//�W�����v�̒��n�n�_
	jump_num = 0;					//0:�O�i 1:��� 2:���̏�
	fallSpeed = 0.0;
	wind_time = 200;					//���̎���
	windFlg = false;
	jumpFlg = false;
	gimmick_time = 100;				//�����M�~�b�N�����ɖ߂鎞��
}
