#include "LightsManager.h"
#include <algorithm>
#include <sstream>

LightsManager::LightsManager()
{
}


LightsManager::~LightsManager()
{
}

void LightsManager::addLight( shared_ptr<C_Light> light)
{
	switch (light->typeL)
	{
		case LightType::Point:
			pLights.push_back(static_pointer_cast<Pointlight>(light));
			break;
		case LightType::Directional:
			dLights.push_back(static_pointer_cast<DirectionalLight>(light));
			break;
		case LightType::Spot:
			sLights.push_back(static_pointer_cast<Spotlight>(light));
			break;
		default:
			break;
	}
}

void LightsManager::activateDLights(const Shader & shader)
{
	for (int i = 0; i < dLights.size(); i++)
	{

	}
}

void LightsManager::activateSLights(const Shader & shader)
{
	for (int i = 0; i < sLights.size(); i++)
	{

	}
}

void LightsManager::activatePLights(const Shader & shader)
{
	for (int i = 0; i < pLights.size(); i++)
	{
		ostringstream ss;
		ss << i;
		string str = ss.str();
		GLuint wow = glGetUniformLocation(shader.Program, ("pointLights[" + str + "].position").c_str());
		glUniform3f(glGetUniformLocation(shader.Program, ("pointLights["+ str +"].position").c_str()), pLights[i]->position.x, pLights[i]->position.y, pLights[i]->position.z);
		glUniform3f(glGetUniformLocation(shader.Program, ("pointLights[" + str + "].ambient").c_str()), pLights[i]->ambientColor.x, pLights[i]->ambientColor.y, pLights[i]->ambientColor.z);
		glUniform3f(glGetUniformLocation(shader.Program, ("pointLights["+ str +"].diffuse").c_str()), pLights[i]->diffuseColor.x, pLights[i]->diffuseColor.y, pLights[i]->diffuseColor.z);
		glUniform3f(glGetUniformLocation(shader.Program, ("pointLights[" + str + "].specular").c_str()), pLights[i]->specularColor.x, pLights[i]->specularColor.y, pLights[i]->specularColor.z);
		glUniform1f(glGetUniformLocation(shader.Program, ("pointLights[" + str + "].constant").c_str()), pLights[i]->constant);
		glUniform1f(glGetUniformLocation(shader.Program, ("pointLights[" + str + "].linear").c_str()), pLights[i]->linear);
		glUniform1f(glGetUniformLocation(shader.Program, ("pointLights[" + str + "].quadratic").c_str()), pLights[i]->quadratic);
	}
}

void LightsManager::activateLights(const Shader& shader)
{
	activatePLights(shader);
	activateSLights(shader);
	activateDLights(shader);
}


