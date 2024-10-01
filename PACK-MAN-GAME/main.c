#include "game.h"

extern char maze[HEIGHT][WIDTH];

int main() {
    HANDLE hConsole, hOriginalBuffer;  // 더블 버퍼링용 콘솔 핸들
    InitializeDoubleBuffer(&hConsole, &hOriginalBuffer);  // 더블 버퍼링 초기화

    while (1) {
        ShowStartScreen(hConsole);  // 시작 화면

        Character player = { 3, 3, "▲" };
        Character ghosts[3] = { { 20, 18, "●" }, { 23, 15, "●" }, { 18, 20, "●" } };
        Item items[ITEM_COUNT];
        int score = 0;
        int moveCounters[3] = { 0, 0, 0 };  // 고스트 이동 카운터

        GenerateItems(items);  // 아이템 생성

        while (1) {
            // 게임 렌더링
            Render(hConsole, player, ghosts, 3, items, score, hConsole);

            // 플레이어 이동 입력
            if (_kbhit()) {
                char key = _getch();
                if (key == -32) {
                    key = _getch();  // 방향키 입력 처리
                    if (key == UP && player.y > 0 && maze[player.y - 1][player.x] != '1') player.y--;
                    else if (key == DOWN && player.y < HEIGHT - 1 && maze[player.y + 1][player.x] != '1') player.y++;
                    else if (key == LEFT && player.x > 0 && maze[player.y][player.x - 1] != '1') player.x--;
                    else if (key == RIGHT && player.x < WIDTH - 1 && maze[player.y][player.x + 1] != '1') player.x++;
                }
            }

            // 아이템 수집 체크
            score += CheckItemCollection(&player, items);

            // 고스트 이동
            for (int i = 0; i < 3; i++) {
                MoveGhost(&ghosts[i], player, &moveCounters[i]);
            }

            // 고스트와 충돌 체크
            for (int i = 0; i < 3; i++) {
                if (player.x == ghosts[i].x && player.y == ghosts[i].y) {
                    GameOver(hConsole);
                    if (!AskRestart(hConsole)) {
                        return 0;  // 게임 종료
                    }
                    break;
                }
            }

            // 모든 아이템 수집 체크
            if (AllItemsCollected(items)) {
                Victory(hConsole);
                if (!AskRestart(hConsole)) {
                    return 0;  // 게임 종료
                }
                break;
            }

            // 더블 버퍼링을 위한 버퍼 스위칭
            SwitchBuffer(&hConsole, &hOriginalBuffer);
        }
    }
}
