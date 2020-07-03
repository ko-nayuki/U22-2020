#pragma once
#include "DxLib.h"
#include "player.h"

#define ITEM_MAX 5		//アイテムの最大数

void PlayerMove();

struct Player {
	//移動係数
	float move = 1.0f;

	// 移動係数
	float speed = 1.0f;

	//横方向と縦方向のカウント数。
	int xcount = 0, ycount = 0;
	//添字用変数
	int ix = 0, iy = 0, result = 0;

	//x座標
	int px = 700, py = 560, y_prev = 0, y_temp = 0;

	//ジャンプしてるかのフラグ。
	bool jflag = false;

	//向き
	int dir = 0;

	//アイテム所持数
	int item[ITEM_MAX] = { 0 };
	int itemNo = 0;
	int itemSelect = 0;
};

extern Player g_player;

//キー取得用配列
extern char key[256];