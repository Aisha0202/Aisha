#include<stdio.h>
#include<unistd.h> 
#define ROW 40
#define LINE 20
#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_RESET "\x1b[0m"
int chara(){
    int row_position = 0;
    int line_position = 0; 
    int row_direction = 1;
    int line_direction = 1; 
    while (1) { 
        printf("\033[H\033[J");
        for (int i = 0; i < line_position; i++) {
            printf("\n");
        }
        for (int i = 0; i < row_position; i++) {
            printf(" ");
        }
        printf(ANSI_COLOR_RED"*\n"ANSI_COLOR_RESET);
        row_position += row_direction;
        line_position += line_direction;

        if (row_position >= ROW) { 
            row_direction = -1; 
        } else if (row_position <= 0) { 
            row_direction = 1; 
        }

        if (line_position >= LINE) { 
            line_direction = -1; 
        } else if (line_position <= 0) { 
            line_direction = 1; 
        }
        usleep(100000); 
    }
    return 0;
}
int main(){
    chara();
    return 0;
}
