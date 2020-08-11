#include "DxLib.h"
#include "KeyControl.h"
#include "GameScene.h"
#include "GameTitle.h"
#include "Map.h"
#include "player.h"
#include "Picture.h"
#include "yoshitaka.h"

void GameTitle() {
	TitleDisp();
	TitleMove();
}

void TitleDisp() {
	BackStageDisp();
	TitleMAPDisp();
	PlayerMove();

	DrawFormatString(600, 300, 0xFFFFFF, "Dキー");

	//SetDrawBright(255, 255, 255);

	//DrawFormatString(600, 465, 0xFFFFFF, "開始（仮）");
	//DrawFormatString(600, 535, 0xFFFFFF, "終了（機能しません）");
	//g_gameScene = GAME_SELECT;
}
void TitleMove() {
	static int MenuNo = 0;
	int MenuY;
	
	//決定
	if (MenuNo == 0) {
		DrawGraph(128, 514, g_img.T_kanzi[1], TRUE);
		if (g_KeyFlg & PAD_INPUT_M ) {
			Fead.InfoStg = 1;
			FeadOut();
			if (CheckHitKey(KEY_INPUT_SPACE) == 1) 
				g_KeyFlg = 0;
		}
	}
	//終了
	if (MenuNo == 1) {
		DrawGraph(128, 514, g_img.T_kanzi[3], TRUE);
		if (g_KeyFlg & PAD_INPUT_M) {
			g_gameScene = GAME_SELECT;
		}
	}

	//ゲーム開始か終了か、選択
	if (g_KeyFlg & PAD_INPUT_DOWN) if (++MenuNo > 1) MenuNo = 0;
	if (g_KeyFlg & PAD_INPUT_UP) if (--MenuNo < 0) MenuNo = 1;

	//カーソル
	MenuY = MenuNo * 80;
	DrawTriangle(440, 455 + MenuY, 460, 470 + MenuY, 440, 485 + MenuY, GetColor(255, 0, 0), TRUE);
}
