#pragma once
#include "DirectionalLight.h"
#include "Spotlight.h"
#include "Pointlight.h"
#include "Shader.h"
#include <memory>
#include <vector>
#include "GameObject.h"

#include <boost\container\map.hpp>
#include <boost\container\set.hpp>

class Scene;
typedef boost::uuids::uuid UUID;

class LightsManager
{
public:

	glm::mat4 lightSpaceMatrix;

	LightsManager();
	~LightsManager();
	void activateLights(const Shader& shader);
	void addLight( shared_ptr<C_Light> light);
	shared_ptr<ITextureBuffer>calcShadows(Scene* scene);

	void renderObjects(boost::container::set<UUID> renderableCompts, boost::container::map<UUID, shared_ptr<GameObject>> objectsCach);

private:
	Shader shader;
	shared_ptr<IFrameBuffer> fbo;
	vector < shared_ptr<DirectionalLight>> dLights;
	vector < shared_ptr<Spotlight>> sLights;
	vector < shared_ptr<Pointlight>> pLights;
	void LightsManager::activateDLights(const Shader &shader);
	void LightsManager::activateSLights(const Shader &shader);
	void LightsManager::activatePLights(const Shader &shader);
};

