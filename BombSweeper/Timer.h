#pragma once
#include "define.h"

class Timer{
private:
	float nowtime;
	int resulttime;
	bool timerused;
	int font, normalfont, largefont;
	int newrecpng;
	bool newrecord;
public:
	Timer();
	~Timer();
	static int lastcalltime;
	static float frametime;
	void NormalTimer();
	bool LimitTimer(int limittime);
	void setResultTime();
	void startTimer();
	void stopTimer();
	void SaveBestTime();
	void DrawScoreTime();
	void DrawBestOnly();
};
