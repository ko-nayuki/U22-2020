#pragma once
#include "DxLib.h"

//�킵���g���v�f

//PAD_INPUT_1...A�L�[
//PAD_INPUT_2...B�L�[

//g_img.T_kanzi[0]�E�E�E�n
//g_img.T_kanzi[1]�E�E�E�J
//g_img.T_kanzi[2]�E�E�E�I
//g_img.T_kanzi[3]�E�E�E��


//�Q�[���^�C�g���z���ʂ�ɂ��遨�^�C�g���\��
//�Q�[���N���A��ʎd�グ�遨�����悻�����A�m�F���邾��
//�Q�[���I�[�o�[��ʁA�d�グ�Ă���������������������A���グ��
//�����������適���ꂪ�ŗD��

//void StageInit();
//int StageObj(int Objimg);

struct StageInfo {
	int stage1x = 192;
	int stage2x = 576;
	int stage3x = 768;
	int stage4x = 960;

	int Key = 0;		//�Z���N�g��ʂŃX�e�[�W�����b�N����t���O
	int Checkkey = 0;	//�����ƃX�e�[�W�N���A�������`�F�b�N���邽�߂̕ϐ�
	int CheckCorect = 0;	//��Ɣ�r����
};

extern StageInfo g_Select;

//�t�F�[�h�C���E�A�E�g�Ɏg�����
void FeadOut();
void FeadIn();

struct FeadCode{
	int FeadFlg;		//�t�F�[�h�t���O0�ŃA�E�g,1�ŃC��
	int InfoStg;		//�X�e�[�W�؂�ւ����
	int ClearFlg;		//�N���A��ʂłǂ��ɍs���� 0�Ńv���C���,1�ŃZ���N�g���
};

extern FeadCode Fead; 