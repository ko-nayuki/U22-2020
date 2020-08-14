
#pragma once
#include "DxLib.h"
#include "enemy.h"
#include "player.h"

#define ENEMY_MAX  3 //ìGÇÃç≈ëÂÇÃêî

struct Enemy {
	
	int ex=0,ey=0;
	int eh=64, ew=64;

	int es=0;


	
}; extern Enemy g_enemy[ENEMY_MAX];

struct Enemy2 {

	int ex2 = 0, ey2 = 0;
	int eh2 = 64,ew2 = 64;

	int es2 = 0;



}; extern Enemy2 g_enemy2[ENEMY_MAX];

struct Enemy3 {

	int ex3 = 0, ey3 = 0;
	int eh3 = 128, ew3 = 64;

	int es3 = 0;



}; extern Enemy3 g_enemy3[ENEMY_MAX];

void EnemyInit();
void EnemyMove();
void EnemyMove2();
void EnemyMove3();



int HitBoxPlayer(Player* p, Enemy* e);
int HitBoxPlayer2(Player* p, Enemy2* e2);
int HitBoxPlayer3(Player* p, Enemy3* e3);

