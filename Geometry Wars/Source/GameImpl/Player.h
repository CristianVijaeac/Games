#pragma once
#include <include/glm.h>
#include "GameObject.h"
#include <vector>



class Player : public GameObject
{
public:

	std::vector<VertexFormat> vertices
	{
		VertexFormat(glm::vec3(0, 0,  0), glm::vec3(1, 1, 1)),
		VertexFormat(glm::vec3(-30, -30,  0), glm::vec3(1, 1, 1)),
		VertexFormat(glm::vec3(-30, 30,  0), glm::vec3(1, 1, 1)),
		VertexFormat(glm::vec3(30, 30,  0), glm::vec3(1, 1, 1)),
		VertexFormat(glm::vec3(30, -30,  0), glm::vec3(1, 1, 1))

	};

	std::vector<unsigned short> indices 
	{
		0, 1, 2,
		0, 3, 4	
	};

	Player(glm::vec3 pos, float scale, float rotation, glm::vec3 colour, int no_lifes, float speed);

};
