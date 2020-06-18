#pragma once
#include "DxLib.h"

#define GIMMICK_NUM 2	//ギミック数

void gimmickMove();
void gimmickDisp();

enum {
	LIFT = 0,		//エレベーター
	BREAK = 1		//破壊できる壁

};

struct Gimmick {
	int x;				//x座標
	int y;				//y座標
	int w;				//幅
	int h;				//高さ
	bool moveFlg;		//ギミックの起動フラグ
};

extern Gimmick g_gimmick[GIMMICK_NUM];
