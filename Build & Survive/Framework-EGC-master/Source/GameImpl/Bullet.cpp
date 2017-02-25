#include "Bullet.h"
#include "GameObject.h"

#include <Core/Engine.h>


Bullet::Bullet() {

	GameObject();
}


Bullet::Bullet(glm::vec3 pos, float scale, float rotation, float speed,glm::vec3 direction)
	:GameObject(pos, scale, rotation, 0, speed, glm::vec3(0, 1, 0))
{
	this->direction = direction;
}

Bullet::Bullet(glm::vec3 pos, glm::vec3 oldPos,float scale, float rotation, float speed, glm::vec3 direction,int bulletType,float maxDist)
	: GameObject(pos, scale, rotation, 0, speed, glm::vec3(0, 1, 0))
{
	this->bulletType = bulletType;
	this->maxDist = maxDist;
	this->direction = direction;
	this->oldPos = oldPos;
	
}

Bullet::Bullet(glm::vec3 pos, glm::vec3 oldPos, float scale, float rotation, float speed, glm::vec3 direction, int bulletType, float maxDist, bool down)
	: GameObject(pos, scale, rotation, 0, speed, glm::vec3(0, 1, 0))
{
	this->bulletType = bulletType;
	this->maxDist = maxDist;
	this->direction = direction;
	this->oldPos = oldPos;
	this->down = down;
}