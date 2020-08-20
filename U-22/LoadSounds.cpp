#include "DxLib.h"
#include "Sounds.h"

int LoadSounds(void)
{
	//�^�C�g��BGM
	if ((g_sounds.Title = LoadSoundMem("sounds/bgm_title.mp3")) == -1) return -1;
	//���[���h�OBGM
	if ((g_sounds.Title = LoadSoundMem("sounds/bgm_world1.mp3")) == -1) return -1;
	//���[���h�PBGM
	if ((g_sounds.Title = LoadSoundMem("sounds/bgm_world2.mp3")) == -1) return -1;
	//���[���h�QBGM
	if ((g_sounds.Title = LoadSoundMem("sounds/bgm_world3.mp3")) == -1) return -1;
	//���[���h�RBGM
	if ((g_sounds.Title = LoadSoundMem("sounds/bgm_world4.mp3")) == -1) return -1;
	//�{�XBGM
	if ((g_sounds.Title = LoadSoundMem("sounds/bgm_boss.mp3")) == -1) return -1;

	//����SE
	if ((g_sounds.Select = LoadSoundMem("sounds/decision1.mp3")) == -1) return -1;
	//�A�C�e���I��SE
	if ((g_sounds.SenTaku = LoadSoundMem("sounds/item01.mp3")) == -1) return -1;
	//����SE
	if ((g_sounds.Step = LoadSoundMem("sounds/asioto.mp3")) == -1) return -1;
	//�G���x�[�^SE
	if ((g_sounds.Eleverter = LoadSoundMem("sounds/elevator01.mp3")) == -1) return -1;
	//�j��A���eSE
	if ((g_sounds.Break = LoadSoundMem("sounds/hakai.mp3")) == -1) return -1;
	//�o�lSE
	if ((g_sounds.Spring = LoadSoundMem("sounds/bane.mp3")) == -1) return -1;
	//����SE
	if ((g_sounds.Fall = LoadSoundMem("sounds/rakka.mp3")) == -1) return -1;
	//����
	if ((g_sounds.Fire = LoadSoundMem("sounds/syoka.mp3")) == -1) return -1;
	//���[�v
	if ((g_sounds.Warp= LoadSoundMem("sounds/warp.mp3")) == -1) return -1;




	return 0;
}