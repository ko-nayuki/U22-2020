#include "DxLib.h"
#include "Picture.h"
#include "Map.h"
#include "Boss.h"
#include "player.h"
#include "Gimmick.h"
#include "GameScene.h"

#include <math.h>

void thiefMove() {//boss2
	//���[�V�������Z�l
	//0:���ҋ@ 1~3:���U�� 4:�E�ҋ@ 5~7:�E�U�� 8~15:�����烏�[�v 16~23:�E���烏�[�v

	static int motion_attack = 0;		//�U�����Z�l
	static int motion_y = 0;			//�ړ����̍���
	static bool warpFlg = false;		//�ړ��t���O
	static int warp_num = 0;			//0:�ړ��J�n 1:���Α��� 2:�ړ�����

	//player����������Ƃ͋t�����Ƀ��[�v
	if (g_boss[1].x == 17 * CHIPSIZE + 32) DrawGraph(1 * CHIPSIZE + 32, g_boss[1].y + 21 - motion_y, g_img.thief[15], TRUE);
	if (g_boss[1].x == 1 * CHIPSIZE + 32) DrawGraph(17 * CHIPSIZE + 32, g_boss[1].y + 21 - motion_y, g_img.thief[23], TRUE);

	if (g_player.px > 12 * CHIPSIZE + 32 && g_boss[1].x == 17 * CHIPSIZE + 32) {
		if (warpFlg == false) {//player���E�Ɉړ�
			g_boss[1].anime = 16;
			g_boss[1].count = 0;
			g_boss[1].attackFlg = false;
			warp_num = 0;
			warpFlg = true;
		}
	}
	else if (g_player.px < 6 * CHIPSIZE + 32 && g_boss[1].x == 1 * CHIPSIZE + 32) {
		if (warpFlg == false) {//player�����Ɉړ�
			g_boss[1].anime = 8;
			g_boss[1].count = 0;
			g_boss[1].attackFlg = false;
			warp_num = 0;
			warpFlg = true;
		}
	}

	if (warpFlg == true) {
		if (warp_num == 0) {//�ړ��J�n
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
		else if (warp_num == 1) {//���Α���
			if (motion_y > 0) {
				motion_y--;
				if (motion_y <= 80 && motion_y > 10) {
					g_boss[1].anime -= 0.1;
				}
			}
			else {
				if (g_boss[1].x == 1 * CHIPSIZE + 32) g_boss[1].anime = 0;
				if (g_boss[1].x == 17 * CHIPSIZE + 32) g_boss[1].anime = 4;
				warp_num = 2;//�ړ�����
				warpFlg = false;
			}
		}
	}

	if (warpFlg == false && g_boss[1].attackFlg == false) {//�U���ҋ@
		g_boss[1].count++;
		if (g_boss[1].count > 50 * g_boss[1].hp) {
			g_boss[1].count = 0;
			motion_attack = g_boss[1].anime + 3;
			g_boss[1].attackFlg = true;
		}
	}
	if (warpFlg == false && g_boss[1].attackFlg == true) {//�U��
		if (g_boss[1].anime < motion_attack) g_boss[1].anime += 0.1;
		else g_boss[1].attackFlg = false, g_boss[1].anime = g_boss[1].anime - 3;
	}
}
