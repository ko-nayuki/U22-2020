#include "DxLib.h"
#include "GamePlay.h"
#include "KeyControl.h"
#include "player.h"
#include "Gimmick.h"
#include "Picture.h"
#include "Map.h"

void GamePlay() {
	PlayDisp();
	PlayMove();
}

void PlayDisp() {
	StageDisp();
	gimmickDisp();
	DrawFormatString(0, 400, 0xFF00FF, "%d", g_player.px / 64);
	DrawFormatString(0, 450, 0xFF00FF, "%d", g_player.py / 64);
}

void PlayMove() {
	gimmickMove();
	if(g_gimmick->moveFlg != true) PlayerMove();
}