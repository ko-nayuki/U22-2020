#include "DxLib.h"
#include "player.h"
#include "Picture.h"
#include "Map.h"
#include "Gimmick.h"



void PlayerMove(){

	DrawFormatString(0, 60, 0xffffff, "xc%d", g_player.xcount);
	DrawFormatString(0, 80, 0xffffff, "yc%d", g_player.ycount);
	DrawFormatString(0, 100, 0xffffff, "re%d", g_player.result);
	DrawFormatString(0, 120, 0xffffff, "dir%d", g_player.dir);

	DrawFormatString(0, 400, 0x000000, "%d", g_player.px / CHIPSIZE);
	DrawFormatString(0, 450, 0x000000, "%d", g_player.px);
	DrawFormatString(0, 500, 0x000000, "%d", g_player.py / CHIPSIZE);
	DrawFormatString(0, 550, 0x000000, "%d", g_player.py);
	DrawFormatString(0, 600, 0x000000, "%d", g_player.itemNo);
	
	//�ړ�����
	if (key[KEY_INPUT_LEFT] == 1) {

		//�u���b�N�����蔻�肵�Đi��
		if (g_map.playStage[int(g_player.py/CHIPSIZE)][int((g_player.px-4)/CHIPSIZE)] != 1
			&& g_map.playStage[int((g_player.py-1) / CHIPSIZE)+1][int((g_player.px-4)/ CHIPSIZE)] != 1) {
			g_player.px -= 4 * g_player.move;
		}
		
	}

	if (key[KEY_INPUT_RIGHT] == 1) {

		//�u���b�N�����蔻�肵�Đi��
		if (g_map.playStage[int(g_player.py/CHIPSIZE)][int((g_player.px+4)/CHIPSIZE)+1] != 1
			&&g_map.playStage[int((g_player.py-1) / CHIPSIZE)+1][int((g_player.px+4) / CHIPSIZE)+1] != 1) {
			g_player.px += 4 * g_player.move;
		}
		

	}

	//��ʈړ�����

	if (g_player.px + CHIPSIZE > 1280)
		g_player.px = 1280 - CHIPSIZE;

	if (g_player.px < 0)
		g_player.px = 0;


	if (key[KEY_INPUT_LEFT] == 1) {
		if (g_player.xcount > 0)
			g_player.xcount = 0;
		g_player.ycount = 0;
		--g_player.xcount;
		g_player.dir = 1;
	}
	if (key[KEY_INPUT_RIGHT] == 1) {
		if (g_player.xcount < 0)
			g_player.xcount = 0;
		g_player.ycount = 0; 
		++g_player.xcount;
		g_player.dir = 0;
	}


	//�J�E���g������Y�������߂�B
	g_player.ix = abs(g_player.xcount) % 30 / 10;



	///x�J�E���g���v���X�Ȃ�E�����Ȃ̂�1�s�ڂ̐擪�Y���ԍ��𑫂��B
	if (g_player.xcount > 0) {
		g_player.result = g_player.ix;
	}
	else if (g_player.xcount < 0) {
		//x�J�E���g���}�C�i�X�Ȃ獶�����Ȃ̂ŁA2�s�ڂ̐擪�Y���ԍ��𑫂��B
		g_player.ix += 3;
		g_player.result = g_player.ix;
	}

	
	g_player.fallSpeed += GRAVITY;
	g_player.py += g_player.fallSpeed;


	if ((g_map.playStage[int(g_player.py / CHIPSIZE)+1][int((g_player.px+64) / CHIPSIZE)] == BLOCK ||
		 g_map.playStage[int(g_player.py / CHIPSIZE)+1][int(g_player.px / CHIPSIZE)] == BLOCK) ||
		 g_map.playStage[int(g_player.py / CHIPSIZE) + 1][int(g_player.px / CHIPSIZE)] == GIM_2) {

		g_player.fallSpeed = 0;

		if (g_map.playStage[int(g_player.py / CHIPSIZE) + 1][int(g_player.px / CHIPSIZE)] == GIM_2) {
			g_player.py = (g_player.py / CHIPSIZE) * CHIPSIZE;
		}

		if (g_map.playStage[int(g_player.py / CHIPSIZE) + 1][int(g_player.px / CHIPSIZE)] == BLOCK ||
			g_map.playStage[int((g_player.py+64) / CHIPSIZE) + 1][int((g_player.px+64)/CHIPSIZE)] == BLOCK) {
			g_player.py = (g_player.py / CHIPSIZE) * CHIPSIZE;
		}
		
	}

	DrawGraph(g_player.px, g_player.py, g_img.gh[g_player.result], TRUE);
	
	//������ĂȂ���΃J�E���g���[���ɂ���B
	if (key[KEY_INPUT_LEFT] != 1 && key[KEY_INPUT_RIGHT] != 1) {
		g_player.xcount = 0;
		
	}

	}



