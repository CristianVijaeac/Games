#include "Player.h"
#include <Core/Engine.h>
#include <vector>
#include "SpriteSheet.h"

//clasa corespunzatoarea unui player

/*rolul principal al acesteia este de a trimite jocului urmatoarea animatie(prin construirea coordonatelor de textura)
care trebuie afisata in functie de parametrii*/

Player::Player() {

}


Player::Player(glm::vec3 pos, float scale, float rotation,int no_lifes, float speed,glm::vec3 direction){

	this->position = pos;
	this->scale = scale;
	this->rotation = rotation;
	this->no_lifes = no_lifes;
	this->speed = speed;
	this->direction = direction;
	
}

//miscarea playerului pe orizontala
void Player::TranslateRight(float distance)
{

	glm::vec3 proj = glm::normalize(glm::vec3(direction.x, 0, 0));
	position = position + glm::normalize(proj) * distance;

}

//urmatoarea animatie de mers si reinitializarea celorlalte variabile
vector<glm::vec2> Player::getNextWalk(SpriteSheet *sheet) {
	
	no_collapse = 0;
	no_defence = 0;
	no_stay = 0;
	no_sword = 0;
	no_win = 0;
	no_hit = 0;
	hit = 0;
	defence = 0;
	fin_collapse = 0;
	stay = 0;

	vector<glm::vec2> newAnimation = {
		glm::vec2((sheet->walk.at(no_walk)[0] + sheet->walk.at(no_walk)[2]) / 1024, (sheet->walk.at(no_walk)[1]) / 512),
			glm::vec2((sheet->walk.at(no_walk)[0] + sheet->walk.at(no_walk)[2]) / 1024, (sheet->walk.at(no_walk)[1] + sheet->walk.at(no_walk)[3]) / 512),
			glm::vec2((sheet->walk.at(no_walk)[0]) / 1024, (sheet->walk.at(no_walk)[1] + sheet->walk.at(no_walk)[3]) / 512),
			glm::vec2((sheet->walk.at(no_walk)[0]) / 1024, (sheet->walk.at(no_walk)[1]) / 512)
	};
	if (no_walk == sheet->walk.size() - 1) no_walk = 0;
	else no_walk++;
	return newAnimation;
}

//urmatoarea animatie de aparare si reinitializarea celorlalte variabile
vector<glm::vec2> Player::getNextDefence(SpriteSheet *sheet) {

	no_collapse = 0;
	no_walk = 0;
	no_stay = 0;
	no_sword = 0;
	no_win = 0;
	speed = 3;
	no_hit = 0;
	standardTime = 0.3;
	hit = 0;
	fin_collapse = 0;
	defence = 1;
	stay = 0;

	vector<glm::vec2> newAnimation = {
		glm::vec2((sheet->defence.at(no_defence)[0] + sheet->defence.at(no_defence)[2]) / 1024, (sheet->defence.at(no_defence)[1]) / 512),
		glm::vec2((sheet->defence.at(no_defence)[0] + sheet->defence.at(no_defence)[2]) / 1024, (sheet->defence.at(no_defence)[1] + sheet->defence.at(no_defence)[3]) / 512),
		glm::vec2((sheet->defence.at(no_defence)[0]) / 1024, (sheet->defence.at(no_defence)[1] + sheet->defence.at(no_defence)[3]) / 512),
		glm::vec2((sheet->defence.at(no_defence)[0]) / 1024, (sheet->defence.at(no_defence)[1]) / 512)
	};
	if (no_defence == sheet->defence.size() - 1) no_defence = sheet->defence.size() - 1;
	else no_defence++;
	return newAnimation;
}

//urmatoarea animatie de castig si reinitializarea celorlalte variabile
vector<glm::vec2> Player::getNextWin(SpriteSheet *sheet) {

	no_collapse = 0;
	no_defence = 0;
	no_stay = 0;
	no_sword = 0;
	no_walk = 0;
	speed = 3;
	no_hit = 0;
	standardTime = 0.3;
	hit = 0;
	fin_collapse = 0;
	defence = 0;
	stay = 0;

	vector<glm::vec2> newAnimation = {
		glm::vec2((sheet->win.at(no_win)[0] + sheet->win.at(no_win)[2]) / 1024, (sheet->win.at(no_win)[1]) / 512),
		glm::vec2((sheet->win.at(no_win)[0] + sheet->win.at(no_win)[2]) / 1024, (sheet->win.at(no_win)[1] + sheet->win.at(no_win)[3]) / 512),
		glm::vec2((sheet->win.at(no_win)[0]) / 1024, (sheet->win.at(no_win)[1] + sheet->win.at(no_win)[3]) / 512),
		glm::vec2((sheet->win.at(no_win)[0]) / 1024, (sheet->win.at(no_win)[1]) / 512)
	};
	if (no_win == sheet->win.size() - 1) no_win = 0;
	else no_win++;

	return newAnimation;
}

//urmatoarea animatie de stat si reinitializarea celorlalte variabile
vector<glm::vec2> Player::getNextStay(SpriteSheet *sheet) {

	no_collapse = 0;
	no_defence = 0;
	no_walk = 0;
	no_sword = 0;
	no_win = 0;
	speed = 3;
	no_hit = 0;
	hit = 0;
	defence = 0;
	fin_collapse = 0;
	standardTime = 0.3;
	stay = 0;
	vector<glm::vec2> newAnimation = {
		glm::vec2((sheet->stay.at(no_stay)[0] + sheet->stay.at(no_stay)[2]) / 1024, (sheet->stay.at(no_stay)[1]) / 512),
		glm::vec2((sheet->stay.at(no_stay)[0] + sheet->stay.at(no_stay)[2]) / 1024, (sheet->stay.at(no_stay)[1] + sheet->stay.at(no_stay)[3]) / 512),
		glm::vec2((sheet->stay.at(no_stay)[0]) / 1024, (sheet->stay.at(no_stay)[1] + sheet->stay.at(no_stay)[3]) / 512),
		glm::vec2((sheet->stay.at(no_stay)[0]) / 1024, (sheet->stay.at(no_stay)[1]) / 512)
	};
	if (no_stay == sheet->stay.size() - 1) no_stay = 0;
	else no_stay++;
	return newAnimation;
}

//urmatoarea animatie de lovit cu piciorul si reinitializarea celorlalte variabile
vector<glm::vec2> Player::getNextSword(SpriteSheet *sheet) {

	no_collapse = 0;
	no_defence = 0;
	no_stay = 0;
	no_walk = 0;
	no_win = 0;
	speed = 3;
	no_hit = 0;
	defence = 0;
	fin_collapse = 0;
	standardTime = 0.3;
	stay = 0;

	vector<glm::vec2> newAnimation = {
		glm::vec2((sheet->sword.at(no_sword)[0] + sheet->sword.at(no_sword)[2]) / 1024, (sheet->sword.at(no_sword)[1]) / 512),
		glm::vec2((sheet->sword.at(no_sword)[0] + sheet->sword.at(no_sword)[2]) / 1024, (sheet->sword.at(no_sword)[1] + sheet->sword.at(no_sword)[3]) / 512),
		glm::vec2((sheet->sword.at(no_sword)[0]) / 1024, (sheet->sword.at(no_sword)[1] + sheet->sword.at(no_sword)[3]) / 512),
		glm::vec2((sheet->sword.at(no_sword)[0]) / 1024, (sheet->sword.at(no_sword)[1]) / 512)
	};
	if (no_sword == sheet->sword.size() - 1) {
		no_sword = 0;
		hit = 3;
	}
	else no_sword++;
	return newAnimation;
}

//urmatoarea animatie de picaj si reinitializarea celorlalte variabile
vector<glm::vec2> Player::getNextCollapse(SpriteSheet *sheet) {

	no_walk = 0;
	no_defence = 0;
	no_stay = 0;
	no_sword = 0;
	no_win = 0;
	speed = 3;
	no_hit = 0;
	hit = 0;
	defence = 0;
	fin_collapse = 0;
	standardTime = 0.3;
	stay = 0;
	
	vector<glm::vec2> newAnimation = {
		glm::vec2((sheet->collapse.at(no_collapse)[0] + sheet->collapse.at(no_collapse)[2]) / 1024, (sheet->collapse.at(no_collapse)[1]) / 512),
		glm::vec2((sheet->collapse.at(no_collapse)[0] + sheet->collapse.at(no_collapse)[2]) / 1024, (sheet->collapse.at(no_collapse)[1] + sheet->collapse.at(no_collapse)[3]) / 512),
		glm::vec2((sheet->collapse.at(no_collapse)[0]) / 1024, (sheet->collapse.at(no_collapse)[1] + sheet->collapse.at(no_collapse)[3]) / 512),
		glm::vec2((sheet->collapse.at(no_collapse)[0]) / 1024, (sheet->collapse.at(no_collapse)[1]) / 512)
	};
	if (no_collapse == sheet->collapse.size() - 1) {
		no_collapse = 0;
		if (no_lifes > 0) fin_collapse = 1;
	}
	else no_collapse++;
	return newAnimation;
}

//urmatoarea animatie de lovit cu pumnul si reinitializarea celorlalte variabile
vector<glm::vec2> Player::getNextHit(SpriteSheet *sheet) {

	no_walk = 0;
	no_defence = 0;
	no_stay = 0;
	no_sword = 0;
	no_win = 0;
	speed = 3;
	fin_collapse = 0;
	defence = 0;
	standardTime = 0.3;
	stay = 0;
	hit = 0;

	vector<glm::vec2> newAnimation = {
		glm::vec2((sheet->hit.at(no_hit)[0] + sheet->hit.at(no_hit)[2]) / 1024, (sheet->hit.at(no_hit)[1]) / 512),
		glm::vec2((sheet->hit.at(no_hit)[0] + sheet->hit.at(no_hit)[2]) / 1024, (sheet->hit.at(no_hit)[1] + sheet->hit.at(no_hit)[3]) / 512),
		glm::vec2((sheet->hit.at(no_hit)[0]) / 1024, (sheet->hit.at(no_hit)[1] + sheet->hit.at(no_hit)[3]) / 512),
		glm::vec2((sheet->hit.at(no_hit)[0]) / 1024, (sheet->hit.at(no_hit)[1]) / 512)
	};
	if (no_hit == sheet->hit.size() - 1) {
		no_hit = 0;
		hit = 1;
	}
	else no_hit++;
	return newAnimation;
}





