#include "BaseScene.h"
#include "DxLib.h"

BaseScene::BaseScene(SceneChanger* changer){
	mSceneChanger = changer;
}


//背景画像とかずっと描いておくものはここにDrawしておいて継承クラスで呼び出した方がいいかも
