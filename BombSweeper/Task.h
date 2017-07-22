#pragma once

class Task{
public:
	virtual ~Task(){}
	virtual void Init(){}
	virtual void Fin(){}
	virtual void Update() = 0;
	virtual void Draw() = 0;
};
