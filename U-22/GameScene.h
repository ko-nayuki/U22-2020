#pragma once
#include "DxLib.h"

extern int g_gameScene;	// ゲームシーン管理

enum {	// ゲームシーン
	GAME_TITLE,						// ゲームタイトル
	GAME_SELECT,					// ゲームセレクト
	GAME_PLAY,						// ゲームプレイ
	GAME_OVER,						// ゲームオーバー
	GAME_CLEAR,						// ゲームクリア
	GAME_END = 99,					// ゲーム終了
};
