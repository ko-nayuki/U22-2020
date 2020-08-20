#pragma once
int LoadSounds();

struct sounds {
	int Title;		//タイトルBGM
	int World0;		//ワールド１BGM
	int World1;		//ワールド２BGM
	int World2;		//ワールド３BGM
	int World3;		//ワールド４BGM

	int Select;		//決定SE
	int SenTaku;	//アイテム選択SE
	int Step;		//足音SE
	int Eleverter;	//エレベータSE
	int Break;		//破壊、爆弾SE
	int Spring;		//バネSE
	int Fall;		//落下SE
	int Fire;		//消火
	int Warp;		//ワープ
};

extern sounds g_sounds;