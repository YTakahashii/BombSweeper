#pragma once

typedef enum {
	eScene_Title,
	eScene_LvSelect,
	eScene_Standard,
	eScene_Time,
	eScece_Remove,
	eScene_None
}eScene;

class SceneChanger{
public:
	virtual ~SceneChanger() = 0;
	virtual void ChangeScene(eScene NextScene) = 0;
};
