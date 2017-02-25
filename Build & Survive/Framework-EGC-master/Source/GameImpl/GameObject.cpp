#include "GameObject.h"
#include <Core/Engine.h>


GameObject::GameObject()
{
	position = glm::vec3(0, 2, 5);
	forward = glm::vec3(0, 0, -1);
	up = glm::vec3(0, 1, 0);
	right = glm::vec3(1, 0, 0);
	scale = 0;
	rotation = 0;
	no_lifes = 0;
	speed = 0;

}

GameObject::GameObject(glm::vec3 pos, float scale, float rotation, int no_lifes, float speed,glm::vec3 up)
	: position(pos),
	scale(scale),
	rotation(rotation),
	no_lifes(no_lifes),
	speed(speed),
	up(up)
	
{

	}



