#include "DxLib.h"
#include "KeyControl.h"
#include "GameScene.h"
#include "GameTitle.h"
#include "Map.h"
#include "player.h"
#include "Picture.h"
#include "yoshitaka.h"
#include "Sounds.h"

static int MenuNo = 0;


void GameTitle() {
	//^CgBGM
	if (CheckSoundMem(g_sounds.Title) == 0) PlaySoundMem(g_sounds.Title, DX_PLAYTYPE_LOOP);

	//æÊ\¦&®«
	if (Fead.FeadCredit == 0) {
		TitleDisp();
		TitleMove();
		if (Fead.FeadFlg == 0) FeadIn();
	}
	else{
		CrejitDips();
		CrejitMove();
		if (Fead.FeadFlg == 0) FeadIn();
	}


	
}

void TitleDisp() {

	BackStageDisp();
	TitleMAPDisp();

	DrawExtendGraph(220, 110,1100,260, g_img.Title, FALSE);

	DrawFormatString(600, 300, 0xFFFFFF, "Xy[XL[");

	DrawGraph(g_player.px, g_player.py, g_img.gh[g_player.result], TRUE);

	//SetDrawBright(255, 255, 255);

	//DrawFormatString(600, 535, 0xFFFFFF, "I¹i@\µÜ¹ñj");
	//g_gameScene = GAME_SELECT;
}
void TitleMove() {
	int MenuY;

	if (g_Select.CursorFlg == 1) MenuNo = 0, g_Select.CursorFlg = 0;

	//è
	if (MenuNo == 0) {
		if (g_KeyFlg & PAD_INPUT_M || g_KeyFlg & PAD_INPUT_2) {
			DrawGraph(576, 448, g_img.T_kanzi[1], FALSE);//J
			ScreenFlip();
			WaitTimer(2000);
			Fead.InfoStg = 1;
			Fead.FeadCredit = 0;
			FeadOut();
			if (CheckHitKey(KEY_INPUT_SPACE) == 1)
				g_KeyFlg = 0;
		}
		DrawGraph(128, 512, g_img.T_kanzi[1], FALSE);
	}
	//¦^
	if (MenuNo == 1) {
		if (g_KeyFlg & PAD_INPUT_M || g_KeyFlg & PAD_INPUT_2) {
			DrawGraph(640, 512, g_img.T_kanzi[5], FALSE);//^
			ScreenFlip();
			WaitTimer(2000);
			Fead.FeadCredit = 1;
			Fead.InfoStg = 1;
			FeadOut();
		}
		DrawGraph(128, 512, g_img.T_kanzi[5], FALSE);
	}
	//I¹
	if (MenuNo == 2) {
		if (g_KeyFlg & PAD_INPUT_M || g_KeyFlg & PAD_INPUT_2) {
			DrawGraph(576, 576, g_img.T_kanzi[2], FALSE);//I
			ScreenFlip();
			WaitTimer(200);
			g_gameScene = 99;
		}
		DrawGraph(128, 512, g_img.T_kanzi[2], FALSE);
	}


	//Q[Jn©I¹©AIð
	if (g_KeyFlg & PAD_INPUT_DOWN) if (++MenuNo > 2) MenuNo = 0;
	if (g_KeyFlg & PAD_INPUT_UP) if (--MenuNo < 0) MenuNo = 2;

	//J[\
	MenuY = MenuNo * 75;
	DrawTriangle(540, 450 + MenuY, 560, 465 + MenuY, 540, 480 + MenuY, GetColor(0, 0, 0), TRUE);
}

void CrejitDips() {
	BackStageDisp();
	DrawExtendGraph(192, 64,384,256, g_img.T_kanzi[4], FALSE);
	DrawExtendGraph(896, 64, 1090, 256, g_img.T_kanzi[5], FALSE);

	SetFontSize(64);
	DrawString(320, 320, "BGMñ", 0x000000);
	DrawString(384, 384, "h¤°hl", 0x000000);
	DrawString(320, 448, "SEñ", 0x000000);
	DrawString(384, 512, "h¤°hl", 0x000000);
	DrawString(384, 576, "hOn-Jin`¹l`hl", 0x000000);
	SetFontSize(0);

}

void CrejitMove() {
	if (g_KeyFlg & PAD_INPUT_M || g_KeyFlg & PAD_INPUT_2) {
		Fead.FeadCredit = 2;
		Fead.InfoStg = 1;
		g_Select.CursorFlg = 1;
		FeadOut();
	}
}
