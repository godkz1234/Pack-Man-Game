#pragma once
#include "./header/sdGL.h"
#define _CRT_SECURE_NO_WARNINGS
#pragma comment(lib,"./lib/sdGL.lib")
#include<math.h>
#include<Windows.h>
#include<time.h>
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

typedef char STATE;
typedef char COLOR;

const int STOP		= 0;
const int UP		= 1;
const int DOWN		= 2;
const int LEFT		= 3;
const int RIGHT		= 4;
const int WALL		= 5;
const int SPACE		= 6;
const int _POINT	= 7;
const int ITEM		= 8;
const int PLAYER	= 9;
const int ENEMY		= 10;
const int DIED_ENEMY = 11;

typedef struct __POS {
	int x;
	int y;
} Point, Item;

typedef struct __DIRnLENGTH {
	STATE dir;
	long length;
}DnL;