#include "DxLib.h"
#include "GameScene.h"
#include "GameOver.h"
#include "Map.h"
#include "Gimmick.h"


void GameOver() {
	GameOverDisp();
	GameOverMove();
}

void GameOverDisp() {
	BackStageDisp();
	gimmickDisp();
	StageDisp();
}

void GameOverMove() {

}