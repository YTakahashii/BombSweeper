#include "Title.h"
#include "DxLib.h"

//BaseSceneクラスのコンストラクタ呼び出してmSceneChangerにchanger代入
Title::Title(SceneChanger* thispointer) : BaseScene(thispointer), 
 stx(23), tlx(348), rex(671), rurey(174), rwidth(300), rheight(400)
{
}

eScene nowScene;

void Title::Init()
{
	 backpng = LoadGraph("./media/pic/mback.png");
	 strurepng = LoadGraph("./media/pic/strure.png");
	 tlrurepng = LoadGraph("./media/pic/tlrure.png");
	 rerurepng = LoadGraph("./media/pic/removerure.png");
	 selpng = LoadGraph("./media/pic/select.png");
	 selectmp3 = LoadSoundMem("./media/sound/select.mp3");

	 click = new Click();
}

void Title::Fin()
{
	DeleteGraph(backpng);
	DeleteGraph(strurepng);
	DeleteGraph(tlrurepng);
	DeleteGraph(rerurepng);
	DeleteGraph(selpng);
	DeleteSoundMem(selectmp3);
	delete click;
}

//状態遷移はここに
void Title::Update()
{
	if(isContainMouse(stx,rurey,rwidth,rheight) && click->LeftClick()){
		PlaySoundMem(selectmp3,DX_PLAYTYPE_BACK);
		ChangenowScene(eScene_Standard);
		mSceneChanger->ChangeScene(eScene_LvSelect);
	}else if(isContainMouse(tlx,rurey,rwidth,rheight) && click->LeftClick()){
		mSceneChanger->ChangeScene(eScene_LvSelect);
		ChangenowScene(eScene_Time);
		PlaySoundMem(selectmp3,DX_PLAYTYPE_BACK);
	}else if(isContainMouse(rex,rurey,rwidth,rheight) && click->LeftClick()){
		mSceneChanger->ChangeScene(eScene_LvSelect);
		ChangenowScene(eScece_Remove);
		PlaySoundMem(selectmp3,DX_PLAYTYPE_BACK);
	}
}

void Title::Draw()
{
	DrawString(0, 0,"タイトル画面 Aですたんだーど",GetColor(255,255,255));
	DrawGraph(0,0,backpng,false);
	DrawGraph(stx,rurey,strurepng,false);
	DrawGraph(tlx,rurey,tlrurepng,false);
	DrawGraph(rex,rurey,rerurepng,false);
	//マウスカーソル
	if(isContainMouse(stx,rurey,rwidth,rheight)){
		DrawGraph(stx,rurey,selpng,true);
	}else if(isContainMouse(tlx,rurey,rwidth,rheight)){
		DrawGraph(tlx,rurey,selpng,true);
	}else if(isContainMouse(rex,rurey,rwidth,rheight)){
		DrawGraph(rex,rurey,selpng,true);
	}
}

bool Title::isContainMouse(int x, int y, int width, int height)
{
	int mx, my;
	GetMousePoint(&mx, &my);
	if((mx >= x && mx <= x + width) && (my >= y && my <= y + height)){
		return true;
	}
	else return false;
}

void Title::ChangenowScene(eScene anyScene)
{
	nowScene = anyScene;
}
