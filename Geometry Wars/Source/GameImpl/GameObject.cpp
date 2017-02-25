#include "GameObject.h"
#include <Core/Engine.h>


GameObject::GameObject(glm::vec3 pos, float scale, float rotation, glm::vec3 colour, int no_lifes,float speed)
	: position(pos),
	  scale(scale),
	  rotation(rotation),
	  colour(colour),
	  no_lifes(no_lifes),
	  speed(speed)
{

}
