#include "GL\glew.h"
#include <GLFW\glfw3.h>

#include <glm/glm.hpp>

#include "Shader.h"
#include "Camera.h"
#include "Model.h"
#include "Light.h"

#include "MidiDebugger.h"
#include "Context.h"
#include "Pointlight.h"
#include <boost/uuid/uuid.hpp>
#include "DirectionalLight.h"
#include "Scene.h"
#include "Collider.h"
#include "PlaneCollider.h"
#include "SphereCollider.h"
#include "RigidBody.h"

// Function prototypes
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void Do_Movement();

bool keys[1024];
GLfloat lastX = 400, lastY = 300;
bool firstMouse = true;

GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;

Scene* scene;

int main()
{

#pragma region OpenGlSetup
	Context::getInstance().setOGLContext();
	scene = new Scene();

	// Set the required callback functions
	glfwSetKeyCallback(Context::getInstance().window, key_callback);
	glfwSetCursorPosCallback(Context::getInstance().window, mouse_callback);
	glfwSetScrollCallback(Context::getInstance().window, scroll_callback);

#pragma region BulletTest

	Shader shader("Shaders/SimpleShader.vert", "Shaders/SimpleShader.frag");
	shared_ptr <Model> ourModel = make_shared<Model>(Model("Models/nanosuit/nanosuit.obj", shader));
	shared_ptr <Model> plane = make_shared<Model>(Model::genericPlane());

	auto floor = scene->addNewChild(glm::vec3(0.0f, -5.0f, 0.0f),
		glm::vec4(0.0f, 0.0f, 0.0f, 1.0f),
		glm::vec3(1.0f, 1.0f, 1.0f));
	shared_ptr<Collider> floorPlaneColl = make_shared<PlaneCollider>(btVector3(0, 1, 0), 1);
	scene->addRigidBody(floorPlaneColl, floor);
	scene->addComponent(plane, floor);

	auto ball = scene->addNewChild(glm::vec3(0.0f, 10.0f, -10.0f),
		glm::vec4(0.0f, 0.0f, 0.0f, 1.0f),
		glm::vec3(0.2f, 0.2f, 0.2f));
	shared_ptr<Collider> ballSphere = make_shared<SphereCollider>(1);
	scene->addRigidBody(ballSphere, ball);
	auto rb= static_pointer_cast<RigidBody>(scene->getGameObject(ball)->GetComponent(ComponentType_RigidBody));
	rb->setAsDynamic();

	scene->addComponent(ourModel, ball);

#pragma endregion 

	//If you have connected a MIDI controller, this will allow you to debug you code;
#if _DEBUG
	unique_ptr<MidiDebugger> midiDebug;
	try
	{
		midiDebug = std::make_unique<MidiDebugger>();
	}
	catch (_exception e)
	{
		std::cout << "No MIDI port found!";
	}
#endif

#pragma region RenderTests
	Shader skyboxShader("Shaders/SkyboxShader.vert", "Shaders/SkyboxShader.frag");

	string skyboxTex[] = {
		"Models/skybox/right.jpg",
		"Models/skybox/left.jpg",
		"Models/skybox/top.jpg",
		"Models/skybox/bottom.jpg",
		"Models/skybox/back.jpg",
		"Models/skybox/front.jpg"
	};

	shared_ptr <Skybox> skybox = make_shared<Skybox>(Skybox(skyboxTex, skyboxShader));
	scene->addSkybox(skybox);
	
	/* Model Generation tests
	// Setup and compile shaders
	Shader shader("Shaders/SimpleShader.vert", "Shaders/SimpleShader.frag");
	Shader bulbShader("Shaders/LampShader.vert", "Shaders/LampShader.frag");

	//Model ourModel("Models/nanosuit/nanosuit.obj", shader);
	shared_ptr <Model> ourModel = make_shared<Model>(Model("Models/nanosuit/nanosuit.obj", shader));
	shared_ptr <Model> bulb = make_shared<Model>(Model("Models/Bulb/Bulb.3DS", bulbShader));

	int count = 7;
	float x = -10;

	//Temporary creating multiple objects from the same model
	// without use ofinstantiation. Will be implemented later.
	for (int i = 0; i < count; i++)
	{
	x += 2;
	float z = -10;
	for (int i = 0; i < count; i++)
	{
	z += 2;
	boost::uuids::uuid gameObject = scene->addNewChild(glm::vec3(x, -1.75f, z),
	glm::vec4(0.0f, 1.0f, 0.0f, 0.0f),
	glm::vec3(0.2f, 0.2f, 0.2f));
	scene->addComponent(ourModel, gameObject);
	}
	}
	*/
#pragma endregion

#pragma region LightTests
	/* Point light tests
	Pointlight pLight = Pointlight();
	pLight.ambientColor = glm::vec3(0.05f, 0.05f, 0.05f);
	pLight.diffuseColor = glm::vec3(1.0f, 1.0f, 1.0f);
	pLight.specularColor = glm::vec3(1.0f, 1.0f, 1.0f);
	pLight.constant = 1.0f;
	pLight.linear = 0.009;
	pLight.quadratic = 0.0032;


	boost::uuids::uuid pLight1 = scene->addNewChild(glm::vec3(2.3f, 4, -3.0f),
		glm::vec4(0.0f, 0.0f, 1.0f, 3.141592f),
		glm::vec3(0.2f, 0.2f, 0.2f));
	scene->addComponent(make_shared<Pointlight>(pLight), pLight1);
	scene->addComponent(bulb, pLight1);*/

	DirectionalLight dLight = DirectionalLight();
	dLight.position = glm::vec3(0.0f, 0.5f, -2.0f);
	dLight.ambientColor = glm::vec3(0.4f, 0.4f, 0.4f);
	dLight.diffuseColor = glm::vec3(1.0f, 1.0f, 1.0f);
	dLight.specularColor = glm::vec3(1.0f, 1.0f, 1.0f);
	dLight.direction = glm::vec3(0.2f, -0.3f, 1.0f);


	boost::uuids::uuid dLight1 = scene->addNewChild(glm::vec3(0.0f, 0.5f, -12.0f),
		glm::vec4(0.0f, 0.0f, 1.0f, 3.141592f),
		glm::vec3(0.2f, 0.2f, 0.2f));
	scene->addComponent(make_shared<DirectionalLight>(dLight), dLight1);
#pragma endregion

	while (!glfwWindowShouldClose(Context::getInstance().window))
	{
		// Set frame time
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// Check and call events
		glfwPollEvents();
		Do_Movement();

		// Clear the colorbuffer
		glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		scene->update();

		// Swap the buffers
		glfwSwapBuffers(Context::getInstance().window);
	}

	delete scene;
	glfwTerminate();
	return 0;
}

#pragma region "User input"

// Moves/alters the camera positions based on user input
void Do_Movement()
{
	// Camera controls
	if (keys[GLFW_KEY_W])
		scene->camera.ProcessKeyboard(FORWARD, deltaTime);
	if (keys[GLFW_KEY_S])
		scene->camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (keys[GLFW_KEY_A])
		scene->camera.ProcessKeyboard(LEFT, deltaTime);
	if (keys[GLFW_KEY_D])
		scene->camera.ProcessKeyboard(RIGHT, deltaTime);
}

// Is called whenever a key is pressed/released via GLFW
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

	if (action == GLFW_PRESS)
		keys[key] = true;
	else if (action == GLFW_RELEASE)
		keys[key] = false;
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	GLfloat xoffset = xpos - lastX;
	GLfloat yoffset = lastY - ypos;

	lastX = xpos;
	lastY = ypos;

	scene->camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	scene->camera.ProcessMouseScroll(yoffset);
}

#pragma endregion
