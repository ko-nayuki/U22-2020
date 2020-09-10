#include "DxLib.h"
#include "KeyControl.h"
#include "GameScene.h"
#include "StageSelect.h"
#include "Map.h"
#include "player.h"
#include "enemy.h"
#include "Gimmick.h"
#include "yoshitaka.h"
#include "Boss.h"
#include "Picture.h"
#include "Sounds.h"


void StageSelect() {
	//PlayerInit();
	SelectDisp();
	SelectMove();
	if (Fead.FeadFlg == 0) FeadIn();
}

void SelectDisp() {
	BackStageDisp();
	DrawExtendGraph(0, 0,1280,768, g_img.Curtain, TRUE);
	DrawExtendGraph(220, 140, 1050, 280, g_img.Title, FALSE);
	SelectMAPDisp();
	SelectBook();
	//DrawFormatString(600, 300, 0x000000, "SPACE");
	//DrawFormatString(0, 650, 0x000000, "%d", g_map.select);
	//DrawFormatString(0, 670, 0x000000, "%d", g_Select.Key);

}
void SelectMove() {

	//if (g_map.playStage[int(g_player.py /CHIPSIZE) + 1][int(g_player.px / CHIPSIZE)] != 1) {
	//	g_player.py += 16;
	//}
	//if (g_Select.PlayerStay == 1)g_player.px = 1* CHIPSIZE,g_player.py = 9*CHIPSIZE,g_Select.PlayerStay = 0;

	PlayerMove();

	//DrawBox(g_Select.stage3x, 0, g_Select.stage3x + 128, g_Select.stage1y, 0xFFFFFF, FALSE);

	//if (g_Select.stage1x < g_player.px + 64 && g_Select.stage1x + 128 > g_player.px) {
	//	DrawString(0, 650, "ステージ１", 0x000000);
	//}
	//if (g_Select.stage2x < g_player.px + 64 && g_Select.stage2x + 128 > g_player.px) {
	//	DrawString(0, 650, "ステージ２", 0x000000);
	//}
	//if (g_Select.stage3x < g_player.px + 64 && g_Select.stage3x + 128 > g_player.px) {
	//	DrawString(0, 650, "ステージ３", 0x000000);
	//}
	//if (g_Select.stage4x < g_player.px + 64 && g_Select.stage4x + 128 > g_player.px) {
	//	DrawString(0, 650, "ステージ4", 0x000000);
	//}

	/*if (g_KeyFlg & PAD_INPUT_RIGHT) {
		if (++g_map.select > STAGE - 1) g_map.select = 0;
	}
	if (g_KeyFlg & PAD_INPUT_LEFT) {
		if (--g_map.select < 0) g_map.select = STAGE - 1;
	}*/

	if (g_KeyFlg & PAD_INPUT_M || g_KeyFlg & PAD_INPUT_2) {
		/*Fead.InfoStg = 2;
		FeadOut();
		gimmickInit();
		StageInit();
		EnemyInit();
		bossInit();
		for (int i = 0; i < ITEM_MAX; i++) {
			g_player.item[i] = K_NO;
		}
		g_player.itemNo = 0;

		g_gameScene = GAME_PLAY;*/
			if (g_Select.stage1x < g_player.px + 64 && g_Select.stage1x + 128 > g_player.px) {
				PlaySoundMem(g_sounds.Select, DX_PLAYTYPE_BACK, TRUE);
				g_map.select = 0;
				g_Select.Checkkey = 0;
				Fead.InfoStg = 2;
				FeadOut();
				gimmickInit();
				PlayerInit();
				StageInit();
				EnemyInit();
				bossInit();
				//g_gameScene = GAME_PLAY;
			}
			if ((g_Select.stage2x < g_player.px + 64 && g_Select.stage2x + 128 > g_player.px) && g_Select.Key >= 1) {
				PlaySoundMem(g_sounds.Select, DX_PLAYTYPE_BACK, TRUE);
				g_map.select = 3;
				g_Select.Checkkey = 1;
				Fead.InfoStg = 2;
				FeadOut();
				gimmickInit();
				PlayerInit();
				StageInit();
				EnemyInit();
				bossInit();
			}
			if ((g_Select.stage3x < g_player.px + 64 && g_Select.stage3x + 128 > g_player.px) && g_Select.Key >= 2) {
				PlaySoundMem(g_sounds.Select, DX_PLAYTYPE_BACK, TRUE);
				g_map.select = 6;
				g_Select.Checkkey = 2;
				Fead.InfoStg = 2;
				FeadOut();
				gimmickInit();
				PlayerInit();
				StageInit();
				EnemyInit();
				bossInit();
			}
			if ((g_Select.stage4x < g_player.px + 64 && g_Select.stage4x + 128 > g_player.px) && g_Select.Key >= 3) {
				PlaySoundMem(g_sounds.Select, DX_PLAYTYPE_BACK, TRUE);
				g_map.select = 9;
				g_Select.Checkkey = 3;
				Fead.InfoStg = 2;
				FeadOut();
				gimmickInit();
				PlayerInit();
				StageInit();
				EnemyInit();
				bossInit();
			}
	}
}

void SelectBook() {
	static bool text_Flg = true;//テキストをふわふわさせる
	static float text_Y = 0.0;

	static float animation = 0.0;//本のアニメーション(チュートリアル)
	static float animation2 = 0.0;//本のアニメーション(W2)
	static float animation3 = 0.0;//本のアニメーション(W3)
	static float animation4 = 0.0;//本のアニメーション(W4)
	static bool animeFlg[3] = { false, false, false };


	//g_Select.Key = 4;

	//W1
	if (g_Select.stage1x < g_player.px + 64 && g_Select.stage1x + 128 > g_player.px) {
		DrawGraph(3 * CHIPSIZE, 8 * CHIPSIZE, g_img.goal[int(animation)], TRUE);
		if (animation < 4.0) animation += 0.1F;
		else animation = 0.0;
	}
	else {
		DrawGraph(3 * CHIPSIZE, 8 * CHIPSIZE, g_img.goal[0], TRUE);
	}

	//W2
	if (g_Select.stage2x < g_player.px + 64 && g_Select.stage2x + 128 > g_player.px && g_Select.Key >= 1) {
		if (animeFlg[0] == true) {
			if (animation2 < 5.0) animation2 += 0.1F;
			else animation2 = 0.0;
			DrawGraph(8 * CHIPSIZE, 8 * CHIPSIZE, g_img.BookAnime[int(animation2)], TRUE);
		}
		else {
			if (animation2 < 5.0) animation2 += 0.2F;
			else animeFlg[0] = true;
			DrawGraph(8 * CHIPSIZE, 8 * CHIPSIZE, g_img.world_2book[int(animation2)], TRUE);
			//DrawExtendGraph(8 * CHIPSIZE + 48, 8 * CHIPSIZE, 12 * CHIPSIZE - 48, 10 * CHIPSIZE, g_img.BookAnime[int(animation2)], TRUE);
		}
	}
	else {
		if (animeFlg[0] == true) {
			DrawGraph(8 * CHIPSIZE, 8 * CHIPSIZE, g_img.world_2book[int(animation2)], TRUE);
			if (animation2 > 0.1) animation2 -= 0.2F;
			else animation2 = 0.0, animeFlg[0] = false;
		}
		else {
			DrawGraph(9 * CHIPSIZE, 8 * CHIPSIZE, g_img.SelectBook[0], TRUE);
		}
	}

	//W3
	if (g_Select.stage3x < g_player.px + 64 && g_Select.stage3x + 128 > g_player.px && g_Select.Key >= 2) {
		if (animeFlg[1] == true) {
			if (animation3 < 5.0) animation3 += 0.1F;
			else animation3 = 0.0;
			DrawGraph(11 * CHIPSIZE, 8 * CHIPSIZE, g_img.BookAnime[int(animation3)], TRUE);
		}
		else {
			if (animation3 < 5.0) animation3 += 0.2F;
			else animeFlg[1] = true;
			DrawGraph(11 * CHIPSIZE, 8 * CHIPSIZE, g_img.world_3book[int(animation3)], TRUE);
			//DrawExtendGraph(11 * CHIPSIZE + 48, 8 * CHIPSIZE, 15 * CHIPSIZE - 48, 10 * CHIPSIZE, g_img.BookAnime[int(animation3)], TRUE);

		}
	}
	else {
		if (animeFlg[1] == true) {
			DrawGraph(11 * CHIPSIZE, 8 * CHIPSIZE, g_img.world_3book[int(animation3)], TRUE);
			if (animation3 > 0.1) animation3 -= 0.2F;
			else animation3 = 0.0, animeFlg[1] = false;
		}
		else {
			DrawGraph(12 * CHIPSIZE, 8 * CHIPSIZE, g_img.SelectBook[1], TRUE);
		}
	}

	//W4
	if (g_Select.stage4x < g_player.px + 64 && g_Select.stage4x + 128 > g_player.px && g_Select.Key >= 3) {
		if (animeFlg[2] == true) {
			if (animation4 < 5.0) animation4 += 0.1F;
			else animation4 = 0.0;
			DrawGraph(14 * CHIPSIZE, 8 * CHIPSIZE, g_img.BookAnime[int(animation4)], TRUE);
		}
		else {
			if (animation4 < 5.0) animation4 += 0.2F;
			else animeFlg[2] = true;
			DrawGraph(14 * CHIPSIZE, 8 * CHIPSIZE, g_img.world_4book[int(animation4)], TRUE);
			//DrawExtendGraph(14 * CHIPSIZE + 48, 8 * CHIPSIZE, 18 * CHIPSIZE - 48, 10 * CHIPSIZE, g_img.BookAnime[int(animation4)], TRUE);
		}
	}
	else {
		if (animeFlg[2] == true) {
			DrawGraph(14 * CHIPSIZE, 8 * CHIPSIZE, g_img.world_4book[int(animation4)], TRUE);
			if (animation4 > 0.1) animation4 -= 0.2F;
			else animation4 = 0.0, animeFlg[2] = false;
		}
		else {
			DrawGraph(15 * CHIPSIZE, 8 * CHIPSIZE, g_img.SelectBook[2], TRUE);
		}
	}

	//text
	if (text_Flg == true) {
		text_Y += 0.1F;
		if (text_Y >= 1.5F) text_Flg = false;
	}
	if (text_Flg == false) {
		text_Y -= 0.1F;
		if (text_Y <= -1.5F) text_Flg = true;
	}

	SetFontSize(24);
	if (g_Select.Key != 0 && g_Select.Key <= 3) {
		DrawString((6 + (3 * g_Select.Key)) * CHIPSIZE + 38, 480 + text_Y, "NEXT", 0x444444);
	}
	else if (g_Select.Key == 0) {
		DrawString(3 * CHIPSIZE + 30, 480 + text_Y, "START", 0x444444);
	}

	if (g_Select.Key > 0) {
		DrawString(3 * CHIPSIZE + 30, 480, "CLEAR", 0x00FFFF);
	}
	if (g_Select.Key > 1) {
		DrawString(9 * CHIPSIZE + 30, 480, "CLEAR", 0x00FFFF);
	}
	if (g_Select.Key > 2) {
		DrawString(12 * CHIPSIZE + 30, 480, "CLEAR", 0x00FFFF);
	}
	if (g_Select.Key > 3) {
		DrawString(15 * CHIPSIZE + 30, 480, "CLEAR", 0x00FFFF);
	}
	SetFontSize(16);
}
