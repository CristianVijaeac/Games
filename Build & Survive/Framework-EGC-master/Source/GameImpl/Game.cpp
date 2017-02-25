#include "Game.h"

#include <vector>
#include <string>
#include <iostream>
#include "Player.h"
#include "Tower.h"
#include "Enemy.h"
#include "Bullet.h"
#include <time.h>

#include <Core/Engine.h>

using namespace std;

float rotation,rotationS;
Player *player;
vector<Tower*> towers;
vector<Enemy*> enemies;
vector<Bullet*> bullets1,bullets2,bullets3,bullets4;
glm::vec3 offsetC(0.0f, 0.5f, 0.0f);
float offsetF = 3.0f;
float sinceLast1 = 0,sinceLast2 = 0,sinceLastB1 = 0,sinceLastB2 = 0,sinceLastB3 = 0;
int weapon = 1;
float timeForNext = 5, noLifes = 1;
bool down = false;
float orthoLeft = -25,orthoRight = 25,bottom = 25,top = -25;


Game::Game()
{
}

Game::~Game()
{
}

void Game::Init()
{

	player = new Player(glm::vec3(0, 0, 0), 0, 0, 3, 5.0f, glm::vec3(0.0f, 1.0f, 0.0f),bullets4,0);

	//initializare camere

	camera = new Laborator::Camera();
	camera->Set(player->position - (player->forward) * offsetF, player->position + offsetC, glm::vec3(0, 1 ,0));
	camera2 = new Laborator::Camera();
	camera2->Set(glm::vec3(0,200,0), glm::vec3(0,0,0), glm::vec3(0, 0, -1));

	//initializare turnuri

	towers.push_back(new Tower(glm::vec3(-10, 0, -5), 0.01f, 0, 100,bullets1));
	towers.push_back(new Tower(glm::vec3(10, 0, -5), 0.01f , 0, 100,bullets2));
	towers.push_back(new Tower(glm::vec3(0, 0, -10), 0.01f, 0, 100, bullets3));
	
	enemies.push_back(new Enemy(glm::vec3(-20, 2,-20), 2, 0, noLifes,100,0,0));

	{
		Mesh* mesh = new Mesh("box");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "box.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	{
		Mesh* mesh = new Mesh("sphere");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "sphere.obj");
		meshes[mesh->GetMeshID()] = mesh;

	}

	{
		Mesh* mesh = new Mesh("monster");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "MonsterLowPoly.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	{
		Mesh* mesh = new Mesh("player");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "Steve.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	{
		Mesh* mesh = new Mesh("tower");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "tower.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	projectionMatrix = glm::perspective(RADIANS(60), window->props.aspectRatio, 0.01f, 200.0f);
	projectionMatrix2 = glm::ortho(orthoLeft, orthoRight, top, bottom, 0.01f, 1000.0f);
}

void Game::FrameStart()
{
	
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	glViewport(0, 0, resolution.x, resolution.y);

}

//in functie de numarul de vieti punem in scena si rotim cele 3 sfere

void Game::SetLifes(float deltaTimeSeconds) {

	rotationS += 50 * deltaTimeSeconds;

	if (player->no_lifes == 3)
	{
		glm::mat4 modelMatrix = glm::mat4(1);

		modelMatrix = glm::translate(modelMatrix, player->position + offsetC);
		modelMatrix = glm::rotate(modelMatrix, player->rotation, glm::vec3(0, 1, 0));
		modelMatrix = glm::rotate(modelMatrix, RADIANS(rotationS), glm::vec3(1.0f, 0.0f, 0.0f));
		modelMatrix = glm::translate(modelMatrix, offsetC);
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.1f, 0.1f, 0.1f));

		RenderMesh(meshes["sphere"], shaders["VertexNormal"], modelMatrix, 1);

	}

	if (player->no_lifes >=2)

	{
		glm::mat4 modelMatrix = glm::mat4(1);

		modelMatrix = glm::translate(modelMatrix, player->position);
		modelMatrix = glm::rotate(modelMatrix, RADIANS(rotationS), glm::vec3(0.0f, 1.0f, 0.0f));
		modelMatrix = glm::translate(modelMatrix, offsetC + glm::vec3(0, 0, 0.5f));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.1f, 0.1f, 0.1f));

		RenderMesh(meshes["sphere"], shaders["VertexNormal"], modelMatrix,1);
	

	}

	if (player->no_lifes >= 1)

	{
		glm::mat4 modelMatrix = glm::mat4(1);

		modelMatrix = glm::translate(modelMatrix, player->position + offsetC);
		modelMatrix = glm::rotate(modelMatrix, player->rotation, glm::vec3(0, 1, 0));
		modelMatrix = glm::rotate(modelMatrix, RADIANS(rotationS), glm::vec3(0.0f, 0.0f, 1.0f));
		modelMatrix = glm::rotate(modelMatrix, player->rotation, glm::vec3(0, 1, 0));
		modelMatrix = glm::translate(modelMatrix, offsetC - glm::vec3(0.25f, 0, 0));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.1f, 0.1f, 0.1f));

		RenderMesh(meshes["sphere"], shaders["VertexNormal"], modelMatrix,1);
		
	}
}

//plasam in scena playerul si setam camera in functie de coord acestuia

void Game::SetPlayerAndCamera() {

	if (player->no_lifes > 0) {

		//armele 1 si 3 folosesc Third Person,arma 2 First Person

		if (weapon == 1 || weapon == 3)
			camera->Set(player->position - (player->forward) * offsetF, player->position + offsetC, player->up);
		else
			camera->Set(player->position + 2.0f * offsetC, player->position + 2.0f * offsetC + player->forward, player->up);

		glm::mat4 modelMatrix = glm::mat4(1);

		modelMatrix = glm::translate(modelMatrix, player->position);
		modelMatrix = glm::rotate(modelMatrix, player->rotation, glm::vec3(0, 1, 0));
		modelMatrix = glm::rotate(modelMatrix, RADIANS(90), glm::vec3(0, 1, 0));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.1f));

		RenderMesh(meshes["player"], shaders["VertexNormal"], modelMatrix,1);
		
	}
}

//punem turnurile in scena

void Game::SetTowers(float deltaTimeSeconds) {

	for (int i = 0 ; i < towers.size();i++)
	{
		{
			glm::mat4 modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, towers[i]->position);
			modelMatrix = glm::rotate(modelMatrix, towers[i]->rotation, glm::vec3(0, 1, 0));
			modelMatrix = glm::scale(modelMatrix, glm::vec3(towers[i]->scale, towers[i]->scale, towers[i]->scale));
			RenderMesh(meshes["tower"], shaders["VertexNormal"], modelMatrix,1);
			
		}

		//daca putem trage cu un nou glont cautam daca exista cel mai apropiat inamic

		if (Engine::GetElapsedTime() - sinceLast2 > 1) {

			sinceLast2 = Engine::GetElapsedTime();
			for (int j = 0; j < enemies.size(); j++) {

				float dx = abs(enemies[j]->position.x - towers[i]->position.x);
				float dy = abs(enemies[j]->position.z - towers[i]->position.z);
				float dist = sqrt(dx * dx + dy * dy);

				//daca da,adaugam un nou glont tras pe directia inamicului gasit

				if (dist <= 10) {	
					glm::vec3 direction = glm::normalize(enemies[j]->position-(towers[i]->position+ glm::vec3(0, 5, 0)));
					towers[i]->bullets.push_back(new Bullet(towers[i]->position + glm::vec3(0, 5, 0), 0.3f, 0, 100, direction));
				}
			}
		}
		
		//updatam pozitia gloantelor si le stergem pe cele care ies din scena

		for (int k = 0; k < towers[i]->bullets.size(); k++) {
			
			{
				towers[i]->bullets[k]->position += 15.0f * towers[i]->bullets[k]->direction * deltaTimeSeconds;
				
				if (towers[i]->bullets[k]->position.y <= -5){
					towers[i]->bullets.erase(towers[i]->bullets.begin() + k);
					continue;
				}
				glm::mat4 modelMatrix = glm::mat4(1);
				modelMatrix = glm::translate(modelMatrix, towers[i]->bullets[k]->position);
				modelMatrix = glm::scale(modelMatrix, glm::vec3(towers[i]->bullets[k]->scale, towers[i]->bullets[k]->scale, towers[i]->bullets[k]->scale));
				RenderMesh(meshes["sphere"], shaders["VertexNormal"], modelMatrix,1);
				
			}
		}
	}

	

}

//setam noile pozitii ale inamicilor(aici am hardcodat calea pe care o urmeaza(Z))

void Game::SetEnemies(float deltaTimeSeconds) {

	for (int i = 0; i < enemies.size(); i++)

	{
		
		if (enemies[i]->no_lifes > 0) {
			if (enemies[i]->position.x >= 20)
				enemies[i]->path = 1;
			if (enemies[i]->position.z >= 20)
				enemies[i]->path = 2;

			if (enemies[i]->path == 0) {
				enemies[i]->position += glm::vec3(10 * deltaTimeSeconds, 0, 0);
				enemies[i]->rotation = 90;

			}
			else if (enemies[i]->path == 1)
			{
				enemies[i]->position += glm::vec3(-5 * deltaTimeSeconds, 0, 3 * deltaTimeSeconds);
				enemies[i]->rotation = -45;

			}
			else {
				enemies[i]->position += glm::vec3(5 * deltaTimeSeconds, 0, 0);
				enemies[i]->rotation = 90;
			}
			glm::mat4 modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, enemies[i]->position);
			modelMatrix = glm::rotate(modelMatrix, RADIANS(enemies[i]->rotation), glm::vec3(0, 1, 0));
			modelMatrix = glm::scale(modelMatrix, glm::vec3(enemies[i]->scale, enemies[i]->scale, enemies[i]->scale));
			RenderMesh(meshes["monster"], shaders["VertexNormal"], modelMatrix,1);
			
		}
		
	}
}

//adaugarea de noi inamici dupa un timp

void Game::AddNewEnemies() {

	if (Engine::GetElapsedTime() - sinceLast1 > timeForNext) {

		//inamicii vin din ce in ce mai repede

		if (timeForNext > 2)
			timeForNext -= 0.25;

		//fiecare inamic are cu o viata mai mult

			noLifes += 1;

		sinceLast1 = Engine::GetElapsedTime();
		enemies.push_back(new Enemy(glm::vec3(-20, 2, -20), 2, 0, noLifes,100, 0,0));

	}
}

//verificam daca un inamic a reusit sa ajunga in coltul din dreapta jos

void Game::EnemyEscapedDetection() {

	for (int i = 0; i < enemies.size(); i++)
	{
		if (enemies[i]->position.z >= 20 && enemies[i]->position.x >= 20) 
		{
			//daca da,playerul pierde o viata si stergem inamicul
			player->no_lifes -= 1;
			enemies.erase(enemies.begin() + i);
		}
	}
}


//verificam daca un glont tras de turn si-a atins tina sau alt inamic
void Game::TowerHitDetected() {

	for (int i = 0; i < towers.size(); i++) {
		for (int j = 0; j < enemies.size(); j++) {
			for (int k = 0; k < towers[i]->bullets.size(); k++) {

				float dx = abs(towers[i]->bullets[k]->position.x - enemies[j]->position.x);
				float dz = abs(towers[i]->bullets[k]->position.z - enemies[j]->position.z);

				if (dx <= 0.2 || dz <= 0.2) {
					towers[i]->bullets.erase(towers[i]->bullets.begin() + k);
					enemies[j]->no_lifes -= 1;
				}
			}
		}
	}
}

//gloantele trase de player sunt plasate in scena

void Game::TriggerPlayer(float deltaTimeSeconds) {

	for (int i = 0; i < player->bullets.size(); i++) {

		//mai intai verificam daca nu cumva proiectilul si-a depasit distana maxima de parcurs
		float dx = abs(player->bullets[i]->position.x - player->bullets[i]->oldPos.x);
		float dy = abs(player->bullets[i]->position.z - player->bullets[i]->oldPos.z);
		float dist = sqrt(dx * dx + dy * dy);

		if (dist >= player->bullets[i]->maxDist) {
			player->bullets.erase(player->bullets.begin() + i);
			continue;
		}

		//daca nu,ii actualizam pozitia
		if (player->bullets[i]->bulletType == 1 || player->bullets[i]->bulletType == 2) {

			player->bullets[i]->position.x += player->bullets[i]->direction.x * deltaTimeSeconds *player->bullets[i]->speed;
			player->bullets[i]->position.z += player->bullets[i]->direction.z * deltaTimeSeconds * player->bullets[i]->speed;

		}
		else {
			player->bullets[i]->position.x += player->bullets[i]->direction.x * deltaTimeSeconds *player->bullets[i]->speed;
			
			if (player->bullets[i]->position.y < 1.5f && !player->bullets[i]->down)
				player->bullets[i]->position.y += player->bullets[i]->direction.y * deltaTimeSeconds *player->bullets[i]->speed ;
			else {
				player->bullets[i]->down = true;
				player->bullets[i]->position.y -= player->bullets[i]->direction.y*deltaTimeSeconds * player->bullets[i]->speed;
			}
			
			player->bullets[i]->position.z += player->bullets[i]->direction.z * deltaTimeSeconds * player->bullets[i]->speed;

		}
		glm::mat4 modelMatrix = glm::mat4(1);
		
		modelMatrix = glm::translate(modelMatrix, player->bullets[i]->position);
		modelMatrix = glm::scale(modelMatrix, glm::vec3(player->bullets[i]->scale, player->bullets[i]->scale, player->bullets[i]->scale));
		
		RenderMesh(meshes["sphere"], shaders["VertexNormal"], modelMatrix,1);
		
	}
}

//verificam daca un proiectil lansat de player a atins vreun inamic

void Game::PlayerHitDetected() {

	for (int i = 0; i < player->bullets.size(); i++) {
		for (int j = 0; j < enemies.size(); j++) {

			float dx = abs(player->bullets[i]->position.x - enemies[j]->position.x);
			float dz = abs(player->bullets[i]->position.z - enemies[j]->position.z);
			
			float dist = sqrt(dx * dx + dz * dz);

			//in functie de tipul armei,scadem din vietile inamicului
			if (dist <= 1) {
				
				if (player->bullets[i]->bulletType == 1)
					enemies[j]->no_lifes -= 1;
				if (player->bullets[i]->bulletType == 2)
					enemies[j]->no_lifes -= 2;
				if (player->bullets[i]->bulletType == 3)
					enemies[j]->no_lifes -= 5;
				player->bullets.erase(player->bullets.begin() + i);
				break;
			}
		}
	}
}

//cand un inamic este omorat,executam o animatie de scalare si rotire
void Game::EnemyDeadAnimation(float deltaTimeSeconds) {

	for (int i = 0 ; i < enemies.size() ; i++)
		if (enemies[i]->no_lifes <= 0) {
			if (enemies[i]->scale > 0) {
				enemies[i]->scale -= 0.5 * deltaTimeSeconds;
				enemies[i]->rotationZ += 50 * deltaTimeSeconds;

				glm::mat4 modelMatrix = glm::mat4(1);

				modelMatrix = glm::translate(modelMatrix, enemies[i]->position);
				modelMatrix = glm::rotate(modelMatrix, RADIANS(enemies[i]->rotationZ), glm::vec3(0, 0, 1));
				modelMatrix = glm::rotate(modelMatrix, RADIANS(enemies[i]->rotation), glm::vec3(0, 1, 0));
				modelMatrix = glm::scale(modelMatrix, glm::vec3(enemies[i]->scale, enemies[i]->scale, enemies[i]->scale));
				
				RenderMesh(meshes["monster"], shaders["VertexNormal"], modelMatrix,1);
			
			}
				else {
					enemies.erase(enemies.begin() + i);
				}
		}
}

//scena se blocheaza iar playerul se invarta in jurul axei OZ
void Game::PlayerDeadAnimation(float deltaTimeSeconds) {

		camera->Set(player->position - (player->forward) * offsetF, player->position + offsetC, player->up);
		
		if (player->rotationZ < 3.14 / 2)
			player->rotationZ += 2 * deltaTimeSeconds;
		
		glm::mat4 modelMatrix = glm::mat4(1);
		
		modelMatrix = glm::translate(modelMatrix, player->position);
		modelMatrix = glm::rotate(modelMatrix, player->rotationZ, glm::vec3(0, 0, 1));
		modelMatrix = glm::rotate(modelMatrix, player->rotation, glm::vec3(0, 1, 0));
		modelMatrix = glm::rotate(modelMatrix, RADIANS(90), glm::vec3(0, 1, 0));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.1f));
		
		RenderMesh(meshes["player"], shaders["VertexNormal"], modelMatrix,1);
		

		for (int i = 0; i < player->bullets.size(); i++) {
			glm::mat4 modelMatrix = glm::mat4(1);
			
			modelMatrix = glm::translate(modelMatrix, player->bullets[i]->position);
			modelMatrix = glm::scale(modelMatrix, glm::vec3(player->bullets[i]->scale, player->bullets[i]->scale, player->bullets[i]->scale));
			
			RenderMesh(meshes["sphere"], shaders["VertexNormal"], modelMatrix,1);
			
		}

		for (int i = 0; i < towers.size(); i++) {
			glm::mat4 modelMatrix = glm::mat4(1);
			
			modelMatrix = glm::translate(modelMatrix, towers[i]->position);
			modelMatrix = glm::rotate(modelMatrix, towers[i]->rotation, glm::vec3(0, 1, 0));
			modelMatrix = glm::scale(modelMatrix, glm::vec3(towers[i]->scale, towers[i]->scale, towers[i]->scale));
			
			RenderMesh(meshes["tower"], shaders["VertexNormal"], modelMatrix,1);
			
			
			for (int j = 0; j < towers[i]->bullets.size(); j++) {
				glm::mat4 modelMatrix = glm::mat4(1);
				
				modelMatrix = glm::translate(modelMatrix, towers[i]->bullets[j]->position);
				modelMatrix = glm::scale(modelMatrix, glm::vec3(towers[i]->bullets[j]->scale, towers[i]->bullets[j]->scale, towers[i]->bullets[j]->scale));
				
				RenderMesh(meshes["sphere"], shaders["VertexNormal"], modelMatrix,1);
				
			}
		}

		for (int i = 0; i < enemies.size(); i++) {
			glm::mat4 modelMatrix = glm::mat4(1);
			
			modelMatrix = glm::translate(modelMatrix, enemies[i]->position);
			modelMatrix = glm::rotate(modelMatrix, RADIANS(enemies[i]->rotation), glm::vec3(0, 1, 0));
			modelMatrix = glm::scale(modelMatrix, glm::vec3(enemies[i]->scale, enemies[i]->scale, enemies[i]->scale));
			
			RenderMesh(meshes["monster"], shaders["VertexNormal"], modelMatrix,1);
			
		}


}

//metoda ce schimba viewportul si construieste minimap-ul
void Game::CreateMiniMap() {

	glm::ivec2 resolution = window->GetResolution();
	glViewport(resolution.x - 300, 0, 300, 300);

	glEnable(GL_SCISSOR_TEST);
	glScissor(resolution.x - 300, 0, 300, 300);

	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glDisable(GL_SCISSOR_TEST);

	glm::mat4 modelMatrix = glm::mat4(1);
		
		modelMatrix = glm::translate(modelMatrix, player->position);
		modelMatrix = glm::rotate(modelMatrix, player->rotationZ, glm::vec3(0, 0, 1));
		modelMatrix = glm::rotate(modelMatrix, player->rotation, glm::vec3(0, 1, 0));
		modelMatrix = glm::rotate(modelMatrix, RADIANS(90), glm::vec3(1, 0, 0));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(3.0f));
		
	RenderMesh(meshes["box"], shaders["VertexNormal"], modelMatrix,2);
		

		for (int i = 0; i < player->bullets.size(); i++) {
			glm::mat4 modelMatrix = glm::mat4(1);
			
			modelMatrix = glm::translate(modelMatrix, player->bullets[i]->position);
			modelMatrix = glm::scale(modelMatrix, glm::vec3(2));
			
			RenderMesh(meshes["box"], shaders["VertexNormal"], modelMatrix,2);
			
		}

		for (int i = 0; i < towers.size(); i++) {
			glm::mat4 modelMatrix = glm::mat4(1);
			
			modelMatrix = glm::translate(modelMatrix, towers[i]->position);
			modelMatrix = glm::rotate(modelMatrix, RADIANS(90), glm::vec3(0, 0, 1));
			modelMatrix = glm::scale(modelMatrix, glm::vec3(4));
			
			RenderMesh(meshes["box"], shaders["VertexNormal"], modelMatrix,2);
			
			
			for (int j = 0; j < towers[i]->bullets.size(); j++) {
				glm::mat4 modelMatrix = glm::mat4(1);
				
				modelMatrix = glm::translate(modelMatrix, towers[i]->bullets[j]->position);
				modelMatrix = glm::scale(modelMatrix, glm::vec3(2));
				
				RenderMesh(meshes["sphere"], shaders["VertexNormal"], modelMatrix,2);
				
			}
		}

		for (int i = 0; i < enemies.size(); i++) {
			glm::mat4 modelMatrix = glm::mat4(1);
			
			modelMatrix = glm::translate(modelMatrix, enemies[i]->position);
			modelMatrix = glm::rotate(modelMatrix, RADIANS(enemies[i]->rotationZ), glm::vec3(0, 0, 1));
			modelMatrix = glm::rotate(modelMatrix, RADIANS(enemies[i]->rotation), glm::vec3(0, 1, 0));
			modelMatrix = glm::rotate(modelMatrix, RADIANS(90), glm::vec3(0, 1, 0));
			modelMatrix = glm::scale(modelMatrix, glm::vec3(3));
			
			RenderMesh(meshes["box"], shaders["VertexNormal"], modelMatrix,2);
			
		}

}

void Game::Update(float deltaTimeSeconds)
{
	
	
	if (player->no_lifes > 0) {
		SetPlayerAndCamera();
		EnemyDeadAnimation(deltaTimeSeconds);
		SetEnemies(deltaTimeSeconds);
		EnemyEscapedDetection();
		TowerHitDetected();
		PlayerHitDetected();
		SetTowers(deltaTimeSeconds);
		AddNewEnemies();
		TriggerPlayer(deltaTimeSeconds);
		SetLifes(deltaTimeSeconds);
	}else
		PlayerDeadAnimation(deltaTimeSeconds);

	DrawCoordinatSystem(camera->GetViewMatrix(), projectionMatrix);
	CreateMiniMap();

	
}

void Game::FrameEnd()
{
	
	
	DrawCoordinatSystem(camera2->GetViewMatrix(), projectionMatrix2);
}

void Game::RenderMesh(Mesh * mesh, Shader * shader, const glm::mat4 & modelMatrix,int c)
{
	if (!mesh || !shader || !shader->program)
		return;

	
	shader->Use();

	if (c == 1) {
		glUniformMatrix4fv(shader->loc_view_matrix, 1, GL_FALSE, glm::value_ptr(camera->GetViewMatrix()));
		glUniformMatrix4fv(shader->loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
		glUniformMatrix4fv(shader->loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));
	}
	else {
		glUniformMatrix4fv(shader->loc_view_matrix, 1, GL_FALSE, glm::value_ptr(camera2->GetViewMatrix()));
		glUniformMatrix4fv(shader->loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix2));
		glUniformMatrix4fv(shader->loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));
	}
	mesh->Render();
}

//deplasarea inainte,inapoi,stanga,dreapta precum si alegerea armei
void Game::OnInputUpdate(float deltaTime, int mods)
{

	
	if (window->KeyHold(GLFW_KEY_1)) {

		weapon = 1;

	}

	if (window->KeyHold(GLFW_KEY_2)) {

		weapon = 2;

	}

	if (window->KeyHold(GLFW_KEY_3)) {

		weapon = 3;

	}
	
	if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
	{
		
		if (window->KeyHold(GLFW_KEY_W)) {
			
			player->MoveForward(player->speed * deltaTime);
		}

		if (window->KeyHold(GLFW_KEY_A)) {
		
			player->TranslateRight( -deltaTime * player->speed );
		}

		if (window->KeyHold(GLFW_KEY_S)) {
	
			player->MoveForward(-deltaTime * player->speed );
		}

		if (window->KeyHold(GLFW_KEY_D)) {
			
			player->TranslateRight(deltaTime*player->speed );
		}


		
	}
}

void Game::OnKeyPress(int key, int mods)
{
	
}

void Game::OnKeyRelease(int key, int mods)
{
	
}

//playerul se orienteaza intotdeauna cu fata la mouse
void Game::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	

	if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
	{
		float sensivityOX = 0.001f;
		float sensivityOY = 0.001f;

			player->RotateFirstPerson_OX(sensivityOX * -deltaY);
			player->RotateFirstPerson_OY(sensivityOY * -deltaX);

			player->rotation += sensivityOY * -deltaX;
	}

}

//daca click stanga a fost apasat,in functie de tipul armei selectate,adaugam un nou glont in vectori pt a fi lansat
void Game::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	
	if (window->MouseHold(GLFW_MOUSE_BUTTON_LEFT)) {

		glm::vec3 direction1 = player->forward;
		glm::vec3 direction2 (player->forward.x,0.35f,player->forward.z);

		if (weapon == 1 && Engine::GetElapsedTime() - sinceLastB1 >= 0.8) {
			sinceLastB1 = Engine::GetElapsedTime();
			player->bullets.push_back(new Bullet(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), 0.1f, 0, 5,direction1,1, 10));
			player->bullets[player->bullets.size() - 1]->rotation = player->rotation;
			player->bullets[player->bullets.size() - 1]->position = player->position + offsetC;
			player->bullets[player->bullets.size() - 1]->oldPos = player->position + offsetC;
		}
		if (weapon == 2 && Engine::GetElapsedTime() - sinceLastB2 >= 0.5) {
			sinceLastB2 = Engine::GetElapsedTime();
			player->bullets.push_back(new Bullet(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), 0.25f, 0, 10, direction1,2, 30));
			player->bullets[player->bullets.size() - 1]->rotation = player->rotation;
			player->bullets[player->bullets.size() - 1]->position = player->position + player->forward + offsetC;
			player->bullets[player->bullets.size() - 1]->oldPos = player->position + offsetC;
		}
		if (weapon == 3 && Engine::GetElapsedTime() - sinceLastB3 >= 3) {
			sinceLastB3 = Engine::GetElapsedTime();
			player->bullets.push_back(new Bullet(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0),0.2f, 0, 1, direction2, 3, 5,false));
			player->bullets[player->bullets.size() - 1]->rotation = player->rotation;
			player->bullets[player->bullets.size() - 1]->position = player->position + offsetC;
			player->bullets[player->bullets.size() - 1]->oldPos = player->position + offsetC;
		}
	}
}

void Game::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	
}

void Game::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Game::OnWindowResize(int width, int height)
{
}
