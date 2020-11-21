/*******************************************
FileName:dayinfo.c
Author:   刘子恒 
Date：    2020/10/16
Description: 该文件主要用于用户通报数据功能 
Others: 无
Function List: 
        wr_day_inf();  	将每日疫情信息写入文件
 		countcases();		计算单个文件中各项总数
 		countallcases();	计算所有文件中各项总数
 		judge_date();		判断输入的日期是否合法
 		judge_cases();		判断输入的疫情信息是否合法
 		countareacases();	读取某区域各项数据
 		wr_area();			将将要通报的文件名写入文件
 		re_area();			将将要通报的文件名读出 
		wr_database();		将数据写入数据库
 		modify_database();	修改数据库中的数据
 		getoneday();		获取某天在数据库中的位置

********************************************/
#include "common.h"
#include "dayinfo.h"
#include "drawc.h"

/*函数功能：将每日疫情信息写入临时存储文件*/
void wr_day_inf(char area[], char Ye[], char Mo[], char Da[], char In[], char De[], char He[], char User[])
{
    FILE *fp = NULL;
    DAY *d = NULL;
    int i;
    if ((fp = fopen("userepo.dat", "rb+")) == NULL)
    {
        printf(" error file");
        delay(3000);
        exit(1); //打开失败，退出程序
    }
    if ((d = (DAY *)malloc(sizeof(DAY))) == NULL)
    {
        printf("memory error Wrfile");
        delay(3000);
        exit(1); //分配空间不足，退出程序
    }
    memset(d, '\0', sizeof(DAY)); //将结构体每位都写入
    for (i = 0; i < 5; i++)
    {
        d->area[i] = area[i];
    }
    for (i = 0; i < 4; i++)
    {
        d->year[i] = Ye[i];
    }
    for (i = 0; i < 2; i++)
    {
        d->month[i] = Mo[i];
    }
    for (i = 0; i < 2; i++)
    {
        d->day[i] = Da[i];
    }
    for (i = 0; i < 6; i++)
    {
        d->infestor[i] = In[i];
    }
    for (i = 0; i < 6; i++)
    {
        d->death[i] = De[i];
    }
    for (i = 0; i < 6; i++)
    {
        d->heal[i] = He[i];
    }
    for (i = 0; i < 13; i++)
    {
        d->username[i] = User[i];
    }
    d->infostate = '0';
    d->n[0] = '\r'; //在记事本中打开可以换行
    d->n[1] = '\n';
    fseek(fp, 0, SEEK_END);
    fwrite(d, sizeof(DAY), 1, fp);
    free(d);
    if (fclose(fp) != 0) //关闭文件
    {
        printf("\nError in closing file .");
        delay(3000);
        exit(1);
    }
    delay(500);
}

/*函数功能：计算单个文件中各项总数 */
void countcases(char *filename, int *suminf, int *sumdea, int *sumheal, int *nowinf)
{
    int i, j;
    int length;
    FILE *fp;
    SAVEDAY *d = NULL;
    *suminf = 0;
    *sumdea = 0; //初始化总数
    *sumheal = 0;
    *nowinf = 0;

    if ((fp = fopen(filename, "rb+")) == NULL)
    {
        printf("\n%s error file", filename);
        delay(3000);
        exit(1); //打开失败，退出程序
    }
    fseek(fp, 0, SEEK_END);
    length = ftell(fp) / sizeof(SAVEDAY);

    if ((d = (SAVEDAY *)malloc(sizeof(SAVEDAY))) == NULL)
    {
        printf("memory error CountCase");
        delay(3000);
        exit(1); //分配空间不足，退出程序
    }
    fseek(fp, (length - 1) * sizeof(SAVEDAY), SEEK_SET); // 读取数据库最后一天的数据
    fread(d, sizeof(SAVEDAY), 1, fp);

    *suminf = atoi(d->allinf);
    *sumheal = atoi(d->allhea);
    *sumdea = atoi(d->alldea);
    *nowinf = (*suminf) - (*sumdea) - (*sumheal);

    if (d != NULL)
    {
        free(d);
        d = NULL;
    }
    if (fclose(fp) != 0) //关闭文件
    {
        printf("\nError in closing file %s", filename);
        delay(3000);
        exit(1);
    }
}

/*函数功能：计算所有文件中各项总数 */
void countallcases(int filenumbers, int *alsuminf, int *alsumdea, int *alsumheal, int *alnowinf)
{
    int i;
    char tempfilename[10] = {"0.DAT"};
    const char t[4] = {".DAT"};
    int countifn, countdea, countheal, countnoinf;
    *alsuminf = 0;
    *alsumdea = 0;
    *alsumheal = 0;
    *alnowinf = 0;

    for (i = 0; i < filenumbers + 1; i++) // 使用循环逐个读取
    {
        itoa(i, tempfilename, 10);
        strcat(tempfilename, t);
        countcases(tempfilename, &countifn, &countdea, &countheal, &countnoinf);
        *alsuminf = *alsuminf + countifn;
        *alsumdea = *alsumdea + countdea;
        *alsumheal = *alsumheal + countheal;
        *alnowinf = *alsuminf - *alsumdea - *alsumheal;
    }
}

/*函数功能：判断输入的日期是否合法 */
int judge_date(char year[], char month[], char day[])
{
    int i, m, d;
    int flaga = 1;
    int flagb = 1;
    int flagc = 1;
    int flagd = 1;
    int mon[13] = {1, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}; // 每月相对日数

    int lea = strlen(month);
    int leb = strlen(day);
    int lec = strlen(year);
    for (i = 0; i < lec; i++)
    {
        if (year[i] > '9' || year[i] < '0' || year[0] != '2' || year[1] != '0' || year[2] != '2' || year[3] != '0')
        {
            flagc = 1;
            break;
        }
        else
            flagc = 0;
    }
    for (i = 0; i < lea; i++)
    {
        if (month[i] > '9' || month[i] < '0')
        {
            flaga = 1;
            break;
        }
        else
            flaga = 0;
    }
    for (i = 0; i < leb; i++)
    {
        if (day[i] > '9' || day[i] < '0')
        {
            flagb = 1;
            break;
        }

        else
            flagb = 0;
    }

    if (flaga == 0 && flagb == 0)
    {
        m = atoi(month);
        d = atoi(day);
        if (12 < m || m < 1 || mon[0] > d || mon[m] < d)
            flagd = 1;
        else
            flagd = 0;
    }
    return (flaga + flagb + flagc + flagd); // 只有均为零才为零
}

/*函数功能：判断输入的病例是否合法 */
int judge_cases(char inf[], char dea[], char hea[])
{
    int i, m, d;
    int flaga = 1;
    int flagb = 1;
    int flagc = 1;

    int lea = strlen(inf);
    int leb = strlen(dea);
    int lec = strlen(hea);
    for (i = 0; i < lea; i++)
    {
        if (inf[i] > '9' || inf[i] < '0')
        {
            flaga = 1;
            break;
        }
        else
            flaga = 0;
    }
    for (i = 0; i < leb; i++)
    {
        if (dea[i] > '9' || dea[i] < '0')
        {
            flagb = 1;
            break;
        }
        else
            flagb = 0;
    }
    for (i = 0; i < lec; i++)
    {
        if (hea[i] > '9' || hea[i] < '0')
        {
            flagc = 1;
            break;
        }
        else
            flagc = 0;
    }
    return (flaga + flagb + flagc); // 均为0才为0
}

/*函数功能：将某区域数据读出*/
void countareacases(int areakey, int *suminf, int *sumdea, int *sumheal, int *nowinf)
{
    char area[8 + 1] = "";
    const char t[4] = {".DAT"};
    int i = 0, j, length;
    FILE *fp;
    char filename[10] = "start";
    SAVEDAY *d = NULL;
    areafunc(areakey, area); // 得到相应地区号包含地区的序列
    *suminf = 0;
    *sumdea = 0;
    *sumheal = 0;
    *nowinf = 0;

    if ((d = (SAVEDAY *)malloc(sizeof(SAVEDAY))) == NULL)
    {

        delay(3000);
        exit(1); //分配空间不足，退出程序
    }

    while (area[i] != '\0') // 使用循环逐个文件打开
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
        fseek(fp, 0, SEEK_END);
        length = ftell(fp) / sizeof(SAVEDAY);
        fseek(fp, (length - 1) * sizeof(SAVEDAY), SEEK_SET);
        fread(d, sizeof(SAVEDAY), 1, fp);
        *suminf = atoi(d->allinf) + *suminf;
        *sumdea = atoi(d->alldea) + *sumdea;
        *sumheal = atoi(d->allhea) + *sumheal;

        if (fclose(fp) != 0) //关闭文件
        {
            printf("\nError in closing file .");
            delay(3000);
            exit(1);
        }
    }
    free(d);
    *nowinf = *suminf - *sumdea - *sumheal;
}

/*函数功能：将将要通报的文件名写入文件*/
void wr_area(int areakey)
{
    FILE *fp;
    if ((fp = fopen("areanow.dat", "rb+")) == NULL)
    {
        printf("areanow.dat file error\n");
        delay(3000);
        exit(1);
    }
    fseek(fp, 0, SEEK_SET);
    fwrite(&areakey, sizeof(int), 1, fp);
    if (fclose(fp) != 0) //关闭文件
    {
        printf("\nError in closing file areanow.");
        delay(3000);
        exit(1);
    }
}

/*函数功能：将将要通报的文件名读出*/
void re_area(int *areakey)
{
    FILE *fp;
    if ((fp = fopen("areanow.dat", "rb+")) == NULL)
    {
        printf("areanow.dat file error\n");
        delay(3000);
        exit(1);
    }
    fseek(fp, 0, SEEK_SET);
    fread(areakey, sizeof(int), 1, fp);
    if (fclose(fp) != 0) //关闭文件
    {
        printf("\nError in closing file areanow.");
        delay(3000);
        exit(1);
    }
}

/*函数功能：将数据写入数据库*/
void wr_database(DAY *a)
{
    FILE *fp;
    SAVEDAY *d;
    const char t[4] = {".DAT"};
    char filename[10] = "start";
    int i, j, flag = 1, temp, length;
    memset(filename, '\0', sizeof(char) * 10);
    filename[0] = a->area[0];
    filename[1] = '\0';
    strcat(filename, t);
    filename[5] = '\0';
    if ((fp = fopen(filename, "rb+")) == NULL)
    {
        put_asc16_size(185 + 150 + 80 + 80, 600, 2, 2, filename, 0x0000);
        delay(3000);
        exit(1); //打开失败，退出程序
    }
    if ((d = (SAVEDAY *)malloc(sizeof(SAVEDAY))) == NULL)
    {
        printf("memory error Wrfile");
        delay(3000);
        exit(1); //分配空间不足，退出程序
    }

    memset(d, '\0', sizeof(SAVEDAY));
    fseek(fp, 0, SEEK_END);
    length = ftell(fp) / sizeof(SAVEDAY);
    for (i = 0; i < length; i++)
    {
        fseek(fp, i * sizeof(SAVEDAY), SEEK_SET);
        fread(d, sizeof(SAVEDAY), 1, fp);
        if (strcmp(a->year, d->year) == 0 && strcmp(a->month, d->month) == 0 && strcmp(a->day, d->day) == 0)
        {
            flag = 0; // 找到相应日期
            break;
        }
    }
    if (flag == 0)
    {
        fseek(fp, i * sizeof(SAVEDAY), SEEK_SET);
        fread(d, sizeof(SAVEDAY), 1, fp);
        temp = atoi(d->infestor) + atoi(a->infestor);
        itoa(temp, d->infestor, 10);
        temp = atoi(d->death) + atoi(a->death);
        itoa(temp, d->death, 10);
        temp = atoi(d->heal) + atoi(a->heal);
        itoa(temp, d->heal, 10);
        temp = atoi(d->allinf) + atoi(a->infestor);
        itoa(temp, d->allinf, 10);
        temp = atoi(d->alldea) + atoi(a->death);
        itoa(temp, d->alldea, 10);
        temp = atoi(d->allhea) + atoi(a->heal);
        itoa(temp, d->allhea, 10);
        /*修改当日日期数据*/

        fseek(fp, i * sizeof(SAVEDAY), SEEK_SET);
        fwrite(d, sizeof(SAVEDAY), 1, fp);
        i++;

        for (; i < length; i++)
        {
            fseek(fp, i * sizeof(SAVEDAY), SEEK_SET);
            fread(d, sizeof(SAVEDAY), 1, fp);
            temp = atoi(d->allinf) + atoi(a->infestor);
            itoa(temp, d->allinf, 10);
            temp = atoi(d->alldea) + atoi(a->death);
            itoa(temp, d->alldea, 10);
            temp = atoi(d->allhea) + atoi(a->heal);
            itoa(temp, d->allhea, 10);
            fseek(fp, i * sizeof(SAVEDAY), SEEK_SET);
            fwrite(d, sizeof(SAVEDAY), 1, fp);
            /*更新该日日期信息*/

            //prt_hz24d(470,706,"成功",0,"HZK\\Hzk24h");
        }
    }
    free(d);
    if (fclose(fp) != 0) //关闭文件
    {
        printf("\nError in closing file .");
        delay(3000);
        exit(1);
    }
    delay(500);
}
/*函数功能：修改数据库中信息*/
void modify_database(SAVEDAY *a, char *area)
{
    FILE *fp = NULL;
    SAVEDAY *d = NULL;
    const char t[4] = {".DAT"};
    char filename[10] = "start";
    int i, j, flag = 1, temp, length;
    memset(filename, '\0', sizeof(char) * 10);
    filename[0] = *area;
    filename[1] = '\0';
    strcat(filename, t);
    filename[5] = '\0';
    if ((fp = fopen(filename, "rb+")) == NULL)
    {
        put_asc16_size(185 + 150 + 80 + 80, 600, 2, 2, filename, 0x0000);
        delay(3000);
        exit(1); //打开失败，退出程序
    }
    if ((d = (SAVEDAY *)malloc(sizeof(SAVEDAY))) == NULL)
    {
        printf("memory error Wrfile");
        delay(3000);
        exit(1); //分配空间不足，退出程序
    }

    memset(d, '\0', sizeof(SAVEDAY));
    fseek(fp, 0, SEEK_END);
    length = ftell(fp) / sizeof(SAVEDAY);
    for (i = 0; i < length; i++)
    {
        fseek(fp, i * sizeof(SAVEDAY), SEEK_SET);
        fread(d, sizeof(SAVEDAY), 1, fp);
        if (strcmp(a->year, d->year) == 0 && strcmp(a->month, d->month) == 0 && strcmp(a->day, d->day) == 0)
        {
            flag = 0; //找到相应日期
            break;
        }
    }
    if (flag == 0)
    {
        strcpy(d->infestor, a->infestor);
        strcpy(d->death, a->death);
        strcpy(d->heal, a->heal);
        fseek(fp, i * sizeof(SAVEDAY), SEEK_SET);
        fwrite(d, sizeof(SAVEDAY), 1, fp);
        i++;

        for (; i < length; i++)
        {
            fseek(fp, i * sizeof(SAVEDAY), SEEK_SET);
            fread(d, sizeof(SAVEDAY), 1, fp);
            temp = atoi(d->allinf) + atoi(a->infestor);
            itoa(temp, d->allinf, 10);
            temp = atoi(d->alldea) + atoi(a->death);
            itoa(temp, d->alldea, 10);
            temp = atoi(d->allhea) + atoi(a->heal);
            itoa(temp, d->allhea, 10);

            fseek(fp, i * sizeof(SAVEDAY), SEEK_SET);
            fwrite(d, sizeof(SAVEDAY), 1, fp);
            //将日期更新并写入
            //prt_hz24d(470,706,"成功",0,"HZK\\Hzk24h");
        }
    }

    free(d);
    if (fclose(fp) != 0) //关闭文件
    {
        printf("\nError in closing file .");
        delay(3000);
        exit(1);
    }
    delay(500);
}
/*函数功能：获取某天的数据*/
void getoneday(SAVEDAY *a, int areakey, int daykey)
{
    char area[8 + 1] = "";
    const char t[4] = {".DAT"};
    int i = 0, j, temp;
    FILE *fp;
    SAVEDAY *d = NULL;
    char filename[10] = "start";
    areafunc(areakey, area);
    memset(a, '\0', sizeof(SAVEDAY));

    if ((d = (SAVEDAY *)malloc(sizeof(SAVEDAY))) == NULL)
    {
        printf("memory error Wrfile");
        delay(3000);
        exit(1); //分配空间不足，退出程序
    }

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
        fseek(fp, daykey * sizeof(SAVEDAY), SEEK_SET);
        fread(d, sizeof(SAVEDAY), 1, fp);
        strcpy(a->year, d->year);
        strcpy(a->month, d->month);
        strcpy(a->day, d->day);
        temp = atoi(d->infestor) + atoi(a->infestor);
        itoa(temp, a->infestor, 10);
        temp = atoi(d->death) + atoi(a->death);
        itoa(temp, a->death, 10);
        temp = atoi(d->heal) + atoi(a->heal);
        itoa(temp, a->heal, 10);
        temp = atoi(d->allinf) + atoi(a->allinf);
        itoa(temp, a->allinf, 10);
        temp = atoi(d->alldea) + atoi(a->alldea);
        itoa(temp, a->alldea, 10);
        temp = atoi(d->allhea) + atoi(a->allhea);
        itoa(temp, a->allhea, 10);

        if (fclose(fp) != 0) //关闭文件
        {
            printf("\nError in closing file .");
            delay(3000);
            exit(1);
        }
    }
    free(d);
}
