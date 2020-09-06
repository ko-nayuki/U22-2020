#pragma once
#include "DxLib.h"

//わしが使う要素

//PAD_INPUT_1...Aキー
//PAD_INPUT_2...Bキー

//g_img.T_kanzi[0]・・・始
//g_img.T_kanzi[1]・・・開
//g_img.T_kanzi[2]・・・終
//g_img.T_kanzi[3]・・・了

//void StageInit();
//int StageObj(int Objimg);

struct StageInfo {
	//セレクトの扉の座標
	int stage1x = 192;
	int stage2x = 576;
	int stage3x = 768;
	int stage4x = 960;

	int PlayerStay;

	int CursorFlg = 0;	//カーソルを元に戻す
	int Key = 0;		//セレクト画面でステージをロックするフラグ
	int Checkkey = 0;	//ちゃんとステージクリアしたかチェックするための変数
	int CheckCorect = 0;	//上と比較する
};

extern StageInfo g_Select;

//フェードイン・アウトに使う情報
void FeadOut();
void FeadIn();

struct FeadCode{
	int FeadCredit;		//クレジットに飛ばす
	int FeadFlg;		//フェードフラグ0でアウト,1でイン
	int InfoStg;		//ステージ切り替え情報
	int ClearFlg;		//クリア画面でどこに行くか 0でプレイ画面,1でセレクト画面
	int OverFlg;		//ゲームオーバー画面でどこ行くか　0でプレイ画面,1でタイトル画面
	int EndFlg;			//～ゲームエンドでどこへ行く～
};

extern FeadCode Fead; 