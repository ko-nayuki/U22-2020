#pragma once
#include "DxLib.h"

//わしが使う要素

//PAD_INPUT_1...Aキー
//PAD_INPUT_2...Bキー

//シーケンスつなげる（セレクト画面を想像通りにする）→drawxboxを基準にドアに判定を作ってそこでボタン押すとそのステージに行けるようにする
//ゲームタイトル想像通りにする→タイトル貼るだけ
//ゲームクリア画面仕上げる
//ゲームオーバー画面、仕上げておく

//void StageInit();
//int StageObj(int Objimg);

struct StageInfo {
	int stage1x = 192;
	int stage1y = 576;
	int stage2x = 576;
	int stage3x = 768;
	int stage4x = 960;

	int Key = 0;		//セレクト画面でステージをロックするフラグ
	int Checkkey = 0;	//ちゃんとステージクリアしたかチェックするための変数
	int CheckCorect = 0;	//上と比較する
};

extern StageInfo g_Select;

//フェードイン・アウトに使う情報
void FeadOut();
void FeadIn();

struct FeadCode{
	int FeadFlg;		//フェードフラグ0でアウト,1でイン
	int InfoStg;		//ステージ切り替え情報
	int ClearFlg;		//クリア画面でどこに行くか 0でプレイ画面,1でセレクト画面
};

extern FeadCode Fead; 