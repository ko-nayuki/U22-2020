#include "DxLib.h"
#include "player.h"
#include "Picture.h"
#include "Map.h"
#include "KeyControl.h"
#include "Gimmick.h"
#include "GameScene.h"

void PlayerInit() {
	g_gimmick[BOUND].tikara = 0;
	g_player.life = 3;
	g_player.syo = 0;
	g_player.dir = 0;
	g_player.aaa = 0;
	g_player.aab = 0;
	g_player.result = 0;

	for (int i = 0; i < ITEM_MAX; i++) {
		g_player.item[i] = K_NO;
	}
	g_player.itemNo = 0;
	g_player.itemSelect = 0;
}

//void HPDisp() {
//	//HP表示
//	DrawGraph(600,675, g_img.hp, TRUE);
//	SetFontSize(50);
//	DrawFormatString(670, 690, 0xffffff, "×%d", g_player.life);
//	DrawExtendGraph(780, 690,830,740, g_img.RetryButon, TRUE);
//	DrawGraph(840, 685, g_img.RetryText, FALSE);
//	/*DrawExtendGraph(750, 760, 690, 730, g_img.RetryButon, TRUE);
//	DrawExtendGraph(670, 730, 690, 780, g_img.RetryText, FALSE);*/
//}

void PlayerMove(){
	//SetFontSize(20);
	//DrawFormatString(0, 60, 0xffffff, "xc%d", g_player.xcount);
	//DrawFormatString(0, 80, 0xffffff, "yc%d", g_player.ycount);
	//DrawFormatString(0, 100, 0xffffff, "re%d", g_player.result);
	//DrawFormatString(0, 120, 0xffffff, "dir%d", g_player.dir);

	//DrawFormatString(0, 400, 0x000000, "%d", g_player.px / CHIPSIZE);
	//DrawFormatString(0, 450, 0x000000, "%d", g_player.px);
	//DrawFormatString(0, 500, 0x000000, "%d", g_player.py / CHIPSIZE);
	//DrawFormatString(0, 550, 0x000000, "%d", g_player.py);
	//DrawFormatString(0, 600, 0x000000, "%d", g_player.itemNo);
	//
	
	

	//移動処理
	if (g_NowKey & PAD_INPUT_LEFT || key[KEY_INPUT_LEFT] == 1) {

		//ブロック当たり判定して進む
		if (g_map.playStage[int(g_player.py/CHIPSIZE)][int((g_player.px-4)/CHIPSIZE)] != 1
			&& g_map.playStage[int((g_player.py-1) / CHIPSIZE)+1][int((g_player.px-4)/ CHIPSIZE)] != 1) {
			g_player.px -= 4 * g_player.move;
		}
		
	}

	if (g_NowKey & PAD_INPUT_RIGHT || key[KEY_INPUT_RIGHT] == 1) {

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


	if (g_NowKey & PAD_INPUT_LEFT || key[KEY_INPUT_LEFT] == 1) {
		if (g_player.xcount > 0)
			g_player.xcount = 0;
		g_player.ycount = 0;
		--g_player.xcount;
		g_player.dir = 1;
	}
	if (g_NowKey & PAD_INPUT_RIGHT || key[KEY_INPUT_RIGHT] == 1) {
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


	if ((g_map.playStage[int(g_player.py / CHIPSIZE)+1][int((g_player.px) / CHIPSIZE)+1] == BLOCK ||
		 g_map.playStage[int(g_player.py / CHIPSIZE) + 1][int(g_player.px / CHIPSIZE)] == BLOCK) ||
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

	if (g_map.playStage[int(g_player.py / CHIPSIZE)][int(g_player.px / CHIPSIZE)] == BLOCK ||
		g_map.playStage[int((g_player.py - 8) / CHIPSIZE)][int((g_player.px + 64) / CHIPSIZE)] == BLOCK ||
		g_map.playStage[int((g_player.py - 8) / CHIPSIZE)][int((g_player.px) / CHIPSIZE)] == BLOCK ||
		g_map.playStage[int(g_player.py / CHIPSIZE)][int(g_player.px / CHIPSIZE) + 1] == BLOCK ||
		g_player.py == 64) {

		g_player.py = g_player.py + 1;
		g_player.fallSpeed = 0;
	}

	if(g_player.muteki == 0){
		DrawGraph(g_player.px, g_player.py, g_img.gh[g_player.result], TRUE);
	}

	if (g_player.muteki == 1) {
		
		// ５回のうち２回表示する。
		static int count = 0;
		count = (count + 1) % 60;
		DrawFormatString(0, 700, 0x000000, "%d", count);
		if (count%2==0) {
			//表示
			DrawGraph(g_player.px, g_player.py, g_img.gh[g_player.result], TRUE);
		}
		if (count==59||g_player.life==0){
			g_player.muteki = 0;

			if (g_player.life == 0) {
				g_gameScene = GAME_OVER;
			}

		}
	}


	//DrawGraph(g_player.px, g_player.py, g_img.gh[g_player.result], TRUE);
	

	//押されてなければカウントをゼロにする。
	//if (/*CheckHitKey(PAD_INPUT_LEFT) == 0 || CheckHitKey(PAD_INPUT_RIGHT) == 0*/key[KEY_INPUT_LEFT] != 1 && key[KEY_INPUT_RIGHT] != 1) {
	//	g_player.xcount = 0;
	//	
	//}

	}



