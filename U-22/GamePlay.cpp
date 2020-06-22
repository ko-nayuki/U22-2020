#include "DxLib.h"
#include "GamePlay.h"
#include "KeyControl.h"
#include "player.h"
#include "yoshitaka.h"
#include "Gimmick.h"


int i;
int x = 0;
int x2 =600;
int y = 500;
int y2 = 600;
int x3 = 0;
bool ElFlg = FALSE; //エレベーターを動かすフラグ



void GamePlay() {
	PlayDisp();
	PlayMove();
	
}

void PlayDisp() {
	StageInit();
	
}

void PlayMove() {

	PlayerMove();
	/*
	if (key[KEY_INPUT_Z]) ElFlg = TRUE;
	if (ElFlg == TRUE) x3 += 5;
	if (x3 > 500) ElFlg = TRUE, x = 0;
	if (ElFlg == TRUE)DrawBox(500 + x3, 500, 550 + x3, 550, 0xFFFFFF, TRUE);
	*/
	}