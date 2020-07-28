#include "DxLib.h"
#include "KeyControl.h"
#include "GameScene.h"
#include "GameTitle.h"

void GameTitle() {
	TitleDisp();
	TitleMove();
}

void TitleDisp() {
	DrawFormatString(600, 300, 0xFFFFFF, "SPACE");

	DrawFormatString(600, 465, 0xFFFFFF, "�J�n�i���j");
	DrawFormatString(600, 535, 0xFFFFFF, "�I���i�@�\���܂���j");

	//g_gameScene = GAME_SELECT;
}
void TitleMove() {
	static int MenuNo = 0;
	int MenuY;
	
	//����
	if (key[KEY_INPUT_SPACE] == 1) {
		g_gameScene = GAME_SELECT;
	}

	//�Q�[���J�n���I�����A�I��
	if (g_KeyFlg & PAD_INPUT_DOWN) if (++MenuNo > 1) MenuNo = 0;
	if (g_KeyFlg & PAD_INPUT_UP) if (--MenuNo < 0) MenuNo = 1;

	//�J�[�\��
	MenuY = MenuNo * 80;
	DrawTriangle(440, 455 + MenuY, 460, 470 + MenuY, 440, 485 + MenuY, GetColor(255, 0, 0), TRUE);
}
