#include "DxLib.h"
#include "Picture.h"

//画像をロードする

int LoadPicture(){
	if (LoadDivGraph("images/sample3.bmp", 3, 3, 1, 64, 64, g_img.sample) == -1) return -1;					//画像チップ
	if((LoadDivGraph("images/Player.png", 9, 3, 3, 64, 64, g_img.gh)) == -1) return -1;							//プレイヤー変数
	if ((LoadDivGraph("images/Door.png", 3, 3, 3, 64, 64, g_img.door)) == -1) return -1;							//ドア画像変数
	//if ((LoadDivGraph("images/book.png", 1, 1, 1, 64, 64, g_img.book)) == -1)return -1;	 //本画像変数
	if ((g_img.sample[3] = LoadGraph("images/book.png")) == -1) return -1;						//プレイヤー変数
	if ((LoadDivGraph("images/bookshelf.png", 4, 2, 2, 64, 64, g_img.bookshelf)) == -1) return -1;
	if ((LoadDivGraph("images/Player2.png", 6, 3, 2, 64, 64, g_img.gh)) == -1) return -1;						//プレイヤー変数
	return 0;
}