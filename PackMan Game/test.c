#include <conio.h>  // _getch() 함수를 사용하기 위해 필요함
#include <stdio.h>

int main() {
    printf("Press any key to continue...\n");

    // _getch()로 키 입력 대기
    char ch = _getch();  // 사용자가 입력한 키를 변수 ch에 저장

    // 키가 입력되면 그 키와 함께 메시지 출력
    printf("You pressed: %c\n", ch);

    return 0;
}
