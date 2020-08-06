#include "DxLib.h"
#include "Picture.h"
#include "Map.h"
#include "Boss.h"
#include "player.h"

void bossDisp() {
	if (g_map.select == 5) {//boss1
		DrawGraph(g_boss[0].x, g_boss[0].y - CHIPSIZE, g_img.wolf[g_boss[0].anime], TRUE);
		DrawFormatString(500, 400, 0x0000FF, "%d", g_boss[0].y/CHIPSIZE);
	}
	if (g_map.select == 8) {//boss2

	}
	if (g_map.select == 11) {//boss3

	}

}

void bossMove() {
	if (g_map.select == 5) {//boss1
		bossDisp();
		wolfMove();
	}
	if (g_map.select == 8) {//boss2
		bossDisp();
	}
	if (g_map.select == 11) {//boss3
		bossDisp();
	}
}

void wolfMove() {// boss1
	static int next_Attack = 0;					// 1~3:ジャンプ  4:風
	static int jump_x = 10 * CHIPSIZE + 32;		//ジャンプの着地地点
	static float fallSpeed = 0.0;
	static int wind_time = 300;					//風の時間

	DrawFormatString(500, 450, 0x00FFFF, "%d", jump_x);
	DrawFormatString(500, 420, 0x00FFFF, "%d", next_Attack);
	//足場が消えたときに落下
	if (g_map.playStage[(g_boss[0].y / CHIPSIZE) + 1][g_boss[0].x / CHIPSIZE] == AIR && 
		g_map.gimmickData[(g_boss[0].y / CHIPSIZE) + 1][g_boss[0].x / CHIPSIZE] == GIM_401) {
		g_boss[0].y += 2;
	}

	if (g_boss[0].attackFlg == false) g_boss[0].count++, g_boss[0].anime = 4;
	if (g_boss[0].count > 100) {
		next_Attack++;
		if (next_Attack > 4) next_Attack = 1;
		else jump_x = ((GetRand(2) + 1) * 5) * CHIPSIZE + 32;
		g_boss[0].count = 0;
		g_boss[0].attackFlg = true;
	}

	if ((next_Attack >= 1 && next_Attack < 4) && g_boss[0].attackFlg == true) {

		if (g_boss[0].x < jump_x) g_boss[0].x += 2;
		if (g_boss[0].x > jump_x) g_boss[0].x -= 2;
		if (g_boss[0].x == jump_x) g_boss[0].attackFlg = false;
	}
	if (next_Attack == 4 && g_boss[0].attackFlg == true) {
		g_boss[0].anime = 0;
		g_player.px -= 0.1F + (wind_time * 0.01);
		if (wind_time-- <= 0) {
			wind_time = 300;
			g_boss[0].attackFlg = false;
		}
	}
}

void bossInit() {
	//ボス1の初期化
	g_boss[0].x = 15 * CHIPSIZE + 32;
	g_boss[0].y = 6 * CHIPSIZE;
	g_boss[0].anime = 4;
}