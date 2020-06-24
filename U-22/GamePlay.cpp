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
}

void PlayMove() {
	PlayerMove();
}