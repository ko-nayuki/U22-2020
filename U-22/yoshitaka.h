#pragma once
#include "DxLib.h"

//�킵���g���v�f

//PAD_INPUT_1...A�L�[
//PAD_INPUT_2...B�L�[

//�V�[�P���X�Ȃ���i�Z���N�g��ʂ�z���ʂ�ɂ���j��drawxbox����Ƀh�A�ɔ��������Ă����Ń{�^�������Ƃ��̃X�e�[�W�ɍs����悤�ɂ���
//�Q�[���^�C�g���z���ʂ�ɂ��遨�^�C�g���\�邾��
//�Q�[���N���A��ʎd�グ��
//�Q�[���I�[�o�[��ʁA�d�グ�Ă���

//void StageInit();
//int StageObj(int Objimg);

struct StageInfo {
	int stage1x = 192;
	int stage1y = 576;
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