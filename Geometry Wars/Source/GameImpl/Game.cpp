#include "Game.h"

#include <vector>
#include <iostream>
#include <cmath>
#include <time.h>

#include <Core/Engine.h>
#include "Transform2D.h"
#include "GameObject.h"
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"

using namespace std;

Player *player;
vector<Enemy*> enemies;
vector<Bullet*> bullets;
float currentX;
float currentY;
float r = 1280;
float gameOverScreen = 0;
float scaleFactor = 0;
float sinceLast = 0;
float timeForNext = 2;



Game::Game()
{
}

Game::~Game()
{
}

void Game::Init()
{
	srand(time(NULL));
	int angle = rand() % 101;
	glm::ivec2 resolution = window->GetResolution();

	auto camera = GetSceneCamera();
	camera->SetPosition(glm::vec3(0, 0, 50));
	camera->SetRotation(glm::vec3(0, 0, 0));
	camera->Update();
	GetCameraInput()->SetActive(false);

	player = new Player(glm::vec3 (0,0,0),1,0,glm::vec3 (0.000, 0.749, 1.000),3,400);
	enemies.push_back(new Enemy(glm::vec3(0, 0, 0), 1, 0, glm::vec3(1, 1, 0), 2, 50,false));
	Bullet *b = new Bullet(glm::vec3(0, 0, 0), 1, 0, glm::vec3(0.5, 1, 0.5), 0, 1000);
	
	logicSpace.x = -1280;		
	logicSpace.y = -720;		
	logicSpace.width = 2560;	
	logicSpace.height = 1440;	

	viewSpace = ViewportSpace(0, 0, resolution.x, resolution.y);
	SetViewportArea(viewSpace, glm::vec3(0.5f), true);

	visMatrix = glm::mat3(1);
	visMatrix *= VisualizationTransf2D(logicSpace, viewSpace);

	//coordonatele punctelor ce formeaza dreptunghiurile pt vieti

	vector<VertexFormat> vertices
	{
		VertexFormat(glm::vec3(1180,630,  0), glm::vec3(0.5, 1, 0.5)),
		VertexFormat(glm::vec3(1180,700, 0), glm::vec3(0.5, 1, 0.5)),
		VertexFormat(glm::vec3(1190,700,  0), glm::vec3(0.5, 1, 0.5)),
		VertexFormat(glm::vec3(1190,630,  0), glm::vec3(0.5, 1, 0.5)),
		
	};

	std::vector<unsigned short> indices
	{
		0, 1, 3,1,2,3
	};

	//incarcare obiecte memorie

	meshes["life"] = CreateMesh("life", vertices, indices);
	meshes["bullet"] = CreateMesh("bullet", b->vertices, b->indices);
	meshes["player"] = CreateMesh("player", player->vertices, player->indices);
	meshes["enemy"] = CreateMesh("enemy", enemies[0]->vertices, enemies[0]->indices);
	enemies[0]->position[0] = r * cos(angle);
	enemies[0]->position[1] = r * sin(angle);
	enemies[0]->speed *= rand() % 6 + 1;

}

//functie care incarca pe placa grafica detalii despre geometria obiectelor

Mesh* Game::CreateMesh(const char *name, const std::vector<VertexFormat> &vertices, const std::vector<unsigned short> &indices)
{
	unsigned int VAO = 0;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	unsigned int VBO = 0;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0])*vertices.size(), &vertices[0], GL_STATIC_DRAW);

	unsigned int IBO = 0;
	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0])*indices.size(), &indices[0], GL_STATIC_DRAW);


	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), 0);


	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(sizeof(glm::vec3)));


	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3)));


	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3) + sizeof(glm::vec2)));
	CheckOpenGLError();

	meshes[name] = new Mesh(name);
	meshes[name]->InitFromBuffer(VAO, static_cast<unsigned short>(indices.size()));
	return meshes[name];
}


glm::mat3 Game::VisualizationTransf2D(const LogicSpace & logicSpace, const ViewportSpace & viewSpace)
{
	float sx, sy, tx, ty;
	sx = viewSpace.width / logicSpace.width;
	sy = viewSpace.height / logicSpace.height;
	tx = viewSpace.x - sx * logicSpace.x;
	ty = viewSpace.y - sy * logicSpace.y;

	return glm::transpose(glm::mat3(
		sx, 0.0f, tx,
		0.0f, sy, ty,
		0.0f, 0.0f, 1.0f));
}

void Game::SetViewportArea(const ViewportSpace & viewSpace, glm::vec3 colorColor, bool clear)
{
	glViewport(viewSpace.x, viewSpace.y, viewSpace.width, viewSpace.height);

	glEnable(GL_SCISSOR_TEST);
	glScissor(viewSpace.x, viewSpace.y, viewSpace.width, viewSpace.height);

	glClearColor(colorColor.r, colorColor.g, colorColor.b, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glDisable(GL_SCISSOR_TEST);

	GetSceneCamera()->SetOrthographic((float)viewSpace.x, (float)(viewSpace.x + viewSpace.width), (float)viewSpace.y, (float)(viewSpace.y + viewSpace.height), 0.1f, 400);
	GetSceneCamera()->Update();
}

void Game::FrameStart()
{
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
}

//functie ce adauga dupa o anumita perioada de timp un inamic nou

void Game::AddNewPlayer() {
		 
	if (Engine::GetElapsedTime() - sinceLast > timeForNext) {

		sinceLast = Engine::GetElapsedTime();
		int no_lifes = rand() % 2 + 1;
		int angle = rand() % 101;

		if (no_lifes == 2)
			enemies.push_back(new Enemy(glm::vec3(0, 0, 0), 1, 0, glm::vec3(1,1,0), 2, 50,false));
		else
			enemies.push_back(new Enemy(glm::vec3(0, 0, 0), 1, 0, glm::vec3(1.000, 0.412, 0.706), 1, 50,false));
		
		meshes["enemy"] = CreateMesh("enemy", enemies[0]->vertices, enemies[0]->indices);
		enemies[enemies.size()-1]->position[0] = r * cos(angle);
		enemies[enemies.size() - 1]->position[1] = r * sin(angle);
		enemies[enemies.size() - 1]->speed *= rand() % 6 + 1;

		if (timeForNext > 0.5)
			timeForNext -= 0.5;
		else
			timeForNext = 0.5;
	}

	
}

//detecteasa coliziunea inamic-player

void Game::CollisionDetected() {
		
	for (int i = 0; i < enemies.size(); i++) {
		float dx = abs(player->position[0] - enemies[i]->position[0]);
		float dy = abs(player->position[1] - enemies[i]->position[1]);
		float d = sqrt(dx * dx + dy * dy);
		
		if (d <= 60) {
			enemies.erase(enemies.begin() + i);
			player->no_lifes -= 1;
		}
	}
}

//detecteaza coliziunea bullet-inamic

void Game::CollisionBulletDetected() {

	for (int i = 0; i < bullets.size(); i++) {
		for (int j = 0; j < enemies.size(); j++) {
		
			float dx = abs(bullets[i]->position[0] - enemies[j]->position[0]);
			float dy = abs(bullets[i]->position[1] - enemies[j]->position[1]);
			float d = sqrt(dx * dx + dy * dy);
			
			if (d <= 60) {
				bullets.erase(bullets.begin() + i);
				
				if (enemies[j]->no_lifes == 1) {
					enemies.erase(enemies.begin() + j);
				}
				else {
					enemies[j]->no_lifes -= 1;
					enemies[j]->hit = true;
					enemies[j]->colour = glm::vec3(1, 0, 0);
				}
				break;
			}
		}
	}
}

//updateaza pozitia inamicului la fiecare frame

void Game::UpdateEnemiesPositions(float deltaTimeSeconds) {

	for (int i = 0; i < enemies.size(); i++) {

		enemies[i]->rotation = atan2(enemies[i]->position[1] - player->position[1], enemies[i]->position[0] - player->position[0]) + (3.1415 / 2);
		
		float x = player->position[0] - enemies[i]->position[0];
		float y = player->position[1] - enemies[i]->position[1];
		
		glm::vec2 norma(x / sqrt(x * x + y * y), y / sqrt(x * x + y * y));
		enemies[i]->position[0] += norma[0] * enemies[i]->speed * deltaTimeSeconds;
		enemies[i]->position[1] += norma[1] * enemies[i]->speed * deltaTimeSeconds;

		if (enemies[i]->hit){
			if (enemies[i]->scale > 0.5)
				enemies[i]->scale -= 2 * deltaTimeSeconds;
			else enemies[i]->scale = 0.5;
		}

		modelMatrix = visMatrix;
		modelMatrix *= Transform2D::Translate(enemies[i]->position[0], enemies[i]->position[1]);
		modelMatrix *= Transform2D::Rotate(enemies[i]->rotation);
		modelMatrix *= Transform2D::Scale(enemies[i]->scale,enemies[i]->scale);
		RenderMesh2D(meshes["enemy"], modelMatrix, enemies[i]->colour);

	}
}

//seteaza numarul de vieti ramase la fiecare frame(updateaza dreptunghiurile)

void Game::SetNoLifes() {

	if (player->no_lifes == 3) {
		modelMatrix = visMatrix;
		RenderMesh2D(meshes["life"], modelMatrix, glm::vec3(1, 1, 0));
	}

	if (player->no_lifes > 1) {
		modelMatrix = visMatrix;
		modelMatrix *= Transform2D::Translate(30, 0);
		RenderMesh2D(meshes["life"], modelMatrix, glm::vec3(1, 1, 0));
	}

	if (player->no_lifes > 0) {
		modelMatrix = visMatrix;
		modelMatrix *= Transform2D::Translate(60, 0);
		RenderMesh2D(meshes["life"], modelMatrix, glm::vec3(1, 1, 0));
	}
}

//updateaza pozitia playerului

void Game::PutPlayerInScene() {
	modelMatrix = visMatrix;
	modelMatrix *= Transform2D::Translate(player->position[0], player->position[1]);
	modelMatrix *= Transform2D::Rotate(player->rotation);

	RenderMesh2D(meshes["player"], modelMatrix, player->colour);
}

//efectul de ecran rosu cand playerul ramane fara vieti

void Game::StopGame(float deltaTimeSeconds) {
	
	if (gameOverScreen < 1){
		gameOverScreen += 0.5 * deltaTimeSeconds;
		glClearColor(gameOverScreen, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
	else {
		glClearColor(1, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	//repune in scena obiectele

	modelMatrix = visMatrix;	
	RenderMesh2D(meshes["player"], modelMatrix, player->colour);
	
	for (int i = 0; i < enemies.size(); i++) {
		modelMatrix = visMatrix;
		modelMatrix *= Transform2D::Translate(enemies[i]->position[0], enemies[i]->position[1]);
		modelMatrix *= Transform2D::Rotate(enemies[i]->rotation);
		RenderMesh2D(meshes["enemy"], modelMatrix, enemies[i]->colour);
	}
}

//updateaza pozitia gloantelor la fiecare frame

void Game::TriggerBullets(float deltaTimeSeconds) {

	for (int i = 0; i < bullets.size(); i++) {

		modelMatrix = visMatrix;
		modelMatrix *= Transform2D::Translate(bullets[i]->position[0], bullets[i]->position[1]);
		modelMatrix *= Transform2D::Rotate(bullets[i]->rotation);

		bullets[i]->position[0] += bullets[i]->speed * cos(bullets[i]->rotation + 4.68) * deltaTimeSeconds;
		bullets[i]->position[1] += bullets[i]->speed * sin(bullets[i]->rotation + 4.68) * deltaTimeSeconds;
		RenderMesh2D(meshes["bullet"], modelMatrix, bullets[i]->colour);
	}
}

void Game::Update(float deltaTimeSeconds)
{

	//daca jocul nu se termina

	if (player->no_lifes != 0) {	

		PutPlayerInScene();		//seteaza pozitia playerului
		AddNewPlayer();		//adauga un nou inamic daca e cazul
		CollisionDetected();	//detectia coliziunii inamic-player
		CollisionBulletDetected();		//detectia coliziunii glont-inamic
		TriggerBullets(deltaTimeSeconds);		//updateaza pozitia glontului
		UpdateEnemiesPositions(deltaTimeSeconds);		//updateaza pozitia fiecarui inamic
		SetNoLifes();		//recalculeaza numarul de vieti

	}
	else
	{
		StopGame(deltaTimeSeconds);		//daca jocul se termina -> ecran rosu
	}
}

void Game::OnInputUpdate(float deltaTime, int mods)
{

	if (window->KeyHold(GLFW_KEY_W)) {
		player->position[1] += player->speed * deltaTime;		//miscare pe OY in sus
	}

	if (window->KeyHold(GLFW_KEY_S)) {
		player->position[1] -= player->speed * deltaTime;		//miscare pe OY in jos
	}

	if (window->KeyHold(GLFW_KEY_A)) {
		player->position[0] -= player->speed * deltaTime;		//miscare pe OX in stanga
	}

	if (window->KeyHold(GLFW_KEY_D)) {
		player->position[0] += player->speed * deltaTime;		//miscare pe OX in dreapta
	}

	//setarea unghiului de rotatie in functie de pozitia relativa a playerului la mouse

	player->rotation = atan2(currentY - player->position[1], currentX - player->position[0]) + (3.1415 / 2);

}

void Game::OnKeyPress(int key, int mods)
{

}

void Game::OnKeyRelease(int key, int mods)
{
	
}

void Game::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{

	//seteaza unghiul de rotire in functie de pozitia mouseului pe ecran
	
	mouseX = mouseX * (logicSpace.width / window->GetResolution().x) + logicSpace.x;
	mouseY = (window->GetResolution().y - mouseY) * ((logicSpace.height / window->GetResolution().y)) + logicSpace.y;
	currentX = mouseX;
	currentY = mouseY;
	player->rotation = atan2(mouseY-player->position[1],mouseX - player->position[0]) + (3.1415/2);
	
}

void Game::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{

	//creeaza un nou glont atunci cand apasam mouseul

	if (window->MouseHold(GLFW_MOUSE_BUTTON_LEFT)){
	
		bullets.push_back(new Bullet(glm::vec3(0, 0, 0), 1, 0, glm::vec3(0.561, 0.737, 0.561), 0, 1000));
		bullets[bullets.size() - 1]->rotation = player->rotation;
		bullets[bullets.size() - 1] -> position= player->position;
	
	}
}

void Game::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	
}

void Game::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{

}