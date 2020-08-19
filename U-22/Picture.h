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
	int Teki[4];
	int itemBox;
	int wolf[7];		//boss1
	int thief[24];		//boss2
	int Cauldron;		//大釜
	int ClearText;		//クリア文字
	int NextText;		//NEXT文字
	int GameOver;		//オーバー文字
	int OverText[2];	//ゲームオーバーでの選択肢
	int Triger[2];		//トリガー表示
};

extern image g_img;
