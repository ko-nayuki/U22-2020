#include "DxLib.h"
#include "Sounds.h"

int LoadSounds(void)
{
	//タイトルBGM
	if ((g_sounds.Title = LoadSoundMem("sounds/bgm_title.mp3")) == -1) return -1;
	//ワールド０BGM
	if ((g_sounds.World0 = LoadSoundMem("sounds/bgm_world1.mp3")) == -1) return -1;
	//ワールド１BGM
	if ((g_sounds.World1 = LoadSoundMem("sounds/bgm_world2.mp3")) == -1) return -1;
	//ワールド２BGM
	if ((g_sounds.World2 = LoadSoundMem("sounds/bgm_world3.mp3")) == -1) return -1;
	//ワールド３BGM
	if ((g_sounds.World3 = LoadSoundMem("sounds/bgm_world4.mp3")) == -1) return -1;
	//ボスBGM
	if ((g_sounds.Boss = LoadSoundMem("sounds/bgm_boss.mp3")) == -1) return -1;
	//エンドBGM
	if ((g_sounds.End = LoadSoundMem("sounds/bgm_end.mp3")) == -1) return -1;

	//決定SE
	if ((g_sounds.Select = LoadSoundMem("sounds/decision1.mp3")) == -1) return -1;
	//アイテム選択SE
	if ((g_sounds.SenTaku = LoadSoundMem("sounds/item01.mp3")) == -1) return -1;
	//足音SE
	if ((g_sounds.Step = LoadSoundMem("sounds/asioto.mp3")) == -1) return -1;
	//エレベータSE
	if ((g_sounds.Eleverter = LoadSoundMem("sounds/elevator01.mp3")) == -1) return -1;
	//破壊、爆弾SE
	if ((g_sounds.Break = LoadSoundMem("sounds/hakai.mp3")) == -1) return -1;
	//バネSE
	if ((g_sounds.Spring = LoadSoundMem("sounds/bane.mp3")) == -1) return -1;
	//落下SE
	if ((g_sounds.Fall = LoadSoundMem("sounds/rakka.mp3")) == -1) return -1;
	//消火
	if ((g_sounds.Fire = LoadSoundMem("sounds/syoka.mp3")) == -1) return -1;
	//ワープ
	if ((g_sounds.Warp= LoadSoundMem("sounds/warp.mp3")) == -1) return -1;

	/**************/
	/* 音量の設定 */
	/**************/
	//タイトルBGM
	ChangeVolumeSoundMem(255 * 40 / 100, g_sounds.Title);
	//ワールド0BGM
	ChangeVolumeSoundMem(255 * 40 / 100, g_sounds.World0);
	//ワールド1BGM
	ChangeVolumeSoundMem(255 * 40 / 100, g_sounds.World1);
	//ワールド2BGM
	ChangeVolumeSoundMem(255 * 40 / 100, g_sounds.World2);
	//ワールド3BGM
	ChangeVolumeSoundMem(255 * 40 / 100, g_sounds.World3);
	//ボスBGM
	ChangeVolumeSoundMem(255 * 40 / 100, g_sounds.Boss);
	//エンドBGM
	ChangeVolumeSoundMem(255 * 40 / 100, g_sounds.End);

	//決定SE
	ChangeVolumeSoundMem(255 * 50 / 100, g_sounds.Select);
	//アイテム選択SE
	ChangeVolumeSoundMem(255 * 50 / 100, g_sounds.SenTaku);
	//エレベータSE
	ChangeVolumeSoundMem(255 * 50 / 100, g_sounds.Eleverter);
	//バネSE
	ChangeVolumeSoundMem(255 * 50 / 100, g_sounds.Spring);
	//消火
	ChangeVolumeSoundMem(255 * 60 / 100, g_sounds.Fire);
	//ワープ
	ChangeVolumeSoundMem(255 * 40 / 100, g_sounds.Warp);


	return 0;
}
