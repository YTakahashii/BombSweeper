#include "DxLib.h"
#include "Title.h"
#include "Standard.h"
#include "SceneMgr.h"
#include "LvSelect.h"
#include "TimeLimit.h"
#include "Remove.h"

int SceneMgr::titlebgm;
SceneMgr::SceneMgr() : mNextScene(eScene_None)
{
	mScene = (BaseScene*) new Title(this);
	SceneMgr::titlebgm = LoadSoundMem("./media/sound/titlebgm.mp3");
	gamebgm = LoadSoundMem("./media/sound/gamebgm.mp3");
}

void SceneMgr::Init(){
	mScene->Init();
	
}

void SceneMgr::Fin()
{
	mScene->Fin();
}

void SceneMgr::Update()
{
	if(mNextScene != eScene_None){
		mScene->Fin();
		delete mScene;
		switch(mNextScene){
		case eScene_Title:
			mScene = (BaseScene*) new Title(this);
			StopSoundMem(gamebgm);
			ChangeVolumeSoundMem(1,SceneMgr::titlebgm);
			PlaySoundMem(SceneMgr::titlebgm,DX_PLAYTYPE_LOOP);
			break;
		case eScene_LvSelect:
			mScene = (BaseScene*) new LevelSelect(this);
			break;
		case eScene_Standard:
			mScene = (BaseScene*) new Standard(this);
			StopSoundMem(titlebgm);
			ChangeVolumeSoundMem(1,gamebgm);
			PlaySoundMem(gamebgm,DX_PLAYTYPE_LOOP);
			break;
		case eScene_Time:
			mScene = (BaseScene*) new TimeLimit(this);
			StopSoundMem(titlebgm);
			ChangeVolumeSoundMem(1,gamebgm);
			PlaySoundMem(gamebgm,DX_PLAYTYPE_LOOP);
			break;
		case eScece_Remove:
			mScene = (BaseScene*) new Remove(this);
			StopSoundMem(titlebgm);
			ChangeVolumeSoundMem(1,gamebgm);
			PlaySoundMem(gamebgm,DX_PLAYTYPE_LOOP);
			break;
		}
		mNextScene = eScene_None;
		mScene->Init();
	}
	mScene->Update();
}

void SceneMgr::Draw()
{
	mScene->Draw();
}

void SceneMgr::ChangeScene(eScene NextScene)
{
	mNextScene = NextScene;
}