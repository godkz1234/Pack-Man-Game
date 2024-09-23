#include "Player.h"


Player::Player(int x, int y, const char * img, COLOR color, COLOR bgcolor) :
	x(x), y(y), color(color),bgcolor(bgcolor)
{
	state = STOP;
	setImg(img);
	score = 0;
	Buff = false;
	isDie = false;
}

Player::~Player()
{

}

void Player::Input()
{
	state = STOP;
	if (GetAsyncKeyState(VK_UP) & 0x8000)
		state = UP;
	else if (GetAsyncKeyState(VK_DOWN) & 0x8000)
		state = DOWN;
	else if (GetAsyncKeyState(VK_LEFT) & 0x8000)
		state = LEFT;
	else if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
		state = RIGHT;
}

void Player::Update(Map* map)
{
	switch (state) {
	case UP:
		y -= 1;
		if (map->getMapInfo(x, y) == WALL) y += 1;
		break;
	case DOWN:
		y += 1;
		if (map->getMapInfo(x, y) == WALL) y -= 1;
		break;
	case LEFT:
		x -= 1;
		if (x < 0) x = map_width - 1;
		else if (map->getMapInfo(x, y) == WALL) x += 1;
		break;
	case RIGHT:
		x += 1;
		if (x == map_width) x = 0;
		else if (map->getMapInfo(x, y) == WALL) x -= 1;
		break;
	}

	switch (map->GetItem(x, y)) {
	case _POINT: Beep(1000, 20); score += 10; break;
	case ITEM: Beep(1000, 20);	getItem(); break;
	}

	if (clock() - BuffStart > 5000) {
		Buff = false;
	}
	
	map->setBuffer(x, y, PLAYER);

}

void Player::Render() {
	gotoxy(4, 31);
	setColor(WHITE, BLACK);
	if (Buff == true) printf("BUFF  ¡º  ON  ¡»");
	else printf("BUFF  ¡º  OFF ¡»");

	gotoxy(4, 32);
	puts("                  ");
	gotoxy(4, 32);


	gotoxy(30, 31);
	setColor(WHITE, BLACK);
	printf("SCORE ¡º %04d ¡» ", score);
}

void Player::getItem()
{
	BuffStart = clock();
	Buff = true;
}
