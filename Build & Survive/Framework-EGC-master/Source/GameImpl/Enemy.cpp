#include "Enemy.h"
#include "GameObject.h"

#include <Core/Engine.h>


Enemy::Enemy() {

	GameObject();
}


Enemy::Enemy(glm::vec3 pos, float scale, float rotation, int no_lifes,float speed,int path,float rotationZ)
	:GameObject(pos, scale, rotation, no_lifes, speed, glm::vec3(0, 1, 0))
{
	this->path = path;
	this->rotationZ = rotationZ;
}

Enemy::Enemy(glm::vec3 pos, float scale, float rotation, int no_lifes,float speed)
	: GameObject(pos, scale, rotation, no_lifes, speed, glm::vec3(0, 1, 0))
{
}