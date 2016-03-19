#pragma once
#include "GameObject.h"


class Scene
{
public:
	
	/*Singleton pattern methods*/
	static Scene& getInstance();
	void operator=(Scene const&) = delete;
	Scene(Scene const&) = delete;
	~Scene();
	/*  Scene data  */
	static shared_ptr<GameObject> root;
	/*  Scene Functions  */
	void update();
	
private:
	void lightUpdate();
	void renderUpdate();

};

