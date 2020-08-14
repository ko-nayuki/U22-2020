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
	
	//移動処理
	if (key[KEY_INPUT_LEFT] == 1) {

		//ブロック当たり判定して進む
		if (g_map.playStage[int(g_player.py/CHIPSIZE)][int((g_player.px-4)/CHIPSIZE)] != 1
			&& g_map.playStage[int((g_player.py-1) / CHIPSIZE)+1][int((g_player.px-4)/ CHIPSIZE)] != 1) {
			g_player.px -= 4 * g_player.move;
		}
		
	}

	if (key[KEY_INPUT_RIGHT] == 1) {

		//ブロック当たり判定して進む
		if (g_map.playStage[int(g_player.py/CHIPSIZE)][int((g_player.px+4)/CHIPSIZE)+1] != 1
			&&g_map.playStage[int((g_player.py-1) / CHIPSIZE)+1][int((g_player.px+4) / CHIPSIZE)+1] != 1) {
			g_player.px += 4 * g_player.move;
		}
		

	}

	//画面移動制御

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


	//カウント数から添字を求める。
	g_player.ix = abs(g_player.xcount) % 30 / 10;



	///xカウントがプラスなら右向きなので1行目の先頭添字番号を足す。
	if (g_player.xcount > 0) {
		g_player.result = g_player.ix;
	}
	else if (g_player.xcount < 0) {
		//xカウントがマイナスなら左向きなので、2行目の先頭添字番号を足す。
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
	
	//押されてなければカウントをゼロにする。
	if (key[KEY_INPUT_LEFT] != 1 && key[KEY_INPUT_RIGHT] != 1) {
		g_player.xcount = 0;
		
	}

	}



