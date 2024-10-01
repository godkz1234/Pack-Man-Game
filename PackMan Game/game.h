#pragma once
#ifndef GAME_H
#define GAME_H

#include <windows.h>

// 상수 정의
#define WIDTH 37
#define HEIGHT 37
#define ITEM_COUNT 10  // 생성할 아이템 개수

#define UP 72
#define LEFT 75
#define RIGHT 77
#define DOWN 80

// 구조체 정의
typedef struct Character {
    int x;
    int y;
    const char* shape;
} Character;

typedef struct Item {
    int x;
    int y;
    int active;
} Item;

// 함수 선언
void Position(HANDLE hConsole, int x, int y);
void Render(HANDLE hConsole, Character player, Character ghosts[], int ghostCount, Item items[], int score, HANDLE hOutputBuffer);
void MoveGhost(Character* ghost, Character player, int* moveCounter);
void GenerateItems(Item items[]);
int CheckItemCollection(Character* player, Item items[]);
int AllItemsCollected(Item items[]);
void GameOver(HANDLE hConsole);
void Victory(HANDLE hConsole);
void ShowStartScreen(HANDLE hConsole);
int AskRestart(HANDLE hConsole);

// 더블 버퍼링 관련 함수 선언
void InitializeDoubleBuffer(HANDLE* hOutputBuffer, HANDLE* hOriginalBuffer);
void SwitchBuffer(HANDLE* hOutputBuffer, HANDLE* hOriginalBuffer);

#endif
