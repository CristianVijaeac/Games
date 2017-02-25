#pragma once
#include <iostream>
#include "pugixml.hpp"
#include <string>
#include <include/glm.h>
#include <Core/GPU/Mesh.h>
#include <vector>
using namespace std;
class SpriteSheet {

public:

	vector<glm::vec4> stay;
	vector<glm::vec4> walk;
	vector<glm::vec4> hit;
	vector<glm::vec4> sword;
	vector<glm::vec4> collapse;
	vector<glm::vec4> defence;
	vector<glm::vec4> win;
	string fileName;

	float width, height;
	int nextStay;
	int nextWalk;
	int nextSword;
	int nextHit;
	int nextCollapse;
	int nextDefence;
	int nextWin;

	SpriteSheet();
	SpriteSheet(float width,float height);

	Texture2D* getNext_walk();
	Texture2D* getNext_stay();
	Texture2D* getNext_sword();
	Texture2D* getNext_hit();
	Texture2D* getNext_collapse();
	Texture2D* getNext_defence();
	Texture2D* getNext_win();



};