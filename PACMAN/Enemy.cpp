#include "Enemy.h"

bool compare1(DnL a, DnL b) {
	return a.length < b.length;
}

bool compare2(DnL a, DnL b) {
	return a.length > b.length;
}

Enemy::Enemy(int x, int y, COLOR color, COLOR bgcolor) :
	x(x),y(y),color(color),bgcolor(bgcolor)
{
	isDie = false;
	state = STOP;
}


Enemy::~Enemy()
{

}

inline long Enemy::getLength(int posx, int posy, int targetx, int targety)
{
	long a = (float)(posx - targetx);
	long b = (float)(posy - targety);
	float result = sqrt(((a*a) + (b*b)));
	return (long)(result * 100000);
}

void Enemy::selectDir(int x, int y,bool asc)
{
	DnL		dnl[4];
	dnl[0].dir = UP;
	dnl[0].length = getLength(this->x, this->y - 1, x, y);
	dnl[1].dir = DOWN;
	dnl[1].length = getLength(this->x, this->y + 1, x, y);
	dnl[2].dir = LEFT;
	dnl[2].length = getLength(this->x - 1, this->y, x, y);
	dnl[3].dir = RIGHT;
	dnl[3].length = getLength(this->x + 1, this->y, x, y);
	
	if(asc == true)
		sort(dnl, dnl + 4, compare1);
	else
		sort(dnl, dnl + 4, compare2);
	
	for (int i = 0; i < 4; i++)
		proDir[i] = dnl[i].dir;
}

void Enemy::Update(Player * player, Map * map)
{
	if (isDie == true)
		selectDir(map_width / 2, map_height / 2,true);
	else if(player->isBuff())
		selectDir(player->getX(), player->getY(),false);
	else
		selectDir(player->getX(), player->getY(),true);

	bool flag = false;
	for (int i = 0; i < 4 && flag == false; i++) {
		switch (proDir[i]) {
		case UP:
			y -= 0.6f, flag = true;
			if (map->getMapInfo(x, y) == WALL || map->getMapInfo(x, y) == ENEMY) y += 0.6f, flag = false;
			break;
		case DOWN:
			y += 0.6f, flag = true;
			if (map->getMapInfo(x, y) == WALL || map->getMapInfo(x, y) == ENEMY) y -= 0.6f, flag = false;
			break;
		case LEFT:
			x -= 0.6f, flag = true;
			if (x < 0) x = map_width - -1, flag = true;
			if (map->getMapInfo(x, y) == WALL || map->getMapInfo(x, y) == ENEMY) x += 0.6f, flag = false;;
			break;
		case RIGHT:
			x += 0.6f, flag = true;;
			if (x == map_width) x = 0, flag = true;
			if (map->getMapInfo(x, y) == WALL || map->getMapInfo(x, y) == ENEMY) x -= 0.6f, flag = false;
			break;
		}
	}

	if (player->getX() == (int)x && player->getY() == (int)y) {
		if (player->isBuff() == true)
			isDie = true;
		else
			player->setIsDie(true);
	}

	if (isDie && x == map_width / 2 && y == map_height / 2)
		isDie = false;
		
	map->setBuffer((int)x, (int)y, !isDie ? ENEMY : DIED_ENEMY);
	
}
