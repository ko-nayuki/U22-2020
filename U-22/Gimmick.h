#pragma once
#include "DxLib.h"

#define GIMMICK_NUM 4	//�M�~�b�N�̖��O
#define KANZI_NUM 3		//�����̐�

#define G                (0.2F)		// �d��
#define JUMP_POWER       (14.0F)	// �W�����v��̃W�����v��

void gimmickMove();
void gimmickDisp();
void gimmickInit();

void liftMove();	//�G���x�[�^�[
void boundMove();	//�W�����v��
void breakMove();	//�j��ł����
void dropMove();	//�����M�~�b�N

enum {//�M�~�b�N
	LIFT = 0,		//�G���x�[�^�[
	BOUND = 1,		//�W�����v��
	BREAK = 2,		//�j��ł����
	DROP = 3		//�����M�~�b�N
};

enum {//����
	K_NO = 0,		//����
	K_UE = 1,		//��[����]
	K_SITA = 2,		//��[����]
	K_TIKARA = 3,	//��[������]
	K_HA = 4,		//�j[��]
};

struct Gimmick {
	int x;				//x���W
	int y;				//y���W
	int w;				//��
	int h;				//����
	bool ONFlg;			//�M�~�b�N�̍쓮�t���O
	bool moveFlg;		//�M�~�b�N�̃A�j���[�V�����N���t���O
	bool moveFlg2;		//�M�~�b�N�̃A�j���[�V�����N���t���O2
	float anime;		//�M�~�b�N�A�j���[�V����
	//float speed;		//�W�����v�p

	int tikara = 0;
};

extern Gimmick g_gimmick[GIMMICK_NUM];

