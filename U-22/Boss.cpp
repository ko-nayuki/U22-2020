#include "DxLib.h"
#include "Picture.h"
#include "Map.h"
#include "Boss.h"
#include "player.h"
#include "Gimmick.h"
#include "GameScene.h"

#include <math.h>

void bossDisp() {
	if (g_map.select == 5) {//boss1
		DrawGraph(g_boss[0].x, g_boss[0].y - CHIPSIZE, g_img.wolf[int(g_boss[0].anime)], TRUE);
	}
	if (g_map.select == 8) {//boss2
		DrawGraph(g_boss[1].x, g_boss[1].y - CHIPSIZE, g_img.thief[int(g_boss[1].anime)], TRUE);
	}
	if (g_map.select == 11) {//boss3
		DrawGraph(g_boss[2].x, g_boss[2].y - CHIPSIZE, g_img.Colossus[0], TRUE);
	}

}

void bossMove() {
	if (g_map.select == 5) {//boss1
		bossDisp();
		wolfMove();
	}
	if (g_map.select == 8) {//boss2
		bossDisp();
		thiefMove();
	}
	if (g_map.select == 11) {//boss3
		bossDisp();
		ColossusMove();
	}
}

void bossInit() {
	//ボス1の初期化
	g_boss[0].x = 15 * CHIPSIZE + 32;
	g_boss[0].y = 6 * CHIPSIZE;
	g_boss[0].anime = 6;
	g_boss[0].hp = 3;
	g_boss[0].count = 0;
	g_boss[0].damageFlg = false;
	g_boss[0].attackFlg = false;

	//ボス2の初期化
	g_boss[1].x = 1 * CHIPSIZE + 32;
	g_boss[1].y = 3 * CHIPSIZE;
	g_boss[1].anime = 4;
	g_boss[1].hp = 3;
	g_boss[1].count = 0;
	g_boss[1].damageFlg = false;
	g_boss[1].attackFlg = false;

	//ボス3の初期化
	g_boss[2].x = 1 * CHIPSIZE;
	g_boss[2].y = 2 * CHIPSIZE;
	g_boss[2].hp = 3;
	g_boss[2].count = 0;
	g_boss[2].damageFlg = false;
	g_boss[2].attackFlg = false;
}