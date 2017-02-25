#pragma once
#include <include/glm.h>
#include "GameObject.h"
#include <vector>
#include "Bullet.h"



class Player : public GameObject
{
public:

	std::vector<Bullet*> bullets;
	float rotationZ;

	Player();

	Player(glm::vec3 pos, float scale, float rotation, int no_lifes, float speed,glm::vec3 up,std::vector<Bullet*> bullets,float rotationZ);
	void MoveForward(float distance);
	void TranslateForward(float distance);
	void TranslateRight(float distance);
	void RotateFirstPerson_OX(float angle);
	void RotateFirstPerson_OY(float angle);
	
};
