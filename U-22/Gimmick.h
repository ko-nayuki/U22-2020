#pragma once
#include "DxLib.h"

#define GIMMICK_NUM 10	//ギミックの数
#define KANZI_NUM 7		//漢字の数

#define GRAVITY          (0.2F)		// 重力
#define JUMP_POWER       (14.0F)	// ジャンプ台のジャンプ力

void gimmickMove();
void gimmickDisp();
void gimmickInit();

void smoke(int smokeX, int smokeY);		//煙

void liftMove();	//エレベーター
void boundMove();	//ジャンプ台
void breakMove();	//破壊できる壁
void dropMove();	//落下ギミック
void fireMove();	//炎
void warpMove();	//ワープ
void bombMove();	//爆弾

enum {//ギミック
	LIFT = 0,		//エレベーター
	BOUND = 1,		//ジャンプ台
	BREAK = 2,		//破壊できる壁
	DROP = 3,		//落下ギミック
	FIRE = 4,		//炎
	WARP_A = 5,		//ワープA地点
	WARP_B = 6,		//ワープB地点
	BOMB = 7,		//爆弾
};

enum {//漢字
	K_NO = 0,		//無し
	K_UE = 1,		//上[うえ]
	K_SITA = 2,		//下[した]
	K_TIKARA = 3,	//力[ちから]
	K_HA = 4,		//破[は]
	K_SHOU = 5,		//消[しょう]
	K_DOU = 6,		//動[どう]
	K_BAKU = 7,		//爆[ばく]
};

struct Gimmick {
	int x;				//x座標
	int y;				//y座標
	int w;				//幅
	int h;				//高さ
	bool ONFlg;			//ギミックの作動フラグ
	bool moveFlg;		//ギミックのアニメーション起動フラグ
	bool moveFlg2;		//ギミックのアニメーション起動フラグ2
	float anime;		//ギミックアニメーション
	//float speed;		//ジャンプ用

	int tikara = 0;
};

extern Gimmick g_gimmick[GIMMICK_NUM];
