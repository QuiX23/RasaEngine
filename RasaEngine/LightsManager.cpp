#include "LightsManager.h"
#include <sstream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Context.h"
#include "Model.h"

LightsManager::LightsManager() 
{
	fbo=Context::getInstance().CreateFrameBuffer(2048, 2048);
	fbo->setDepthBuffer(true);
	shader=Shader("Shadow.vert", "Shadow.frag");
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

shared_ptr<ITextureBuffer>  LightsManager::calcShadows(boost::container::set<UUID> renderableCompts, boost::container::map<UUID, shared_ptr<GameObject>> objectsCache)
{
	Context::getInstance().renderer->setFrameBuffer(*fbo);
	
	for (int i = 0; i < dLights.size(); i++)
	{
		glm::mat4 lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, 1.0f, 20.0f);

		glm::mat4 lightView = glm::lookAt(dLights[i]->position,
										  dLights[i]->position+dLights[i]->direction,
									      glm::vec3(0.0f, 1.0f, 0.0f));

		lightSpaceMatrix = lightProjection * lightView;
		
		for each (UUID var in renderableCompts)
		{
			auto ptr = static_pointer_cast<Model>(objectsCache[var]->GetComponent(Renderable));
			shader.Use();

			glUniformMatrix4fv(glGetUniformLocation(shader.Program, "lightSpaceMatrix"), 1, GL_FALSE, glm::value_ptr(lightSpaceMatrix));


			glm::mat4 model;
			model = glm::translate(model, objectsCache[var]->position); // Translate it down a bit so it's at the center of the scene
			model = glm::scale(model, objectsCache[var]->scale);	// It's a bit too big for our scene, so scale it down
			model = glm::rotate(model, objectsCache[var]->rotation.w, glm::vec3(objectsCache[var]->rotation));	// It's a bit too big for our scene, so scale it down

			glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
			ptr->draw(*Context::getInstance().renderer);
		}

		

	}

	Context::getInstance().renderer->unSetFrameBuffer();

	Context::getInstance().renderer->setShadowMap(*fbo->getDepthBuffer());
	return fbo->getDepthBuffer();
}



void LightsManager::activateDLights(const Shader & shader)
{
	for (int i = 0; i < dLights.size(); i++)
	{
		ostringstream ss;
		ss << i;
		string str = ss.str();

		glUniform3f(glGetUniformLocation(shader.Program, ("directionalLights[" + str + "].ambient").c_str()), dLights[i]->ambientColor.x, dLights[i]->ambientColor.y, dLights[i]->ambientColor.z);
		glUniform3f(glGetUniformLocation(shader.Program, ("directionalLights[" + str + "].diffuse").c_str()), dLights[i]->diffuseColor.x, dLights[i]->diffuseColor.y, dLights[i]->diffuseColor.z);
		glUniform3f(glGetUniformLocation(shader.Program, ("directionalLights[" + str + "].specular").c_str()), dLights[i]->specularColor.x, dLights[i]->specularColor.y, dLights[i]->specularColor.z);

		glUniform3f(glGetUniformLocation(shader.Program, ("directionalLights[" + str + "].direction").c_str()), dLights[i]->direction.x, dLights[i]->direction.y, dLights[i]->direction.z);

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


