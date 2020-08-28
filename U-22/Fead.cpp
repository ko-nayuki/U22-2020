#include "DxLib.h"
#include "yoshitaka.h"
#include "GameScene.h"
#include "Map.h"
#include "player.h"
#include "Picture.h"
#include "StageSelect.h"
#include "GamePlay.h"
#include "Gimmick.h"
#include "GameClear.h"
#include "GameOver.h"
#include "Boss.h"
#include "enemy.h"
#include "GameTitle.h"
#include "Sounds.h"

static int num = 0;


void FeadOut() {
	num = 0;
	Fead.FeadFlg = 0;
	//�t�F�[�h�A�E�g
	while(num<255) {
		SetDrawBright(255 - num, 255 - num, 255 - num);

		//�X�e�[�W�`��
		if (Fead.InfoStg == 1 && Fead.FeadCredit != 2) {
			TitleDisp();
		}
		else {
			CrejitDips();
		}
		//�Z���N�g�X�e�[�W�`��
		if (Fead.InfoStg == 2) {
			SelectDisp();
		}
		//�Q�[���v���C�`��
		if (Fead.InfoStg == 3) {
			PlayDisp();
		}
		//�Q�[���N���A�`��
		if (Fead.InfoStg == 4 && Fead.EndFlg == 0) {
			GameClearDisp();
		}
		//�Q�[���G���h�`��
		if (Fead.InfoStg == 4 && Fead.EndFlg == 1) {
			GameComplete();
		}
		//�Q�[���I�[�o�[�`��
		if (Fead.InfoStg == 5) {
			GameOverDisp();
		}


		num += 2;

		//��ʂ��ĕ\��
		ScreenFlip();
	}

	//FeadIn();
	if (num >= 255 && g_gameScene == GAME_CLEAR && Fead.ClearFlg == 0) {
		if (g_map.select < STAGE - 1) g_map.select++;
	}
	if (Fead.InfoStg == 1 && Fead.FeadCredit == 0) {
		g_gameScene = GAME_SELECT;
		Fead.InfoStg = 2;
		//StopSoundMem(g_sounds.Title);
	}
	else if (Fead.InfoStg == 1 && Fead.FeadCredit == 1) {
		Fead.InfoStg = 5;
	}
	else if (Fead.InfoStg == 1 && Fead.FeadCredit == 2) {
		Fead.InfoStg = 1;
		Fead.FeadCredit = 0;
	}
	else if (Fead.InfoStg == 2) {
		StopSoundMem(g_sounds.Title);
		g_gameScene = GAME_PLAY;
		Fead.InfoStg = 3;
	}
	else if (Fead.InfoStg == 3 && Fead.EndFlg == 1) {
		Fead.InfoStg = 4;
		StopSoundMem(g_sounds.Boss);
		g_gameScene = GAME_CLEAR;
	}
	else if (Fead.InfoStg == 3) {
		Fead.InfoStg = 3;
		gimmickInit();
		StageInit();
		EnemyInit();
		bossInit();
		for (int i = 0; i < ITEM_MAX; i++) {
			g_player.item[i] = K_NO;
		}
		g_player.itemNo = 0;
		PlayerInit();
		g_gameScene = GAME_PLAY;
	}
	else if(Fead.InfoStg == 4 && Fead.ClearFlg == 0) {
		if (g_map.select == 5 || g_map.select == 8 || g_map.select == 11) {
			StopSoundMem(g_sounds.World1);
			StopSoundMem(g_sounds.World2);
			StopSoundMem(g_sounds.World3);
		}
		Fead.InfoStg = 3;
		//g_map.select++;
		g_gameScene = GAME_PLAY;
	}
	else if(Fead.InfoStg == 4 && Fead.ClearFlg == 1)
	{
		if (g_map.select == 2) {
		StopSoundMem(g_sounds.World0);
		}
		else {
		StopSoundMem(g_sounds.Boss);
		}
		Fead.InfoStg = 2;
		g_gameScene = GAME_SELECT;
	}
	else if (Fead.InfoStg == 4 && Fead.ClearFlg == 2)
	{
		Fead.InfoStg = 1;
		StopSoundMem(g_sounds.End);
		g_gameScene = GAME_TITLE;
	}
	else if (Fead.InfoStg == 5 && Fead.OverFlg == 0)
	{
		Fead.InfoStg = 3;
		gimmickInit();
		StageInit();
		EnemyInit();
		bossInit();
		for (int i = 0; i < ITEM_MAX; i++) {
			g_player.item[i] = K_NO;
		}
		g_player.itemNo = 0;
		PlayerInit();
		g_gameScene = GAME_PLAY;
	}
	else if (Fead.InfoStg == 5 && Fead.OverFlg == 1)
	{
		Fead.InfoStg = 1;
		StopSoundMem(g_sounds.World0);
		StopSoundMem(g_sounds.World1);
		StopSoundMem(g_sounds.World2);
		StopSoundMem(g_sounds.World3);
		StopSoundMem(g_sounds.Boss);
		g_gameScene = GAME_TITLE;
	}
	//if (InfoStg == 3) {
	//	g_gameScene = GAME_CLEAR;
	//	//InfoStg = 4;
	//}
}

void FeadIn() {
	num = 0;
	Fead.FeadFlg = 1;
	//�t�F�[�h�C��
	while (num < 255) {
		SetDrawBright(num,num,num);

		//�^�C�g���X�e�[�W�`��
		if (Fead.InfoStg == 1) {
			BackStageDisp();
			TitleMAPDisp();
			PlayerMove();
		}
		//�Z���N�g�X�e�[�W�`��
		if (Fead.InfoStg == 2) {
			if (CheckSoundMem(g_sounds.Title) == 0) PlaySoundMem(g_sounds.Title, DX_PLAYTYPE_LOOP);
			SelectDisp();
		}
		//�Q�[���v���C�`��
		if (Fead.InfoStg == 3) {
			PlayDisp();
			if ((g_map.select + 1) % 3 != 0) {
				if (g_map.select >= 0 && g_map.select <= 2)
					if (CheckSoundMem(g_sounds.World0) == 0) PlaySoundMem(g_sounds.World0, DX_PLAYTYPE_LOOP);
				if (g_map.select >= 3 && g_map.select <= 4)
					if (CheckSoundMem(g_sounds.World1) == 0) PlaySoundMem(g_sounds.World1, DX_PLAYTYPE_LOOP);
				if (g_map.select >= 6 && g_map.select <= 7)
					if (CheckSoundMem(g_sounds.World2) == 0) PlaySoundMem(g_sounds.World2, DX_PLAYTYPE_LOOP);
				if (g_map.select >= 9 && g_map.select <= 10)
					if (CheckSoundMem(g_sounds.World3) == 0) PlaySoundMem(g_sounds.World3, DX_PLAYTYPE_LOOP);
			}
			else if(g_map.select != 2){
				if (CheckSoundMem(g_sounds.Boss) == 0) PlaySoundMem(g_sounds.Boss, DX_PLAYTYPE_LOOP);
			}
		}
		//�G���h
		if (Fead.InfoStg == 4) {
			if (CheckSoundMem(g_sounds.End) == 0) PlaySoundMem(g_sounds.End, DX_PLAYTYPE_LOOP);
			GameComplete();
		}
		//�N���W�b�g
		if (Fead.InfoStg == 5) {
			CrejitDips();
		}
		num += 2;

		//��ʂ��ĕ\��
		ScreenFlip();
	}
}