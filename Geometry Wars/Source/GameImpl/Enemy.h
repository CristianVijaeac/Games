#pragma once
#include <vector>

#include "GameObject.h"
#include "Enemy.h"




class Enemy : public GameObject
{


public:

	std::vector<VertexFormat> vertices 
	{
			VertexFormat(glm::vec3(0, 0, 0), glm::vec3(0, 1, 1)),
			VertexFormat(glm::vec3(-40, -40, 0), glm::vec3(0, 1, 1)),
			VertexFormat(glm::vec3(-40, 40, 0), glm::vec3(0, 1, 1)),
			VertexFormat(glm::vec3(40, 40, 0), glm::vec3(0, 1, 1)),
			VertexFormat(glm::vec3(40, -40, 0), glm::vec3(0, 1, 1))


	};

	std::vector<unsigned short> indices 
	{
			0, 1, 2,	
			0, 3, 4	
	};


	Enemy(glm::vec3 pos, float scale, float rotation, glm::vec3 colour, int no_lifes, float speed, bool hit);
	
	bool hit ;
};