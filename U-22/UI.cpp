#include "DxLib.h"
#include "UI.h"
#include "player.h"
#include "Map.h"
#include "Picture.h"
#include "KeyControl.h"
#include "Sounds.h"

const char data[] = __DATE__;
const char time[] = __TIME__;

void build_Time() {
	/*
	static int month = 0;	//åé

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
    DrawFormatString(1150, 10, 0x000000, "ç≈èIÉrÉãÉhì˙éû\n %c%c%c%c %c%c%c %c%c\n  %s",
        data[7], data[8], data[9], data[10],
        data[0], data[1], data[2],
        data[4], data[5],
        time);
}

void item_Box() {

	static float ItemAnime = 0;

	if (ItemAnime < 7.5) ItemAnime += 0.5F;

	for (int i = 0; i < ITEM_MAX; i++) {
		if (i != g_player.itemSelect) {
			DrawGraph(96 + (CHIPSIZE + 32) * i, CHIPSIZE * 10 + 32, g_img.itemBox, TRUE);
		}
		else {
			DrawExtendGraph(70 + (CHIPSIZE + 32) * i, 655, 100 + (CHIPSIZE + 32) * i, 675, g_img.Triger[0], FALSE);
			DrawExtendGraph(150 + (CHIPSIZE + 32) * i, 655, 180 + (CHIPSIZE + 32) * i, 675, g_img.Triger[1], FALSE);

			SetDrawBright(255, 0, 0);
			//DrawGraph(96 + (CHIPSIZE + 32) * i, CHIPSIZE * 10 + 32, g_img.itemBox, TRUE);
			DrawRotaGraph(128 + (CHIPSIZE + 32) * i, CHIPSIZE * 10 + 64, 1, -(ItemAnime / 3.14), g_img.itemBox, TRUE);
			SetDrawBright(255, 255, 255);
		}
		if (g_player.item[i] != 0) {
			DrawGraph(96 + (CHIPSIZE + 32) * i, CHIPSIZE * 10 + 32, g_img.kanzi[g_player.item[i] - 1], TRUE);
		}
	}

	if (g_KeyFlg & PAD_INPUT_Z) {
		PlaySoundMem(g_sounds.SenTaku, DX_PLAYTYPE_BACK, TRUE);
		if (++g_player.itemSelect > ITEM_MAX - 1) g_player.itemSelect = 0;
		ItemAnime = 0;
	}
	if (g_KeyFlg & PAD_INPUT_5 || g_KeyFlg & PAD_INPUT_X) {
		PlaySoundMem(g_sounds.SenTaku, DX_PLAYTYPE_BACK, TRUE);
		if (--g_player.itemSelect < 0) g_player.itemSelect = ITEM_MAX - 1;
		ItemAnime = 0;
	}

}