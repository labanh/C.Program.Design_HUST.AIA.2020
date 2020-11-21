/*******************************************
FileName: areview.c
Author:   韩海若
Date：    2020/10/29
Description: 该程序文件用于通报数据审核
Function List: 
        admin_review(void); //通报数据审核函数
        judge_redata(void); //判断是否有待审核通报
********************************************/
#include "areview.h"
#include "common.h"

/*********************************
Function: admin_review()
Description: 通报数据审核函数 
Calls:  judge_redata
        wr_database
Called by: main()
Table Accessed: userepo.DAT
Table Updated:  userepo.DAT
********************************/
int admin_review(void)
{
    int flg = 0;
    FILE *fp;
    DAY *d = NULL;
    int i, j;
    int length;
    char key = 0;

    Bar1(0, 0, 1024, 768, 0xa794);

    if ((fp = fopen("userepo.dat", "rb+")) == NULL)
    { //打开userepo.dat

        printf("\nUserInfo.dat error file");
        delay(3000);
        exit(1); //打开失败，退出程序
    }

    if ((d = (DAY *)malloc(sizeof(DAY))) == NULL)
    { //初始化当日信息结构体

        printf("memory error JudgeSameName");
        delay(3000);
        exit(1); //分配空间不足，退出程序
    }

    fseek(fp, 0, SEEK_END); //移至文件末尾
    length = ftell(fp) / sizeof(DAY); //计算通报个数

    for (i = 0; i < length; i++)
    {
        memset(d, '\0', sizeof(DAY));   //初始化结构体
        fseek(fp, i * sizeof(DAY), SEEK_SET);   //移至当前通报数据
        fread(d, sizeof(DAY), 1, fp);   //将数据写进结构体
        if (d->infostate == '0')        //如果未审核则跳出
        {
            break;
        }
    }

    if (fclose(fp) != 0) //关闭文件
    {
        printf("\nError in closing file .");
        delay(3000);
        exit(1);
    }
    
    key = judge_redata();   //判断是否有待审核通报
    
    if (key == '1')
    {
        prt_hz16_size(420, 300, 2, 2, "无数据待审核", 0, "HZK\\Hzk16s");
        prt_hz16_size(375, 350, 2, 2, "将自动返回上一界面", 0, "HZK\\Hzk16s");
        delay(2000);
        if (d != NULL)
        {
            free(d);
            d = NULL;
        }
        return 8;
    }

    //标题
    prt_hz24d(40, 50, "用户名", 0, "HZK\\Hzk24h");
    prt_hz24d(250, 50, "年", 0, "HZK\\Hzk24h");
    prt_hz24d(320, 50, "月", 0, "HZK\\Hzk24h");
    prt_hz24d(400, 50, "日", 0, "HZK\\Hzk24h");
    prt_hz24d(500, 50, "新增确诊", 0, "HZK\\Hzk24h");
    prt_hz24d(650, 50, "新增死亡", 0, "HZK\\Hzk24h");
    prt_hz24d(800, 50, "新增治愈", 0, "HZK\\Hzk24h");
    prt_hz24d(920, 50, "数据区域", 0, "HZK\\Hzk24h");

    Line3(0, 98, 1024, 98, 2, 0);
    Bar1(0, 100, 1024, 198, 14137); //突出第一行

    Line3(0, 198, 1024, 198, 2, 0);
    Line3(0, 298, 1024, 298, 2, 0);
    Line3(0, 398, 1024, 398, 2, 0);
    Line3(0, 498, 1024, 498, 2, 0);
    
    Bar1(0, 666, 100, 768, 0x5b4f);
    Bar1(0, 668, 98, 768, 0x37dc);
    prt_hz24d(25, 706, "返回", 0, "HZK\\Hzk24h");
    Bar1(924, 666, 1024, 768, 0x5b4f);
    Bar1(926, 668, 1024, 768, 0x37dc);
    prt_hz24d(951, 706, "退出", 0, "HZK\\Hzk24h");
    Bar1(204, 666, 408, 768, 0x5b4f);
    Bar1(206, 668, 406, 768, 0xfd84);
    prt_hz24d(258, 706, "采纳数据", 0, "HZK\\Hzk24h");
    Bar1(616, 666, 820, 768, 0x5b4f);
    Bar1(618, 668, 818, 768, 0xfd84);
    prt_hz24d(670, 706, "删除数据", 0, "HZK\\Hzk24h");

    prt_hz16_asc16_size(20, 20 + 100, 2, 2, d->username, 0, "HZK\\Hzk16k");
    prt_hz16_asc16_size(40 + 200, 20 + 100, 2, 2, d->year, 0, "HZK\\Hzk16k");
    prt_hz16_asc16_size(40 + 200 + 100, 20 + 100, 2, 2, d->month, 0, "HZK\\Hzk16k");
    prt_hz16_asc16_size(40 + 200 + 100 + 60, 20 + 100, 2, 2, d->day, 0, "HZK\\Hzk16k");
    prt_hz16_asc16_size(520, 20 + 100, 2, 2, d->infestor, 0, "HZK\\Hzk16k");
    prt_hz16_asc16_size(670, 20 + 100, 2, 2, d->death, 0, "HZK\\Hzk16k");
    prt_hz16_asc16_size(820, 20 + 100, 2, 2, d->heal, 0, "HZK\\Hzk16k");
    if (d->area[0] == '0')
    {
        prt_hz24(920, 20 + 100, "益民小区", 0x0000, "HZK\\Hzk24k");
    }
    if (d->area[0] == '1')
    {
        prt_hz24(920, 20 + 100, "北门小区", 0x0000, "HZK\\Hzk24k");
    }
    if (d->area[0] == '2')
    {
        prt_hz24(920, 20 + 100, "光明小区", 0x0000, "HZK\\Hzk24k");
    }
    if (d->area[0] == '3')
    {
        prt_hz24(920, 20 + 100, "桂园小区", 0x0000, "HZK\\Hzk24k");
    }
    if (d->area[0] == '4')
    {
        prt_hz24(920, 20 + 100, "南池小区", 0x0000, "HZK\\Hzk24k");
    }
    if (d->area[0] == '5')
    {
        prt_hz24(920, 20 + 100, "丽景小区", 0x0000, "HZK\\Hzk24k");
    }
    if (d->area[0] == '6')
    {
        prt_hz24(920, 20 + 100, "风韵荷都", 0x0000, "HZK\\Hzk24k");
    }
    if (d->area[0] == '7')
    {
        prt_hz24(920, 20 + 100, "恒大名都", 0x0000, "HZK\\Hzk24k");
    }

    if (d != NULL)
    {
        free(d);
        d = NULL;
    }

    Mouse_Init();
    while (1)
    {
        MouseShow(&mouse);
        if (flg == 0 && MouseIn(926, 668, 1024, 768)) //退出框反馈
        {
            MouseOff(&mouse);
            Bar1(926, 668, 1024, 768, 0x9ea0);
            prt_hz24d(951, 706, "退出", 0x0000, "HZK\\Hzk24h");
            MouseOn(mouse);
            flg = 1;
        }
        if (flg == 0 && MouseIn(0, 668, 98, 768)) //返回框反馈
        {
            MouseOff(&mouse);
            Bar1(0, 668, 98, 768, 0x9ea0);
            prt_hz24d(25, 706, "返回", 0x0000, "HZK\\Hzk24h");
            MouseOn(mouse);
            flg = 1;
        }
        if (flg == 0 && MouseIn(206, 668, 406, 768)) //采纳数据键反馈
        {
            MouseOff(&mouse);
            Bar1(206, 668, 406, 768, 0x2f44);
            prt_hz24d(258, 706, "采纳数据", 0, "HZK\\Hzk24h");
            MouseOn(mouse);
            flg = 1;
        }
        if (flg == 0 && MouseIn(618, 668, 818, 768)) //删除键反馈
        {
            MouseOff(&mouse);
            Bar1(618, 668, 818, 768, 0x2f44);
            prt_hz24d(670, 706, "删除数据", 0, "HZK\\Hzk24h");
            MouseOn(mouse);
            flg = 1;
        }

        else if (flg == 1 && !(MouseIn(926, 668, 1024, 768)) 
                           && !(MouseIn(0, 668, 98, 768)) 
                           && !(MouseIn(206, 668, 406, 768)) 
                           && !(MouseIn(618, 668, 818, 768)))
        {
            MouseOff(&mouse);
            Bar1(926, 668, 1024, 768, 0xccff);
            Bar1(0, 668, 98, 768, 0xccff);
            Bar1(206, 668, 406, 768, 0xffff);
            Bar1(618, 668, 818, 768, 0xffff);
            prt_hz24d(951, 706, "退出", 0x0000, "HZK\\Hzk24h");
            prt_hz24d(25, 706, "返回", 0x0000, "HZK\\Hzk24h");
            prt_hz24d(258, 706, "采纳数据", 0, "HZK\\Hzk24h");
            prt_hz24d(670, 706, "删除数据", 0, "HZK\\Hzk24h");
            MouseOn(mouse);
            flg = 0;
        }
        else if (MousePress(206, 668, 406, 768)) //点击采纳数据
        {
            if ((fp = fopen("userepo.dat", "rb+")) == NULL)
            {
                printf("\nUserInfo.dat error file");
                delay(3000);
                exit(1); //打开失败，退出程序
            }

            if ((d = (DAY *)malloc(sizeof(DAY))) == NULL)
            {
                printf("memory error JudgeSameName");
                delay(3000);
                exit(1); //分配空间不足，退出程序
            }
            
            fseek(fp, 0, SEEK_END);
            length = ftell(fp) / sizeof(DAY);
            
            for (i = 0; i < length; i++)
            {
                memset(d, '\0', sizeof(DAY));
                fseek(fp, i * sizeof(DAY), SEEK_SET);
                fread(d, sizeof(DAY), 1, fp);
                if (d->infostate == '0')    
                {
                    d->infostate = '1'; //审核通过将参数置为1
                    break;
                }
            }

            fseek(fp, i * sizeof(DAY), SEEK_SET);
            
            fwrite(d, sizeof(DAY), 1, fp);  //在文件中重设用户通报状态

            wr_database(d); //将通报的数据写入文件
            
            prt_hz24d(458, 706, "审核通过", 0, "HZK\\Hzk24h");
            delay(1000);
            
            if (d != NULL)
            {
                free(d);
                d = NULL;
            }
            if (fclose(fp) != 0) //关闭文件
            {
                printf("\nError in closing file .");
                delay(3000);
                exit(1);
            }
            return 10;
        }
        else if (MousePress(618, 668, 818, 768)) //点击删除数据
        {
            if ((fp = fopen("userepo.dat", "rb+")) == NULL)
            {
                printf("\nUserInfo.dat error file");
                delay(3000);
                exit(1); //打开失败，退出程序
            }
            if ((d = (DAY *)malloc(sizeof(DAY))) == NULL)
            {
                printf("memory error JudgeSameName");
                delay(3000);
                exit(1); //分配空间不足，退出程序
            }
            
            fseek(fp, 0, SEEK_END);
            length = ftell(fp) / sizeof(DAY);
            
            for (i = 0; i < length; i++)
            {
                memset(d, '\0', sizeof(DAY));
                fseek(fp, i * sizeof(DAY), SEEK_SET);
                fread(d, sizeof(DAY), 1, fp);
                if (d->infostate == '0')
                {
                    d->infostate = '2';
                    break;
                }
            }

            fseek(fp, i * sizeof(DAY), SEEK_SET);
            fwrite(d, sizeof(DAY), 1, fp); //在文件中重设用户通报状态
            
            prt_hz24d(458, 706, "数据有误", 0, "HZK\\Hzk24h");
            delay(1000);
            
            if (d != NULL)
            {
                free(d);
                d = NULL;
            }
            if (fclose(fp) != 0) //关闭文件
            {
                printf("\nError in closing file .");
                delay(3000);
                exit(1);
            }
            return 10;
        }

        if (MousePress(926, 668, 1024, 768)) //点击退出
        {
            CloseSVGA();
            delay(1000);
            exit(1);
        }
        else if (MousePress(0, 668, 98, 768)) //点击返回
        {
            if (d != NULL)
            {
                free(d);
                d = NULL;
            }
            return 8;
        }
    }
}

/*********************************
Function: judge_redata()
Description: 通报数据审核函数 
Called by: admin_review()
Table Accessed: userepo.DAT
********************************/
char judge_redata(void)
{
    char flg = '1';
    FILE *fp;
    DAY *d = NULL; //记得free
    int i;
    int length;
    
    if ((fp = fopen("userepo.dat", "rb+")) == NULL)
    {
        printf("\nUserInfo.dat error file");
        delay(3000);
        exit(1); //打开失败，退出程序
    }
    
    if ((d = (DAY *)malloc(sizeof(DAY))) == NULL)
    {
        printf("memory error JudgeSameName");
        delay(3000);
        exit(1); //分配空间不足，退出程序
    }
    
    memset(d, '\0', sizeof(DAY));   //初始化结构体
    fseek(fp, 0, SEEK_END); //移至文件末尾
    length = ftell(fp) / sizeof(DAY);   //计算通报个数
    
    for (i = 0; i < length; i++)
    {
        fseek(fp, i * sizeof(DAY), SEEK_SET);
        fread(d, sizeof(DAY), 1, fp);
        if (d->infostate == '0')    //如果有未审核通报
        {
            flg = '0';
            break;  //退出循环
        }
    }

    if (d != NULL)
    {
        free(d);
        d = NULL;
    }

    if (fclose(fp) != 0) //关闭文件
    {
        printf("\nError in closing file .");
        delay(3000);
        exit(1);
    }
    return flg;
}
