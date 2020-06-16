#pragma once

int LoadPicture();

struct image {
	int sample;
	int gh[9];
};

extern image g_img;