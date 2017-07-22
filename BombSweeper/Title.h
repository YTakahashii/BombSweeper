#include "BaseScene.h"
#include "click.h"

typedef enum{
	eLevel_Easy,
	eLevel_Normal,
	eLevel_Hard
}eLevel;

//eScene BaseScene::nowScene;

class Title : public BaseScene{
private:
	Click* click;
	int backpng, strurepng, tlrurepng, rerurepng, selpng;
	int selectmp3;
	const int stx;
	const int tlx;
	const int rex;
	const int rurey;
	const int rwidth;
	const int rheight;
public:
	Title(SceneChanger* thispointer);
    void Init() override;
    void Fin() override;
    void Update() override;
    void Draw() override;
	bool isContainMouse(int x, int y, int width, int height);
	void ChangenowScene(eScene anyScene);
};
