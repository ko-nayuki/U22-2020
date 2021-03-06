#include "DxLib.h"
#include "GameScene.h"
#include "GameOver.h"
#include "Map.h"
#include "Gimmick.h"
#include "Picture.h"
#include "Sounds.h"
#include "KeyControl.h"
#include "yoshitaka.h"
#include "enemy.h"
#include "Boss.h"

void GameOver() {
	GameOverDisp();
	GameOverMove();
}

void GameOverDisp() {
	BackStageDisp();
	gimmickDisp();
	StageDisp();

	DrawGraph(180, 100, g_img.GameOver, FALSE);

	DrawGraph(280, 420, g_img.OverText[1], FALSE);
	DrawGraph(280, 570, g_img.OverText[0], FALSE);



}

void GameOverMove() {
	static int OverMenu;
	int OverY;

	if (g_Select.CursorFlg == 1) OverMenu = 0, g_Select.CursorFlg = 0;

	//決定
	if (OverMenu == 0) {
		if (g_KeyFlg & PAD_INPUT_M || g_KeyFlg & PAD_INPUT_2) {
			Fead.InfoStg = 5;
			Fead.OverFlg = 0;
			FeadOut();

			//g_gameScene = GAME_PLAY;
			if (CheckHitKey(KEY_INPUT_SPACE) == 1)
				g_KeyFlg = 0;
		}
	}
	//終了
	if (OverMenu == 1) {
		if (g_KeyFlg & PAD_INPUT_M || g_KeyFlg & PAD_INPUT_2) {
			Fead.InfoStg = 5;
			Fead.OverFlg = 1;
			FeadOut();
			//g_gameScene = GAME_TITLE;
		}
	}

	//ゲーム開始か終了か、選択
	if (g_KeyFlg & PAD_INPUT_DOWN) if (++OverMenu > 1) OverMenu = 0;
	if (g_KeyFlg & PAD_INPUT_UP) if (--OverMenu < 0) OverMenu = 1;

	//カーソル
	OverY = OverMenu * 150;
	DrawTriangle(240, 445 + OverY, 260, 460 + OverY, 240, 475 + OverY, GetColor(0, 0, 0), TRUE);
}