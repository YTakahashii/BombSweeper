#include "TimeLimit.h"
#include "DxLib.h"

TimeLimit::TimeLimit(SceneChanger* thispointer) : BaseScene(thispointer){
}

void TimeLimit::Init()
{
	switch(nowLevel){
	case eLv_Easy:
		field = new Field(E_MAXROW, E_MAXCOL, E_MAXBOMB, E_CLEARNUM, E_STX, E_STY, L_SQUARE_WIDTH, L_SQUARE_HEIGHT, E_TIME, E_CLICKMAX);
		break;
	case eLv_Medium:
		field = new Field(M_MAXROW, M_MAXCOL, M_MAXBOMB, M_CLEARNUM, M_STX, M_STY, S_SQUARE_WIDTH, S_SQUARE_HEIGHT, M_TIME, M_CLICKMAX);
		break;
	case eLv_Expert:
		field = new Field(EX_MAXROW, EX_MAXCOL, EX_MAXBOMB, EX_CLEARNUM, EX_STX, EX_STY, S_SQUARE_WIDTH, S_SQUARE_HEIGHT, EX_TIME, EX_CLICKMAX);
		break;
	}
	click = new Click();
	timer = new Timer();
	back = LoadGraph("./media/pic/gback.png");
	watchpng = LoadGraph("./media/pic/watch.png");
	bombpng = LoadGraph("./media/pic/bombicon.png");
	btn1png = LoadGraph("./media/pic/backbtn1.png");
	btn2png = LoadGraph("./media/pic/backbtn2.png");
	info1png = LoadGraph("./media/pic/tltop.png");
	cresultpng = LoadGraph("./media/pic/clearresult.png");
	fresultpng = LoadGraph("./media/pic/failureresult.png");
	newgamepng = LoadGraph("./media/pic/newgame1.png");
	viewpng = LoadGraph("./media/pic/viewboard1.png");
	gotitlepng = LoadGraph("./media/pic/gotitle1.png");
	newgamepng2 = LoadGraph("./media/pic/newgame2.png");
	viewpng2 = LoadGraph("./media/pic/viewboard2.png");
	gotitlepng2 = LoadGraph("./media/pic/gotitle2.png");

	resultvisible = true;
	switch(nowLevel){
	case eLv_Easy:
		info2png = LoadGraph("./media/pic/easytop.png");
		break;
	case eLv_Medium:
		info2png = LoadGraph("./media/pic/mediumtop.png");
		break;
	case eLv_Expert:
		info2png = LoadGraph("./media/pic/exptop.png");
		break;
	}
	timer->startTimer();
}

void TimeLimit::Fin()
{
	delete field;
	delete click;
	delete timer;
	DeleteGraph(back);
	DeleteGraph(watchpng);
	DeleteGraph(bombpng);
	DeleteGraph(btn1png);
	DeleteGraph(btn2png);
	DeleteGraph(info1png);
	DeleteGraph(info2png);
	DeleteGraph(cresultpng);
	DeleteGraph(fresultpng);
	DeleteGraph(newgamepng);
	DeleteGraph(viewpng);
	DeleteGraph(gotitlepng);
	DeleteGraph(newgamepng2);
	DeleteGraph(viewpng2);
	DeleteGraph(gotitlepng2);
}

void TimeLimit::Update()
{
	if(isContainMouse(20,0,75,75) && click->LeftClick()){
		mSceneChanger->ChangeScene(eScene_Title);
	}
}

void TimeLimit::Draw()
{
	DrawGraph(0,0,back,false);
	bool t;

	DrawGraph(300,70,watchpng,true);
	DrawGraph(500,70,bombpng,true);
	DrawGraph(130,10,info1png,true);
	DrawGraph(430,10,info2png,true);

	switch(nowLevel){
		case eLv_Easy:
		t = timer->LimitTimer(E_TIME);	
		break;
	case eLv_Medium:
		t = timer->LimitTimer(M_TIME);
		break;
	case eLv_Expert:
		t = timer->LimitTimer(EX_TIME);
		break;
	}

	if(field->CheckFailure() == false && field->CheckClear() == false && t == false){
		field->Method();

		if(isContainMouse(20,0,75,75)){
			DrawGraph(20,0,btn2png,true);
		}else{
			DrawGraph(20,0,btn1png,true);
		}
	}

	if(t == true || field->CheckFailure()){
		Failure();
	}
	
	if(field->CheckClear()){
		Clear();
	}
}

void TimeLimit::Clear()
{
	field->Clear();
	timer->stopTimer();
	
	timer->SaveBestTime();

	if(resultvisible){
		DrawGraph(90,50,cresultpng,true);
		timer->DrawScoreTime();

		/*新しいゲーム*/
		if(isContainMouse(130,450,210,70)){
			DrawGraph(130,450,newgamepng2,true);
			if(click->LeftClick()){
			Init();
			Draw();
			return;
			}
		}else{
			DrawGraph(130,450,newgamepng,true);
		}
		/*ボードを見る*/
		if(isContainMouse(370,450,210,70)){
			DrawGraph(370,450,viewpng2,true);
			if(click->LeftClick()) resultvisible = false;
		}else{
			DrawGraph(370,450,viewpng,true);
		}
		/*タイトル*/
		if(isContainMouse(610,450,210,70)){
			DrawGraph(610,450,gotitlepng2,true);
			if(click->LeftClick()){
				mSceneChanger->ChangeScene(eScene_Title);
			}
		}else{
			DrawGraph(610,450,gotitlepng,true);
		}
	}
	
	if(resultvisible == false && click->LeftClick()){
			resultvisible = true;
	}
}

void TimeLimit::Failure()
{
	field->Failure();
	timer->stopTimer();
	if(resultvisible){
		DrawGraph(90,50,fresultpng,true);
		timer->DrawBestOnly();
		/*新しいゲーム*/
		if(isContainMouse(130,450,210,70)){
			DrawGraph(130,450,newgamepng2,true);
			if(click->LeftClick()){
			Init();
			Draw();
			return;
			}
		}else{
			DrawGraph(130,450,newgamepng,true);
		}
		/*ボードを見る*/
		if(isContainMouse(370,450,210,70)){
			DrawGraph(370,450,viewpng2,true);
			if(click->LeftClick()) resultvisible = false;
		}else{
			DrawGraph(370,450,viewpng,true);
		}
		/*タイトル*/
		if(isContainMouse(610,450,210,70)){
			DrawGraph(610,450,gotitlepng2,true);
			if(click->LeftClick()){
				mSceneChanger->ChangeScene(eScene_Title);
			}
		}else{
			DrawGraph(610,450,gotitlepng,true);
		}
	}
	
	if(resultvisible == false && click->LeftClick()){
			resultvisible = true;
	}
}

bool TimeLimit::isContainMouse(int x, int y, int width, int height)
{
	int mx, my;
	GetMousePoint(&mx, &my);
	if((mx >= x && mx <= x + width) && (my >= y && my <= y + height)){
		return true;
	}else return false;
}
