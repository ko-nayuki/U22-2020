//ステージ生成プログラム

#include "DxLib.h"
#include "yoshitaka.h"
#include "Map.h"
#include "Picture.h"

int g_Stage = 0;
StageInfo Stage;

void StageInit() {
	for (int i = 0; i < STAGE_HEIGHT; i++) {
		for (int j = 0; j < STAGE_WIDTH; j++) {
			if (g_StageData[g_Stage][j][i] != 0){
				DrawExtendGraph(i * Stage.HEIGHT,
					j * Stage.WIDTH,
					i * Stage.HEIGHT+Stage.HEIGHT,
					j * Stage.WIDTH+Stage.WIDTH,
					StageObj(g_StageData[g_Stage][j][i]), TRUE);
			}
		}
	}
}

int StageObj(int Objimg) {
	switch (Objimg)
	{
	case 0:		break;
	case 1:		return g_img.sample[1]; break;
	case 2:		return g_img.sample[2]; break;
	case 3:		return g_img.sample[3]; break;
	case 4:		return g_img.sample[4]; break;
	case 5:		return g_img.sample[5]; break;
	case 6:		return g_img.sample[6]; break;
	case 7:		return g_img.sample[7]; break;
	case 8:		return g_img.sample[8]; break;
	case 9:		return g_img.sample[9]; break;
	}
}
