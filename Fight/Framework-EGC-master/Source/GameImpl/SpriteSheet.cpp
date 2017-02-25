#include "SpriteSheet.h"

//clasa care citeste pozitia fiecarui sprite in spritesheet folosind un utilitar numit pugixml

SpriteSheet::SpriteSheet() {

}

SpriteSheet::SpriteSheet(float width,float height) {
	
	//parsam inaltimea si latimea
	this->width = width;
	this->height = height;

	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file("Source/GameImpl/Textures/sprites.xml");
	pugi::xml_node tool = doc.child("TextureAtlas").child("SubTexture");

	//parsam animatiile de miscare stanga-dreapta
	for (int i = 0; i < 6; i++, tool = tool.next_sibling("SubTexture"))
	{
		walk.push_back(glm::vec4(tool.attribute("x").as_float(),tool.attribute("y").as_float(), tool.attribute("width").as_float(),
			tool.attribute("height").as_float()));

	}

	//sarim cateva spriteuri
	for (int i = 0; i < 23; i++, tool = tool.next_sibling("SubTexture"))
	{
		
	}

	//parsam animatiile pentru lovitura cu pumnul
	for (int i = 0; i < 4; i++, tool = tool.next_sibling("SubTexture"))
	{
		hit.push_back(glm::vec4(tool.attribute("x").as_float(), tool.attribute("y").as_float(), tool.attribute("width").as_float(),
			tool.attribute("height").as_float()));

		if (i == 3) {
			defence.push_back(glm::vec4(tool.attribute("x").as_float(), tool.attribute("y").as_float(), tool.attribute("width").as_float(),
				tool.attribute("height").as_float()));
		}
	}

	//parsam animatiile pentru aparare
	for (int i = 0; i < 2; i++, tool = tool.next_sibling("SubTexture"))
	{
		defence.push_back(glm::vec4(tool.attribute("x").as_float(), tool.attribute("y").as_float(), tool.attribute("width").as_float(),
			tool.attribute("height").as_float()));

	}

	//sarima cateva animatii
	for (int i = 0; i < 22; i++, tool = tool.next_sibling("SubTexture"))
	{
	}

	//parsam animatiile pentru lovitura cu piciorul
	for (int i = 0; i < 6; i++, tool = tool.next_sibling("SubTexture"))
	{
		sword.push_back(glm::vec4(tool.attribute("x").as_float(), tool.attribute("y").as_float(), tool.attribute("width").as_float(),
			tool.attribute("height").as_float()));

	}

	tool = tool.next_sibling("SubTexture");

	//parsam animatiile de picaj(cand un jucator este lovit)
	for (int i = 0; i < 5; i++, tool = tool.next_sibling("SubTexture"))
	{
		collapse.push_back(glm::vec4(tool.attribute("x").as_float(), tool.attribute("y").as_float(), tool.attribute("width").as_float(),
			tool.attribute("height").as_float()));

	}

	//parsam animatiile de stat
	for (int i = 0; i < 3; i++, tool = tool.next_sibling("SubTexture"))
	{
		stay.push_back(glm::vec4(tool.attribute("x").as_float(), tool.attribute("y").as_float(), tool.attribute("width").as_float(),
			tool.attribute("height").as_float()));

	}

	//parsam animatia de castig
	for (int i = 0; i < 2; i++, tool = tool.next_sibling("SubTexture"))
	{
		win.push_back(glm::vec4(tool.attribute("x").as_float(), tool.attribute("y").as_float(), tool.attribute("width").as_float(),
			tool.attribute("height").as_float()));

	}

}