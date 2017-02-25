#pragma once
#include <string>

#include <include/glm.h>
#include <Core/GPU/Mesh.h>


class GameObject {

	public:

		glm::vec3 position;
		glm::vec3 forward;
		glm::vec3 right;
		glm::vec3 up;

		float scale;
		float rotation;
		int no_lifes;
		float speed;

		GameObject();

		GameObject(glm::vec3 pos,float scale,float rotation,int no_lifes,float speed,glm::vec3 up);
		

		
		
};


