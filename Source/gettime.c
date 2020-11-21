/*获取当日时间*/
#include "common.h"

void gett(int *year, int *month, int *day)
{
    time_t timep;
    struct tm *p;
    time(&timep);
    p = gmtime(&timep);
    if ((p->tm_hour) < 8) /*将世界标准时间转换为中国时间*/
        *day = p->tm_mday - 1;
    else
        *day = p->tm_mday;     /*获取当前月份日数,范围是1-31*/
    *month = 1 + p->tm_mon;    /*获取当前月份,范围是0-11,所以要加1*/
    *year = 1900 + p->tm_year; /*获取当前年份,从1900开始，所以要加1900*/
}
