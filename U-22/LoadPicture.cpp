#include "DxLib.h"
#include "Picture.h"

//画像をロードする

int LoadPicture(){
	if (LoadDivGraph("images/sample4.bmp", 3, 3, 1, 64, 64, g_img.MAP) == -1) return -1;					//画像チップ
	//if((LoadDivGraph("images/Player.png", 9, 3, 3, 64, 64, g_img.gh)) == -1) return -1;							//プレイヤー変数
	if ((LoadDivGraph("images/Door.png", 3, 3, 3, 64, 64, g_img.door)) == -1) return -1;							//ドア画像変数
	if ((g_img.spring[0] = LoadGraph("images/Bane.png")) == -1) return -1;
	if ((g_img.spring[1] = LoadGraph("images/Bane2.png")) == -1)return -1;
	if ((g_img.spring[2] = LoadGraph("images/Bane3.png")) == -1)return -1;
	//if ((LoadDivGraph("images/book.png", 1, 1, 1, 64, 64, g_img.book)) == -1)return -1;	 //本画像変数
	if ((g_img.MAP[3] = LoadGraph("images/book.png")) == -1) return -1;						//プレイヤー変数
	if ((LoadDivGraph("images/bookshelf.png", 4, 2, 2, 64, 64, g_img.bookshelf)) == -1) return -1;
	if ((LoadDivGraph("images/Player2.png", 6, 3, 2, 64, 64, g_img.gh)) == -1) return -1;		//プレイヤー変数
	//ギミック漢字
	if ((g_img.kanzi[0] = LoadGraph("images/maruzyo.png")) == -1) return -1;
	if ((g_img.kanzi[1] = LoadGraph("images/maruge.png")) == -1) return -1;
	if ((g_img.kanzi[2] = LoadGraph("images/maruchikara.png")) == -1) return -1;
	if ((g_img.kanzi[3] = LoadGraph("images/maruha.png")) == -1) return -1;
	if ((g_img.kanzi[4] = LoadGraph("images/marukesi.png")) == -1) return -1;
	if ((g_img.kanzi[5] = LoadGraph("images/marudou.png")) == -1) return -1;
	if ((g_img.kanzi[6] = LoadGraph("images/marubaku.png")) == -1) return -1;
	//タイトル漢字
	if ((g_img.T_kanzi[0] = LoadGraph("images/title_start01.png")) == -1) return -1;
	if ((g_img.T_kanzi[1] = LoadGraph("images/title_start02.png")) == -1) return -1;
	if ((g_img.T_kanzi[2] = LoadGraph("images/title_end01.png")) == -1) return -1;
	if ((g_img.T_kanzi[3] = LoadGraph("images/title_end02.png")) == -1) return -1;

	if ((g_img.itemBox = LoadGraph("images/itembox.png")) == -1) return -1;
	if (LoadDivGraph("images/smoke.png", 8, 8, 1, 64, 64, g_img.smoke) == -1) return -1;
	if (LoadDivGraph("images/marubatu.png", 2, 2, 1, 64, 64, g_img.marubatu) == -1) return -1;
	if (LoadDivGraph("images/gimmick_kanji.png", 5, 5, 1, 64, 64, g_img.gimKanzi) == -1) return -1;
	if (LoadDivGraph("images/wolf.png", 7, 7, 1, 64, 128, g_img.wolf) == -1) return -1;				//boss1
	if (LoadDivGraph("images/BossThief.png", 24, 8, 3, 64, 128, g_img.thief) == -1) return -1;		//boss2
	if ((g_img.Cauldron = LoadGraph("images/Cauldron.png")) == -1) return -1;
	return 0;
}