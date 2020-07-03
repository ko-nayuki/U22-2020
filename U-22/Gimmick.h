#pragma once
#include "DxLib.h"

#define GIMMICK_NUM 2	//�M�~�b�N��
#define KANZI_NUM 2		//�����̐�

void gimmickMove();
void gimmickDisp();
void gimmickInit();

enum {
	LIFT = 0,		//�G���x�[�^�[
	BREAK = 1		//�j��ł����

};

enum {//����
	K_NO = 0,		//����
	K_UE = 1,		//��
	K_SITA = 2		//��
};

struct Gimmick {
	int x;				//x���W
	int y;				//y���W
	int w;				//��
	int h;				//����
	bool moveFlg;		//�M�~�b�N�̋N���t���O
	bool moveFlg2;		//�M�~�b�N�̋N���t���O2
	float anime;		//�M�~�b�N�A�j���[�V����
};

extern Gimmick g_gimmick[GIMMICK_NUM];
