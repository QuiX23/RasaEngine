#include "GL\glew.h"
#include <GLFW\glfw3.h>

#include <glm/glm.hpp>


//Bullet includes
//#include "btBulletCollisionCommon.h"
//#include "btBulletCollisionCommon.h"
//#include "BulletDynamics\Dynamics\btDiscreteDynamicsWorld.h"
//#include "BulletDynamics\ConstraintSolver\btSequentialImpulseConstraintSolver.h"


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

// The MAIN function, from here we start our application and run the Game loop
int main()
{
#pragma region OpenGlSetup
	Context::getInstance().setOGLContext();
	scene = new Scene();

	// Set the required callback functions
	glfwSetKeyCallback(Context::getInstance().window, key_callback);
	glfwSetCursorPosCallback(Context::getInstance().window, mouse_callback);
	glfwSetScrollCallback(Context::getInstance().window, scroll_callback);


	//#pragma region BulletSetup
	////Bullet Broadphase alghoritm configuration
	//btBroadphaseInterface* broadphase = new btDbvtBroadphase();
	//
	//// Collision configuration for full  (not broadphase) collision detection
	//btDefaultCollisionConfiguration* collisionConfiguration = new btDefaultCollisionConfiguration();
	//btCollisionDispatcher* dispatcher = new btCollisionDispatcher(collisionConfiguration);
	//
	////Setting up "solver" for Bullet 
	//btSequentialImpulseConstraintSolver* solver = new btSequentialImpulseConstraintSolver;

	//btDiscreteDynamicsWorld* dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfiguration);
	//#pragma endregion

	//If you have connected a MIDI controller, this will allow you to debug you code;
#if _DEBUG
	std::unique_ptr<MidiDebugger> midiDebug;
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
	// Setup and compile our shaders
	Shader shader("Shaders/SimpleShader.vert", "Shaders/SimpleShader.frag");
	Shader bulbShader("Shaders/LampShader.vert", "Shaders/LampShader.frag");

	//Model ourModel("Models/nanosuit/nanosuit.obj", shader);
	shared_ptr <Model> ourModel = make_shared<Model>(Model("Models/nanosuit/nanosuit.obj", shader));
	shared_ptr <Model> bulb = make_shared<Model>(Model("Models/Bulb/Bulb.3DS", bulbShader));

	int count = 7;
	float x = -10;

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
#pragma endregion

#pragma region LightTests
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
	//scene->addComponent(make_shared<Pointlight>(pLight), pLight1);
	//scene->addComponent(bulb, pLight1);

	DirectionalLight dLight = DirectionalLight();
	dLight.position = glm::vec3(0.0f, 0.5f, -2.0f);
	dLight.ambientColor = glm::vec3(0.1f, 0.1f, 0.1f);
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