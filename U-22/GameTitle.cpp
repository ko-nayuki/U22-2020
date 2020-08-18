#include "DxLib.h"
#include "KeyControl.h"
#include "GameScene.h"
#include "GameTitle.h"
#include "Map.h"
#include "player.h"
#include "Picture.h"
#include "yoshitaka.h"

static int MenuNo = 0;
static int Sketch = 0;

void GameTitle() {
	TitleDisp();
	TitleMove();
}

void TitleDisp() {

	BackStageDisp();
	TitleMAPDisp();

	if (Sketch == 0) {
		//決定
		if (MenuNo == 0) {
		}
		//終了
		if (MenuNo == 1) {
		}
	}

	DrawFormatString(600, 300, 0xFFFFFF, "スペースキー");

	DrawGraph(g_player.px, g_player.py, g_img.gh[g_player.result], TRUE);

	//SetDrawBright(255, 255, 255);

	//DrawFormatString(600, 465, 0xFFFFFF, "開始（仮）");
	//DrawFormatString(600, 535, 0xFFFFFF, "終了（機能しません）");
	//g_gameScene = GAME_SELECT;
}
void TitleMove() {
	int MenuY;
	
	//決定
	if (MenuNo == 0) {
		if (g_KeyFlg & PAD_INPUT_M || g_KeyFlg & PAD_INPUT_2) {
			++Sketch;
			DrawGraph(576, 448, g_img.T_kanzi[1], TRUE);//開
			ScreenFlip();
			WaitTimer(2000);
			Fead.InfoStg = 1;
			FeadOut();
			if (CheckHitKey(KEY_INPUT_SPACE) == 1)
				g_KeyFlg = 0;
		}
		if(Sketch == 0)DrawGraph(128, 512, g_img.T_kanzi[1], TRUE);
	}
	//終了
	if (MenuNo == 1) {
		if (g_KeyFlg & PAD_INPUT_M || g_KeyFlg & PAD_INPUT_2) {
			++Sketch;
			DrawGraph(640, 512, g_img.T_kanzi[3], TRUE);//了
			ScreenFlip();
			WaitTimer(200);
			g_gameScene = 99;
		}
		if (Sketch == 0) DrawGraph(128, 512, g_img.T_kanzi[3], TRUE);
	}

	//ゲーム開始か終了か、選択
	if (g_KeyFlg & PAD_INPUT_DOWN) if (++MenuNo > 1) MenuNo = 0;
	if (g_KeyFlg & PAD_INPUT_UP) if (--MenuNo < 0) MenuNo = 1;

	//カーソル
	MenuY = MenuNo * 80;
	DrawTriangle(440, 455 + MenuY, 460, 470 + MenuY, 440, 485 + MenuY, GetColor(255, 0, 0), TRUE);
}
