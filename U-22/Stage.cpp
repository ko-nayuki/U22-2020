//ステージ生成プログラム

#include "DxLib.h"
#include "Map.h"
#include "Picture.h"
#include "Gimmick.h"

int g_Stage = 0;
//StageInfo Stage;

void StageInit() {

	//ステージ読み込み
	for (int i = 0; i < STAGE_HEIGHT; i++) {
		for (int j = 0; j < STAGE_WIDTH; j++) {
			g_map.playStage[i][j] = g_map.stageData[g_Stage][i][j];
			if (g_map.playStage[i][j] == 2) {
				g_gimmick[LIFT].x = j * CHIPSIZE;
				g_gimmick[LIFT].y = i * CHIPSIZE;
			}
		}
	}
}

void StageDisp() {
	//ステージ描画
	for (int i = 0; i < STAGE_HEIGHT; i++) {
		for (int j = 0; j < STAGE_WIDTH; j++) {
			if (g_map.playStage[i][j] != 0 && g_map.playStage[i][j] != 2) {
				DrawGraph(j * CHIPSIZE, i * CHIPSIZE, g_img.sample[g_map.playStage[i][j]], TRUE);
			}
		}
	}

}


//int StageObj(int Objimg) {
//	//オブジェクト判定
//	switch (Objimg)
//	{
//	case 0:		break;
//	case 1:		return g_img.sample[1]; break;
//	case 2:		return g_img.door[0]; break;
//	case 3:		return g_img.sample[3]; break;
//	case 4:		return g_img.sample[4]; break;
//	case 5:		return g_img.sample[5]; break;
//	case 6:		return g_img.sample[6]; break;
//	case 7:		return g_img.sample[7]; break;
//	case 8:		return g_img.sample[8]; break;
//	case 9:		return g_img.sample[9]; break;
//	case 10:    return g_img.book[1]; break;
//	}
//	
//}
