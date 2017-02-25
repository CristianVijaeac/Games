#include "Tower.h"
#include "GameObject.h"
#include "Bullet.h"
//#include <vector>

#include <Core/Engine.h>


Tower::Tower() {

	GameObject();
}


Tower::Tower(glm::vec3 pos, float scale, float rotation, float speed,std::vector<Bullet*> bullets)
	:GameObject(pos, scale, rotation, 0,speed,glm::vec3 (0,1,0)) 
{
	this->bullets = bullets;
}