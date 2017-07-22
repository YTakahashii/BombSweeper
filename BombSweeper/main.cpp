#include "DxLib.h"
#include "SceneMgr.h"
#include "Timer.h"
#include "resource.h"
#pragma warning(disable:4996)

int WINAPI WinMain(HINSTANCE,HINSTANCE,LPSTR,int){
	ChangeWindowMode(TRUE);
	SetGraphMode(1000,600,16);
	SetMainWindowText( "Bomb sweeper" );
	SetWindowIconID(IDI_ICON2);
	if( DxLib_Init() == -1 ) return -1;
	SetDrawScreen(DX_SCREEN_BACK);
	SceneMgr mgr;
	mgr.Init();
	Timer::lastcalltime = GetNowCount() & INT_MAX;
	ChangeVolumeSoundMem(1,SceneMgr::titlebgm);
	PlaySoundMem(SceneMgr::titlebgm,DX_PLAYTYPE_BACK);

	while( ScreenFlip()==0 && ProcessMessage()==0 && ClearDrawScreen()==0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0 ){
		int curtime = GetNowCount() & INT_MAX;
		int curinterval = curtime - Timer::lastcalltime;
		Timer::frametime = (float)(curinterval) / 1000.0f;
		mgr.Update();
		mgr.Draw();
		Timer::lastcalltime = curtime;
	}
	
	DxLib_End();
	return 0;
}

