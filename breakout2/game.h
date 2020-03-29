#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "TextureManager.h"
#include "SpriteRenderer.h"

enum GameState {
	GAME_ACTIVE,
	GAME_MENU,
	GAME_WIN
};

class Game
{
public:
	GameState State;
	GLboolean Keys[1024];
	GLuint Width, Height;
	
	Game(GLuint width, GLuint height);
	~Game();

	void SetTextureManager(TextureManager t);
	void Load();
	void Init();
	
	// GameLoop
	void ProcessInput(GLfloat dt);
	void Update(GLfloat dt);
	void Render();
private:
	TextureManager texm;
	Shader spriteShader;
	std::string ballstr;
};

