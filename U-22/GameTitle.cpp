#include "DxLib.h"
#include "KeyControl.h"
#include "GameScene.h"
#include "GameTitle.h"
#include "Map.h"
#include "player.h"
#include "Picture.h"
#include "yoshitaka.h"
#include "Sounds.h"

static int MenuNo = 0;


void GameTitle() {
	//�^�C�g��BGM
	if (CheckSoundMem(g_sounds.Title) == 0) PlaySoundMem(g_sounds.Title, DX_PLAYTYPE_LOOP);

	//��ʕ\��&����
	if (Fead.FeadCredit == 0) {
		Fead.EndFlg = 0;
		TitleDisp();
		TitleMove();
		if (Fead.FeadFlg == 0) FeadIn();
	}
	else{
		CrejitDips();
		CrejitMove();
		if (Fead.FeadFlg == 0) FeadIn();
	}
}

void TitleDisp() {

	BackStageDisp();
	TitleMAPDisp();

	DrawExtendGraph(220, 110,1100,260, g_img.Title, FALSE);


	//DrawFormatString(600, 300, 0xFFFFFF, "�X�y�[�X�L�[");

	DrawGraph(g_player.px, g_player.py, g_img.gh[0], TRUE);

	//SetDrawBright(255, 255, 255);

	//DrawFormatString(600, 535, 0xFFFFFF, "�I���i�@�\���܂���j");
	//g_gameScene = GAME_SELECT;
}
void TitleMove() {
	int MenuY;

	if (g_Select.CursorFlg == 1) MenuNo = 0, g_Select.CursorFlg = 0;

	//�����\���i�t�F�[�h�A�E�g�ŏ�����悤�Ɂj
	DrawGraph(640, 448, g_img.T_kanzi[0], FALSE);
	DrawGraph(578, 512, g_img.T_kanzi[4], FALSE);
	DrawGraph(640, 576, g_img.T_kanzi[3], FALSE);

	//����
	if (MenuNo == 0) {
		if (g_KeyFlg & PAD_INPUT_M || g_KeyFlg & PAD_INPUT_2) {
			DrawGraph(576, 448, g_img.T_kanzi[1], FALSE);//�J
			PlaySoundMem(g_sounds.SenTaku, DX_PLAYTYPE_BACK, TRUE);
			ScreenFlip();
			WaitTimer(1000);
			Fead.InfoStg = 1;
			Fead.FeadCredit = 0;
			FeadOut();
		}
		DrawGraph(128, 512, g_img.T_kanzi[1], FALSE);
	}
	//���^
	if (MenuNo == 1) {
		if (g_KeyFlg & PAD_INPUT_M || g_KeyFlg & PAD_INPUT_2) {
			DrawGraph(640, 512, g_img.T_kanzi[5], FALSE);//�^
			PlaySoundMem(g_sounds.Select, DX_PLAYTYPE_BACK, TRUE);
			ScreenFlip();
			WaitTimer(1000);
			Fead.FeadCredit = 1;
			Fead.InfoStg = 1;
			FeadOut();
		}
		DrawGraph(128, 512, g_img.T_kanzi[5], FALSE);
	}
	//�I��
	if (MenuNo == 2) {
		if (g_KeyFlg & PAD_INPUT_M || g_KeyFlg & PAD_INPUT_2) {
			DrawGraph(576, 576, g_img.T_kanzi[2], FALSE);//�I
			PlaySoundMem(g_sounds.Select, DX_PLAYTYPE_BACK, TRUE);
			ScreenFlip();
			WaitTimer(200);
			g_gameScene = 99;
		}
		DrawGraph(128, 512, g_img.T_kanzi[2], FALSE);
	}


	//�Q�[���J�n���I�����A�I��
	if (g_KeyFlg & PAD_INPUT_DOWN)if (++MenuNo > 2) MenuNo = 0;
	if (g_KeyFlg & PAD_INPUT_UP)if (--MenuNo < 0) MenuNo = 2;

	if (g_KeyFlg & PAD_INPUT_DOWN)PlaySoundMem(g_sounds.SenTaku, DX_PLAYTYPE_BACK, TRUE);
	if (g_KeyFlg & PAD_INPUT_UP)PlaySoundMem(g_sounds.SenTaku, DX_PLAYTYPE_BACK, TRUE);

	//�J�[�\��
	MenuY = MenuNo * 75;
	DrawTriangle(540, 450 + MenuY, 560, 465 + MenuY, 540, 480 + MenuY, GetColor(255, 0, 0), TRUE);
	DrawGraph(480, 432 + MenuY, g_img.Button, TRUE);
}

void CrejitDips() {
	BackStageDisp();
	DrawExtendGraph(192, 64,384,256, g_img.T_kanzi[4], FALSE);
	DrawExtendGraph(896, 64, 1090, 256, g_img.T_kanzi[5], FALSE);

	SetFontSize(64);
	DrawString(320, 300, "BGM��", 0x000000);
	DrawString(384, 364, "�h�������h�l", 0x000000);
	DrawString(320, 428, "SE��", 0x000000);
	DrawString(384, 492, "�h�������h�l", 0x000000);
	DrawString(384, 556, "�hOn-Jin�`���l�`�h�l", 0x000000);
	DrawString(320, 620, "�C���X�g��", 0x000000);
	DrawString(384, 684, "�hAC�C���X�g�h�l", 0x000000);
	SetFontSize(0);

}

void CrejitMove() {
	if (g_KeyFlg & PAD_INPUT_M || g_KeyFlg & PAD_INPUT_2) {
		PlaySoundMem(g_sounds.Select, DX_PLAYTYPE_BACK, TRUE);
		Fead.FeadCredit = 2;
		Fead.InfoStg = 1;
		Fead.EndFlg = 0;
		g_Select.CursorFlg = 1;
		FeadOut();
	}
}
