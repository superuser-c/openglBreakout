#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

//#define LOGGER_CREATE_LOG_FILE
#include "game.h"
#include "flog.h"

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

#define SCR_WIDTH 800
#define SCR_HEIGHT 600

Game Breakout(SCR_WIDTH, SCR_HEIGHT);

int main(int argc, char *argv[])
{
	FLog::init();
	FLog::glogf("running", "MAIN", LogType::info);
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT,
		"Breakout 2", NULL, NULL);
	if (window == NULL)
	{
		FLog::glogf("GLFW", "window creation failed", LogType::error);
		glfwTerminate();
		std::cin.get();
		FLog::logShutdown();
		return -1;
	}
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwMakeContextCurrent(window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		FLog::glogf("GLAD", "GLAD initialization failed.", LogType::error);
		std::cin.get();
		FLog::logShutdown();
		return -1;
	}
	glfwSetKeyCallback(window, key_callback);

	glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	TextureManager *tm = new TextureManager();
	Breakout.SetTextureManager(*tm);
	Breakout.Load();
	Breakout.Init();
	//FLog::glogf(std::to_string(tm->getResource("ball").ID), "T/MAIN", LogType::info);
	//FLog::glogf(std::to_string(tm->getResource("block").ID), "T/MAIN", LogType::info);

	float deltaTime = 0.0f;
	float lastFrame = 0.0f;

	Breakout.State = GameState::GAME_ACTIVE;

	while (!glfwWindowShouldClose(window))
	{
		// Calculate delta time
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		glfwPollEvents();

		// Manage user input
		Breakout.ProcessInput(deltaTime);

		// Update Game state
		Breakout.Update(deltaTime);

		// Render
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		Breakout.Render();

		glfwSwapBuffers(window);
	}

	glfwTerminate();
	FLog::logShutdown();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
			Breakout.Keys[key] = GL_TRUE;
		else if (action == GLFW_RELEASE)
			Breakout.Keys[key] = GL_FALSE;
	}
}