#include "DxLib.h"
#include "enemy.h"
#include "player.h"
#include "Picture.h"
#include "Map.h"
#include "Gimmick.h"
#include "GameScene.h"
#include "GameTitle.h"

Enemy g_enemy[ENEMY_MAX];
Enemy2 g_enemy2[ENEMY_MAX];
Enemy3 g_enemy3[ENEMY_MAX];


void EnemyInit() {
	
	for (int i = 1; i < ENEMY_MAX; i++) {
		
				if (g_map.select == 1) {
					
						g_enemy[i].ex = CHIPSIZE * 13, g_enemy[i].ey = CHIPSIZE * 2;
					
				
						
				}
				if (g_map.select == 2) {
					
						g_enemy[i].ex = CHIPSIZE * 10, g_enemy[i].ey = CHIPSIZE * 2;

						g_enemy[2].ex = CHIPSIZE * 16, g_enemy[2].ey = CHIPSIZE * 2;
					
					
				}
				if (g_map.select == 3) {
					
						g_enemy3[i].ex3 = CHIPSIZE * 13, g_enemy3[i].ey3 = CHIPSIZE * 8;
						
				}
				if (g_map.select == 4) {
					g_enemy3[i].ex3 = CHIPSIZE * 4, g_enemy3[i].ey3 = CHIPSIZE * 3;

				}
				
				if (g_map.select == 6) {
					
						g_enemy[i].ex = CHIPSIZE * 8, g_enemy[i].ey = CHIPSIZE * 2;
					
						g_enemy2[i].ex2 = CHIPSIZE * 16, g_enemy2[i].ey2 = CHIPSIZE * 4;
					
				}
				
				if (g_map.select == 7) {
				
						g_enemy[i].ex = CHIPSIZE * 16, g_enemy[i].ey = CHIPSIZE * 6;
						
					
				}
				
			}
		
	}



void EnemyMove() {
	for (int i = 1; i < ENEMY_MAX; i++){
		//上下
		if (g_map.playStage[int((g_enemy[i].ey) / CHIPSIZE)][int(g_enemy[i].ex / CHIPSIZE)] != 1
			&& g_enemy[i].es == 0) {
			g_enemy[i].ey -= 3;

		}
		else {
			g_enemy[i].es = 1;
		}

		if (g_enemy[i].ey == 0) {
			g_enemy[i].es = 1;
		}

		if (g_map.playStage[int((g_enemy[i].ey + 64) / CHIPSIZE)][int(g_enemy[i].ex / CHIPSIZE)] != 1
			&& g_enemy[i].es == 1) {
			g_enemy[i].ey += 2;

		}
		else {
			g_enemy[i].es = 0;
		}

		//当たり判定
		if (HitBoxPlayer(&g_player, &g_enemy[i]) == TRUE
			&& g_player.dir == 0) {
			g_player.life -= 1;
			g_player.px = g_player.px - 80;
		}

		if (HitBoxPlayer(&g_player, &g_enemy[i]) == TRUE
			&& g_player.dir == 1) {
			g_player.life -= 1;
			g_player.px = g_player.px + 80;

		}

		//プレイヤーのライフが０なったら
		if (g_player.life == 0) {
			g_gameScene = GAME_SELECT;
			g_player.px = CHIPSIZE * 1, g_player.py = CHIPSIZE * 9;
		}
		//敵の表示
		DrawGraph(g_enemy[i].ex, g_enemy[i].ey, g_img.Teki[1], TRUE);
	}
}

void EnemyMove2() {
	for (int i = 1; i < ENEMY_MAX; i++) {
		//左右
		if (g_map.playStage[int(g_enemy2[i].ey2 / CHIPSIZE)][int(g_enemy2[i].ex2 / CHIPSIZE)] != 1
			&& g_enemy2[i].es2 == 0) {
			g_enemy2[i].ex2 -= 3;
		
		}
		else {
			g_enemy2[i].es2 = 1;
		}

		if (g_map.playStage[int(g_enemy2[i].ey2 / CHIPSIZE)][int((g_enemy2[i].ex2 + 64) / CHIPSIZE)] != 1
			&& g_enemy2[i].es2 == 1) {
			g_enemy2[i].ex2 += 3;
		
		}
		else {
			g_enemy2[i].es2 = 0;
		}
		//当たり判定
		if (HitBoxPlayer2(&g_player, &g_enemy2[i]) == TRUE
			&& g_player.dir == 0) {
			g_player.life -= 1;
			g_player.px = g_player.px - 80;
		}

		if (HitBoxPlayer2(&g_player, &g_enemy2[i]) == TRUE
			&& g_player.dir == 1) {
			g_player.life -= 1;
			g_player.px = g_player.px + 80;

		}

		//プレイヤーのライフが０なったら
		if (g_player.life == 0) {
			g_gameScene = GAME_SELECT;
			g_player.px = CHIPSIZE * 1, g_player.py = CHIPSIZE * 9;
		}
	
			//敵の表示
			DrawGraph(g_enemy2[i].ex2, g_enemy2[i].ey2, g_img.Teki[2], TRUE);
		
		
	}
}

void EnemyMove3() {
	for (int i = 1; i < ENEMY_MAX; i++) {
		
		//当たり判定
		if (HitBoxPlayer3(&g_player, &g_enemy3[i]) == TRUE
			&& g_player.dir == 0&&g_player.syo != 1) {
			g_player.life -= 1;
			g_player.px = g_player.px - 80;
		}
		else if(HitBoxPlayer3(&g_player, &g_enemy3[i]) == TRUE
			&& g_player.dir == 0 && g_player.syo == 1){
			g_enemy3[i].ex3 = CHIPSIZE * -1, g_enemy3[i].ey3 = CHIPSIZE * -1;
		}

		if (HitBoxPlayer3(&g_player, &g_enemy3[i]) == TRUE
			&& g_player.dir == 1&&g_player.syo!=1) {
			g_player.life -= 1;
			g_player.px = g_player.px + 80;

		}
		else if (HitBoxPlayer3(&g_player, &g_enemy3[i]) == TRUE
			&& g_player.dir == 0 && g_player.syo == 1) {
			g_enemy3[i].ex3 = CHIPSIZE * -1, g_enemy3[i].ey3 = CHIPSIZE * -1;
		}

		//プレイヤーのライフが０なったら
		if (g_player.life == 0) {
			g_gameScene = GAME_SELECT;
			g_player.px = CHIPSIZE * 1, g_player.py = CHIPSIZE * 9;
		}

		//敵の表示
		DrawGraph(g_enemy3[i].ex3, g_enemy3[i].ey3, g_img.Teki[3], TRUE);
	}
}


/*************************************
*自機と敵機の当たり判定（四角）
* 引数：PLAYER　ポインタ
* 戻り値：TRUE：あたり、FALSE：はずれ
*************************************/
int HitBoxPlayer(Player* p, Enemy* e)
{
	//x,yは中心座標とする
	int sx1 = p->px - (p->pw-49);
	int sy1 = p->py - (p->ph/32);
	int sx2 = sx1 + p->pw;
	int sy2 = sy1 + p->ph;

	int dx1 = e->ex - (e->ew-64);
	int dy1 = e->ey - (e->eh-63);
	int dx2 = dx1 + e->ew;
	int dy2 = dy1 + e->eh;

	////判定確認用
	//DrawBox(sx1, sy1, sx2, sy2, 0xFFFFFF, TRUE);
	//DrawBox(dx1, dy1, dx2, dy2, 0xFFFFFF, TRUE);

	//短径が重なっていたら当たり
	if (sx1 < dx2 && dx1 < sx2 && sy1 < dy2 && dy1 < sy2) {
		return TRUE;
	}

	return FALSE;

}

/**************************************
*自機と敵機の当たり判定（四角）
* 引数：PLAYER　ポインタ
* 戻り値：TRUE：あたり、FALSE：はずれ
************************************* */
int HitBoxPlayer2(Player * p, Enemy2* e2)
{
	//x,yは中心座標とする
	int sx1 = p->px - (p->pw - 49);
	int sy1 = p->py - (p->ph / 32);
	int sx2 = sx1 + p->pw;
	int sy2 = sy1 + p->ph;


	int dx3 = e2->ex2 - (e2->ew2 - 64);
	int dy3 = e2->ey2 - (e2->eh2 - 63);
	int dx4 = dx3 + e2->ew2;
	int dy4 = dy3 + e2->eh2;

	////判定確認用
	//DrawBox(sx1, sy1, sx2, sy2, 0xFFFFFF, TRUE);
	//DrawBox(dx3, dy3, dx4, dy4, 0xFFFFFF, TRUE);

	//短径が重なっていたら当たり
	if (sx1 < dx4 && dx3 < sx2 && sy1 < dy4 && dy3 < sy2) {
		return TRUE;
	}

	return FALSE;

}

/**************************************
*自機と敵機の当たり判定（四角）
* 引数：PLAYER　ポインタ
* 戻り値：TRUE：あたり、FALSE：はずれ
************************************* */
int HitBoxPlayer3(Player * p, Enemy3 * e3)
{
	//x,yは中心座標とする
	int sx1 = p->px - (p->pw - 49);
	int sy1 = p->py - (p->ph / 32);
	int sx2 = sx1 + p->pw;
	int sy2 = sy1 + p->ph;


	int dx5 = e3->ex3 - (e3->ew3 - 64);
	int dy5 = e3->ey3 - (e3->eh3 - 128);
	int dx6 = dx5 + e3->ew3;
	int dy6 = dy5 + e3->eh3;

	////判定確認用
	//DrawBox(sx1, sy1, sx2, sy2, 0xFFFFFF, TRUE);
	//DrawBox(dx5, dy5, dx6, dy6, 0xFFFFFF, TRUE);

	//短径が重なっていたら当たり
	if (sx1 < dx6 && dx5 < sx2 && sy1 < dy6 && dy5 < sy2) {
		return TRUE;
	}

	return FALSE;

}