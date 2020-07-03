#pragma once
#include "DxLib.h"

#define GIMMICK_NUM 2	//ギミック数
#define KANZI_NUM 2		//漢字の数

void gimmickMove();
void gimmickDisp();
void gimmickInit();

enum {
	LIFT = 0,		//エレベーター
	BREAK = 1		//破壊できる壁

};

enum {//漢字
	K_NO = 0,		//無し
	K_UE = 1,		//上
	K_SITA = 2		//下
};

struct Gimmick {
	int x;				//x座標
	int y;				//y座標
	int w;				//幅
	int h;				//高さ
	bool moveFlg;		//ギミックの起動フラグ
	bool moveFlg2;		//ギミックの起動フラグ2
	float anime;		//ギミックアニメーション
};

extern Gimmick g_gimmick[GIMMICK_NUM];
