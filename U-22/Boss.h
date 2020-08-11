#pragma once
#include "DxLib.h"

void bossMove();
void bossDisp();
void bossInit();

void wolfMove();

struct boss {
	int x;			//x座標
	int y;			//y座標
	int hp;			//体力
	int damageFlg;	//ダメージフラグ
	int attackFlg;	//攻撃フラグ
	int anime;		//アニメーション
	int count;		//次の行動までの時間

};

extern boss g_boss[4];