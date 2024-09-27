#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>

#define WIDTH 31
#define HEIGHT 31
#define ITEM_COUNT 10  // 생성할 아이템 개수

#define UP 72
#define LEFT 75
#define RIGHT 77
#define DOWN 80

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

char maze[HEIGHT][WIDTH] = {
{ '1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1' },
{ '1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1' },
{ '1','0','1','1','1','1','0','1','1','1','1','0','1','1','0','1','0','1','1','0','1','1','1','1','0','1','1','1','1','0','1' },
{ '1','0','1','1','1','1','0','1','1','1','1','0','1','1','0','1','0','1','1','0','1','1','1','1','0','1','1','1','1','0','1' },
{ '1','0','1','1','1','1','0','1','1','1','1','0','1','1','0','1','0','1','1','0','1','1','1','1','0','1','1','1','1','0','1' },
{ '1','0','1','1','1','1','0','1','1','1','1','0','1','1','0','1','0','1','1','0','1','1','1','1','0','1','1','1','1','0','1' },
{ '1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1' },
{ '1','0','1','1','1','1','0','1','1','0','1','1','1','1','1','1','1','1','1','1','1','0','1','1','0','1','1','1','1','0','1' },
{ '1','0','1','1','1','1','0','1','1','0','1','1','1','1','1','1','1','1','1','1','1','0','1','1','0','1','1','1','1','0','1' },
{ '1','0','0','0','0','0','0','1','1','0','0','0','0','1','1','1','1','1','0','0','0','0','1','1','0','0','0','0','0','0','1' },
{ '1','1','1','1','1','1','0','1','1','1','1','1','0','1','1','1','1','1','0','1','1','1','1','1','0','1','1','1','1','1','1' },
{ '1','1','1','1','1','1','0','1','1','1','1','1','0','1','1','1','1','1','0','1','1','1','1','1','0','1','1','1','1','1','1' },
{ '1','1','1','1','1','1','0','1','1','0','0','0','0','1','1','1','1','1','0','0','0','0','1','1','0','1','1','1','1','1','1' },
{ '1','1','1','1','1','1','0','1','1','0','1','1','0','0','0','0','0','0','0','1','1','0','1','1','0','1','1','1','1','1','1' },
{ '1','0','0','0','0','0','0','0','0','0','0','0','0','1','1','1','1','1','0','0','0','0','0','0','0','0','0','0','0','0','1' },
{ '1','0','1','1','1','1','0','1','1','1','0','1','0','0','0','0','0','0','0','1','0','1','1','1','0','1','1','1','1','0','1' },
{ '1','0','0','0','0','1','0','1','1','1','0','1','1','1','1','1','1','1','1','1','0','1','1','1','0','1','0','0','0','0','1' },
{ '1','0','0','0','0','1','0','1','1','1','0','0','0','0','0','0','0','0','0','0','0','1','1','1','0','1','0','0','0','0','1' },
{ '1','0','1','1','1','1','0','1','1','1','0','1','1','1','1','1','1','1','1','1','0','1','1','1','0','1','1','1','1','0','1' },
{ '1','0','0','0','0','0','0','0','0','0','0','1','0','0','0','1','0','0','0','1','0','0','0','0','0','0','0','0','0','0','1' },
{ '1','0','1','1','1','1','0','1','1','1','0','0','0','0','0','1','0','0','0','0','0','1','1','1','0','1','1','1','1','0','1' },
{ '1','0','0','0','0','1','0','0','0','0','0','0','0','0','0','1','0','0','0','0','0','0','0','0','0','1','0','0','0','0','1' },
{ '1','1','1','1','0','1','0','0','1','1','0','1','0','0','0','1','0','0','0','1','0','1','1','0','0','1','0','1','1','1','1' },
{ '1','1','1','1','0','1','0','0','1','1','0','1','1','1','1','1','1','1','1','1','0','1','1','0','0','1','0','1','1','1','1' },
{ '1','1','1','1','0','1','0','0','1','1','0','0','0','0','0','0','0','0','0','0','0','1','1','0','0','1','0','1','1','1','1' },
{ '1','0','0','0','0','0','0','0','1','1','0','1','1','1','1','1','1','1','1','1','0','1','1','0','0','0','0','0','0','0','1' },
{ '1','0','1','1','1','1','1','1','1','1','0','1','0','0','0','1','0','0','0','1','0','1','1','1','1','1','1','1','1','0','1' },
{ '1','0','1','1','1','1','1','1','1','1','0','1','0','0','0','1','0','0','0','1','0','1','1','1','1','1','1','1','1','0','1' },
{ '1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1' },
{ '1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1' }
};

// Position 함수 선언
void Position(HANDLE hConsole, int x, int y);

void Render(HANDLE hConsole, Character player, Character ghosts[], int ghostCount, Item items[], int score) {
    // 화면을 지우고 게임 요소를 그리기
    COORD coord = { 0, 0 };  // 화면 좌표 초기화
    DWORD dwBytesWritten = 0;
    FillConsoleOutputCharacter(hConsole, ' ', WIDTH * HEIGHT, coord, &dwBytesWritten);  // 화면 지우기

    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (maze[i][j] == '0') {
                Position(hConsole, j, i);
                printf("  ");
            }
            else if (maze[i][j] == '1') {
                Position(hConsole, j, i);
                printf("■");
            }
        }
    }

    // 플레이어 위치에 플레이어 그리기
    Position(hConsole, player.x, player.y);
    printf("%s", player.shape);

    // 고스트 위치에 고스트들 그리기
    for (int i = 0; i < ghostCount; i++) {
        Position(hConsole, ghosts[i].x, ghosts[i].y);
        printf("%s", ghosts[i].shape);
    }

    // 활성화된 아이템 그리기
    for (int i = 0; i < ITEM_COUNT; i++) {
        if (items[i].active) {
            Position(hConsole, items[i].x, items[i].y);
            printf("★");
        }
    }

    // 점수 표시
    Position(hConsole, 0, HEIGHT + 1);
    printf("Score: %d\n", score);
}

void Position(HANDLE hConsole, int x, int y) {
    COORD position = { x * 2, y };  // x를 2배로 하여 공백 고려
    SetConsoleCursorPosition(hConsole, position);
}

void MoveGhost(Character* ghost, Character player, int* moveCounter) {
    (*moveCounter)++;
    if (*moveCounter % 3 != 0) {
        return;  // 3번 루프 중 1번만 이동, 고스트의 속도 조절
    }

    if (ghost->x < player.x) {
        if (maze[ghost->y][ghost->x + 1] != '1') {
            ghost->x++;
        }
    }
    else if (ghost->x > player.x) {
        if (maze[ghost->y][ghost->x - 1] != '1') {
            ghost->x--;
        }
    }

    if (ghost->y < player.y) {
        if (maze[ghost->y + 1][ghost->x] != '1') {
            ghost->y++;
        }
    }
    else if (ghost->y > player.y) {
        if (maze[ghost->y - 1][ghost->x] != '1') {
            ghost->y--;
        }
    }
}

void GenerateItems(Item items[]) {
    srand(time(NULL));  // 랜덤 시드 설정

    int generated = 0;
    while (generated < ITEM_COUNT) {
        int x = rand() % WIDTH;
        int y = rand() % HEIGHT;

        if (maze[y][x] == '0') {  // 빈 공간에만 아이템을 생성
            items[generated].x = x;
            items[generated].y = y;
            items[generated].active = 1;
            generated++;
        }
    }
}

int CheckItemCollection(Character* player, Item items[]) {
    for (int i = 0; i < ITEM_COUNT; i++) {
        if (items[i].active && player->x == items[i].x && player->y == items[i].y) {
            items[i].active = 0;  // 아이템 비활성화
            return 1;  // 점수 1점 추가
        }
    }
    return 0;
}

int AllItemsCollected(Item items[]) {
    for (int i = 0; i < ITEM_COUNT; i++) {
        if (items[i].active) {
            return 0;  // 아직 남은 아이템이 있다면 0을 반환
        }
    }
    return 1;  // 모든 아이템이 수집되었다면 1을 반환
}

void GameOver(HANDLE hConsole) {
    Position(hConsole, 0, HEIGHT + 2);
    printf("Game Over! You were caught by a ghost!\n");
}

void Victory(HANDLE hConsole) {
    Position(hConsole, 0, HEIGHT + 2);
    printf("Victory! You collected all the items!\n");
}

// 새로운 함수: 시작 화면 출력
void ShowStartScreen(HANDLE hConsole) {
    system("cls");  // 화면을 지우기
    SetConsoleActiveScreenBuffer(hConsole);  // 현재 활성화된 버퍼로 설정

    printf("####################################################################################\n");
    printf("#                                                                                  #\n");
    printf("#                                                                                  #\n");
    printf("#                                                                                  #\n");
    printf("#                                                                                  #\n");
    printf("#                                                                                  #\n");
    printf("#                                                                                  #\n");
    printf("#                                                                                  #\n");
    printf("#                                                                                  #\n");
    printf("#                                                                                  #\n");
    printf("#                                                                                  #\n");
    printf("#                                                                                  #\n");
    printf("#                                  Pac-Man                                         #\n");
    printf("#                                                                                  #\n");
    printf("#                          맵안에 있는 모든 아이템을                               #\n");
    printf("#                             전부 먹으시면 승리!                                  #\n");
    printf("#                          고스트에게 붙잡히면 패배!                               #\n");
    printf("#                          고스트에게서 도망치세요!                                #\n");
    printf("#                                                                                  #\n");
    printf("#                                  -Controls-                                      #\n");
    printf("#                                    방향키                                        #\n");
    printf("#                                                                                  #\n");
    printf("#                          -Press any key to start-                                #\n");
    printf("#                                                                                  #\n");
    printf("#                                                                                  #\n");
    printf("#                                                                                  #\n");
    printf("#                                                                                  #\n");
    printf("#                                                                                  #\n");
    printf("#                                                                                  #\n");
    printf("#                                                                                  #\n");
    printf("#                                                                                  #\n");
    printf("#                                                                                  #\n");
    printf("#                                                                                  #\n");
    printf("#                                                                                  #\n");
    printf("####################################################################################\n");


    _getch();  // 사용자가 아무 키나 누르면 계속 진행
}

// 게임 종료 후 다시 시작 여부를 묻는 함수
int AskRestart(HANDLE hConsole) {
    Position(hConsole, 0, HEIGHT + 3);
    printf("게임이 종료되었습니다. 다시 시작하려면 r키를 누르세요.\n");
    char key = _getch();  // 사용자가 키 입력을 기다림
    if (key == 'r' || key == 'R') {
        return 1;  // 다시 시작
    }
    return 0;  // 종료
}

int main() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);  // 기본 콘솔 핸들 가져오기

    while (1) {
        // 시작 화면 호출
        ShowStartScreen(hConsole);

        Character player = { 1, 1, "▲" };  // 초기 위치 (1, 1)
        Character ghosts[3] = {            // 고스트 3마리 정의
            { 20, 17, "●" },               // 고스트 1 초기 위치
            { 22, 15, "●" },               // 고스트 2 초기 위치
            { 18, 19, "●" }                // 고스트 3 초기 위치
        };
        Item items[ITEM_COUNT];  // 아이템 배열
        int score = 0;
        int moveCounters[3] = { 0, 0, 0 };  // 각 고스트의 이동을 제어하는 변수
        int playerMoved = 0;  // 플레이어가 처음 움직였는지 확인하는 변수

        GenerateItems(items);  // 아이템 생성

        while (1) {
            // 사용자 입력 받기
            if (_kbhit()) {
                int key = _getch();
                if (key == 224) {  // 방향키 입력 처리
                    key = _getch();
                    int newX = player.x;
                    int newY = player.y;
                    if (key == UP && maze[player.y - 1][player.x] != '1') newY--;
                    if (key == DOWN && maze[player.y + 1][player.x] != '1') newY++;
                    if (key == LEFT && maze[player.y][player.x - 1] != '1') newX--;
                    if (key == RIGHT && maze[player.y][player.x + 1] != '1') newX++;

                    player.x = newX;
                    player.y = newY;
                    playerMoved = 1;  // 플레이어가 이동했음을 표시
                }
            }

            // 고스트 이동 처리
            for (int i = 0; i < 3; i++) {
                MoveGhost(&ghosts[i], player, &moveCounters[i]);
            }

            // 플레이어가 고스트에 잡혔는지 확인
            for (int i = 0; i < 3; i++) {
                if (player.x == ghosts[i].x && player.y == ghosts[i].y) {
                    GameOver(hConsole);  // 게임 오버 메시지 출력
                    goto game_end;       // 게임 종료
                }
            }

            // 아이템 수집 처리
            score += CheckItemCollection(&player, items);

            // 모든 아이템 수집 여부 확인
            if (AllItemsCollected(items)) {
                Victory(hConsole);  // 승리 메시지 출력
                goto game_end;      // 게임 종료
            }

            // 게임 화면 렌더링 (첫 이동 전에만 호출)
            if (playerMoved) {
                Render(hConsole, player, ghosts, 3, items, score);
            }

            Sleep(100);  // 게임 속도 조절을 위한 딜레이
        }

    game_end:
        // 게임 종료 후 다시 시작 여부 확인
        if (!AskRestart(hConsole)) {
            break;  // 다시 시작하지 않는 경우 메인 루프 종료
        }
    }

    return 0;
}
