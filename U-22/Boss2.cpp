#include "DxLib.h"
#include "Picture.h"
#include "Map.h"
#include "Boss.h"
#include "player.h"
#include "Gimmick.h"
#include "GameScene.h"

#include <math.h>

void thiefMove() {//boss2
	//モーション加算値
	//0:左待機 1~3:左攻撃 4:右待機 5~7:右攻撃 8~15:左からワープ 16~23:右からワープ

	static int motion_attack = 0;		//攻撃加算値
	static int motion_y = 0;			//移動時の高さ
	static bool warpFlg = false;		//移動フラグ
	static int warp_num = 0;			//0:移動開始 1:反対側へ 2:移動完了

	//playerがいる方向とは逆方向にワープ
	if (g_boss[1].x == 17 * CHIPSIZE + 32) DrawGraph(1 * CHIPSIZE + 32, g_boss[1].y + 21 - motion_y, g_img.thief[15], TRUE);
	if (g_boss[1].x == 1 * CHIPSIZE + 32) DrawGraph(17 * CHIPSIZE + 32, g_boss[1].y + 21 - motion_y, g_img.thief[23], TRUE);

	if (g_player.px > 12 * CHIPSIZE + 32 && g_boss[1].x == 17 * CHIPSIZE + 32) {
		if (warpFlg == false) {//playerが右に移動
			g_boss[1].anime = 16;
			g_boss[1].count = 0;
			g_boss[1].attackFlg = false;
			warp_num = 0;
			warpFlg = true;
		}
	}
	else if (g_player.px < 6 * CHIPSIZE + 32 && g_boss[1].x == 1 * CHIPSIZE + 32) {
		if (warpFlg == false) {//playerが左に移動
			g_boss[1].anime = 8;
			g_boss[1].count = 0;
			g_boss[1].attackFlg = false;
			warp_num = 0;
			warpFlg = true;
		}
	}

	if (warpFlg == true) {
		if (warp_num == 0) {//移動開始
			if (motion_y < 85) {
				motion_y++;
				if (motion_y < 80) {
					g_boss[1].anime += 0.1;
				}
				else {
					if (g_boss[1].x == 17 * CHIPSIZE + 32) {
						g_boss[1].x = 1 * CHIPSIZE + 32;
						g_boss[1].anime = 15;
						warp_num = 1;
					}
					else if (g_boss[1].x == 1 * CHIPSIZE + 32) {
						g_boss[1].x = 17 * CHIPSIZE + 32;
						g_boss[1].anime = 23;
						warp_num = 1;
					}
				}
			}
		}
		else if (warp_num == 1) {//反対側へ
			if (motion_y > 0) {
				motion_y--;
				if (motion_y <= 80 && motion_y > 10) {
					g_boss[1].anime -= 0.1;
				}
			}
			else {
				if (g_boss[1].x == 1 * CHIPSIZE + 32) g_boss[1].anime = 0;
				if (g_boss[1].x == 17 * CHIPSIZE + 32) g_boss[1].anime = 4;
				warp_num = 2;//移動完了
				warpFlg = false;
			}
		}
	}

	if (warpFlg == false && g_boss[1].attackFlg == false) {//攻撃待機
		g_boss[1].count++;
		if (g_boss[1].count > 50 * g_boss[1].hp) {
			g_boss[1].count = 0;
			motion_attack = g_boss[1].anime + 3;
			g_boss[1].attackFlg = true;
		}
	}
	if (warpFlg == false && g_boss[1].attackFlg == true) {//攻撃
		if (g_boss[1].anime < motion_attack) g_boss[1].anime += 0.1;
		else g_boss[1].attackFlg = false, g_boss[1].anime = g_boss[1].anime - 3;
	}
}
