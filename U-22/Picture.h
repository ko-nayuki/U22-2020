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
	int kanzi[6];		//����
	int marubatu[2];
	int itemBox;

};

extern image g_img;
