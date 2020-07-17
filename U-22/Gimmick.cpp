#include "DxLib.h"
#include "Gimmick.h"
#include "player.h"
#include "GamePlay.h"
#include "Map.h"
#include "Picture.h"

void gimmickDisp() {
	DrawGraph(g_gimmick[LIFT].x, g_gimmick[LIFT].y, g_img.door[int(g_gimmick[LIFT].anime)], TRUE);
	DrawGraph(g_gimmick[BOUND].x, g_gimmick[BOUND].y, g_img.spring[int(g_gimmick[BOUND].anime)], TRUE);
	DrawGraph(g_gimmick[DROP].x, g_gimmick[DROP].y, g_img.itemBox, TRUE);
	DrawFormatString(200, 550, 0x0000ff, "%d", g_gimmick[LIFT].h * CHIPSIZE);
	DrawFormatString(200, 570, 0x0000ff, "%d", g_gimmick[LIFT].y);
}

void gimmickMove() {

	//player���A�C�e�����E������
	if (g_player.itemNo < ITEM_MAX) {
		//��
		if (g_map.playStage[int(g_player.py / CHIPSIZE)][int((g_player.px + 32) / CHIPSIZE)] == A) {
			g_player.item[g_player.itemNo++] = K_UE;
			g_map.playStage[int(g_player.py / CHIPSIZE)][int((g_player.px + 32) / CHIPSIZE)] = 0;
		}
		//��
		if (g_map.playStage[int(g_player.py / CHIPSIZE)][int((g_player.px + 32) / CHIPSIZE)] == B) {
			g_player.item[g_player.itemNo++] = K_SITA;
			g_map.playStage[int(g_player.py / CHIPSIZE)][int((g_player.px + 32) / CHIPSIZE)] = 0;
		}
		//��
		if (g_map.playStage[int(g_player.py / CHIPSIZE)][int((g_player.px + 32) / CHIPSIZE)] == C) {
			g_player.item[g_player.itemNo++] = K_TIKARA;
			g_map.playStage[int(g_player.py / CHIPSIZE)][int((g_player.px + 32) / CHIPSIZE)] = 0;
		}
		//�j
		if (g_map.playStage[int(g_player.py / CHIPSIZE)][int((g_player.px + 32) / CHIPSIZE)] == D) {
			g_player.item[g_player.itemNo++] = K_HA;
			g_map.playStage[int(g_player.py / CHIPSIZE)][int((g_player.px + 32) / CHIPSIZE)] = 0;
		}
		//��
		if (g_map.playStage[int(g_player.py / CHIPSIZE)][int((g_player.px + 32) / CHIPSIZE)] == E) {
			g_player.item[g_player.itemNo++] = K_SHOU;
			g_map.playStage[int(g_player.py / CHIPSIZE)][int((g_player.px + 32) / CHIPSIZE)] = 0;
		}

		//�A�C�e�������l��
		for (int i = 0; i < g_player.itemNo; i++) {
			if (g_player.item[i] == K_NO) {
				g_player.item[i] = g_player.item[i + 1];
				g_player.item[i + 1] = K_NO;
			}
		}
	}

	liftMove();		//�G���x�[�^�[
	boundMove();	//�W�����v��
	breakMove();	//�j��ł����
	dropMove();		//�����M�~�b�N
	fireMove();		//��
}

void liftMove() {
	//�G���x�[�^�[����
	if (g_map.playStage[int(g_player.py / CHIPSIZE)][int((g_player.px + 32) / CHIPSIZE)] == GIM_1) {
		if (g_player.item[g_player.itemSelect] == K_UE || g_player.item[g_player.itemSelect] == K_SITA &&
			g_gimmick[LIFT].moveFlg == false && g_gimmick[LIFT].moveFlg2 == false) {
			if (g_gimmick[LIFT].anime < 2.0F)g_gimmick[LIFT].anime += 0.1F;
		}
		//if (g_gimmick[LIFT].y != CHIPSIZE) {//[��]���g��
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
						break;

					}
				}
			}
		}
		//}
		//if (g_gimmick[LIFT].y != CHIPSIZE * 9) {//[��]���g��
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
						break;
					}
				}
			}
		}
		//}
	}
	else {
		if (g_gimmick[LIFT].anime > 0.0F)g_gimmick[LIFT].anime -= 0.1F;
	}

	if (g_gimmick[LIFT].moveFlg == true) {//�㏸�̏���
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

	if (g_gimmick[LIFT].moveFlg2 == true) {//���~�̏���
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
	//�W�����v�䏈��
	if (g_map.playStage[int(g_player.py / CHIPSIZE) + 1][int((g_player.px + 32) / CHIPSIZE)] == GIM_2) {
		if (g_gimmick[BOUND].y != CHIPSIZE) {//[��]���g��
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
			if (g_map.playStage[int(g_player.py / CHIPSIZE) + 1][int((g_player.px + 32) / CHIPSIZE)] == GIM_2) {
				g_player.fallSpeed = -JUMP_POWER;
				g_gimmick[BOUND].anime = 3;
			}

			//����Ƀu���b�N����������
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
	//�j��ł���ǂ̏���
	if (g_map.gimmickData[int(g_player.py / CHIPSIZE)][int((g_player.px + 4) / CHIPSIZE) + 1] == GIM_3 ||
		g_map.gimmickData[int(g_player.py / CHIPSIZE)][int((g_player.px - 4) / CHIPSIZE)] == GIM_3) {
		if (g_player.item[g_player.itemSelect] == K_HA && key[KEY_INPUT_SPACE] == 1) {
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
void dropMove() {
	//�����M�~�b�N�̏���
	if (g_map.playStage[int(g_player.py / CHIPSIZE)][int((g_player.px + 32) / CHIPSIZE)] == GIM_402) {
		if (g_player.item[g_player.itemSelect] == K_SITA && key[KEY_INPUT_SPACE] == 1) {
			g_gimmick[DROP].ONFlg = true;
			g_player.item[g_player.itemSelect] = K_NO;
			g_player.itemNo--;
		}
	}
	if (g_gimmick[DROP].ONFlg == true) {

		for (int i = (g_gimmick[DROP].x / CHIPSIZE) + 1; i < STAGE_WIDTH; i++) {
			if (g_map.gimmickData[int(g_gimmick[DROP].y / CHIPSIZE) + 1][i] == 8) {
				g_map.playStage[int(g_gimmick[DROP].y / CHIPSIZE) + 1][i] = AIR;
			} else {
				break;
			}
		}
		for (int i = (g_gimmick[DROP].x / CHIPSIZE) - 1; i > 0; i--) {
			if (g_map.gimmickData[int(g_gimmick[DROP].y / CHIPSIZE) + 1][i] == 8) {
				g_map.playStage[int(g_gimmick[DROP].y / CHIPSIZE) + 1][i] = AIR;
			} else {
				break;
			}
		}
		for (int i = 0; i < STAGE_HEIGHT; i++) {
			for (int j = 0; j < STAGE_WIDTH; j++) {
				if (g_map.gimmickData[int(g_player.py / CHIPSIZE) - 1][int((g_player.px + 32) / CHIPSIZE)] == GIM_401) {
					if (g_map.gimmickData[i][j] == 8) {
						g_map.playStage[i][j] = BLOCK;
					}
					g_gimmick[DROP].ONFlg = false;
				}
			}
		}
	}
}
void fireMove() {
	//���̏���
	if (g_map.gimmickData[int(g_player.py / CHIPSIZE)][int((g_player.px + 4) / CHIPSIZE) + 1] == GIM_5 ||
		g_map.gimmickData[int(g_player.py / CHIPSIZE)][int((g_player.px - 4) / CHIPSIZE)] == GIM_5) {
		if (g_player.item[g_player.itemSelect] == K_SHOU && key[KEY_INPUT_SPACE] == 1) {
			g_gimmick[FIRE].ONFlg = true;
			g_player.item[g_player.itemSelect] = K_NO;
			g_player.itemNo--;
		}
	}
	if (g_gimmick[FIRE].ONFlg == true) {
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


void gimmickInit() {
	for (int i = 0; i < GIMMICK_NUM; i++) {
		g_gimmick[i].ONFlg = false;
		g_gimmick[i].moveFlg = false;
		g_gimmick[i].moveFlg2 = false;
		g_gimmick[i].x = 0;
		g_gimmick[i].y = 0;
		g_gimmick[i].w = 0;
		g_gimmick[i].h = 0;
		g_gimmick[i].anime = 0;
	}
}