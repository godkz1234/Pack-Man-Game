#pragma once
#include"Util.h"
#include"Player.h"
#include"Map.h"

class Enemy
{
public:
	Enemy(int x,int y,COLOR color, COLOR bgcolor);
	~Enemy();

public:
	inline long getLength(int posx, int posy, int targetx, int targety);
	void	selectDir(int posx, int posy, bool asc);
	void	Update(Player* player,Map* map);

private:
	float		x;
	float		y;
	COLOR   color;
	COLOR	bgcolor;
	STATE	state;
	STATE	proDir[4];
	bool	isDie;
	

public:
	void	setX(int x)		{ this->x = x; }
	void	setY(int y)		{ this->y = y; }
	
	COLOR	getColor()		{ return color; }
	COLOR	getBgcolor()	{ return bgcolor; }
};

