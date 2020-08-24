#include "DxLib.h"
#include "KeyControl.h"
#include "GameScene.h"
#include "StageSelect.h"
#include "Map.h"
#include "player.h"
#include "enemy.h"
#include "Gimmick.h"
#include "yoshitaka.h"
#include "Boss.h"
#include "Picture.h"


void StageSelect() {
	//PlayerInit();
	SelectDisp();
	SelectMove();
	if (Fead.FeadFlg == 0) FeadIn();

}

void SelectDisp() {
	BackStageDisp();
	SelectMAPDisp();
	SelectBook();
	DrawFormatString(600, 300, 0x000000, "SPACE");
	DrawFormatString(0, 650, 0x000000, "%d", g_map.select);
	DrawFormatString(0, 670, 0x000000, "%d", g_Select.Key);

}
void SelectMove() {

	//if (g_map.playStage[int(g_player.py /CHIPSIZE) + 1][int(g_player.px / CHIPSIZE)] != 1) {
	//	g_player.py += 16;
	//}

	PlayerMove();

	//DrawBox(g_Select.stage3x, 0, g_Select.stage3x + 128, g_Select.stage1y, 0xFFFFFF, FALSE);

	if (g_Select.stage1x < g_player.px + 64 && g_Select.stage1x + 128 > g_player.px) {
		DrawString(0, 650, "ステージ１", 0x000000);
	}
	if (g_Select.stage2x < g_player.px + 64 && g_Select.stage2x + 128 > g_player.px) {
		DrawString(0, 650, "ステージ２", 0x000000);
	}
	if (g_Select.stage3x < g_player.px + 64 && g_Select.stage3x + 128 > g_player.px) {
		DrawString(0, 650, "ステージ３", 0x000000);
	}
	if (g_Select.stage4x < g_player.px + 64 && g_Select.stage4x + 128 > g_player.px) {
		DrawString(0, 650, "ステージ4", 0x000000);
	}

	/*if (g_KeyFlg & PAD_INPUT_RIGHT) {
		if (++g_map.select > STAGE - 1) g_map.select = 0;
	}
	if (g_KeyFlg & PAD_INPUT_LEFT) {
		if (--g_map.select < 0) g_map.select = STAGE - 1;
	}*/

	if (g_KeyFlg & PAD_INPUT_M || g_KeyFlg & PAD_INPUT_2) {
		/*Fead.InfoStg = 2;
		FeadOut();
		gimmickInit();
		StageInit();
		EnemyInit();
		bossInit();
		for (int i = 0; i < ITEM_MAX; i++) {
			g_player.item[i] = K_NO;
		}
		g_player.itemNo = 0;

		g_gameScene = GAME_PLAY;*/
			if (g_Select.stage1x < g_player.px + 64 && g_Select.stage1x + 128 > g_player.px) {
				g_map.select = 0;
				g_Select.Checkkey = 0;
				Fead.InfoStg = 2;
				FeadOut();
				gimmickInit();
				PlayerInit();
				StageInit();
				EnemyInit();
				bossInit();
				//g_gameScene = GAME_PLAY;
			}
			if ((g_Select.stage2x < g_player.px + 64 && g_Select.stage2x + 128 > g_player.px) && g_Select.Key >= 1) {
				g_map.select = 3;
				g_Select.Checkkey = 1;
				Fead.InfoStg = 2;
				FeadOut();
				gimmickInit();
				PlayerInit();
				StageInit();
				EnemyInit();
				bossInit();
			}
			if ((g_Select.stage3x < g_player.px + 64 && g_Select.stage3x + 128 > g_player.px) && g_Select.Key >= 2) {
				g_map.select = 6;
				g_Select.Checkkey = 2;
				Fead.InfoStg = 2;
				FeadOut();
				gimmickInit();
				PlayerInit();
				StageInit();
				EnemyInit();
				bossInit();
			}
			if ((g_Select.stage4x < g_player.px + 64 && g_Select.stage4x + 128 > g_player.px) && g_Select.Key >= 3) {
				g_map.select = 9;
				g_Select.Checkkey = 3;
				Fead.InfoStg = 2;
				FeadOut();
				gimmickInit();
				PlayerInit();
				StageInit();
				EnemyInit();
				bossInit();
			}
	}
}

void SelectBook() {
	static bool text_Flg = true;//テキストをふわふわさせる
	static float text_Y = 0.0;

	static float animation =  0.0;//本のアニメーション

	if (animation < 4.0) animation += 0.1F;
	else animation = 0.0;

	//g_Select.Key = 3;

	//W1
	if (g_Select.stage1x < g_player.px + 64 && g_Select.stage1x + 128 > g_player.px) {
		DrawGraph(3 * CHIPSIZE, 8 * CHIPSIZE, g_img.goal[int(animation)], TRUE);
	}
	else {
		DrawGraph(3 * CHIPSIZE, 8 * CHIPSIZE, g_img.goal[0], TRUE);
	}

	//W2
	if (g_Select.stage2x < g_player.px + 64 && g_Select.stage2x + 128 > g_player.px && g_Select.Key >= 1) {
		//SetDrawBright(255, 255, 255);
		DrawGraph(9 * CHIPSIZE, 8 * CHIPSIZE, g_img.goal[int(animation)], TRUE);
		//SetDrawBright(255, 255, 255);
	}
	else {
		DrawGraph(9 * CHIPSIZE, 8 * CHIPSIZE, g_img.SelectBook[0], TRUE);
	}

	//W3
	if (g_Select.stage3x < g_player.px + 64 && g_Select.stage3x + 128 > g_player.px && g_Select.Key >= 2) {
		//SetDrawBright(255, 0, 0);
		DrawGraph(12 * CHIPSIZE, 8 * CHIPSIZE, g_img.goal[int(animation)], TRUE);
		//SetDrawBright(255, 255, 255);
	}
	else {
		DrawGraph(12 * CHIPSIZE, 8 * CHIPSIZE, g_img.SelectBook[1], TRUE);
	}

	//W4
	if (g_Select.stage4x < g_player.px + 64 && g_Select.stage4x + 128 > g_player.px && g_Select.Key >= 3) {
		//SetDrawBright(255, 0, 0);
		DrawGraph(15 * CHIPSIZE, 8 * CHIPSIZE, g_img.goal[int(animation)], TRUE);
		//SetDrawBright(255, 255, 255);
	}
	else {
		DrawGraph(15 * CHIPSIZE, 8 * CHIPSIZE, g_img.SelectBook[2], TRUE);
	}

	//text
	if (text_Flg == true) {
		text_Y += 0.1F;
		if (text_Y >= 1.5F) text_Flg = false;
	}
	if (text_Flg == false) {
		text_Y -= 0.1F;
		if (text_Y <= -1.5F) text_Flg = true;
	}

	SetFontSize(24);
	if (g_Select.Key != 0 && g_Select.Key <= 3) {
		DrawString((6 + (3 * g_Select.Key)) * CHIPSIZE + 38, 480 + text_Y, "NEXT", 0x444444);
	} else if(g_Select.Key == 0){
		DrawString(3 * CHIPSIZE + 30, 480 + text_Y, "START", 0x444444);
	}

	if (g_Select.Key > 0) {
		DrawString(3 * CHIPSIZE + 30, 480, "CLEAR", 0x00FFFF);
	}
	if (g_Select.Key > 1) {
		DrawString(9 * CHIPSIZE + 30, 480, "CLEAR", 0x00FFFF);
	}
	if (g_Select.Key > 2) {
		DrawString(12 * CHIPSIZE + 30, 480, "CLEAR", 0x00FFFF);
	}
	if (g_Select.Key > 3) {
		DrawString(15 * CHIPSIZE + 30, 480, "CLEAR", 0x00FFFF);
	}
	SetFontSize(16);
}
