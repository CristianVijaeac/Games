#pragma once
#include <string>

#include <include/glm.h>
#include <Core/GPU/Mesh.h>


class GameObject {

	public:

		GameObject(glm::vec3 pos,float scale,float rotation,glm::vec3 colour,int no_lifes,float speed);

		glm::vec3 position;
		float scale;
		float rotation;
		glm::vec3 colour;
		int no_lifes;
		float speed;
		
	};


