//画像の変数とか

#pragma once

int LoadPicture();

struct image {
	int MAP[5];			//画像が入っている数値
	int gh[9];			//player
	int door[4];		//エレベータ
	int spring[3];		//ジャンプ台
	int bookshelf[4];	//本棚
	int smoke[8];		//煙
	int kanzi[7];		//漢字
	int T_kanzi[4];		//タイトル用漢字
	int marubatu[2];
	int gimKanzi[5];
	int itemBox;
	int wolf[7];		//boss1
	int thief[24];		//boss2
	int Cauldron;		//大釜
};

extern image g_img;
