#pragma once

#include "GameObject.h"
#include "Bullet.h"
#include <vector>


class Tower : public GameObject
{
public:

	Tower();

	Tower(glm::vec3 pos, float scale, float rotation,float speed,std::vector<Bullet*> bullets);

	std::vector<Bullet*> bullets;
};

