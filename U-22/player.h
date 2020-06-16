#pragma once
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
int x = 300, y = 420, y_prev = 0, y_temp = 0;

//ジャンプしてるかのフラグ。
bool jflag = false;

//グラフィックハンドル格納用配列
int gh[9];

//向き
int dir = 0;