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
	int kanzi[6];		//漢字
	int marubatu[2];
	int itemBox;

};

extern image g_img;
