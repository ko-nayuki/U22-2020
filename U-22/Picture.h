//�摜�̕ϐ��Ƃ�

#pragma once

int LoadPicture();

struct image {
	int MAP[5];			//�摜�������Ă��鐔�l
	int gh[9];			//player
	int door[4];		//�G���x�[�^
	int spring[3];		//�W�����v��
	int bookshelf[4];	//�{�I
	int smoke[8];		//��
	int kanzi[7];		//����
	int T_kanzi[4];		//�^�C�g���p����
	int marubatu[2];
	int gimKanzi[5];
	int itemBox;
	int wolf[7];		//boss1
	int thief[24];		//boss2
	int Cauldron;		//�劘
};

extern image g_img;
