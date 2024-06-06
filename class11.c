#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // 用于sleep函数的头文件

#define ROWS 7 // 行数
#define COLS 7 // 列数

// 清屏函数
void clear_screen() {
    system("cls || clear");
}

// 显示字符动画
void display_animation(char animation_array[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            printf("%c", animation_array[i][j]);
        }
        printf("\n");
    }
    sleep(1); // 暂停1秒，调整动画速度
    clear_screen(); // 清屏
}

int main() {
    char animation_frames[ROWS][COLS] = {
        {' ', ' ', ' ', '*', ' ', ' ', ' '},
        {' ', ' ', '*', ' ', '*', ' ', ' '},
        {' ', '*', ' ', ' ', ' ', '*', ' '},
        {'*', ' ', ' ', ' ', ' ', ' ', '*'},
        {' ', '*', ' ', ' ', ' ', '*', ' '},
        {' ', ' ', '*', ' ', '*', ' ', ' '},
        {' ', ' ', ' ', '*', ' ', ' ', ' '}
    };

    while (1) {
        // 循环移动字符
        char first_row[COLS];
        for (int i = 0; i < COLS; i++) {
            first_row[i] = animation_frames[0][i];
        }
        for (int i = 0; i < ROWS - 1; i++) {
            for (int j = 0; j < COLS; j++) {
                animation_frames[i][j] = animation_frames[i + 1][j];
            }
        }
        for (int i = 0; i < COLS; i++) {
            animation_frames[ROWS - 1][i] = first_row[i];
        }

        display_animation(animation_frames);
    }

    return 0;
}
