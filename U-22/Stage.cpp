//ステージ生成プログラム

#include "DxLib.h"
#include "Map.h"
#include "Picture.h"

int g_Stage = 0;
//StageInfo Stage;

void StageInit() {

	//ステージ生成
	for (int i = 0; i < STAGE_HEIGHT; i++) {
		for (int j = 0; j < STAGE_WIDTH; j++) {
			if (g_map.stageData[g_Stage][i][j] != 0 && g_map.stageData[g_Stage][i][j] != 2) {
				g_map.playStage[i][j] = g_map.stageData[g_Stage][i][j];
			}
		}
	}
}

void StageDisp() {
	for (int i = 0; i < STAGE_HEIGHT; i++) {
		for (int j = 0; j < STAGE_WIDTH; j++) {
			DrawGraph(j * CHIPSIZE, i * CHIPSIZE, g_img.sample[g_map.playStage[i][j]], TRUE);
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
