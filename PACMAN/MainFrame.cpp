#include "MainFrame.h"
#include<mmsystem.h>
#pragma comment(lib,"winmm.lib")



MainFrame::MainFrame(int delay) : delay(delay)
{
	PlaySound("./bgm.wav", 0, SND_ASYNC | SND_LOOP);

	CONSOLE_CURSOR_INFO cursorInfo = { 0, };
	cursorInfo.dwSize = 1;
	cursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
	system("mode con lines=34 cols=54");

	player	 = new Player(13, 17, "¡Ü", YELLOW, BLACK);
	map		 = new Map();
	running  = true;
	
	enemy[0] = new Enemy(2, 2, RED, BLACK);
	enemy[1] = new Enemy(map_width - 2, 2, RED, BLACK);
	enemy[2] = new Enemy(2,map_height - 2, RED, BLACK);
	enemy[3] = new Enemy(map_width - 2, map_height - 2, RED, BLACK);
}


MainFrame::~MainFrame()
{
	PlaySound(NULL, NULL, NULL);
	delete player;
	delete map;
	for (int i = 0; i < 4; i++)
		delete enemy[i];
}

void MainFrame::Update()
{
	if (player->getScore() == 2350) running = false;
	if (player->isDied()) running = false;

	player->Input();
	map->Update();
	player->Update(map);
	
	for (int i = 0; i < 4; i++) {
		enemy[i]->Update(player, map);
	}

	Sleep(delay);
}

void MainFrame::Render()
{
	map->Render();
	player->Render();
}
