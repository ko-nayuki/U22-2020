#pragma once
#include "DxLib.h"

//�킵���g���v�f

//void StageInit();
//int StageObj(int Objimg);

struct StageInfo {
	const int HEIGHT = 64;
	const int WIDTH = 64;
};

//�t�F�[�h�C���E�A�E�g�Ɏg�����
void FeadOut();
void FeadIn();

struct FeadCode{
	int FeadFlg;		//�t�F�[�h�t���O0�ŃA�E�g,1�ŃC��
	int InfoStg;		//�X�e�[�W�؂�ւ����
	int ClearFlg;		//�N���A��ʂłǂ��ɍs���� 0�Ńv���C���,1�ŃZ���N�g���
};

extern FeadCode Fead;
