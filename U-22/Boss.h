#pragma once
#include "DxLib.h"

void bossMove();
void bossDisp();
void bossInit();

void wolfMove();

struct boss {
	int x;			//x���W
	int y;			//y���W
	int hp;			//�̗�
	int damageFlg;	//�_���[�W�t���O
	int attackFlg;	//�U���t���O
	int anime;		//�A�j���[�V����
	int count;		//���̍s���܂ł̎���

};

extern boss g_boss[4];