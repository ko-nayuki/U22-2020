#pragma once
#include "DxLib.h"
#define STAGE 12				//ステージの数
#define STAGE_HEIGHT 12		//画面 高さ
#define STAGE_WIDTH 20		//画面 幅
#define CHIPSIZE 64			//マップチップサイズ

void TitleMAPDisp();
void SelectMAPDisp();
void StageDisp();
void StageInit();
void BackStageDisp();

enum {//マップチップ番号
	AIR = 0,		//何もなし
	BLOCK = 1,		//地面
	GOAL = 2,		//ゴール
	START = 3,		//playerのスタート地点
	GIM_1 = 5,		//エレベーター
	GIM_2 = 6,		//ジャンプ台
	GIM_3 = 7,		//破壊できる壁
	GIM_401 = 8,	//落下ギミック
	GIM_402 = 9,	//落下看板
	GIM_5 = 10,		//炎(a)
	GIM_601 = 11,	//ワープA(b)
	GIM_602 = 12,	//ワープB(c)
	GIM_603 = 13,	//ワープC(d)
	GIM_7 = 14,		//爆弾(e)
	GIM_403 = 15,	//破損ギミック(f)

	INVI = 16,		//透明壁(g)
	BOSS_G_1 = 17,	//bossギミック(大釜)(h)
	BOSS_G_2 = 18,	//bossギミック(横長ジャンプ台_kanzi)(k)
	BOSS_G_3 = 19,	//bossギミック(横長ジャンプ台)(l)

	Board = 20,		//看板(m)

	A = 30,			//上
	B,				//下
	C,				//力
	D,				//破
	E,				//消
	F,				//動
	G,				//爆

	//番号
	a = 10, b, c, d, e, f, g, h, k, l, m
};

struct MAP {

	int TitleMap[STAGE_HEIGHT][STAGE_WIDTH] =
	{
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 }
	};


	int select = 0;

	int selectMap[STAGE_HEIGHT][STAGE_WIDTH] =
	{
	  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	  { 0,0,0,2,2,0,0,0,0,2,2,0,2,2,0,2,2,0,0,0 },
	  { 0,3,0,2,2,0,0,0,0,2,2,0,2,2,0,2,2,0,0,0 },
	  { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
	  { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 }
	};

	//ステージの更新
	int playStage[STAGE_HEIGHT][STAGE_WIDTH];
	//ギミックの場所
	int gimmickData[STAGE_HEIGHT][STAGE_WIDTH];

	int stageData[STAGE][STAGE_HEIGHT][STAGE_WIDTH] =
	{
		//ステージ1-1
		{
			{1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,1,1},
			{1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,2,2,0,1,1},
			{1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,2,2,0,1,1},
			{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
			{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
			{1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1},
			{1,0,3,0,0,m,0,0,0,0,5,0,0,0,A,0,1,1,1,1},
			{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
			{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		},
		//ステージ1-2
		{
			{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
			{1,1,1,1,1,1,0,0,0,0,7,7,0,0,0,0,0,1,1,1},
			{1,1,1,1,1,0,0,0,0,0,7,7,0,0,2,2,0,0,1,1},
			{1,1,1,1,1,0,0,0,0,0,7,7,0,0,2,2,0,0,1,1},
			{1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1},
			{1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1},
			{1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1},
			{1,0,3,0,0,0,0,0,0,0,0,D,0,0,C,0,0,1,1,1},
			{1,1,1,1,1,1,6,1,1,1,1,1,1,1,1,1,1,1,1,1},
			{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		},
		//ステージ1-3
		{
			{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,5,0,D,0,B,0,1},
			{1,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1},
			{1,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1},
			{1,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,2,2,0,1},
			{1,0,3,0,0,0,0,0,0,C,0,7,0,0,0,0,2,2,0,1},
			{1,1,1,1,1,6,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
			{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		},
		//ステージ2-1
		{
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
			{1,0,0,0,0,0,0,0,a,a,0,0,2,2,0,0,0,0,1,1},
			{1,0,D,0,0,0,0,0,a,a,0,0,2,2,0,0,0,0,1,1},
			{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1},
			{1,0,0,0,0,0,0,0,0,0,7,0,0,0,1,0,0,0,1,1},
			{1,0,B,0,0,0,A,0,0,0,7,0,E,0,1,0,0,0,1,1},
			{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
			{1,0,3,0,5,0,0,B,0,A,0,0,0,0,0,0,C,0,1,1},
			{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,6,1,1,1},
			{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		},
		//ステージ2-2
		{
			{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,1},
			{1,0,D,0,0,0,9,0,0,0,0,0,0,B,0,7,0,0,0,1},
			{1,1,1,1,8,8,1,1,1,0,0,0,1,1,1,1,1,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1},
			{1,0,0,0,h,h,0,0,0,0,0,0,1,0,2,2,0,0,0,1},
			{1,0,3,0,0,0,0,0,C,0,0,0,1,0,2,2,0,0,0,1},
			{1,1,1,1,1,1,1,1,1,1,6,1,1,1,1,1,1,1,1,1},
			{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		},
		//ステージ2-3(ボス)
		{
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{0,0,3,0,9,0,0,0,0,9,0,0,0,0,9,0,0,0,B,1},
			{1,1,1,1,1,8,8,1,1,1,8,8,1,1,1,8,8,1,1,1},
			{1,1,1,1,1,0,0,1,1,1,0,0,1,1,1,0,0,1,1,1},
			{1,1,1,1,0,h,h,0,0,0,h,h,0,0,0,h,h,0,1,1},
			{1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
			{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		},
		//ステージ3-1
		{
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,3,0,D,0,0,0,0,0,0,0,0,0,0,0,9,0,G,0,1},
			{1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1,8,8,8,1},
			{1,0,0,0,0,0,1,1,1,1,1,1,6,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,1,0,0,0,2,2,1,0,0,0,0,0,0,1},
			{1,E,0,C,0,0,1,0,b,0,2,2,1,0,0,1,1,6,1,1},
			{1,1,1,1,0,0,1,1,1,1,1,1,1,0,0,1,1,1,1,1},
			{1,0,a,a,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,1},
			{1,B,a,a,0,0,0,0,0,0,0,0,C,0,0,7,0,b,0,1},
			{1,1,1,1,1,6,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
			{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		},
		//ステージ3-2
		{
			{1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,b,0,E,1,0,0,C,0,B,0,0,0,0,G,f,0,E,0,1},
			{1,1,1,1,1,0,0,1,1,1,1,1,1,7,7,1,1,1,1,1},
			{1,0,0,0,0,0,0,7,0,0,0,1,0,0,0,0,2,2,0,1},
			{1,D,0,0,0,0,0,7,G,9,b,1,0,0,0,0,2,2,0,1},
			{1,1,1,1,0,0,1,8,8,1,1,1,0,0,6,1,1,1,1,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,a,a,0,0,1},
			{1,3,0,0,0,0,0,0,0,0,F,0,C,0,0,a,a,0,5,1},
			{1,1,1,1,1,6,1,1,6,1,1,1,1,1,1,1,1,1,1,1},
			{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		},
		//ステージ3-3(ボス)
		{
			{1,0,g,0,0,0,0,0,0,0,0,0,0,0,0,0,0,g,0,1},
			{1,0,g,0,0,0,0,0,0,0,0,0,0,0,0,0,0,g,0,1},
			{1,0,g,0,0,0,0,0,0,0,0,0,0,0,0,0,0,g,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,k,k,0,0,0,0,0,0,0,0,0,0,0,0,0,0,k,k,1},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,C,0},
			{1,1,1,k,k,1,k,k,1,k,k,1,k,k,1,k,k,1,1,1},
			{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		},
		//ステージ4-1
		{
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,9,0,0,C,0,0,f,0,0,0,0,E,0,0,0,0,1},
			{1,8,8,1,1,1,1,1,1,1,7,7,1,1,1,1,0,0,0,1},
			{1,0,0,a,a,0,0,0,0,1,0,0,1,1,0,0,0,0,0,1},
			{1,0,0,a,a,0,0,0,0,1,0,0,1,1,E,0,0,0,0,1},
			{1,1,1,1,1,0,0,5,5,1,0,0,1,1,1,1,0,0,0,1},
			{1,0,0,0,0,0,0,1,1,1,0,0,1,1,1,0,0,0,0,1},
			{1,0,0,0,0,0,0,1,0,0,2,2,1,1,0,0,0,0,0,1},
			{1,3,0,A,0,0,C,1,0,0,2,2,1,1,B,0,0,B,D,1},
			{1,1,1,1,1,6,1,1,1,1,1,1,1,1,1,1,6,1,1,1},
			{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		},
		//ステージ4-2
		{
			{1,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,1},
			{1,0,b,0,C,0,0,1,c,0,1,B,0,0,0,0,0,d,0,1},
			{1,1,1,1,1,0,0,1,1,1,1,1,0,0,0,1,1,1,1,1},
			{1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1,0,2,2,1},
			{1,5,3,0,C,0,0,0,0,0,1,0,0,0,0,1,c,2,2,1},
			{1,1,1,1,1,0,0,0,0,5,1,F,0,0,0,1,1,1,1,1},
			{0,0,0,0,1,0,0,1,1,1,1,1,1,0,0,1,1,1,1,1},
			{0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,a,a,0,0,1},
			{d,0,F,E,1,0,F,0,0,0,1,b,0,0,0,a,a,0,A,1},
			{1,1,1,1,1,6,1,1,1,1,1,1,1,6,1,1,1,1,1,1},
			{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		},
		//ステージ4-3(ボス)
		{
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,3,0,0,0,0,0,0,D,0,0,0,0,0,0,0,0,0,0},
			{1,1,1,1,1,1,1,1,1,k,k,1,1,1,1,1,1,1,1,1},
			{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		},
	};

	int random[STAGE_HEIGHT][STAGE_WIDTH] = { 0 };
};

extern MAP g_map;
