#pragma once
#include "DxLib.h"
#include "player.h"

#define ITEM_MAX 5		//�A�C�e���̍ő吔

void PlayerMove();

struct Player {
	//�ړ��W��
	int move = 1;

	// �ړ��W��
	int speed = 1;

	//�������Əc�����̃J�E���g���B
	int xcount = 0, ycount = 0;
	//�Y���p�ϐ�
	int ix = 0, iy = 0, result = 0;

	//x���W
	int px = 64, py = 592, y_prev = 0, y_temp = 0;

	//�W�����v���Ă邩�̃t���O�B
	bool jflag = false;

	//����
	int dir = 0;

	//�A�C�e��������
	int item[ITEM_MAX] = { 0 };
	int itemNo = 0;
	int itemSelect = 0;

	//�����X�s�[�h
	float fallSpeed = 0;
};

extern Player g_player;

//�L�[�擾�p�z��
extern char key[256];