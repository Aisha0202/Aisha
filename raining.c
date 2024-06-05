#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <ncurses.h>

#define STR_NUM 10
#define RAIN_NUM 128

struct Rain
{
    int x;
    int y;
    int speed;
    char str[STR_NUM+1];
} rain[RAIN_NUM];

char CreateChar()
{
    return (char) (rand() % 26 + 'a'); 
}

char* CreateStr(size_t len)
{
    char* str = malloc(len + 1);
    for (size_t i = 0; i < len; i++)
    {
        str[i] = CreateChar();
    }
    str[len] = '\0';
    return str;
}

void initRain(int i)
{
    rain[i].x = i * 15;
    rain[i].y = rand() % LINES;
    rain[i].speed = rand() % 3 + 1;
    strncpy(rain[i].str, CreateStr(STR_NUM), STR_NUM);
}

void drawRain(int i)
{
    int tmp;
    for (size_t k = 0; k < STR_NUM; k++)
    {
        attron(COLOR_PAIR(1));
        for(tmp=0;tmp < strlen(rain[i].str);tmp++){
        mvprintw(rain[i].y + tmp- k * 15,rain[i].x, "%c", *(rain[i].str+tmp));
        }
        attroff(COLOR_PAIR(1));
    }
}


void ChangeChar(int i)
{
    rain[i].str[rand() % STR_NUM] = CreateChar();
}

void raining(int i)
{
    rain[i].y += rain[i].speed;
    if (rain[i].y - STR_NUM * 15 > LINES)
    {
        rain[i].y = 0;
        rain[i].speed = rand() % 3 + 1;
    }
}

int main()
{
    srand((unsigned)time(NULL));

    initscr();
    start_color();
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    curs_set(0);

    for (size_t i = 0; i < RAIN_NUM; i++)
    {
        initRain(i);
    }

    while (1)
    {
        clear();

        for (size_t i = 0; i < RAIN_NUM; i++)
        {
            drawRain(i);
            ChangeChar(i);
            raining(i);
        }

        refresh();
        usleep(50000); 
    }

    endwin();

    return 0;
}
