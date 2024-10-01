#include "game.h"

extern char maze[HEIGHT][WIDTH];

int main() {
    HANDLE hConsole, hOriginalBuffer;  // ���� ���۸��� �ܼ� �ڵ�
    InitializeDoubleBuffer(&hConsole, &hOriginalBuffer);  // ���� ���۸� �ʱ�ȭ

    while (1) {
        ShowStartScreen(hConsole);  // ���� ȭ��

        Character player = { 3, 3, "��" };
        Character ghosts[3] = { { 20, 18, "��" }, { 23, 15, "��" }, { 18, 20, "��" } };
        Item items[ITEM_COUNT];
        int score = 0;
        int moveCounters[3] = { 0, 0, 0 };  // ��Ʈ �̵� ī����

        GenerateItems(items);  // ������ ����

        while (1) {
            // ���� ������
            Render(hConsole, player, ghosts, 3, items, score, hConsole);

            // �÷��̾� �̵� �Է�
            if (_kbhit()) {
                char key = _getch();
                if (key == -32) {
                    key = _getch();  // ����Ű �Է� ó��
                    if (key == UP && player.y > 0 && maze[player.y - 1][player.x] != '1') player.y--;
                    else if (key == DOWN && player.y < HEIGHT - 1 && maze[player.y + 1][player.x] != '1') player.y++;
                    else if (key == LEFT && player.x > 0 && maze[player.y][player.x - 1] != '1') player.x--;
                    else if (key == RIGHT && player.x < WIDTH - 1 && maze[player.y][player.x + 1] != '1') player.x++;
                }
            }

            // ������ ���� üũ
            score += CheckItemCollection(&player, items);

            // ��Ʈ �̵�
            for (int i = 0; i < 3; i++) {
                MoveGhost(&ghosts[i], player, &moveCounters[i]);
            }

            // ��Ʈ�� �浹 üũ
            for (int i = 0; i < 3; i++) {
                if (player.x == ghosts[i].x && player.y == ghosts[i].y) {
                    GameOver(hConsole);
                    if (!AskRestart(hConsole)) {
                        return 0;  // ���� ����
                    }
                    break;
                }
            }

            // ��� ������ ���� üũ
            if (AllItemsCollected(items)) {
                Victory(hConsole);
                if (!AskRestart(hConsole)) {
                    return 0;  // ���� ����
                }
                break;
            }

            // ���� ���۸��� ���� ���� ����Ī
            SwitchBuffer(&hConsole, &hOriginalBuffer);
        }
    }
}
