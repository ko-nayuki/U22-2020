#pragma once
#include "DxLib.h"

void bossMove();
void bossDisp();
void bossInit();

void boss1_Init();
void boss2_Init();
void boss3_Init();

void wolfMove();
void thiefMove();
void ColossusMove();

struct boss {
	float x;		//x座標
	float y;		//y座標
	int hp;			//体力
	int damageFlg;	//ダメージフラグ
	int attackFlg;	//攻撃フラグ
	float anime;	//アニメーション
	int count;		//次の行動までの時間

};

extern boss g_boss[4];//0 :BOSS_1, 1 :BOSS_2, 2 :BOSS_3_L, BOSS_3_R 
extern boss g_boss3head;
