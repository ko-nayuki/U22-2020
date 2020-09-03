#include "DxLib.h"
#include "UI.h"
#include "player.h"
#include "Map.h"
#include "Picture.h"
#include "KeyControl.h"
#include "Sounds.h"
#include "yoshitaka.h"//fead

const char data[] = __DATE__;
const char time[] = __TIME__;

void build_Time() {
	/*
	static int month = 0;	//月

	switch (data[0]) {

		case 'J':
			if (data[2] == 'a') month = 1;
			if (data[2] == 'u') {
				if (data[3] == 'n') month = 6;
				if (data[3] == 'l') month = 7;
			}
			break;
		case 'F': month = 2; break;
		case 'M': 
			if (data[2] == 'r') month = 2;
			if (data[2] == 'y') month = 5;
			break;
		case 'A':
			if (data[2] == 'r') month = 4;
			if (data[2] == 'g') month = 8;
			break;
		case 'S': month = 9; break;
		case 'O': month = 10; break;
		case 'N': month = 11; break;
		case 'D': month = 12; break;
	}
	*/
	SetFontSize(18);
    DrawFormatString(1150, 10, 0x000000, "最終ビルド日時\n %c%c%c%c %c%c%c %c%c\n  %s",
        data[7], data[8], data[9], data[10],
        data[0], data[1], data[2],
        data[4], data[5],
        time);
}

void player_Life() {

	static float effect = 0;

	if (effect > 255 / ((4 - g_player.life) * 5)) effect = 0;
	else effect += 0.5;

	//HP表示
	DrawGraph(25,675, g_img.hp, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 - effect * 5);
	DrawModiGraph((25) - effect, (675) - effect,
		(25 + 64) + effect, (675) - effect,
		(25 + 64) + effect, ((675 + 64)) + effect,
		(25) - effect, ((675 + 64)) + effect,
		g_img.hp, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	SetFontSize(45);
	DrawFormatString(45, 690, 0xffffff, "%d", g_player.life);
	SetFontSize(16);

}

void retry_Button() {

	static float Anime = 255;
	static bool AnimeFlg = false;
	static int control_time = 0;

	//リトライボタン
	DrawExtendGraph(1230 - Anime, 650, 1280 - Anime, 700, g_img.RetryButon, TRUE);
	if (AnimeFlg == true) {
		if (Anime <= 0) AnimeFlg = false;
		else Anime -= 2;
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, Anime);
	} else {
		if (control_time++ > 400) {
			if (Anime < 255) Anime++;
		}
	}
	DrawGraph(1290 - Anime, 640, g_img.RetryText, FALSE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	if ((g_NowKey & PAD_INPUT_LEFT || key[KEY_INPUT_LEFT] == 1) ||
		(g_NowKey & PAD_INPUT_RIGHT || key[KEY_INPUT_RIGHT] == 1)) {//playerが操作されたら
		AnimeFlg = true;
		control_time = 0;
	}

	if (/*g_KeyFlg & PAD_INPUT_2 ||*/ g_KeyFlg & PAD_INPUT_X) {//コントローラを基準にしています。デバッグ時はコメント化なりしてください。コントローラはY
		Fead.InfoStg = 3;
		Fead.OverFlg = 0;
		FeadOut();
	}

	//セレクトに戻るボタン
	DrawExtendGraph(1230 - Anime, 710, 1280 - Anime, 760, g_img.ReturnButton, TRUE);
	if (AnimeFlg == true) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, Anime);
	}
	else {
	}
	DrawGraph(1290 - Anime, 705, g_img.ReturnText, FALSE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	if ((g_NowKey & PAD_INPUT_LEFT || key[KEY_INPUT_LEFT] == 1) ||
		(g_NowKey & PAD_INPUT_RIGHT || key[KEY_INPUT_RIGHT] == 1)) {//playerが操作されたら
		AnimeFlg = true;
		control_time = 0;
	}

	if (/*g_KeyFlg & PAD_INPUT_2 ||*/ g_KeyFlg & PAD_INPUT_C) {//コントローラを基準にしています。デバッグ時はコメント化なりしてください。コントローラはX
		Fead.InfoStg = 3;
		Fead.OverFlg = 1;
		FeadOut();
	}
}

void item_Box() {

	static bool L_Flg = false;
	static bool R_Flg = false;
	static int delay = 5;

	static float ItemAnime = 0;

	if (ItemAnime < 7.5) ItemAnime += 0.5F;

	for (int i = 0; i < ITEM_MAX; i++) {
		if (i != g_player.itemSelect) {
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
			DrawGraph(128 + (CHIPSIZE + 24) * i, CHIPSIZE * 10 + 80, g_img.itemBox, TRUE);
			if (g_player.item[i] != 0) {
				DrawGraph(128 + (CHIPSIZE + 24) * i, CHIPSIZE * 10 + 80, g_img.kanzi[g_player.item[i] - 1], TRUE);
			}
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		}
		else {
			DrawExtendGraph(104 + (CHIPSIZE + 24) * i, 750, 134 + (CHIPSIZE + 24) * i, 770, g_img.Triger[1], FALSE);//L
			DrawExtendGraph(184 + (CHIPSIZE + 24) * i, 750, 214 + (CHIPSIZE + 24) * i, 770, g_img.Triger[0], FALSE);//R

			SetDrawBright(255, 0, 0);
			//DrawGraph(96 + (CHIPSIZE + 32) * i, CHIPSIZE * 10 + 32, g_img.itemBox, TRUE);
			DrawRotaGraph(160 + (CHIPSIZE + 24) * i, (CHIPSIZE * 10 + 64) + (ItemAnime * 3), 1, -(ItemAnime / 3.14), g_img.itemBox, TRUE);
			SetDrawBright(255, 255, 255);
			if (g_player.item[i] != 0) {
				DrawGraph(128 + (CHIPSIZE + 24) * i, (CHIPSIZE * 10 + 32) + (ItemAnime * 3), g_img.kanzi[g_player.item[i] - 1], TRUE);
			}
		}
	}

	if (g_KeyFlg & PAD_INPUT_Z) {//コントローラを基準にしています。デバッグ時はコメント化なりしてください。コントローラはトリガーR
		if (L_Flg == false && R_Flg == false) R_Flg = true;
	}
	if (g_KeyFlg & PAD_INPUT_5 /*|| g_KeyFlg & PAD_INPUT_X*/) {//コントローラを基準にしています。デバッグ時はコメント化なりしてください。コントローラはトリガーL
		if (L_Flg == false && R_Flg == false) L_Flg = true;
	}

	//L・Rの入力を遅延
	if (L_Flg == true) {
		if (delay-- < 0) {
			PlaySoundMem(g_sounds.SenTaku, DX_PLAYTYPE_BACK, TRUE);
			if (--g_player.itemSelect < 0) g_player.itemSelect = ITEM_MAX - 1;
			ItemAnime = 0;
			L_Flg = false;
			delay = 5;
		}
	}
	if (R_Flg == true) {
		if (delay-- < 0) {
			PlaySoundMem(g_sounds.SenTaku, DX_PLAYTYPE_BACK, TRUE);
			if (++g_player.itemSelect > ITEM_MAX - 1) g_player.itemSelect = 0;
			ItemAnime = 0;
			R_Flg = false;
			delay = 5;
		}
	}
}