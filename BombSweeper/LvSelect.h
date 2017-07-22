#include "BaseScene.h"
#include "click.h"

//eScene BaseScene::nowScene;
//eLv BaseScene::nowLevel;

class LevelSelect : BaseScene{
private:
	int backpng, easypng, medpng, exppng, selpng;
	Click* click;
	const int ex; //easyX
	const int mx; //mediumX
	const int expx; //expertX
	const int y;
	const int width;
	const int height;
public:
	LevelSelect(SceneChanger* thispointer);
	void Init() override;
    void Fin() override;
    void Update() override;
    void Draw() override;
	bool isContainMouse(int x, int y, int width, int height);
	void ChangenowLevel(eLv anyLevel);
};