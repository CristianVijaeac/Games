#include "Game.h"
#include "SpriteSheet.h"
#include "Player.h"
#include <vector>
#include <string>
#include <iostream>


#include <Core/Engine.h>

using namespace std;

SpriteSheet* sheet;
Player* p1, *p2;
Mesh* mesh1, *mesh2, *mesh3;
vector<glm::vec3> direction1, direction2, directionBack,normals;
vector<glm::vec2> textureCoords1,textureCoords2;
vector<unsigned short> indices,indices2;
Texture2D *texture_back;
vector<VertexFormat> vertices2;

Game::Game()
{
}

Game::~Game()
{
}

void Game::Init()
{
	//setam pozitia camerei
	const string textureLoc = "Source/GameImpl/Textures/";
	GetSceneCamera()->SetPosition(glm::vec3(0.0f, 2.0f, 7.0f));
	sheet = new SpriteSheet(1024, 512);

	//initializam valori default ale celor 2 playeri
	p1 = new Player(glm::vec3(-4.0f, -1.0f, 0.0f), 1, 0, 10, 2, glm::vec3(1.0f, 0.0f, 0.0f));
	p2 = new Player(glm::vec3(4.0f, -1.0f, 0.0f), 1, 0, 10, 2, glm::vec3(-1.0f, 0.0f, 0.0f));
	
	//textura pentru playeri si background
	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "sprites.png").c_str(), GL_REPEAT);
		mapTextures["fight"] = texture;
	}

	{	Texture2D *texture = new Texture2D();
		texture->Load2D((textureLoc + "background.png").c_str(), GL_REPEAT);
		mapTextures["background"] = texture;
	}

	//directia corespunzatoare pozitionarii spre stanga
	direction1 =
	{
		glm::vec3(1.0f,   2.0f, 0.0f),	
		glm::vec3(1.0f,  -2.0f, 0.0f),	
		glm::vec3(-1.0f, -2.0f, 0.0f),	
		glm::vec3(-1.0f,  2.0f, 0.0f),	
	};

	//directia corespunzatoare pozitionarii spre dreapta
	direction2 =
	{
		glm::vec3(-1.0f,   2.0f, 0.0f),	// Top Right
		glm::vec3(-1.0f,  -2.0f, 0.0f),	// Bottom Right
		glm::vec3(1.0f, -2.0f, 0.0f),	// Bottom Left
		glm::vec3(1.0f,  2.0f, 0.0f),	// Top Left
	};

	//dimensiunile backgroundului
	directionBack =
	{
		glm::vec3(10.0f,   5.0f, -1.0f),	// Top Right
		glm::vec3(10.0f,  -6.0f, -1.0f),	// Bottom Right
		glm::vec3(-10.0f, -6.0f, -1.0f),	// Bottom Left
		glm::vec3(-10.0f,  5.0f, -1.0f),	// Top Left
	};

	normals =
	{
		glm::vec3(0, 1, 1),
		glm::vec3(1, 0, 1),
		glm::vec3(1, 0, 0),
		glm::vec3(0, 1, 0)
	};

	//coordonatele initiale de textura pentru cei 2 playeri
	textureCoords1 =
	{
		glm::vec2((sheet->stay.front()[0] + sheet->stay.front()[2]) / 1024, (sheet->stay.front()[1]) / 512),
		glm::vec2((sheet->stay.front()[0] + sheet->stay.front()[2]) / 1024 ,(sheet->stay.front()[1] + sheet->stay.front()[3]) / 512),
		glm::vec2((sheet->stay.front()[0]) / 1024, (sheet->stay.front()[1] + sheet->stay.front()[3]) / 512),
		glm::vec2((sheet->stay.front()[0]) / 1024, (sheet->stay.front()[1]) / 512)
	};

	//coordonatele de textura pentru background
	textureCoords2 =
	{
		glm::vec2(1.0f,0.0f),
		glm::vec2(1.0f,1.0f),
		glm::vec2(0.0f,1.0f),
		glm::vec2(0.0f,0.0f)
	};

	indices =
	{
		0, 1, 3,
		1, 2, 3
	};

	mesh1 = new Mesh("player1");
	mesh1->InitFromData(direction1, normals, textureCoords1, indices);
	meshes[mesh1->GetMeshID()] = mesh1;

	mesh2 = new Mesh("player2");
	mesh2->InitFromData(direction2, normals, textureCoords1, indices);
	meshes[mesh2->GetMeshID()] = mesh2;

	mesh3 = new Mesh("back");
	mesh3->InitFromData(directionBack, normals, textureCoords2, indices);
	meshes[mesh3->GetMeshID()] = mesh3;

	// Create a shader program for drawing face polygon with the color of the normal
	{
		Shader *shader = new Shader("ShaderLab9");
		shader->AddShader("Source/GameImpl/Shaders/VertexShader.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/GameImpl/Shaders/FragmentShader.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}

}

void Game::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
	
}



void Game::CheckCollision() {

	//mai intai se verifica ca lovitura se poate executa (nu sunt spate in spate,jucatorul care loveste nu e in fata celuilalt,etc)

	if ((p1->position.x <= p2->position.x && p1->direction.x == -1 && p2->direction.x == 1) ||
		(p1->position.x >= p2->position.x && p1->direction.x == 1 && p2->direction.x == -1) ||
		( p1->position.x >= p2->position.x && p1->direction.x ==1 && p2->direction.x == 1 && p1->hit ==1) ||
		( p1->position.x <= p2->position.x && p1->direction.x == -1 && p2->direction.x == -1 && p1->hit == 1) ||
		(p2->position.x >= p1->position.x && p1->direction.x == 1 && p2->direction.x == 1 && p2->hit == 1) ||
		(p2->position.x <= p1->position.x && p1->direction.x == -1 && p2->direction.x == -1 && p2->hit == 1))
		return;
	
	//se verifica daca un player a executat o lovitura iar daca celalalt a barat-o sau daca a exista coliziune
	else {
		if (p1->hit != 0) {
			if (abs(p1->position.x - p2->position.x) < 2 && p2->defence == 0) {
				p2->is_hit = 1;
				p2->stay = 0;
				if (p1->hit == 1) p2->no_lifes -= 1;
				else p2->no_lifes -= 3;
				return;
			}
		}
		if (p2->hit != 0) {
			if (abs(p1->position.x - p2->position.x) < 2 && p1->defence == 0) {
				p1->is_hit = 1;
				p1->stay = 0;
				if (p2->hit == 1) p1->no_lifes -= 1;
				else p1->no_lifes -= 3;
				return;
			}
		}
	}
}

//animatia de stat pe loc a primului player
void Game::runStayAnimationP1() {

	if (Engine::GetElapsedTime() - p1->lastTime > 0.3) {
		p1->lastTime = Engine::GetElapsedTime();
		if (p1->direction.x == 1) mesh1->InitFromData(direction1, normals, p1->getNextStay(sheet), indices);
		else mesh1->InitFromData(direction2, normals, p1->getNextStay(sheet), indices);


	}
}

//animatia de stat pe loc a celui de-al doilea
void Game::runStayAnimationP2(){
	if (Engine::GetElapsedTime() - p2->lastTime > 0.3) {
		p2->lastTime = Engine::GetElapsedTime();
		if (p2->direction.x == 1) mesh2->InitFromData(direction1, normals, p2->getNextStay(sheet), indices);
		else mesh2->InitFromData(direction2, normals, p2->getNextStay(sheet), indices);
	}
}

//animatiile in cazul in care player 1 il loveste pe 2 sau castiga runda
void Game::player1Wins() {

	if (Engine::GetElapsedTime() - p1->lastTime > 0.5) {
		p1->lastTime = Engine::GetElapsedTime();
		if (p2->no_lifes <= 0) {
			if (p1->direction.x == 1) mesh1->InitFromData(direction1, normals, p1->getNextWin(sheet), indices);
			else mesh1->InitFromData(direction2, normals, p1->getNextWin(sheet), indices);
		}
		else {
			if (p1->direction.x == 1) mesh1->InitFromData(direction1, normals, p1->getNextStay(sheet), indices);
			else mesh1->InitFromData(direction2, normals, p1->getNextStay(sheet), indices);
		}

	}

	if (Engine::GetElapsedTime() - p2->lastTime > 0.5) {
		p2->lastTime = Engine::GetElapsedTime();
		if (p2->direction.x == 1) mesh2->InitFromData(direction1, normals, p2->getNextCollapse(sheet), indices);
		else mesh2->InitFromData(direction2, normals, p2->getNextCollapse(sheet), indices);
	}
	if (p2->fin_collapse == 1) p2->is_hit = 0;
}

//animatiile pentru cazul in care player 2 il loveste pe 1 sau castiga runda
void Game::player2Wins() {
	if (Engine::GetElapsedTime() - p1->lastTime > 0.5) {
		p1->lastTime = Engine::GetElapsedTime();
		if (p1->direction.x == 1) mesh1->InitFromData(direction1, normals, p1->getNextCollapse(sheet), indices);
		else mesh1->InitFromData(direction2, normals, p1->getNextCollapse(sheet), indices);


	}
	if (Engine::GetElapsedTime() - p2->lastTime > 0.5) {
		p2->lastTime = Engine::GetElapsedTime();
		if (p1->no_lifes <= 0) {
			if (p2->direction.x == 1) mesh2->InitFromData(direction1, normals, p2->getNextWin(sheet), indices);
			else mesh2->InitFromData(direction2, normals, p2->getNextWin(sheet), indices);
		}
		else {
			if (p2->direction.x == 1) mesh2->InitFromData(direction1, normals, p2->getNextStay(sheet), indices);
			else mesh2->InitFromData(direction2, normals, p2->getNextStay(sheet), indices);
		}
	}
	if (p1->fin_collapse == 1) p1->is_hit = 0;
}

void Game::Update(float deltaTimeSeconds)
{
	//daca niciun player nu a fost lovit si nicio tasta apasata,inseamna ca stau pe loc

	if (p1->is_hit == 0 && p2->is_hit == 0) {
		CheckCollision();
		if (p1->stay == 1) {
			runStayAnimationP1();
		}
		if (p2->is_hit == 0 && p2->stay == 1) {
			runStayAnimationP2();
		}
	}

	//player 2 lovit,1 castiga
	if (p2->is_hit == 1) {
		player1Wins();
	}

	//player 1 lovit,2 castiga
	if (p1->is_hit == 1) {
		player2Wins();
	}

	//randam obiectele + backgroundul

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, p1->position);
		RenderSimpleMesh(meshes["player1"], shaders["ShaderLab9"], modelMatrix, mapTextures["fight"]);
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, p2->position);
		RenderSimpleMesh(meshes["player2"], shaders["ShaderLab9"], modelMatrix, mapTextures["fight"]);
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		RenderSimpleMesh(meshes["back"], shaders["ShaderLab9"], modelMatrix, mapTextures["background"]);
	}

	//la finalul fiecarui frame consideram ca playerii se opresc
	p1->stay = 1;
	p2->stay = 1;

}

void Game::FrameEnd()
{
	
}

void Game::RenderSimpleMesh(Mesh *mesh, Shader *shader, const glm::mat4 & modelMatrix, Texture2D* texture1,Texture2D* texture2)
{
	if (!mesh || !shader || !shader->GetProgramID())
		return;

	if (!texture2)
		texture2 = texture1;
	// render an object using the specified shader and the specified position
	glUseProgram(shader->program);

	// Bind model matrix
	GLint loc_model_matrix = glGetUniformLocation(shader->program, "Model");
	glUniformMatrix4fv(loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	// Bind view matrix
	glm::mat4 viewMatrix = GetSceneCamera()->GetViewMatrix();
	int loc_view_matrix = glGetUniformLocation(shader->program, "View");
	glUniformMatrix4fv(loc_view_matrix, 1, GL_FALSE, glm::value_ptr(viewMatrix));

	// Bind projection matrix
	glm::mat4 projectionMatrix = GetSceneCamera()->GetProjectionMatrix();
	int loc_projection_matrix = glGetUniformLocation(shader->program, "Projection");
	glUniformMatrix4fv(loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

	if (texture1)
	{
		glActiveTexture(GL_TEXTURE0);

		glBindTexture(GL_TEXTURE_2D, texture1->GetTextureID());

		glUniform1i(glGetUniformLocation(shader->program, "texture_1"), 0);


	}

	if (texture2)
	{
		glActiveTexture(GL_TEXTURE1);

		glBindTexture(GL_TEXTURE_2D, texture2->GetTextureID());

		glUniform1i(glGetUniformLocation(shader->program, "texture_2"), 1);
		glUniform1i(glGetUniformLocation(shader->program, "t1"), 1);
	}

	// Draw the object
	glBindVertexArray(mesh->GetBuffers()->VAO);
	glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_SHORT, 0);
}



// Documentation for the input functions can be found in: "/Source/Core/Window/InputController.h" or
// https://github.com/UPB-Graphics/Framework-EGC/blob/master/Source/Core/Window/InputController.h

void Game::OnInputUpdate(float deltaTime, int mods)
{
	//daca player 1 nu a fost lovit inseamna ca acesta poate executa actiuni
	if (p1->is_hit == 0) {
		//miscare stanga
		if (window->KeyHold(GLFW_KEY_A)) {
			p1->stay = 0;
			p1->direction.x = -1;
			if (p1->position.x <= -7) p1->position.x = -7;
			p1->TranslateRight(deltaTime * p1->speed);
			
			if (Engine::GetElapsedTime() - p1->lastTime > p1->standardTime) {
				p1->standardTime -= deltaTime;
				p1->speed += deltaTime * 50;
				p1->lastTime = Engine::GetElapsedTime();
				mesh1->InitFromData(direction2, normals, p1->getNextWalk(sheet), indices);
			}

		}
		//miscare dreapta
		if (window->KeyHold(GLFW_KEY_D)) {
			p1->stay = 0;
			p1->direction.x = 1;
			p1->TranslateRight(deltaTime * p1->speed);
			if (p1->position.x >= 7) p1->position.x = 7;
			if (Engine::GetElapsedTime() - p1->lastTime > p1->standardTime) {
				p1->standardTime -= deltaTime;
				p1->speed += deltaTime * 50;
				p1->lastTime = Engine::GetElapsedTime();
				mesh1->InitFromData(direction1, normals, p1->getNextWalk(sheet), indices);
			}
		}

		//lovitura pumn
		if (window->KeyHold(GLFW_KEY_S)) {
			p1->stay = 0;
			if (Engine::GetElapsedTime() - p1->lastTime > 0.2) {
				
				p1->lastTime = Engine::GetElapsedTime();
				if (p1->direction.x == 1)
					mesh1->InitFromData(direction1, normals, p1->getNextHit(sheet), indices);
				else mesh1->InitFromData(direction2, normals, p1->getNextHit(sheet), indices);
			}
		}
		//lovitura picior
		if (window->KeyHold(GLFW_KEY_SPACE)) {
			p1->stay = 0;
			if (Engine::GetElapsedTime() - p1->lastTime > 0.3) {
				p1->lastTime = Engine::GetElapsedTime();
				if (p1->direction.x == 1)
					mesh1->InitFromData(direction1, normals, p1->getNextSword(sheet), indices);
				else mesh1->InitFromData(direction2, normals, p1->getNextSword(sheet), indices);
			}
		}
		//aparare
		if (window->KeyHold(GLFW_KEY_W)) {
			p1->stay = 0;
			if (Engine::GetElapsedTime() - p1->lastTime > 0.3) {
				p1->lastTime = Engine::GetElapsedTime();
				if (p1->direction.x == 1)
					mesh1->InitFromData(direction1, normals, p1->getNextDefence(sheet), indices);
				else mesh1->InitFromData(direction2, normals, p1->getNextDefence(sheet), indices);
			}
		}
	}

	//daca playerul 2 nu a fost lovit inseamna ca poate executa alte miscari
	if (p2->is_hit == 0){
		//miscare stanga
		if (window->KeyHold(GLFW_KEY_LEFT)) {
			p2->stay = 0;
			p2->direction.x = -1;
			p2->TranslateRight(deltaTime * p2->speed);
			if (p2->position.x <= -7) p2->position.x = -7;
			if (Engine::GetElapsedTime() - p2->lastTime > p2->standardTime) {
				p2->standardTime -= deltaTime;
				p2->speed += deltaTime * 50;
				p2->lastTime = Engine::GetElapsedTime();
				mesh2->InitFromData(direction2, normals, p2->getNextWalk(sheet), indices);
			}
		}
		//miscare dreapta
		if (window->KeyHold(GLFW_KEY_RIGHT)) {
			p2->stay = 0;
			p2->direction.x = 1;
			p2->TranslateRight(deltaTime * p2->speed);
			if (p2->position.x >= 7) p2->position.x = 7;
			if (Engine::GetElapsedTime() - p2->lastTime > p2->standardTime) {
				p2->standardTime -= deltaTime;
				p2->speed += deltaTime * 50;
				p2->lastTime = Engine::GetElapsedTime();
				mesh2->InitFromData(direction1, normals, p2->getNextWalk(sheet), indices);
			}
		}
		//lovitura pumn
		if (window->KeyHold(GLFW_KEY_DOWN)) {
			p2->stay = 0;
			if (Engine::GetElapsedTime() - p2->lastTime > 0.2) {
				p2->lastTime = Engine::GetElapsedTime();
				if (p2->direction.x == 1)
					mesh2->InitFromData(direction1, normals, p2->getNextHit(sheet), indices);
				else mesh2->InitFromData(direction2, normals, p2->getNextHit(sheet), indices);
			}
		}
		//aparare
		if (window->KeyHold(GLFW_KEY_UP)) {
			p2->stay = 0;
			if (Engine::GetElapsedTime() - p2->lastTime > 0.3) {
				p2->lastTime = Engine::GetElapsedTime();
				if (p2->direction.x == 1)
					mesh2->InitFromData(direction1, normals, p2->getNextDefence(sheet), indices);
				else mesh2->InitFromData(direction2, normals, p2->getNextDefence(sheet), indices);
			}
		}
		//lovitura picior
		if (window->KeyHold(GLFW_KEY_KP_0)) {
			p2->stay = 0;
			if (Engine::GetElapsedTime() - p2->lastTime > 0.3) {
				p2->lastTime = Engine::GetElapsedTime();
				if (p2->direction.x == 1)
					mesh2->InitFromData(direction1, normals, p2->getNextSword(sheet), indices);
				else mesh2->InitFromData(direction2, normals, p2->getNextSword(sheet), indices);
			}
		}
	}
}

void Game::OnKeyPress(int key, int mods)
{
	// add key press event
}

void Game::OnKeyRelease(int key, int mods)
{
	// add key release event
}

void Game::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// add mouse move event
}

void Game::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
}

void Game::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
}

void Game::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Game::OnWindowResize(int width, int height)
{
}
