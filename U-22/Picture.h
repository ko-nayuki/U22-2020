//画像の変数とか

#pragma once

int LoadPicture();

struct image {
	int MAP[12];			//画像が入っている数値
	int gh[9];			//player
	int door[4];		//エレベータ
	int spring[3];		//ジャンプ台
	int bookshelf[4];	//本棚
	int smoke[8];		//煙
	int kanzi[7];		//漢字
	int Title;			//タイトル
	int T_kanzi[6];		//タイトル用漢字
	int Button;			//Bボタン
	int goal[5];
	int marubatu[2];
	int gimKanzi[6];
	int Teki[5];        //敵
	int hp;             //player hp
	int itemBox;
	int wolf[9];		//boss1
	int thief[24];		//boss2
	int Colossus[6];    //boss3
	int fire[2];		//炎
	int drop;			//落下看板
	int crack;			//ヒビ入りブロック
	int gear[2];		//回転足場
	int warp;			//ワープ
	int bomb;
	int Cauldron;		//大釜
	int trampoline[2];	//トランポリン
	int wind;

	int BombEff;

	int KanBan[2];		//看板画像

	int stage3;
	int stage4;
	int SelectBook[3];
	int BookAnime[6];
	int world_4book[6];

	int Curtain;		//セレクト画面の幕
	int RetryButon;		//リトライボタン
	int RetryText;		//リトライテキスト
	int ReturnButton;	//セレクトに戻るためのボタン
	int ReturnText;		//セレクトテキスト
	int ClearText;		//クリア文字
	int NextText;		//NEXT文字
	int GameOver;		//オーバー文字
	int OverText[2];	//ゲームオーバーでの選択肢
	int Triger[2];		//トリガー表示
	int End;		//最後の一枚絵
};

extern image g_img;
