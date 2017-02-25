#pragma once
#include "GameObject.h"

class Enemy : public GameObject
{
public:

	Enemy();

	Enemy(glm::vec3 pos, float scale, float rotation, int no_lifes,float speed, int path,float rotationZ);

	Enemy(glm::vec3 pos, float scale, float rotation,int no_lifes, float speed);
public:
	int path;
	float rotationZ;

};