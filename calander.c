#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//justy odd^double
int justy(int year){
    if ((year % 4 == 0&&year % 100 != 0 )||(year % 400 ==0)){
       return 1;
    }else{
       return 0;
    }
}
    
//justy date
int getdays(int month , int year){
    switch(month){
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
            return 31;
            break;
        case 4:
        case 6:
        case 9:
        case 11:
            return 30;
            break;
        case 2:
            if (justy(year) == 1){
            return 29;
            }else{
            return 28;
            }
            break;
        default:
            printf("err\n");
            break;
    }
}

//justy week_first
int getfirst(int year,int month){
    return (year - year/4 + year/100 - year/400 +(13 * month + 8) / 5 + 3)% 7;
    }


     
//print calander
int calander(int year){
    for(int month = 1;month <= 12;month++){
    printf("\n\n Month: %d\n",month);
    printf(" Sun Mon Tue Wed Thu Fri Sat\n");
    int first = getfirst(year,month);
    int days = getdays(month,year);
    int DAY = 1;
    for(int i = 0;i < 6;i++){
        for(int j = 0;j < 7;j++){
            if (i == 0 && j < first){
            printf("    ");
            }else if (DAY > days){
            break;
            }else{
            printf("%4d",DAY);
            DAY++;
            }
        }
        printf("\n");
    }
    }
    return 0;
    
}

int main(){
    int year;
    printf("input:    \n");
    scanf("%d",&year);
    calander(year);
    return 0;
}
