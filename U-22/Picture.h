//‰æ‘œ‚Ì•Ï”‚Æ‚©

#pragma once

int LoadPicture();

struct image {
	int sample[11];//0~9 ‰æ‘œ‚ª“ü‚Á‚Ä‚¢‚é”’l
	int gh[9];  //10~18
	int door[4]; //19~21
	
};

extern image g_img;
