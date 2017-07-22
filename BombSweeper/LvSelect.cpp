#include "LvSelect.h"
#include "DxLib.h"

LevelSelect::LevelSelect(SceneChanger* thispointer) : BaseScene(thispointer), ex(23), mx(348), expx(671), y(174), width(300), height(400){
}
//eScene nowScene;
eLv nowLevel;

void LevelSelect::Init()
{
	click = new Click();
	backpng = LoadGraph("./media/pic/lback.png");
	easypng = LoadGraph("./media/pic/easy.png");
	medpng = LoadGraph("./media/pic/medium.png");
	exppng = LoadGraph("./media/pic/expert.png");
	selpng = LoadGraph("./media/pic/select.png");
}

void LevelSelect::Fin()
{
	delete click;
	DeleteGraph(backpng);
	DeleteGraph(easypng);
	DeleteGraph(medpng);
	DeleteGraph(exppng);
	DeleteGraph(selpng);
}

void LevelSelect::Draw()
{
	DrawGraph(0,0,backpng,false);
	DrawGraph(ex,y,easypng,false);
	DrawGraph(mx,y,medpng,false);
	DrawGraph(expx,y,exppng,false);

	if(isContainMouse(ex,y,width,height)){
		DrawGraph(ex,y,selpng,true);
	}else if(isContainMouse(mx,y,width,height)){
		DrawGraph(mx,y,selpng,true);
	}else if(isContainMouse(expx,y,width,height)){
		DrawGraph(expx,y,selpng,true);
	}
}

void LevelSelect::Update()
{
	if(isContainMouse(ex,y,width,height) && click->LeftClick()){
		ChangenowLevel(eLv_Easy);
		switch(nowScene){
		case eScene_Standard:
			mSceneChanger->ChangeScene(eScene_Standard);
			break;
		case eScene_Time:
			mSceneChanger->ChangeScene(eScene_Time);
			break;
		case eScece_Remove:
			mSceneChanger->ChangeScene(eScece_Remove);
			break;
		}
	}else if(isContainMouse(mx,y,width,height) && click->LeftClick()){
		ChangenowLevel(eLv_Medium);
		switch(nowScene){
		case eScene_Standard:
			mSceneChanger->ChangeScene(eScene_Standard);
			break;
		case eScene_Time:
			mSceneChanger->ChangeScene(eScene_Time);
			break;
		case eScece_Remove:
			mSceneChanger->ChangeScene(eScece_Remove);
			break;
		}
	}else if(isContainMouse(expx,y,width,height) && click->LeftClick()){
		ChangenowLevel(eLv_Expert);
		switch(nowScene){
		case eScene_Standard:
			mSceneChanger->ChangeScene(eScene_Standard);
			break;
		case eScene_Time:
			mSceneChanger->ChangeScene(eScene_Time);
			break;
		case eScece_Remove:
			mSceneChanger->ChangeScene(eScece_Remove);
			break;
		}
	}
}

bool LevelSelect::isContainMouse(int x, int y, int width, int height)
{
	int mx, my;
	GetMousePoint(&mx, &my);
	if((mx >= x && mx <= x + width) && (my >= y && my <= y + height)){
		return true;
	}
	else return false;
}

void LevelSelect::ChangenowLevel(eLv anyLevel)
{
	nowLevel = anyLevel;
	
}
