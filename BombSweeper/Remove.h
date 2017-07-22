#include "BaseScene.h"
#include "field.h"
#include "Timer.h"

class Remove : public BaseScene{
private:
	Field* field;
	Click* click;
	Timer* timer;
	int back, watchpng, bombpng, mousepng,  btn1png, btn2png, info1png, info2png, cresultpng, fresultpng, newgamepng, viewpng, gotitlepng, newgamepng2, viewpng2, gotitlepng2;
	bool resultvisible;
public:
	Remove(SceneChanger* thispointer);
    void Init() override;
    void Fin() override;
    void Update() override;
    void Draw() override;
	void Clear();
	void Failure();
	bool isContainMouse(int x, int y, int width, int height);
};