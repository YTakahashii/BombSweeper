#include "Timer.h"
#include "BaseScene.h"
#include "DxLib.h"
#include <cstdio>

int Timer::lastcalltime;
float Timer::frametime;

Timer::Timer()
{
	Timer::lastcalltime = 0;
	Timer::frametime = 0;
	nowtime = 0;
	resulttime = 0;
	normalfont = CreateFontToHandle( "���C���I",32,1, DX_FONTTYPE_ANTIALIASING );
	largefont = CreateFontToHandle( "���C���I",48,1, DX_FONTTYPE_ANTIALIASING );
	timerused = false;
	newrecord = false;
	newrecpng = LoadGraph("./media/pic/newrecord.png");
}

Timer::~Timer()
{

}

void Timer::NormalTimer()
{
	char buf[32];
	sprintf_s(buf,32,"%d",(int)nowtime);
	//DrawString(100,440,buf,GetColor(0,0,0));
	DrawStringToHandle(360,80,buf,GetColor(255,255,255),normalfont,1);
	if(timerused){
		nowtime += Timer::frametime;
	}
}

bool Timer::LimitTimer(int limittime)
{
	char buf[32],buf2[32];
	int time = limittime - (int)nowtime;
	sprintf_s(buf,32,"%d", time);
	sprintf_s(buf2,32,"%d",limittime);
	DrawStringToHandle(360,80,buf,GetColor(255,255,255),normalfont,1);
	DrawStringToHandle(420,80,"/",GetColor(255,255,255),normalfont,1);
	DrawStringToHandle(440,80,buf2,GetColor(255,255,255),normalfont,1);
	if(timerused){
		nowtime += Timer::frametime;
	}
	if(nowtime <=0) nowtime = 0;
	if(time <= 0) return true;
	else return false;
}

void Timer::setResultTime()
{
	resulttime = (int)nowtime;
}

void Timer::startTimer()
{
	timerused = true;
}

void Timer::stopTimer()
{
	timerused = false;
	resulttime = (int)nowtime;
}

void Timer::SaveBestTime()
{
	int bestscore;
	FILE *wfp;
	FILE *rfp;
	
	/*��ɑO��̃X�R�A��ǂݍ���*/
	switch(nowScene){
	case eScene_Standard:
		switch(nowLevel){
		case eLv_Easy:
			rfp = fopen("./score/easy_standard_time.dat", "rb");
			break;
		case eLv_Medium:
			rfp = fopen("./score/med_standard_time.dat", "rb");
			break;
		case eLv_Expert:
			rfp = fopen("./score/exp_standard_time.dat", "rb");
			break;
		}
		break;
	case eScene_Time:
		switch(nowLevel){
		case eLv_Easy:
			rfp = fopen("./score/easy_time_time.dat", "rb");
			break;
		case eLv_Medium:
			rfp = fopen("./score/med_time_time.dat", "rb");
			break;
		case eLv_Expert:
			rfp = fopen("./score/exp_time_time.dat", "rb");
			break;
		}
		break;
	case eScece_Remove:
		switch(nowLevel){
		case eLv_Easy:
			rfp = fopen("./score/easy_remove_time.dat", "rb");
			break;
		case eLv_Medium:
			rfp = fopen("./score/med_remove_time.dat", "rb");
			break;
		case eLv_Expert:
			rfp = fopen("./score/exp_remove_time.dat", "rb");
			break;
		}
		break;
	}
	if(rfp == NULL){
		bestscore = 9999999; //time.dat������������K���ɂł����l��
	}else{
		fread(&bestscore, sizeof(int),1,rfp);
		fclose(rfp); //fread���Ȃ�������fclose���Ȃ�...�H
	}
	
	/*���Ɍ��ʂƃx�X�g���ׂĂ��񂽂�*/
	switch(nowScene){
	case eScene_Standard:
		switch(nowLevel){
		case eLv_Easy:
			wfp = fopen("./score/easy_standard_time.dat", "wb");
			break;
		case eLv_Medium:
			wfp = fopen("./score/med_standard_time.dat", "wb");
			break;
		case eLv_Expert:
			wfp = fopen("./score/exp_standard_time.dat", "wb");
			break;
		}
		break;
	case eScene_Time:
		switch(nowLevel){
		case eLv_Easy:
			wfp = fopen("./score/easy_time_time.dat", "wb");
			break;
		case eLv_Medium:
			wfp = fopen("./score/med_time_time.dat", "wb");
			break;
		case eLv_Expert:
			wfp = fopen("./score/exp_time_time.dat", "wb");
			break;
		}
		break;
	case eScece_Remove:
		switch(nowLevel){
		case eLv_Easy:
			wfp = fopen("./score/easy_remove_time.dat", "wb");
			break;
		case eLv_Medium:
			wfp = fopen("./score/med_remove_time.dat", "wb");
			break;
		case eLv_Expert:
			wfp = fopen("./score/exp_remove_time.dat", "wb");
			break;
		}
		break;
	}
	if (wfp == NULL) {
		fwrite( &resulttime, sizeof(int),1,wfp);
	}else {
		if(resulttime < bestscore || bestscore < 0){
			fwrite( &resulttime, sizeof(int),1,wfp);
			newrecord = true;
		}else{
			fwrite( &bestscore,sizeof(int),1,wfp);
		}
	}

	fclose(wfp);
}

void Timer::DrawScoreTime()
{
	int bestscore, v;
	int rx, ry, bx, by;
	FILE *rfp;

	switch(nowScene){
	case eScene_Standard:
		switch(nowLevel){
		case eLv_Easy:
			rfp = fopen("./score/easy_standard_time.dat", "rb");
			break;
		case eLv_Medium:
			rfp = fopen("./score/med_standard_time.dat", "rb");
			break;
		case eLv_Expert:
			rfp = fopen("./score/exp_standard_time.dat", "rb");
			break;
		}
		font = largefont;
		rx = 650, ry = 170, bx = 650, by = 260, v = 8;
		break;
	case eScene_Time:
		switch(nowLevel){
		case eLv_Easy:
			rfp = fopen("./score/easy_time_time.dat", "rb");
			break;
		case eLv_Medium:
			rfp = fopen("./score/med_time_time.dat", "rb");
			break;
		case eLv_Expert:
			rfp = fopen("./score/exp_time_time.dat", "rb");
			break;
		}
		font = largefont;
		rx = 650, ry = 170, bx = 650, by = 260, v = 8;
		break;
	case eScece_Remove:
		switch(nowLevel){
		case eLv_Easy:
			rfp = fopen("./score/easy_remove_time.dat", "rb");
			break;
		case eLv_Medium:
			rfp = fopen("./score/med_remove_time.dat", "rb");
			break;
		case eLv_Expert:
			rfp = fopen("./score/exp_remove_time.dat", "rb");
			break;
		}
		font = normalfont;
		rx = 650, ry = 160, bx = 650, by = 230, v = 0;
		break;
		
	}
	if(rfp == NULL){
		return;
	}else{
		fread( &bestscore,sizeof(int),1,rfp);
		fclose(rfp);
	}
	/*if(resulttime < bestscore){
		bestscore = resulttime;
		//�j���[���R�[�h�`������
		newrecord = true;
	}*/

	char buf[32];
	
	sprintf_s(buf,32,"%d",bestscore);
	DrawStringToHandle(bx,by,buf,GetColor(255,255,255),font,1); //best
	sprintf_s(buf,32,"%d",resulttime);
	DrawStringToHandle(rx,ry,buf,GetColor(255,255,255),font,1); //result
	if(newrecord){
		DrawGraph(rx - 200, ry - 17 + v, newrecpng,true);
	}
}

void Timer::DrawBestOnly()
{
	int bestscore;
	int bx, by;
	FILE *rfp;

	switch(nowScene){
	case eScene_Standard:
		switch(nowLevel){
		case eLv_Easy:
			rfp = fopen("./score/easy_standard_time.dat", "rb");
			break;
		case eLv_Medium:
			rfp = fopen("./score/med_standard_time.dat", "rb");
			break;
		case eLv_Expert:
			rfp = fopen("./score/exp_standard_time.dat", "rb");
			break;
		}
		font = largefont;
		bx = 650, by = 260;
		break;
	case eScene_Time:
		switch(nowLevel){
		case eLv_Easy:
			rfp = fopen("./score/easy_time_time.dat", "rb");
			break;
		case eLv_Medium:
			rfp = fopen("./score/med_time_time.dat", "rb");
			break;
		case eLv_Expert:
			rfp = fopen("./score/exp_time_time.dat", "rb");
			break;
		}
		font = largefont;
		bx = 650, by = 260;
		break;
	case eScece_Remove:
		switch(nowLevel){
		case eLv_Easy:
			rfp = fopen("./score/easy_remove_time.dat", "rb");
			break;
		case eLv_Medium:
			rfp = fopen("./score/med_remove_time.dat", "rb");
			break;
		case eLv_Expert:
			rfp = fopen("./score/exp_remove_time.dat", "rb");
			break;
		}
		font = normalfont;
		bx = 650, by = 230;
		break;
	}
	if(rfp == NULL){
		return;
	}else{
		fread( &bestscore,sizeof(int),1,rfp);
		fclose(rfp);
	}

	char buf[32];
	sprintf_s(buf,32,"%d",bestscore);
	DrawStringToHandle(bx,by,buf,GetColor(255,255,255),font,1);
}