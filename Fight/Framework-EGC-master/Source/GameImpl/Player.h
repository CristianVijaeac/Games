#pragma once
#include <include/glm.h>
#include <vector>
#include "SpriteSheet.h"



class Player 
{	
public:

	glm::vec3 position;
	float scale, rotation, speed;
	int no_lifes;
	glm::vec3 direction;
	int no_walk=0, no_defence = 0, no_win = 0, no_stay = 0, no_sword = 0, no_collapse = 0,no_hit = 0;
	float standardTime = 0.3f;
	int hit = 0, defence = 0;
	int fin_collapse = 0;
	int stay = 0;
	float lastTime = 0;
	int is_hit = 0;
	//vector<glm::vec2> textCoords;
	
	Player();

	Player(glm::vec3 pos, float scale, float rotation, int no_lifes, float speed,glm::vec3 direction);
	void TranslateRight(float distance);
	std::vector<glm::vec2> getNextWalk(SpriteSheet *sheet);
	vector<glm::vec2> getNextDefence(SpriteSheet *sheet);
	vector<glm::vec2> getNextWin(SpriteSheet *sheet);
	vector<glm::vec2> getNextStay(SpriteSheet *sheet);
	vector<glm::vec2> getNextSword(SpriteSheet *sheet);
	vector<glm::vec2> getNextCollapse(SpriteSheet *sheet);
	vector<glm::vec2> getNextHit(SpriteSheet *sheet);
	
	
};
