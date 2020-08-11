#pragma once
#include "DxLib.h"

//わしが使う要素

//void StageInit();
//int StageObj(int Objimg);

struct StageInfo {
	const int HEIGHT = 64;
	const int WIDTH = 64;
};

//フェードイン・アウトに使う情報
void FeadOut();
void FeadIn();

struct FeadCode{
	int FeadFlg;		//フェードフラグ0でアウト,1でイン
	int InfoStg;		//ステージ切り替え情報
	int ClearFlg;		//クリア画面でどこに行くか 0でプレイ画面,1でセレクト画面
};

extern FeadCode Fead;
