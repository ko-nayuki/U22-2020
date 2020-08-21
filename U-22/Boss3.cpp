#include "DxLib.h"
#include "Picture.h"
#include "Map.h"
#include "Boss.h"
#include "player.h"
#include "Gimmick.h"
#include "GameScene.h"


#include <math.h>

void ColossusMove() {//boss3
	//0~2 �����̎�  3~5 �E���̎�

    static int boos3_attack = 1; //�U��
	static int Random;	

	static int UpDown_flg = 1;  // 0:�㉺���Ȃ� 1:�����Ə㉺����
	static int UpDown_s = 0;
	static int UpDown_count = 0;

	static int search_LR = 1;  //0:�I�t 1:�I��
	static int search_count = 250;
	static int search_stop = 100;
	static int search_attack1 = 0;//0:�I�t 1:�I��

	static int attack1_Fall = 0;

	static int time = 0;


	if (boos3_attack > 0 && (g_boss[2].hp > 0 || g_boss[3].hp > 0)) {
		if (g_boss[2].hp > 0 && g_boss[3].hp > 0) {
			Random = GetRand(1);
			Random += 2;
		}
		else if(g_boss[2].hp > 0 && g_boss[3].hp == 0){
			Random = 2;
		}
		else
		{
			Random = 3;
		}
	}


	if (UpDown_flg == 1) {               //�㉺�ړ�����
		if (UpDown_s == 0) {
			g_boss[2].y += 0.5;
			UpDown_count += 1;
			if (UpDown_count == 50) {
				UpDown_s = 1;
			}
		}
		if (UpDown_s == 1) {
			g_boss[2].y -= 0.5;
			UpDown_count -= 1;
			if (UpDown_count == 0) {
				UpDown_s = 0;
			}
		}
	}

	if (boos3_attack == 1) {             //�����U��
		if (search_LR == 1) {
			if (g_boss[2].x < g_player.px - 96) {
				g_boss[2].x += 3;
				search_count -= 1;
			}

			if (g_boss[2].x > g_player.px - 96) {
				g_boss[2].x -= 3;
				search_count -= 1;
			}
		}

		if (search_count <= 0) {
			search_LR = 0;
			UpDown_flg = 0;
			search_stop -= 1;
			if (search_stop <= 0) {
				search_attack1 = 1;
			}
		}

		if (search_attack1 == 1)  //�U�艺�낵���[�V����
		{
			if ((g_map.playStage[(int(g_boss[2].y) / CHIPSIZE) + 1][int(g_boss[2].x) / CHIPSIZE] == AIR &&
				g_boss[2].damageFlg == false)) {

				if ((g_map.playStage[(int(g_boss[2].y) / CHIPSIZE) + 3][int(g_boss[2].x) / CHIPSIZE]) == AIR) {
					g_boss[2].y += CHIPSIZE;
				}
				attack1_Fall += 1;
			}
		}
		if (attack1_Fall >= 500) {
			search_count = 250;
			search_attack1 = 0;
			if (g_boss[2].y >= -192)
				g_boss[2].y -= 10;
			if (g_boss[2].y <= -192) {
				boos3_attack = 0;
				search_LR = 1;
				UpDown_count = 0;
				attack1_Fall = 0;
			}
		}
	}



}