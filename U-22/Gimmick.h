#pragma once
#include "DxLib.h"

#define GIMMICK_NUM 10	//�M�~�b�N�̐�
#define KANZI_NUM 7		//�����̐�

#define GRAVITY          (0.2F)		// �d��
#define JUMP_POWER       (14.0F)	// �W�����v��̃W�����v��

void gimmickMove();
void gimmickDisp();
void gimmickInit();

void smoke(int smokeX, int smokeY);		//��

void liftMove();	//�G���x�[�^�[
void boundMove();	//�W�����v��
void breakMove();	//�j��ł����
void dropMove();	//�����M�~�b�N
void fireMove();	//��
void warpMove();	//���[�v
void bombMove();	//���e

enum {//�M�~�b�N
	LIFT = 0,		//�G���x�[�^�[
	BOUND = 1,		//�W�����v��
	BREAK = 2,		//�j��ł����
	DROP = 3,		//�����M�~�b�N
	FIRE = 4,		//��
	WARP_A = 5,		//���[�vA�n�_
	WARP_B = 6,		//���[�vB�n�_
	BOMB = 7,		//���e
};

enum {//����
	K_NO = 0,		//����
	K_UE = 1,		//��[����]
	K_SITA = 2,		//��[����]
	K_TIKARA = 3,	//��[������]
	K_HA = 4,		//�j[��]
	K_SHOU = 5,		//��[���傤]
	K_DOU = 6,		//��[�ǂ�]
	K_BAKU = 7,		//��[�΂�]
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
