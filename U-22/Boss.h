#pragma once
#include "DxLib.h"

void bossMove();
void bossDisp();
void bossInit();

void wolfMove();
void thiefMove();

struct boss {
	float x;		//x���W
	float y;		//y���W
	int hp;			//�̗�
	int damageFlg;	//�_���[�W�t���O
	int attackFlg;	//�U���t���O
	float anime;	//�A�j���[�V����
	int count;		//���̍s���܂ł̎���

};

extern boss g_boss[4];//0 :BOSS_1, 1 :BOSS_2, 2 :BOSS_3_L, BOSS_3_R 