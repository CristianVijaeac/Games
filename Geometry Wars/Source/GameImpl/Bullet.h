#pragma once
#pragma once
#include <include/glm.h>
#include "GameObject.h"
#include <vector>



class Bullet : public GameObject
{

public:

	std::vector<VertexFormat> vertices
	{
		VertexFormat(glm::vec3(0,0,  0), glm::vec3(0.5, 1, 0.5)),
		VertexFormat(glm::vec3(-5,35, 0), glm::vec3(0.5, 1, 0.5)),
		VertexFormat(glm::vec3(5,35,  0), glm::vec3(0.5, 1, 0.5)),
		VertexFormat(glm::vec3(5,-35,  0), glm::vec3(0.5, 1, 0.5)),
		VertexFormat(glm::vec3(-5,-35,  0), glm::vec3(0.5, 1, 0.5)),

	};

	std::vector<unsigned short> indices
	{
		0, 1, 2,
		0, 2, 3,
		0, 3, 4,
		0, 4, 1
	};

	Bullet(glm::vec3 pos, float scale, float rotation, glm::vec3 colour, int no_lifes, float speed);

};
