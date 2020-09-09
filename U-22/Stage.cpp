//ステージ生成プログラム

#include "DxLib.h"
#include "Map.h"
#include "Picture.h"
#include "Gimmick.h"
#include "player.h"
#include "GameScene.h"

//int g_Stage = 0;
//StageInfo Stage;

void StageInit() {

	//ステージ読み込み
	for (int i = 0; i < STAGE_HEIGHT; i++) {
		for (int j = 0; j < STAGE_WIDTH; j++) {
			g_map.playStage[i][j] = g_map.stageData[g_map.select][i][j];
			g_map.gimmickData[i][j] = 0;

			if (g_map.playStage[i][j] == 3) {//プレイヤーの座標
				g_player.px = j * CHIPSIZE;
				g_player.py = i * CHIPSIZE;
			}

			if (g_map.playStage[i][j] == 5) {//エレベータの情報
				g_map.gimmickData[i][j] = g_map.playStage[i][j];
				//g_gimmick[LIFT].x = j * CHIPSIZE;
				//g_gimmick[LIFT].y = i * CHIPSIZE;
			}
			if (g_map.playStage[i][j] == 6) {//ジャンプ台の情報
				g_map.gimmickData[i][j] = g_map.playStage[i][j];
				//g_gimmick[BOUND].x = j * CHIPSIZE;
				//g_gimmick[BOUND].y = i * CHIPSIZE;
			}
			if (g_map.playStage[i][j] == 7) {//破壊できる壁の情報
				g_map.gimmickData[i][j] = g_map.playStage[i][j];
				g_map.playStage[i][j] = 1;
			}
			if (g_map.playStage[i][j] == 8) {//落下ギミックの情報
				g_map.gimmickData[i][j] = g_map.playStage[i][j];
				g_map.playStage[i][j] = 1;
			}
			if (g_map.playStage[i][j] == 9) {//落下看板の情報
				g_map.gimmickData[i][j] = g_map.playStage[i][j];
				//g_gimmick[DROP].x = j * CHIPSIZE;
				//g_gimmick[DROP].y = i * CHIPSIZE;
			}
			if (g_map.playStage[i][j] == 15) {//破損看板の情報
				g_map.gimmickData[i][j] = g_map.playStage[i][j];
			}
			if (g_map.playStage[i][j] == 10) {//炎の情報
				g_map.gimmickData[i][j] = g_map.playStage[i][j];
				g_map.playStage[i][j] = 1;
			}
			if (g_map.playStage[i][j] == 11) {//ワープAの情報
				g_map.gimmickData[i][j] = g_map.playStage[i][j];
				g_gimmick[WARP_A].x = j * CHIPSIZE;
				g_gimmick[WARP_A].y = i * CHIPSIZE;
			}
			if (g_map.playStage[i][j] == 12) {//ワープBの情報
				g_map.gimmickData[i][j] = g_map.playStage[i][j];
				g_gimmick[WARP_B].x = j * CHIPSIZE;
				g_gimmick[WARP_B].y = i * CHIPSIZE;
			}
			if (g_map.playStage[i][j] == 13) {//ワープCの情報
				g_map.gimmickData[i][j] = g_map.playStage[i][j];
				g_gimmick[WARP_C].x = j * CHIPSIZE;
				g_gimmick[WARP_C].y = i * CHIPSIZE;
			}
			if (g_map.playStage[i][j] == 16) {//透明壁
				g_map.gimmickData[i][j] = g_map.playStage[i][j];
				g_map.playStage[i][j] = 1;
			}
			if (g_map.playStage[i][j] == 18) {//横長ジャンプ台の情報
				g_map.gimmickData[i][j] = g_map.playStage[i][j];
				g_map.playStage[i][j] = 1;
			}
			g_map.random[i][j] = rand() % 3;
		}
	}
}

void StageDisp() {
	//ステージ描画
	for (int i = 0; i < STAGE_HEIGHT; i++) {
		for (int j = 0; j < STAGE_WIDTH; j++) {//マップの描画
			if (g_map.playStage[i][j] != 0 && g_map.playStage[i][j] < 5 && g_map.playStage[i][j] < A) {
				if (g_map.playStage[i][j] == 1 && g_map.gimmickData[i][j] == 0) {
					if (g_map.playStage[i - 1][j] != 1) {
						DrawGraph(j * CHIPSIZE, i * CHIPSIZE, g_img.MAP[(g_map.select / 3) * 3 + 1], FALSE);
					}
					else if (g_map.playStage[i][j] != 3) {
						DrawGraph(j * CHIPSIZE, i * CHIPSIZE, g_img.MAP[(g_map.select / 3) * 3 + 2], FALSE);
					}
				}
				else {

					if (g_map.gimmickData[i][j] == GIM_3) {
						DrawGraph(j * CHIPSIZE, i * CHIPSIZE, g_img.crack, TRUE);
					}
					if (g_map.gimmickData[i][j] == BOSS_G_2 && g_map.gimmickData[i][j + 1] == BOSS_G_2) {
						DrawGraph(j * CHIPSIZE, i * CHIPSIZE, g_img.trampoline[0], TRUE);
					}
					if (g_map.gimmickData[i][j] == BOSS_G_3 && g_map.gimmickData[i][j + 1] == BOSS_G_3) {
						DrawGraph(j * CHIPSIZE, i * CHIPSIZE, g_img.trampoline[1], TRUE);
					}
				}
			}
			if (g_map.playStage[i][j] >= A) {//漢字の描画
				//if(g_map.playStage[i][j] == G) SetDrawBright(255, 0, 0);
				DrawGraph(j * CHIPSIZE, i * CHIPSIZE, g_img.kanzi[g_map.playStage[i][j] - A], TRUE);
				//SetDrawBright(255, 255, 255);
			}
			if (g_map.gimmickData[i][j] == GIM_1) {
				if (g_player.item[g_player.itemSelect] == K_SITA) {
					DrawGraph(j * CHIPSIZE, i * CHIPSIZE, g_img.gimKanzi[1], TRUE);
				}
				else {
					DrawGraph(j * CHIPSIZE, i * CHIPSIZE, g_img.gimKanzi[0], TRUE);
				}
			}
			if (g_map.playStage[i][j] == GIM_2 && g_map.gimmickData[i][j] == GIM_2) {
				DrawGraph(j * CHIPSIZE, i * CHIPSIZE, g_img.gimKanzi[2], TRUE);
			}
			else if (g_map.playStage[i][j] == GIM_2 && g_map.gimmickData[i][j] == AIR) {
				if (g_gimmick[BOUND].x != j * CHIPSIZE && g_gimmick[BOUND].y + CHIPSIZE != i * CHIPSIZE) {
					DrawGraph(j * CHIPSIZE, i * CHIPSIZE, g_img.spring[0], TRUE);
				}

			}


			if (g_map.gimmickData[i][j] == GIM_402) {
				DrawGraph(j * CHIPSIZE, i * CHIPSIZE, g_img.gimKanzi[3], TRUE);
			}
			if (g_map.gimmickData[i][j] == GIM_403) {
				DrawGraph(j * CHIPSIZE, i * CHIPSIZE, g_img.gimKanzi[5], TRUE);
			}

			if (g_map.gimmickData[i][j] == GIM_601 && g_map.gimmickData[i][j] == GIM_601) {
				DrawGraph(j * CHIPSIZE, i * CHIPSIZE, g_img.gimKanzi[4], TRUE);
			}
			else if (g_map.playStage[i][j] == GIM_601 && g_map.gimmickData[i][j] == AIR) {
				SetDrawBright(0, 0, 255);
				DrawGraph(j * CHIPSIZE, i * CHIPSIZE, g_img.warp, TRUE);
				SetDrawBright(255, 255, 255);
			}
			if (g_map.gimmickData[i][j] == GIM_602 && g_map.gimmickData[i][j] == GIM_602) {
				DrawGraph(j * CHIPSIZE, i * CHIPSIZE, g_img.gimKanzi[4], TRUE);
			}
			else if (g_map.playStage[i][j] == GIM_602 && g_map.gimmickData[i][j] == AIR) {
				SetDrawBright(255, 0, 0);
				DrawGraph(j * CHIPSIZE, i * CHIPSIZE, g_img.warp, TRUE);
				SetDrawBright(255, 255, 255);
			}
			if (g_map.gimmickData[i][j] == GIM_603 && g_map.gimmickData[i][j] == GIM_603) {
				DrawGraph(j * CHIPSIZE, i * CHIPSIZE, g_img.gimKanzi[4], TRUE);
			}
			else if (g_map.playStage[i][j] == GIM_603 && g_map.gimmickData[i][j] == AIR) {
				SetDrawBright(0, 255, 0);
				DrawGraph(j * CHIPSIZE, i * CHIPSIZE, g_img.warp, TRUE);
				SetDrawBright(255, 255, 255);
			}

			if (g_map.playStage[i][j] == BOSS_G_1 && g_map.playStage[i][j + 1] == BOSS_G_1) {
				DrawGraph(j * CHIPSIZE, i * CHIPSIZE, g_img.Cauldron, TRUE);
			}

			if (g_map.playStage[i][j] == Board) {
				DrawGraph(j * CHIPSIZE - 18, i * CHIPSIZE - 46, g_img.KanBan[0], TRUE);
				//DrawExtendGraph(j * CHIPSIZE, i * CHIPSIZE, j * CHIPSIZE + 64, i * CHIPSIZE + 64, g_img.KanBan[0], TRUE);
			}
		}
	}

}

void SelectMAPDisp() {
	for (int i = 0; i < STAGE_HEIGHT; i++) {
		for (int j = 0; j < STAGE_WIDTH; j++) {
			g_map.playStage[i][j] = g_map.selectMap[i][j];
			if (g_map.playStage[i][j] == 1) {
				DrawGraph(j * CHIPSIZE, i * CHIPSIZE, g_img.MAP[1], TRUE);
			}
			//if (g_map.playStage[i][j] == 3) {//プレイヤーの座標
			//	g_player.px = j * CHIPSIZE;
			//	g_player.py = i * CHIPSIZE;
			//}
		}
	}
}

void TitleMAPDisp() {
	for (int i = 0; i < STAGE_HEIGHT; i++) {
		for (int j = 0; j < STAGE_WIDTH; j++) {
			g_map.playStage[i][j] = g_map.TitleMap[i][j];
			if (g_map.playStage[i][j] == 1) {
				DrawGraph(j * CHIPSIZE, i * CHIPSIZE, g_img.MAP[g_map.playStage[i][j]], TRUE);
			}
			if (g_map.playStage[i][j] == 3) {//プレイヤーの座標
				g_player.px = j * CHIPSIZE;
				g_player.py = i * CHIPSIZE;
			}
			//if (g_map.playStage[i][j] == 30) {//始
			//	DrawGraph(j * CHIPSIZE, i * CHIPSIZE, g_img.T_kanzi[0], FALSE);
			//}
			////if (g_map.playStage[i][j] == 31) {//開
			////	DrawGraph(j * CHIPSIZE, i * CHIPSIZE, g_img.T_kanzi[1], FALSE);
			////}
			//if (g_map.playStage[i][j] == 32) {//終
			//	DrawGraph(j * CHIPSIZE, i * CHIPSIZE, g_img.T_kanzi[4], FALSE);
			//}
			////if (g_map.playStage[i][j] == 33) {//了
			////	DrawGraph(j * CHIPSIZE, i * CHIPSIZE, g_img.T_kanzi[3], FALSE);
			////}
			//if (g_map.playStage[i][j] == 33) {//了
			//	DrawGraph(j * CHIPSIZE, i * CHIPSIZE, g_img.T_kanzi[3], FALSE);
			//}
		}
	}
}

void BackStageDisp() {
	for (int i = 0; i < STAGE_HEIGHT; i++) {
		for (int j = 0; j < STAGE_WIDTH; j++) {
			//DrawGraph(j * CHIPSIZE, i * CHIPSIZE, g_img.bookshelf[g_map.random[i][j]], TRUE);

			if (g_gameScene == GAME_PLAY || g_gameScene == GAME_CLEAR || g_gameScene == GAME_OVER) {
				DrawGraph(j * CHIPSIZE, i * CHIPSIZE, g_img.MAP[(g_map.select / 3) * 3], FALSE);
			}
			else {
				DrawGraph(j * CHIPSIZE, i * CHIPSIZE, g_img.MAP[0], TRUE);
			}
		}
	}
	if (g_gameScene == GAME_PLAY || g_gameScene == GAME_CLEAR || g_gameScene == GAME_OVER) {
		if (g_map.select >= 6 && g_map.select <= 8) {
			DrawGraph(0, 0, g_img.stage3, FALSE);
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
			DrawBox(0, 0, 1280, 768, 0x000000, TRUE);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		}
		if (g_map.select >= 9 && g_map.select <= 11) {
			DrawGraph(0, 0, g_img.stage4, FALSE);
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 50);
			DrawBox(0, 0, 1280, 768, 0x000000, TRUE);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
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
