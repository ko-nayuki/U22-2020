#include "DxLib.h"
#include "player.h"

//プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(TRUE);

	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}



	//画像読み込み
	LoadDivGraph("images/P2.png", 9, 3, 3, 60, 60, gh);



	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0 && GetHitKeyStateAll(key) == 0) {

		if (key[KEY_INPUT_LEFT] == 1 || key[KEY_INPUT_RIGHT] == 1) {

			if (key[KEY_INPUT_UP] == 1 || key[KEY_INPUT_DOWN] == 1) {
				//移動係数を０．７１に設定
				move = 0.71f;
			}
			else {
				//斜めじゃなければ１．０に設定
				move = 1.0f;
			}
		}
		else if (key[KEY_INPUT_UP] == 1 || key[KEY_INPUT_DOWN] == 1) {
			move = 1.0f;
		}


		if (key[KEY_INPUT_LEFT] == 1) {
			x -= (int)4 * move;
		}
		if (key[KEY_INPUT_RIGHT] == 1) {
			x += (int)4 * move;

		}
		//画面移動制御

		if (x + 49 > 640)
			x = 640 - 49;
		if (x < 0)
			x = 0;

		DrawFormatString(0, 0, 0xffffff, "xc%d", xcount);
		DrawFormatString(0, 20, 0xffffff, "yc%d", ycount);
		DrawFormatString(0, 40, 0xffffff, "re%d", result);
		DrawFormatString(0, 60, 0xffffff, "dir%d", dir);
		DrawFormatString(0, 80, 0xffffff, "x%d", x);
		DrawFormatString(0, 100, 0xffffff, "y%d", y);

		//ジャンプ処理

		if (jflag == true) {
			y_temp = y;
			y += (y - y_prev) + 1;
			y_prev = y_temp;
			if (y == 420) {
				jflag = false;
				if (dir == 0) {
					result = 0;
				}
				if (dir == 1) {
					result = 3;
				}
			}
		}

		if (key[KEY_INPUT_SPACE] == 1 && jflag == false) {
			jflag = true;
			y_prev = y;
			y = y - 15;

		}

		if (key[KEY_INPUT_LEFT] == 1) {
			if (xcount > 0)
				xcount = 0;
			ycount = 0;
			--xcount;
			dir = 1;
		}
		if (key[KEY_INPUT_RIGHT] == 1) {
			if (xcount < 0)
				xcount = 0;
			ycount = 0;
			++xcount;
			dir = 0;
		}

		if (key[KEY_INPUT_SPACE] == 1 && dir == 0) {
			if (ycount < 0)
				ycount = 0;
			++ycount;

		}

		if (key[KEY_INPUT_SPACE] == 1 && dir == 1) {
			if (ycount > 0)
				ycount = 0;
			--ycount;

		}


		//カウント数から添字を求める。
		ix = abs(xcount) % 30 / 10;
		iy = abs(ycount) % 30 / 10;


		///xカウントがプラスなら右向きなので1行目の先頭添字番号を足す。
		if (xcount > 0) {
			result = ix;
		}
		else if (xcount < 0) {
			//xカウントがマイナスなら左向きなので、2行目の先頭添字番号を足す。
			ix += 3;
			result = ix;
		}

		///yカウントがプラスなら上右向きなので3行目の先頭添字番号を足す。
		if (ycount == 1) {
			iy += 6;
			result = iy;

		}
		else if (ycount == -1) {
			//yカウントがマイナスなら上左向きなので、4行目の先頭添字番号を足す。
			iy += 7;
			result = iy;

		}

		DrawGraph(x, y, gh[result], TRUE);


		//押されてなければカウントをゼロにする。
		if (key[KEY_INPUT_LEFT] != 1 && key[KEY_INPUT_RIGHT] != 1) {
			xcount = 0;
			ycount = 0;
		}

		if (key[KEY_INPUT_ESCAPE] == 1) {

			break;
		}

	}

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}