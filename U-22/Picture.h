//�摜�̕ϐ��Ƃ�

#pragma once

int LoadPicture();

struct image {
	int sample[11];//0~9 �摜�������Ă��鐔�l
	int gh[9];  //10~18
	int door[4]; //19~21
	int bookshelf[4];
	
};

extern image g_img;
