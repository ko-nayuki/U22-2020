#pragma once
int LoadSounds();

struct sounds {
	int Title;		//�^�C�g��BGM
	int World0;		//���[���h�PBGM
	int World1;		//���[���h�QBGM
	int World2;		//���[���h�RBGM
	int World3;		//���[���h�SBGM
	int Boss;		//�{�XBGM
	int End;		//�G���hBGM

	int Select;		//����SE
	int SenTaku;	//�A�C�e���I��SE
	int Step;		//����SE
	int Eleverter;	//�G���x�[�^SE
	int Break;		//�j��A���eSE
	int Spring;		//�o�lSE
	int Fall;		//����SE
	int Fire;		//����
	int Warp;		//���[�v

	int Damage;		//�_���[�W
	int Clear_SE;	//�N���ASE
	int Breath;		//�I�I�J�~�j�̑�
	int Arm;		//���l�̘r�̏Ռ�
};

extern sounds g_sounds;