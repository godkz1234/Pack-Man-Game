#include <conio.h>  // _getch() �Լ��� ����ϱ� ���� �ʿ���
#include <stdio.h>

int main() {
    printf("Press any key to continue...\n");

    // _getch()�� Ű �Է� ���
    char ch = _getch();  // ����ڰ� �Է��� Ű�� ���� ch�� ����

    // Ű�� �ԷµǸ� �� Ű�� �Բ� �޽��� ���
    printf("You pressed: %c\n", ch);

    return 0;
}
