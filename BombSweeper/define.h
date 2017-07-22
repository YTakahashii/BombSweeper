#pragma once

const int E_MAXROW = 9, E_MAXCOL = 9;
const int M_MAXROW = 16, M_MAXCOL = 16;
const int EX_MAXROW = 16, EX_MAXCOL = 30;
const int E_MAXBOMB = 10, M_MAXBOMB = 40, EX_MAXBOMB = 99;
const int E_CLEARNUM = E_MAXROW * E_MAXCOL - E_MAXBOMB;
const int M_CLEARNUM = M_MAXROW * M_MAXCOL - M_MAXBOMB;
const int EX_CLEARNUM = EX_MAXROW * EX_MAXCOL - EX_MAXBOMB;
const int E_TIME = 60, M_TIME = 120, EX_TIME = 300;
const int L_SQUARE_WIDTH = 39; //easy—p
const int L_SQUARE_HEIGHT = 39;
const int S_SQUARE_WIDTH = 27; //medium, expert—p
const int S_SQUARE_HEIGHT = 27;
const int E_STX = 300, E_STY = 150;
const int M_STX = 250, M_STY = 150;
const int EX_STX = 80,  EX_STY = 130;
const int E_CLICKMAX = 20, M_CLICKMAX = 100, EX_CLICKMAX = 200;

//const int stx = 80;
//const int sty = 130;

struct MineField{
	int arroundbomb;
	bool isOpened;
	bool isFlag;
	bool isPointed;
};