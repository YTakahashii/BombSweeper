#pragma once
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include "define.h"
#include "click.h"
#include "BaseScene.h"

using namespace std;

class Field{
private:
	Click *click;
	//media用
	int mmaspng, maspng,zeropng,onepng,twopng,threepng,fourpng;
	int fivepng,sixpng,sevenpng,eightpng,flagpng,bombpng,bomb2png,bomb3png, newrecpng;
	int normalfont;
	int chainmp3, explodemp3;
	//内部処理用
	int row, col, bombnum,stx, sty, width, height, clearnum;
	int isopened, remainderbomb, removalnum, clickcnt, remainderclick;
	bool l_mousepressed;
	bool r_mousepressed;
	int lastr, lastc;
	bool clear, failure, newrecord;
public:
	vector<int> calc;//地雷計算用
	vector<vector<MineField>> field;
	Field(int MAXROW, int MAXCOL, int MAXBOMB, int CLEARNUM, int STX, int STY, int SQUARE_WIDTH, int SQUARE_HEIGHT, int TIME, int CLICKMAX);
	~Field();
	void MineOpen(int mx, int my);
	void SetFlag(int mx, int my);
	void DrawField();
	void Init();
	void Method();
	void Clear();
	void Failure();
	void AllOpen();
	void BombShuffle();
	void CheckClick();
	void LightCursor(int mx, int my);
	void OpenChain(int openr, int openc);
	bool CheckClear();
	bool CheckFailure();
	void DrawRemainderBomb();
	void ClearAnswerShow();
	void FailureAnswerShow();
	//Remove Mode
	void RemoveOpen(int mx, int my);
	void RemoveMethod();
	void RemoveClear();
	void RemoveFailure();
	void RemoveModeCheckClick();
	bool RemoveModeCheckClear();
	bool RemoveModeCheckFailure();
	void DrawRemainderClick();
	void SaveClickBestScore();
	void DrawClickScore();
	void DrawClickBestOnly();
	void RemoveAnswerShow();
};
