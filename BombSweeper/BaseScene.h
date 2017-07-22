#pragma once

#include "Task.h"
#include "SceneChanger.h"

typedef enum{
	eLv_Easy,
	eLv_Medium,
	eLv_Expert
}eLv;

extern eScene nowScene;
extern eLv nowLevel;

class BaseScene : public Task {
protected:
	SceneChanger* mSceneChanger;
public:
	BaseScene(SceneChanger* changer);
	virtual ~BaseScene(){}
	virtual void Init() override{}
	virtual void Fin() override{}      
	virtual void Update() override{}       
	virtual void Draw() override{}
	virtual void ChangenowScene(eScene anyScene){}
	virtual void ChangenowLevel(eLv anyLevel){}
	//static eScene nowScene;
	//static eLv nowLevel;
	//virtual bool isCountainmouse(int x, int y, int width, int height){}
};