#pragma once
#include "DxLib.h"

#define GIMMICK_NUM 2	//ギミック数

void gimmickMove();
void gimmickDisp();
void gimmickInit();

enum {
	LIFT = 0,		//エレベーター(ワープゾーン)
	BREAK = 1		//破壊できる壁

};

enum {//漢字
	K_UE = 0,		//上
	K_HA = 1		//破
};

struct Gimmick {
	int x;				//x座標
	int y;				//y座標
	int w;				//幅
	int h;				//高さ
	bool moveFlg;		//ギミックの起動フラグ
};

extern Gimmick g_gimmick[GIMMICK_NUM];
