#include "game.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Loader.h"

SpriteRenderer *p_sr;
unsigned int VBO;
unsigned int VAO;

Game::Game(GLuint width, GLuint height)
	: State(GAME_ACTIVE), Keys(), Width(width), Height(height)
{
	ballstr = "ball";
}

Game::~Game()
{
	delete p_sr;
}

void Game::SetTextureManager(TextureManager t)
{
	texm = t;
}

void Game::Load()
{
	texm.loadResource("textures/face.png", ballstr);
	texm.loadResource("textures/block.png", "block");
	texm.loadResource("textures/block_solid.png", "block_solid");
}

void Game::Init()
{
	spriteShader = loadShaders("shaders/vertex.glvs",
		"shaders/fragment.glfs", nullptr);
	glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(this->Width),
		static_cast<float>(this->Height), 0.0f, -1.0f, 1.0f);
	spriteShader.Use().SetInteger("image", 0);
	spriteShader.SetMatrix4("projection", projection);
	p_sr = new SpriteRenderer(spriteShader);
}

void Game::ProcessInput(GLfloat dt)
{
}

void Game::Update(GLfloat dt)
{
}

void Game::Render()
{
	p_sr->DrawSprite(texm.getResource(ballstr),
		glm::vec2(200, 200), glm::vec2(300, 400),
		45.0f, glm::vec3(0.0f, 1.0f, 1.0f));
	p_sr->DrawSprite(texm.getResource(ballstr),
		glm::vec2(1, 1), glm::vec2(300, 300));
}
