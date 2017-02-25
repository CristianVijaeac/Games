#include "Enemy.h"
#include "GameObject.h"
#include <Core/Engine.h>


Enemy::Enemy(glm::vec3 pos, float scale, float rotation, glm::vec3 colour, int no_lifes, float speed , bool hit)
	:GameObject(pos, scale, rotation, colour, no_lifes, speed),hit(hit)

{

};