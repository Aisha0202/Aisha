#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ncurses.h>
typedef struct {
    char symbol; // 物体的字符表示
    int x; // 物体的x坐标
    int y; // 物体的y坐标
    int deltaX; // 物体的x方向位移
    int deltaY; // 物体的y方向位移
    char* style; // 物体的样式字符串（例如颜色、样式等）
} Object;

#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 24
#define MAX_OBJECTS 10

#define FRAMES 30
#define FRAME_DELAY 100000

char frames[FRAMES][SCREEN_HEIGHT][SCREEN_WIDTH];// 定义存储帧数据的数组
Object objects[MAX_OBJECTS];// 定义物体数组
int numObjects = 0;

void initNcurses() {
    initscr();
    cbreak();
    noecho();
    timeout(0);
    curs_set(0);
}

void cleanupNcurses() {
    endwin();
}

void addObject(Object object) {
    if (numObjects < MAX_OBJECTS) {
        objects[numObjects++] = object;
    }
}

void drawObjects() {
    for (int i = 0; i < numObjects; i++) {
        Object object = objects[i];
        attron(object.color);
        mvaddstr(object.y, object.x, object.style);
        addch(object.symbol);
        attroff(object.color);
    }
}

// 更新所有物体的位置
void updateObjects() {
    for (int i = 0; i < numObjects; i++) {
        Object* object = &objects[i];
        object->x += object->deltaX;
        object->y += object->deltaY;

        // 检查是否撞到屏幕边界，如果是则改变方向
        if (object->x <= 0 || object->x >= SCREEN_WIDTH - 1) {
            object->deltaX = -object->deltaX;
        }
        if (object->y <= 0 || object->y >= SCREEN_HEIGHT - 1) {
            object->deltaY = -object->deltaY;
        }
    }
}

// 保存当前帧数据到帧数组中
void saveFrame(int frame) {
    for (int i = 0;i < SCREEN_HEIGHT;i++){
        for (int j = 0;j < SCREEN_WIDTH;j++){
            frames[frame][i][j] = mvinch(i,j) & A_CHARTEXT;
            }
        }
}

// 导出帧数据到文件
void exportFrames(const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("无法打开文件\n");
        return;
    }

    fwrite(frames, sizeof(frames), 1, file);
    fclose(file);

    printf("帧数据已导出到文件\n");
}

// 从文件导入帧数据
void importFrames(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("无法打开文件\n");
        return;
    }

    fread(frames, sizeof(frames), 1, file);
    fclose(file);

    printf("帧数据已导入\n");
}





int main() {
    // 初始化物体
    Object object1 = {'O', 60, 10, 1, -1, " * * \n*   *\n * * \n* * *\n * * \n*   *\n*   *\n"};
    Object object2 = {'X', 20, 20, -1, 1, "  ^^ \n  ^  \n ^^^ \n^   ^\n^   ^\n ^^^ \n"};
    addObject(object1);
    addObject(object2);
    printf(" * * \n*   *\n * * \n* * *\n * * \n*   *\n*   *\n");
    printf("  ^^ \n ^^^ \n^   ^\n ^^^ \n");
    // 初始化ncurses
    initNcurses();

    // 循环渲染和更新帧
    for (int frame = 0; frame < FRAMES; frame++) {     
        clear();
        drawObjects();
        saveFrame(frame);
        refresh();
        updateObjects();
        usleep(FRAME_DELAY);
    }
    exportFrames("frames.txt");
    importFrames("frames.txt");
    cleanupNcurses();
    
    
    return 0;
}

