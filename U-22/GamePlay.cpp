#include "DxLib.h"
#include "GamePlay.h"
#include  "KeyControl.h"

void GamePlay() {
	PlayDisp();
	PlayMove();
}

void PlayDisp() {
	DrawBox(500, 500, 600, 600, 0xFF0000, TRUE);
}
void PlayMove() {
	if (g_KeyFlg & KEY_INPUT_Z) {
		DrawBox(500, 500,650, 650, 0xFF0000, TRUE);
	}
}