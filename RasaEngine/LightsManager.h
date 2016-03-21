#pragma once
#include "DirectionalLight.h"
#include "Spotlight.h"
#include "Pointlight.h"
#include "Shader.h"
#include <memory>
#include <vector>
using namespace std;
class LightsManager
{
public:
	LightsManager();
	~LightsManager();
	void activateLights(const Shader& shader);
	void addLight( shared_ptr<C_Light> light);


private:
	vector < shared_ptr<DirectionalLight>> dLights;
	vector < shared_ptr<Spotlight>> sLights;
	vector < shared_ptr<Pointlight>> pLights;
	void LightsManager::activateDLights(const Shader &shader);
	void LightsManager::activateSLights(const Shader &shader);
	void LightsManager::activatePLights(const Shader &shader);
};

