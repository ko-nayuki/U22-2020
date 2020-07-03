//画像の変数とか

#pragma once

int LoadPicture();

struct image {
	int MAP[5];//画像が入っている数値
	int gh[9];  //player
	int door[4]; //エレベータ
	int bookshelf[4];//本棚
	int kanzi[5];//漢字
	int itemBox;
};

extern image g_img;
