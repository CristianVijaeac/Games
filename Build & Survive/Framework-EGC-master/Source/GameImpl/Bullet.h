#pragma once
#include "GameObject.h"

class Bullet : public GameObject
{
public:

	Bullet();

	Bullet(glm::vec3 pos, float scale, float rotation, float speed,glm::vec3 direction);
	Bullet(glm::vec3 pos, glm::vec3 oldPos,float scale, float rotation, float speed, glm::vec3 direction, 
		   int bulletType,float maxDist);

	Bullet(glm::vec3 pos, glm::vec3 oldPos, float scale, float rotation, float speed, glm::vec3 direction,
		int bulletType, float maxDist, bool down);

	glm::vec3 direction;
	int bulletType;
	float maxDist;
	glm::vec3 oldPos;
	bool down;

};
