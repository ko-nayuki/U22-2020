//�摜�̕ϐ��Ƃ�

#pragma once

int LoadPicture();

struct image {
	int MAP[12];			//�摜�������Ă��鐔�l
	int gh[9];			//player
	int door[4];		//�G���x�[�^
	int spring[3];		//�W�����v��
	int bookshelf[4];	//�{�I
	int smoke[8];		//��
	int kanzi[7];		//����
	int Title;			//�^�C�g��
	int T_kanzi[6];		//�^�C�g���p����
	int Button;			//B�{�^��
	int goal[5];
	int marubatu[2];
	int gimKanzi[6];
	int Teki[5];        //�G
	int hp;             //player hp
	int itemBox;
	int wolf[9];		//boss1
	int thief[24];		//boss2
	int Colossus[6];    //boss3
	int fire[2];		//��
	int drop;			//�����Ŕ�
	int crack;			//�q�r����u���b�N
	int gear[2];		//��]����
	int warp;			//���[�v
	int bomb;
	int Cauldron;		//�劘
	int trampoline[2];	//�g�����|����
	int wind;

	int BombEff;

	int KanBan[2];		//�Ŕ摜

	int stage3;
	int stage4;
	int SelectBook[3];
	int BookAnime[6];
	int world_4book[6];

	int Curtain;		//�Z���N�g��ʂ̖�
	int RetryButon;		//���g���C�{�^��
	int RetryText;		//���g���C�e�L�X�g
	int ReturnButton;	//�Z���N�g�ɖ߂邽�߂̃{�^��
	int ReturnText;		//�Z���N�g�e�L�X�g
	int ClearText;		//�N���A����
	int NextText;		//NEXT����
	int GameOver;		//�I�[�o�[����
	int OverText[2];	//�Q�[���I�[�o�[�ł̑I����
	int Triger[2];		//�g���K�[�\��
	int End;		//�Ō�̈ꖇ�G
};

extern image g_img;
