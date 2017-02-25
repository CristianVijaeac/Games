#include "Bullet.h"
#include "GameObject.h"

#include <Core/Engine.h>


Bullet::Bullet(glm::vec3 pos, float scale, float rotation, glm::vec3 colour, int no_lifes, float speed)
	:GameObject(pos, scale, rotation, colour, no_lifes, speed)
{

};