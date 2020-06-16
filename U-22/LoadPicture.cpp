#include "DxLib.h"
#include "Picture.h"

int LoadPicture(){
	//if ((g_img.sample = LoadGraph("images/sample.bmp")) == -1) return -1;		//マップチップ用画像
	if((LoadDivGraph("images/Player.png", 9, 3, 3, 64, 64, g_img.gh)) == -1) return -1;							//プレイヤー変数

	return 0;
}