#include "DxLib.h"
#include "GamePlay.h"
#include "KeyControl.h"
#include "player.h"


int i;
int x = 0;
int x2 =600;
int y = 500;
int y2 = 600;
int x3 = 0;
bool Flg = FALSE;



void GamePlay() {
	PlayDisp();
	PlayMove();
}

void PlayDisp() {
	DrawBox(500, 600, 600, 700, 0xFF0000, true);
}

void PlayMove() {
	PlayerMove();
	if (g_KeyFlg & KEY_INPUT_Z) Flg = TRUE;
	if (Flg == TRUE) x3 += 5;
	if (x3 > 500) Flg = TRUE, x = 0;
	if (Flg == TRUE)DrawBox(500 + x3, 500, 550 + x3, 550, 0xFFFFFF, TRUE);
}