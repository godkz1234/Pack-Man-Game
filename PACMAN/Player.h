#pragma once
#include "Util.h"
#include"Map.h"

class Player
{
public:
	Player(int x,int y,const char * img,COLOR color,COLOR bgcolor);
	~Player();

public:
	void Input();
	void Update(Map* map);
	void Render();

	void getItem();

private:
	int		x;
	int		y;
	char	img[3];
	STATE	state;
	int		score;
	COLOR	color;
	COLOR	bgcolor;

	bool	Buff;
	int		BuffStart;

	bool	isDie;


public:
	void	setX		(int x)				{ this->x		= x;	  }
	void	setY		(int y)				{ this->y		= y;	  }
	void	setImg		(const char * img)	{ strcpy(this->img, img); }
	void	setState	(STATE state)		{ this->state	= state;  }
	void	setIsDie	(bool temp)			{ this->isDie	= temp;	  }

	int			getX()		{ return x; }
	int			getY()		{ return y; }
	const char* getImg()	{ return img; }
	int			getState()	{ return state; }
	int			getScore()	{ return score; }
	bool		isDied()	{ return isDie; }
	bool		isBuff()	{ return Buff; }
};

