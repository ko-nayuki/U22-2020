//�摜�̕ϐ��Ƃ�

#pragma once

int LoadPicture();

struct image {
	int MAP[5];//�摜�������Ă��鐔�l
	int gh[9];  //player
	int door[4]; //�G���x�[�^
	int bookshelf[4];//�{�I
	int kanzi[5];//����
	int itemBox;
};

extern image g_img;
