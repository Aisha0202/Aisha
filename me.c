#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 

int main(){
    char arr[10]={' ',' ',' ',' ',' ',' ',' ',' ',' ','\0'};
    printf("input= ");
    scanf(" %c",&arr[0]);
    char *p = &arr[0];
    int i;
    for(i=0;i<9;i++){
     system("cls||clear");
        p++;
        *p = arr[i];
        arr[i+1] = *p;
        *(p - 1) = ' ';
        int k;
        for(k=0;k<10;k++){
        printf("arr[%d] = %c\n",k,arr[k]);
    }
        usleep(500000);
        }
     return 0;
}
