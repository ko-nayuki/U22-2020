#pragma once
#include "DxLib.h"
#define STAGE 1
#define STAGE_HEIGHT 1124
#define STAGE_WIDTH 768
//#define HEIGHT 64
//#define WIDTH 64

int	g_StageData[STAGE][STAGE_HEIGHT][STAGE_WIDTH]{
	//チュートリアル（ステージ0)
	{
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,0,9,9},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,0,9,9},
		{0,0,0,0,0,0,0,0,0,0,0,9,9,9,9,9,9,9,9,9},
		{0,0,0,0,0,0,0,0,0,0,0,9,9,9,9,9,9,9,9,9},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,9,9},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,9,9},
		{0,0,0,0,0,2,2,0,0,0,0,0,0,0,0,0,0,0,9,9},
		{0,0,0,0,0,2,2,0,0,0,0,0,0,0,0,0,0,0,9,9},
		{0,0,0,0,0,2,2,0,0,2,2,0,0,0,0,0,0,0,9,9},
		{0,0,0,1,0,2,2,0,0,2,2,0,1,0,0,0,0,0,9,9},
		{9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9},
		{9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9},

	},
};