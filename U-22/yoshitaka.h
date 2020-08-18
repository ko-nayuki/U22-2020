#pragma once
#include "DxLib.h"

//わしが使う要素

//PAD_INPUT_1...Aキー
//PAD_INPUT_2...Bキー

//g_img.T_kanzi[0]・・・始
//g_img.T_kanzi[1]・・・開
//g_img.T_kanzi[2]・・・終
//g_img.T_kanzi[3]・・・了


//ゲームタイトル想像通りにする→タイトル貼る
//ゲームクリア画面仕上げる→おおよそ完成、確認するだけ
//ゲームオーバー画面、仕上げておく→文字が完成し次第、作り上げる
//音を実装する←これが最優先

//void StageInit();
//int StageObj(int Objimg);

struct StageInfo {
	int stage1x = 192;
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