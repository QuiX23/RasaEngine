#pragma warning(disable : 4996)

#include "Scene.h"
#include "Model.h"
#include "Component.h"


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <boost/uuid/uuid_generators.hpp> // generators
#include <assert.h> 
#include "Context.h"


#pragma region Quad Dedub
// RenderQuad() Renders a 1x1 quad in NDC, best used for framebuffer color targets
// and post-processing effects.
GLuint quadVAO = 0;
GLuint quadVBO;
Shader debugDepthQuad;
void RenderQuad()
{
	if (quadVAO == 0)
	{
		GLfloat quadVertices[] = {
			// Positions        // Texture Coords
			-1.0f,  1.0f, 0.0f,  0.0f, 1.0f,
			-1.0f, -1.0f, 0.0f,  0.0f, 0.0f,
			1.0f,  1.0f, 0.0f,  1.0f, 1.0f,
			1.0f, -1.0f, 0.0f,  1.0f, 0.0f,
		};
		// Setup plane VAO
		glGenVertexArrays(1, &quadVAO);
		glGenBuffers(1, &quadVBO);
		glBindVertexArray(quadVAO);
		glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	}
	glBindVertexArray(quadVAO);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glBindVertexArray(0);
}

#pragma endregion 

Scene::Scene()
{
	debugDepthQuad = Shader("Quad.vert", "Quad.frag");

	auto camera = Camera(glm::vec3(0.0f, 0.0f, 3.0f));
	root = make_shared<GameObject>(GameObject(glm::vec3(0, 0, 0), glm::vec4(0, 0, 0, 0), glm::vec3(1, 1, 1)));
	lightsManager = LightsManager();
}

Scene::~Scene()
{
	
};

UUID Scene::addNewChild()
{
	
	return addChild(root);
}

UUID Scene::addNewChild(glm::vec3 position, glm::vec4 rotation, glm::vec3 scale)
{
	auto id = addChild(root);
	objectsCache[id]->position = position;
	objectsCache[id]->rotation = rotation;
	objectsCache[id]->scale = scale;
	return id;
}

void Scene::addComponent(shared_ptr<Component> component, const UUID & gameObject)
{
	
		if (component->type==ComponentType_LIGHTS)
		{
			addLight(component, gameObject);
		}
		else if (component->type == ComponentType_RENDERABLE)
		{
			addRenderable(component, gameObject);
		}
}

void Scene::addLight(shared_ptr<Component> component, const UUID & gameObject) 
{
	if (objectsCache[gameObject]->HasComponent(ComponentType_LIGHTS)) return;

	auto m = static_pointer_cast<C_Light>(component);
	m->position = objectsCache[gameObject]->position;

	objectsCache[gameObject]->AddComponent(component);
	
	lightsManager.addLight(static_pointer_cast<C_Light>(component));
}

void Scene::addRenderable(shared_ptr<Component> component, const UUID & gameObject) 
{
	if (objectsCache[gameObject]->HasComponent(ComponentType::ComponentType_RENDERABLE)) return;

	auto m = static_pointer_cast<Model>(component);

	objectsCache[gameObject]->AddComponent(component);
	renderableCompts.insert(gameObject);
}

void Scene::addSkybox(shared_ptr<Skybox> component)
{
	if(skybox) return;
	skybox = component;
}

UUID Scene::addChild(shared_ptr<GameObject> parent)
{
	shared_ptr<GameObject> newObject = make_shared<GameObject>(GameObject(glm::vec3(0, 0, 0), glm::vec4(0, 0, 0,0), glm::vec3(1, 1, 1)));
	newObject->uid = boost::uuids::random_generator()();
	newObject->parent = root;
	root->children.push_back(newObject);
	
	assert(objectsCache.find(newObject->uid)==objectsCache.end());
	
	objectsCache[newObject->uid] = newObject;
	return newObject->uid;
}

void Scene::update()
{
	renderUpdate();
}   

void Scene::renderUpdate() 
{
	
	lightsManager.calcShadows(*this);

#pragma region Transformation matrices 
	
	auto projection = glm::perspective(camera.Zoom, (float)(Context::getInstance().screenWidth) / (float)(float)(Context::getInstance().screenHeight), 0.1f, 100.0f);
	auto view = camera.GetViewMatrix();

	
#pragma endregion 
	
	renderObjects(projection, view);

	// Render Depth map to quad
	//OGLTextureBuffer otb = *static_pointer_cast<OGLTextureBuffer>(tb);

	//Context::getInstance().renderer->unSetFrameBuffer();
	//debugDepthQuad.Use();
	//glUniform1f(glGetUniformLocation(debugDepthQuad.Program, "near_plane"), 1.0);
	//glUniform1f(glGetUniformLocation(debugDepthQuad.Program, "far_plane"), 20.0);
	//glActiveTexture(GL_TEXTURE0);
	//glBindTexture(GL_TEXTURE_2D, otb.id);
	//RenderQuad();

	renderSkybox(projection, view);
}

void Scene::setViewProjection(glm::mat4 projection, glm::mat4 view)
{
	GLuint uboMatrices;
	glGenBuffers(1, &uboMatrices);

	glBindBuffer(GL_UNIFORM_BUFFER, uboMatrices);
	//Reserve memory
	glBufferData(GL_UNIFORM_BUFFER, 2 * sizeof(glm::mat4), NULL, GL_STATIC_DRAW);

	//Fill buffers with data
	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), glm::value_ptr(projection));
	glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(view));

	glBindBuffer(GL_UNIFORM_BUFFER, 0);

	//BindBuffer to binding point
	glBindBufferRange(GL_UNIFORM_BUFFER, 0, uboMatrices, 0, 2 * sizeof(glm::mat4));
}

void Scene::renderSkybox(glm::mat4 projection, glm::mat4 view)
{
	if (skybox)
	{
		skybox->shader.Use();
		glUniformMatrix4fv(glGetUniformLocation(skybox->shader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(glGetUniformLocation(skybox->shader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

		glm::mat4 model;
		model = glm::translate(model, camera.Position);
		//model = glm::scale(model, objectsCache[skybox]->scale);	// It's a bit too big for our scene, so scale it down
		//model = glm::rotate(model, objectsCache[skybox]->rotation.w, glm::vec3(objectsCache[skybox]->rotation));	// It's a bit too big for our scene, so scale it down

		glUniformMatrix4fv(glGetUniformLocation(skybox->shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));

		skybox->draw(*Context::getInstance().renderer);
	}
}

void Scene::renderObjects(glm::mat4 projection, glm::mat4 view)
{
	setViewProjection(projection, view);

	for each (UUID var in renderableCompts)
	{
		auto ptr = static_pointer_cast<Model>(objectsCache[var]->GetComponent(ComponentType_RENDERABLE));
		ptr->shader.Use();

		// Transformation matrices
		GLuint uniformBlock = glGetUniformBlockIndex(ptr->shader.Program, "Matrices");
		glUniformBlockBinding(ptr->shader.Program, uniformBlock, 0);

		glUniform3f(glGetUniformLocation(ptr->shader.Program, "viewPos"), camera.Position.x, camera.Position.y, camera.Position.z);

		lightsManager.activateLights(ptr->shader);

		glm::mat4 model;
		model = glm::translate(model, objectsCache[var]->position); // Translate it down a bit so it's at the center of the scene
		model = glm::scale(model, objectsCache[var]->scale);	// It's a bit too big for our scene, so scale it down
		model = glm::rotate(model, objectsCache[var]->rotation.w, glm::vec3(objectsCache[var]->rotation));	// It's a bit too big for our scene, so scale it down

		glUniformMatrix4fv(glGetUniformLocation(ptr->shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
		ptr->draw(*Context::getInstance().renderer);
	}
}

void Scene::renderObjects(glm::mat4 projection, glm::mat4 view, Shader shader)
{
	setViewProjection(projection, view);

	for each (UUID var in renderableCompts)
	{
		auto ptr = static_pointer_cast<Model>(objectsCache[var]->GetComponent(ComponentType_RENDERABLE));
		shader.Use();

		// Transformation matrices
		GLuint uniformBlock = glGetUniformBlockIndex(shader.Program, "Matrices");
		glUniformBlockBinding(shader.Program, uniformBlock, 0);

		glUniform3f(glGetUniformLocation(shader.Program, "viewPos"), camera.Position.x, camera.Position.y, camera.Position.z);


		lightsManager.activateLights(shader);

		glm::mat4 model;
		model = glm::translate(model, objectsCache[var]->position); // Translate it down a bit so it's at the center of the scene
		model = glm::scale(model, objectsCache[var]->scale);	// It's a bit too big for our scene, so scale it down
		model = glm::rotate(model, objectsCache[var]->rotation.w, glm::vec3(objectsCache[var]->rotation));	// It's a bit too big for our scene, so scale it down

		glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
		ptr->draw(*Context::getInstance().renderer);
	}
}

void Scene::lightUpdate()
{
	
}


