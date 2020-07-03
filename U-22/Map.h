#pragma once
#include "DxLib.h"
#define STAGE 1
#define STAGE_HEIGHT 12		//画面 幅
#define STAGE_WIDTH 20		//画面 高さ
#define CHIPSIZE 64			//マップチップサイズ

void SelectMAPDisp();
void StageDisp();
void StageInit();
void BackStageDisp();

enum {//マップチップ番号
	AIR = 0,		//何もなし
	BLOCK = 1,		//地面
	GOAL = 2,		//ゴール
	BOOK = 3,		//本
	GIM_1 = 5,		//エレベーター

	A = 10,			//上
	B = 11,			//下
};

struct MAP {

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
	  { 0,2,2,0,0,2,2,0,0,2,2,0,0,2,2,0,0,2,2,0 },
	  { 0,2,2,0,0,2,2,0,0,2,2,0,0,2,2,0,0,2,2,0 },
	  { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
	  { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 }
	};

	int playStage[STAGE_HEIGHT][STAGE_WIDTH];

	int stageData[STAGE][STAGE_HEIGHT][STAGE_WIDTH] =
	{
		//ステージ1-1
		{
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,0,1,1},
			{1,0,B,0,0,0,0,0,0,0,0,0,0,0,0,2,2,0,1,1},
			{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
			{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
			{1,0,0,0,0,A,B,A,0,0,5,0,0,A,0,0,A,B,1,1},
			{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
			{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		}
	};

	int random[STAGE_HEIGHT][STAGE_WIDTH] = { 0 };
};

extern MAP g_map;
