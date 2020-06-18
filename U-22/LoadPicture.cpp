#include "DxLib.h"
#include "Picture.h"

//画像をロードする

int LoadPicture(){
	if (LoadDivGraph("images/sample.bmp", 10, 10, 1, 24, 24, g_img.sample) == -1) return -1;					//画像チップ
	if((LoadDivGraph("images/Player.png", 9, 3, 3, 64, 64, g_img.gh)) == -1) return -1;							//プレイヤー変数
	if ((LoadDivGraph("images/Door.png", 3, 3, 3, 64, 64, g_img.door)) == -1) return -1;							//プレイヤー変数

	return 0;
}