#pragma once

#include "BaseScene.h"
#include "SceneChanger.h"

class SceneMgr : public SceneChanger, Task {
private:
	BaseScene* mScene;
	eScene mNextScene;
	
    int gamebgm;
public:
	SceneMgr();
	void Init() override;
    void Fin() override;
    void Update() override;
    void Draw() override;

    void ChangeScene(eScene NextScene) override; //SceneCahanger

	static int titlebgm;
};