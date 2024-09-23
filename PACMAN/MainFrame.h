#pragma once

#include"Player.h"
#include"Map.h"
#include"Enemy.h"

class MainFrame
{
public:
	MainFrame(int delay);
	~MainFrame();

	bool isRunning() { return running; }
	void Update();
	void Render();

private:
	int	delay;
	bool running;

	Player*		player;
	Map*		map;
	Enemy*		enemy[4];
	
};

