#pragma once
#include "DxLib.h"

//�킵���g���v�f

//PAD_INPUT_1...A�L�[
//PAD_INPUT_2...B�L�[

//g_img.T_kanzi[0]�E�E�E�n
//g_img.T_kanzi[1]�E�E�E�J
//g_img.T_kanzi[2]�E�E�E�I
//g_img.T_kanzi[3]�E�E�E��

//����Ȃ���
//�^�C�g��(OK)�E�Z���N�g�E�N���A��ʁE�v���C��ʁE�{�X�i���]�T�������������邩�H�j�E�^�C�g���p���艹

//���̎���
//�����t�F�[�h�A�E�g�����Z����(���Z�u�����h) ( SetDrawBlendMode ������DX_BLENDMODE_ADD ) �摜�ɂ����g�p�ł��Ȃ��A�����搶�ɕ���

//�����������遨�o�O�C���I���������|����

//void StageInit();
//int StageObj(int Objimg);

struct StageInfo {
	int stage1x = 192;
	int stage2x = 576;
	int stage3x = 768;
	int stage4x = 960;

	int CursorFlg = 0;
	int Key = 0;		//�Z���N�g��ʂŃX�e�[�W�����b�N����t���O
	int Checkkey = 0;	//�����ƃX�e�[�W�N���A�������`�F�b�N���邽�߂̕ϐ�
	int CheckCorect = 0;	//��Ɣ�r����
};

extern StageInfo g_Select;

//�t�F�[�h�C���E�A�E�g�Ɏg�����
void FeadOut();
void FeadIn();

struct FeadCode{
	int FeadCredit;		//�N���W�b�g�ɔ�΂�
	int FeadFlg;		//�t�F�[�h�t���O0�ŃA�E�g,1�ŃC��
	int InfoStg;		//�X�e�[�W�؂�ւ����
	int ClearFlg;		//�N���A��ʂłǂ��ɍs���� 0�Ńv���C���,1�ŃZ���N�g���
	int OverFlg;		//�Q�[���I�[�o�[��ʂłǂ��s�����@0�Ńv���C���,1�Ń^�C�g�����
	int EndFlg;			//�`�Q�[���G���h�łǂ��֍s���`
};

extern FeadCode Fead; 