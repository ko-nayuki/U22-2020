#pragma once
#include "DxLib.h"
void PlayerMove();

//移動係数
float move = 1.0f;

// 移動係数
float speed = 1.0f;

//横方向と縦方向のカウント数。
int xcount = 0, ycount = 0;
//添字用変数
int ix = 0, iy = 0, result = 0;
//キー取得用配列
char key[256];

//x座標
int px = 300, py = 416, y_prev = 0, y_temp = 0;

//ジャンプしてるかのフラグ。
bool jflag = false;

//向き
int dir = 0;