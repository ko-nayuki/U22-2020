#include "DxLib.h"
#include "Picture.h"

//�摜�����[�h����

int LoadPicture(){
	if (LoadDivGraph("images/sample5.png", 12, 3, 4, 64, 64, g_img.MAP) == -1) return -1;					//�摜�`�b�v
	//if((LoadDivGraph("images/Player.png", 9, 3, 3, 64, 64, g_img.gh)) == -1) return -1;							//�v���C���[�ϐ�
	if ((LoadDivGraph("images/Door.png", 3, 3, 3, 64, 64, g_img.door)) == -1) return -1;							//�h�A�摜�ϐ�
	if ((g_img.spring[0] = LoadGraph("images/Bane.png")) == -1) return -1;
	if ((g_img.spring[1] = LoadGraph("images/Bane2.png")) == -1)return -1;
	if ((g_img.spring[2] = LoadGraph("images/Bane3.png")) == -1)return -1;
	//if ((LoadDivGraph("images/book.png", 1, 1, 1, 64, 64, g_img.book)) == -1)return -1;	 //�{�摜�ϐ�
	//if ((g_img.MAP[3] = LoadGraph("images/book.png")) == -1) return -1;						//�v���C���[�ϐ�
	if ((LoadDivGraph("images/bookshelf.png", 4, 2, 2, 64, 64, g_img.bookshelf)) == -1) return -1;
	if ((LoadDivGraph("images/Player2.png", 6, 3, 2, 64, 64, g_img.gh)) == -1) return -1;		//�v���C���[�ϐ�
	//�M�~�b�N����
	if ((g_img.kanzi[0] = LoadGraph("images/maruzyo.png")) == -1) return -1;
	if ((g_img.kanzi[1] = LoadGraph("images/maruge.png")) == -1) return -1;
	if ((g_img.kanzi[2] = LoadGraph("images/maruchikara.png")) == -1) return -1;
	if ((g_img.kanzi[3] = LoadGraph("images/maruha.png")) == -1) return -1;
	if ((g_img.kanzi[4] = LoadGraph("images/marukesi.png")) == -1) return -1;
	if ((g_img.kanzi[5] = LoadGraph("images/marudou.png")) == -1) return -1;
	if ((g_img.kanzi[6] = LoadGraph("images/marubaku.png")) == -1) return -1;
	//�^�C�g������
	if ((g_img.Title = LoadGraph("images/title01.png")) == -1) return -1;
	if ((g_img.T_kanzi[0] = LoadGraph("images/title_start01.png")) == -1) return -1;
	if ((g_img.T_kanzi[1] = LoadGraph("images/title_start02.png")) == -1) return -1;
	if ((g_img.T_kanzi[2] = LoadGraph("images/title_end01.png")) == -1) return -1;
	if ((g_img.T_kanzi[3] = LoadGraph("images/title_end02.png")) == -1) return -1;
	if ((g_img.T_kanzi[4] = LoadGraph("images/kyo.png")) == -1) return -1;
	if ((g_img.T_kanzi[5] = LoadGraph("images/ryoku.png")) == -1) return -1;
	//���g���C�E�Z���N�g�Ŏg������
	if ((g_img.RetryButon = LoadGraph("images/Ybutton01.png")) == -1) return -1;
	if ((g_img.RetryText = LoadGraph("images/retry.png")) == -1) return -1;
	if ((g_img.ReturnButton = LoadGraph("images/Xbutton01.png")) == -1) return -1;
	if ((g_img.ReturnText = LoadGraph("images/select (1).png")) == -1) return -1;

	//�N���A����
	if ((g_img.ClearText = LoadGraph("images/stageclear.png")) == -1) return -1;
	if ((g_img.NextText = LoadGraph("images/next01.png")) == -1) return -1;
	if ((g_img.End = LoadGraph("images/EndingScnene.png")) == -1) return -1;
	//�Q�[���I�[�o�[���
	if ((g_img.GameOver = LoadGraph("images/gameover.png")) == -1) return -1;
	if ((g_img.OverText[0] = LoadGraph("images/backtitle.png")) == -1) return -1;
	if ((g_img.OverText[1] = LoadGraph("images/replay.png")) == -1) return -1;
	//�g���K�[�\��
	if ((g_img.Triger[0] = LoadGraph("images/Rbutton01.png")) == -1) return -1;	//R
	if ((g_img.Triger[1] = LoadGraph("images/Lbutton01.png")) == -1) return -1;	//L

	//�Z���N�g��ʂ̖�
	if ((g_img.Curtain = LoadGraph("images/Select.png")) == -1)return -1;
	//���e�G�t�F�N�g
	if ((g_img.BombEff = LoadGraph("images/Bomb_eff.png")) == -1)return -1;

	//�Ŕ摜
	if ((g_img.KanBan[0] = LoadGraph("images/kanban.png")) == -1)return -1;
	if ((g_img.KanBan[1] = LoadGraph("images/board.png")) == -1)return -1;


	//�G
	if ((g_img.Teki[1] = LoadGraph("images/Cone.png")) == -1)return -1;
	if ((g_img.Teki[2] = LoadGraph("images/Cone2.png")) == -1)return -1;
	if ((g_img.Teki[3] = LoadGraph("images/Cone3.png")) == -1)return -1;
	if ((g_img.Teki[4] = LoadGraph("images/Cone4.png")) == -1)return -1;

	//player hp
	if ((g_img.hp = LoadGraph("images/heart01.png")) == -1)return -1;

	if ((g_img.itemBox = LoadGraph("images/itembox.png")) == -1) return -1;
	if ((g_img.Button = LoadGraph("images/Bbutton01.png")) == -1)return -1;
	if (LoadDivGraph("images/GOALBOOK.png", 5, 3, 2, 128, 128, g_img.goal) == -1) return -1;
	if (LoadDivGraph("images/smoke.png", 8, 8, 1, 64, 64, g_img.smoke) == -1) return -1;
	if (LoadDivGraph("images/marubatu.png", 2, 2, 1, 64, 64, g_img.marubatu) == -1) return -1;
	if (LoadDivGraph("images/gimmick_kanji.png", 6, 6, 1, 64, 64, g_img.gimKanzi) == -1) return -1;
	if (LoadDivGraph("images/wolf.png", 9, 9, 1, 64, 128, g_img.wolf) == -1) return -1;				//boss1
	if (LoadDivGraph("images/BossThief.png", 24, 8, 3, 64, 128, g_img.thief) == -1) return -1;		//boss2
	if (LoadDivGraph("images/BOSS3HAND.png", 6, 3, 2, 384, 256, g_img.Colossus) == -1) return -1;   //boss3
	if (LoadDivGraph("images/GLM.png", 3, 3, 1, 448, 256, g_img.GLM) == -1)return -1;               //boss3head
	if ((g_img.Cauldron = LoadGraph("images/Cauldron.png")) == -1) return -1;
	if ((g_img.trampoline[0] = LoadGraph("images/trampoline0.png")) == -1) return -1;
	if ((g_img.trampoline[1] = LoadGraph("images/trampoline.png")) == -1) return -1;
	if ((g_img.fire[0] = LoadGraph("images/flame.png")) == -1) return -1;
	if ((g_img.fire[1] = LoadGraph("images/flame1.png")) == -1) return -1;
	if ((g_img.drop = LoadGraph("images/Stage2Swich.png")) == -1) return -1;
	if ((g_img.crack = LoadGraph("images/Stege1Blockbreak0.png")) == -1) return -1;
	if (LoadDivGraph("images/warpzone.png", 3, 3, 1, 64, 64, g_img.warp) == -1) return -1;
	if ((g_img.bomb = LoadGraph("images/bomb.png")) == -1) return -1;
	if (LoadDivGraph("images/RYuka0.png", 2, 2, 1, 64, 64, g_img.gear) == -1) return -1;
	if (LoadDivGraph("images/SelectBooks.png", 3, 3, 1, 128, 128, g_img.SelectBook) == -1) return -1;
	if (LoadDivGraph("images/SelectBookO3.png", 6, 3, 2, 256, 128, g_img.world_4book) == -1) return -1;
	if (LoadDivGraph("images/SelectBook1.png", 6, 3, 2, 256, 128, g_img.world_3book) == -1) return -1;
	if (LoadDivGraph("images/SelectBook3.png", 6, 3, 2, 256, 128, g_img.world_2book) == -1) return -1;
	
	if (LoadDivGraph("images/SCBook.png", 6, 3, 2, 256, 128, g_img.BookAnime) == -1) return -1;

	if ((g_img.stage3 = LoadGraph("images/Stage3.png")) == -1) return -1;
	if ((g_img.stage4 = LoadGraph("images/Stage4.png")) == -1) return -1;
	if ((g_img.boss3_back = LoadGraph("images/BossField3.png")) == -1) return -1;
	if ((g_img.wind = LoadGraph("images/TKaze.png")) == -1) return -1;
	return 0;
}