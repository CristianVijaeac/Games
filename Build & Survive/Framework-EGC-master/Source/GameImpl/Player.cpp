#include "Player.h"
#include "GameObject.h"

#include <Core/Engine.h>


Player::Player() {

	GameObject();
}


Player::Player(glm::vec3 pos, float scale, float rotation,int no_lifes, float speed,glm::vec3 up,std::vector<Bullet*> bullets,float rotationZ)
	:GameObject(pos, scale, rotation, no_lifes, speed, up){

	this->forward = glm::normalize(glm::vec3(0,0,-1));
	this->bullets = bullets;
	right = glm::cross(forward, up);
	this->up = glm::cross(right, forward); 
	this->rotationZ = rotationZ;

}

void Player::MoveForward(float distance)
{
	glm::vec3 dir = glm::normalize(glm::vec3(forward.x, 0, forward.z));
	position = position + glm::normalize(dir) * distance;
}

void Player::TranslateForward(float distance)
{
	position = position + glm::normalize(forward) * distance;
}

void Player::TranslateRight(float distance)
{

	glm::vec3 proj = glm::normalize(glm::vec3(right.x, 0, right.z));
	position = position + glm::normalize(proj) * distance;

}

void Player::RotateFirstPerson_OX(float angle)
{

	glm::vec4 newVector = glm::rotate(glm::mat4(1.0f), angle, right) * glm::vec4(forward, 1);
	forward = glm::normalize(glm::vec3(newVector));

	newVector = glm::rotate(glm::mat4(1.0f), angle, right) * glm::vec4(up, 1);
	up = glm::normalize(glm::vec3(newVector));

}

void Player::RotateFirstPerson_OY(float angle)
{

	glm::vec4 newVector = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0, 1, 0)) * glm::vec4(forward, 1);
	forward = glm::normalize(glm::vec3(newVector));

	newVector = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0, 1, 0)) * glm::vec4(right, 1);
	right = glm::normalize(glm::vec3(newVector));

	newVector = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0, 1, 0)) * glm::vec4(up, 1);
	up = glm::normalize(glm::vec3(newVector));
}





