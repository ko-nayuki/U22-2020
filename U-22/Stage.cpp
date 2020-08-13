//�X�e�[�W�����v���O����

#include "DxLib.h"
#include "Map.h"
#include "Picture.h"
#include "Gimmick.h"
#include "player.h"

//int g_Stage = 0;
//StageInfo Stage;

void StageInit() {

	//�X�e�[�W�ǂݍ���
	for (int i = 0; i < STAGE_HEIGHT; i++) {
		for (int j = 0; j < STAGE_WIDTH; j++) {
			g_map.playStage[i][j] = g_map.stageData[g_map.select][i][j];
			g_map.gimmickData[i][j] = 0;

			if (g_map.playStage[i][j] == 3) {//�v���C���[�̍��W
				g_player.px = j * CHIPSIZE;
				g_player.py = i * CHIPSIZE;
			}

			if (g_map.playStage[i][j] == 5) {//�G���x�[�^�̏��
				g_map.gimmickData[i][j] = g_map.playStage[i][j];
				g_gimmick[LIFT].x = j * CHIPSIZE;
				g_gimmick[LIFT].y = i * CHIPSIZE;
			}
			if (g_map.playStage[i][j] == 6) {//�W�����v��̏��
				g_map.gimmickData[i][j] = g_map.playStage[i][j];
				//g_gimmick[BOUND].x = j * CHIPSIZE;
				//g_gimmick[BOUND].y = i * CHIPSIZE;
			}
			if (g_map.playStage[i][j] == 7) {//�j��ł���ǂ̏��
				g_map.gimmickData[i][j] = g_map.playStage[i][j];
				g_map.playStage[i][j] = 1;
			}
			if (g_map.playStage[i][j] == 8) {//�����M�~�b�N�̏��
				g_map.gimmickData[i][j] = g_map.playStage[i][j];
				g_map.playStage[i][j] = 1;
			}
			if (g_map.playStage[i][j] == 9) {//�����Ŕ̏��
				g_map.gimmickData[i][j] = g_map.playStage[i][j];
				//g_gimmick[DROP].x = j * CHIPSIZE;
				//g_gimmick[DROP].y = i * CHIPSIZE;
			}
			if (g_map.playStage[i][j] == 10) {//���̏��
				g_map.gimmickData[i][j] = g_map.playStage[i][j];
				g_map.playStage[i][j] = 1;
			}
			if (g_map.playStage[i][j] == 11) {//���[�vA�̏��
				g_map.gimmickData[i][j] = g_map.playStage[i][j];
				g_gimmick[WARP_A].x = j * CHIPSIZE;
				g_gimmick[WARP_A].y = i * CHIPSIZE;
			}
			if (g_map.playStage[i][j] == 12) {//���[�vB�̏��
				g_map.gimmickData[i][j] = g_map.playStage[i][j];
				g_gimmick[WARP_B].x = j * CHIPSIZE;
				g_gimmick[WARP_B].y = i * CHIPSIZE;
			}
			g_map.random[i][j] = rand() % 3;
		}
	}
}

void StageDisp() {
	//�X�e�[�W�`��
	for (int i = 0; i < STAGE_HEIGHT; i++) {
		for (int j = 0; j < STAGE_WIDTH; j++) {//�}�b�v�̕`��
			if (g_map.playStage[i][j] != 0 && g_map.playStage[i][j] < 5 && g_map.playStage[i][j] < A) {
				DrawGraph(j * CHIPSIZE, i * CHIPSIZE, g_img.MAP[g_map.playStage[i][j]], TRUE);
			}
			if (g_map.playStage[i][j] >= A) {//�����̕`��
				//if(g_map.playStage[i][j] == G) SetDrawBright(255, 0, 0);
				DrawGraph(j * CHIPSIZE, i * CHIPSIZE, g_img.kanzi[g_map.playStage[i][j] - A], TRUE);
				//SetDrawBright(255, 255, 255);
			}
			if (g_map.gimmickData[i][j] == GIM_1) {
				if (g_player.item[g_player.itemSelect] == K_SITA) {
					DrawGraph(j * CHIPSIZE, i * CHIPSIZE, g_img.gimKanzi[1], TRUE);
				} else {
					DrawGraph(j* CHIPSIZE, i* CHIPSIZE, g_img.gimKanzi[0], TRUE);
				}
			}
			if (g_map.gimmickData[i][j] == GIM_2) {
				DrawGraph(j * CHIPSIZE, i * CHIPSIZE, g_img.gimKanzi[2], TRUE);
			}
			if (g_map.gimmickData[i][j] == GIM_402) {
				DrawGraph(j * CHIPSIZE, i * CHIPSIZE, g_img.gimKanzi[3], TRUE);
			}
			if (g_map.gimmickData[i][j] == GIM_601 || g_map.gimmickData[i][j] == GIM_602) {
				DrawGraph(j * CHIPSIZE, i * CHIPSIZE, g_img.gimKanzi[4], TRUE);
			}

			if (g_map.playStage[i][j] == BOSS_G_1 && g_map.playStage[i][j + 1] == BOSS_G_1) {
				DrawGraph(j * CHIPSIZE, i * CHIPSIZE, g_img.Cauldron, TRUE);
			}
		}
	}

}

void SelectMAPDisp() {
	for (int i = 0; i < STAGE_HEIGHT; i++) {
		for (int j = 0; j < STAGE_WIDTH; j++) {
			g_map.playStage[i][j] = g_map.selectMap[i][j];
			if (g_map.playStage[i][j] != 0) {
			DrawGraph(j * CHIPSIZE, i * CHIPSIZE, g_img.MAP[g_map.playStage[i][j]], TRUE);
			}
			if (g_map.playStage[i][j] == 3) {//�v���C���[�̍��W
				g_player.px = j * CHIPSIZE;
				g_player.py = i * CHIPSIZE;
			}
		}
	}
}

void TitleMAPDisp() {
	for (int i = 0; i < STAGE_HEIGHT; i++) {
		for (int j = 0; j < STAGE_WIDTH; j++) {
			g_map.playStage[i][j] = g_map.TitleMap[i][j];
			if (g_map.playStage[i][j] == 1) {
				DrawGraph(j * CHIPSIZE, i * CHIPSIZE, g_img.MAP[g_map.playStage[i][j]], TRUE);
			}
			if (g_map.playStage[i][j] == 3) {//�v���C���[�̍��W
				g_player.px = j * CHIPSIZE;
				g_player.py = i * CHIPSIZE;
			}
			if (g_map.playStage[i][j] == 30) {//�n
				DrawGraph(j * CHIPSIZE, i * CHIPSIZE, g_img.T_kanzi[0], TRUE);
			}
			//if (g_map.playStage[i][j] == 31) {//�J
			//	DrawGraph(j * CHIPSIZE, i * CHIPSIZE, g_img.T_kanzi[1], TRUE);
			//}
			if (g_map.playStage[i][j] == 32) {//�I
				DrawGraph(j * CHIPSIZE, i * CHIPSIZE, g_img.T_kanzi[2], TRUE);
			}
			//if (g_map.playStage[i][j] == 33) {//��
			//	DrawGraph(j * CHIPSIZE, i * CHIPSIZE, g_img.T_kanzi[3], TRUE);
			//}
		}
	}
}

void BackStageDisp() {
	for (int i = 0; i < STAGE_HEIGHT; i++) {
		for (int j = 0; j < STAGE_WIDTH; j++) {
			//DrawGraph(j * CHIPSIZE, i * CHIPSIZE, g_img.bookshelf[g_map.random[i][j]], TRUE);
			DrawGraph(j * CHIPSIZE, i * CHIPSIZE, g_img.MAP[0], TRUE);
		}
	}
}


//int StageObj(int Objimg) {
//	//�I�u�W�F�N�g����
//	switch (Objimg)
//	{
//	case 0:		break;
//	case 1:		return g_img.sample[1]; break;
//	case 2:		return g_img.door[0]; break;
//	case 3:		return g_img.sample[3]; break;
//	case 4:		return g_img.sample[4]; break;
//	case 5:		return g_img.sample[5]; break;
//	case 6:		return g_img.sample[6]; break;
//	case 7:		return g_img.sample[7]; break;
//	case 8:		return g_img.sample[8]; break;
//	case 9:		return g_img.sample[9]; break;
//	case 10:    return g_img.book[1]; break;
//	}
//	
//}
