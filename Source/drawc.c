/*******************************************
FileName: drawc.c
Author:   刘子恒 
Date：    2020/10/16
Description: 该文件主要用于绘制折线图 
Others: 无
Function List: 
        drawchart(); 绘制折线图函数 
 		readata();	 读取数据函数 
 		areafunc();	 地区编号转换函数 
 		giveweight();改变权重函数 
 		findday();	 寻找对应日期数据函数 
********************************************/
#include "common.h"
#include "drawc.h"
#include "gettime.h"

/*函数功能：画折线图*/

void drawchart(CHARTDATA *data, int areakey, int count)
{
    int i, j;
    float x = 1.0;
    int inf, hea, dea, alinf, alhea, aldea;
    giveweight(&areakey, &x);      //由不同区域给与不同权重防止折线图过大
    readata(data, areakey, count); //读取数据
    Line3(221, 706, 221, 300, 3, 0x0000);
    Line3(221, 706, 920, 706, 3, 0x0000);
    for (i = 0; i < 10; i++) //绘制箭头
    {
        Line3(221 - i, 300 + 2 * i, 221 + i, 300 + 2 * i, 1, 0x0000);
    }
    for (i = 0; i < 10; i++) //绘制箭头
    {
        Line3(920 - 2 * i, 706 + i, 920 - 2 * i, 706 - i, 1, 0x0000);
    }
    
    for (i = 0; i < 135 - 1; i++) //绘制折线图
    {
        Line2(224 + (5 * i), 700 - x * data[i].allinf, 224 + 5 * (i + 1), 700 - x * data[i + 1].allinf, 0x1111);
        Line2(224 + (5 * i), 700 - x * data[i].alldea, 224 + 5 * (i + 1), 700 - x * data[i + 1].alldea, 0x2222);
        Line2(224 + (5 * i), 700 - x * data[i].allhea, 224 + 5 * (i + 1), 700 - x * data[i + 1].allhea, 0xffff);
        Line2(224 + (5 * i), 700 - x * data[i].heal, 224 + 5 * (i + 1), 700 - x * data[i + 1].heal, 0x4444);
        Line2(224 + (5 * i), 700 - x * data[i].death, 224 + 5 * (i + 1), 700 - x * data[i + 1].death, 0x5555);
        Line2(224 + (5 * i), 700 - x * data[i].infestor, 224 + 5 * (i + 1), 700 - x * data[i + 1].infestor, 0x6666);
    }
}
/*函数功能：读取数据*/
void readata(CHARTDATA *data, int areakey, int count)
{
    char area[8 + 1] = "";
    const char t[4] = {".DAT"};
    int i, j, dnum, year, month, day;
    FILE *fp;
    char filename[10] = "start";
    SAVEDAY *d = NULL;
    memset(data, '\0', sizeof(CHARTDATA) * 135);
    areafunc(areakey, area); //得到地区编号对应区域

    if ((d = (SAVEDAY *)malloc(sizeof(SAVEDAY))) == NULL)
    {

        delay(3000);
        exit(1); //分配空间不足，退出程序
    }
    gett(&year, &month, &day);                            //找到当日日期
    dnum = findday(year, month, day) - 135 * (count + 1); //从当日开始画图
    if (dnum < 0)
        dnum = 0; //防止越界

    while (area[i] != '\0')
    {
        filename[0] = area[i];
        filename[1] = '\0';
        strcat(filename, t);
        filename[5] = '\0';
        i++;

        if ((fp = fopen(filename, "rb+")) == NULL)
        {
            put_asc16_size(185 + 150 + 80 + 80, 600, 2, 2, filename, 0x0000);
            delay(3000);
            exit(1); //打开失败，退出程序
        }
        for (j = 0; j < 135; j++)
        {
            fseek(fp, (dnum + j) * sizeof(SAVEDAY), SEEK_SET);
            fread(d, sizeof(SAVEDAY), 1, fp);
            data[j].infestor = data[j].infestor + atoi(d->infestor); //该日新增感染
            data[j].death = data[j].death + atoi(d->death);          //该日新增死亡
            data[j].heal = data[j].heal + atoi(d->heal);             //该日治愈
            data[j].allinf = data[j].allinf + atoi(d->allinf);       //到该日为止 总感染数
            data[j].alldea = data[j].alldea + atoi(d->alldea);       //到该日为止 总治愈数
            data[j].allhea = data[j].allhea + atoi(d->allhea);       //到该日为止 总死亡数
        }
        if (fclose(fp) != 0) //关闭文件
        {
            printf("\nError in closing file .");
            delay(3000);
            exit(1);
        }
    }
    free(d);
}
/*函数功能：地区编号转换*/
void areafunc(int areakey, char area[])
{
    switch (areakey)
    {
    case 0:
        strcpy(area, "0");
        break;
    case 1:
        strcpy(area, "1");
        break;
    case 2:
        strcpy(area, "2");
        break;
    case 3:
        strcpy(area, "3");
        break;
    case 4:
        strcpy(area, "4");
        break;
    case 5:
        strcpy(area, "5");
        break;
    case 6:
        strcpy(area, "6");
        break;
    case 7:
        strcpy(area, "7");
        break;
    case 8:
        strcpy(area, "01");
        break;
    case 9:
        strcpy(area, "23");
        break;
    case 10:
        strcpy(area, "45");
        break;
    case 11:
        strcpy(area, "67");
        break;
    case 12:
        strcpy(area, "0123");
        break;
    case 13:
        strcpy(area, "4567");
        break;
    case 14:
        strcpy(area, "01234567");
        break;
    }
}
/*函数功能：赋予权重*/
void giveweight(int *areakey, float *x)
{

    if (*areakey < 8)
    {
        *x = 3;
    }
    if (*areakey < 12 && *areakey > 7)
    {
        *x = 2;
    }
    if (*areakey > 11 && *areakey < 14)
    {
        *x = 1;
    }
    if (*areakey == 14)
    {
        *x = 0.5;
    }
}
/*函数功能：寻找某天对应编号*/
int findday(int year, int month, int day)
{
    FILE *fp;
    SAVEDAY *d = NULL;
    int length, i, count;
    if ((fp = fopen("0.DAT", "rb+")) == NULL)
    {
        put_asc16_size(185 + 150 + 80 + 80, 600, 2, 2, "file error", 0x0000);
        delay(3000);
        exit(1); //打开失败，退出程序
    }
    if ((d = (SAVEDAY *)malloc(sizeof(SAVEDAY))) == NULL)
    {

        delay(3000);
        exit(1); //分配空间不足，退出程序
    }
    fseek(fp, 0, SEEK_END);
    length = ftell(fp) / sizeof(SAVEDAY);
    for (i = 0; i < length; i++)
    {
        fseek(fp, i * sizeof(SAVEDAY), SEEK_SET);
        fread(d, sizeof(SAVEDAY), 1, fp);
        if (year == atoi(d->year) && month == atoi(d->month) && day == atoi(d->day))
        {
            //找到对应日期后停止
            break;
        }
    }
    free(d);
    if (fclose(fp) != 0) //关闭文件
    {
        printf("\nError in closing file .");
        delay(3000);
        exit(1);
    }
    return i;
}
