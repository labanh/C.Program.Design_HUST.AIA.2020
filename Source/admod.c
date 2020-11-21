/*******************************************
FileName: admod.c
Author:   韩海若
Date：    2020/10/29
Description: 该程序文件用于管理员的数据修改
Function List: 
        admin_modify()  //数据修改主控制函数
        pop_window1     //地点与时间弹窗
        pop_window2     //输入修改数据弹窗
        click_Data_Block//点击数据框高亮
        Unhighlight     //取消高亮
        modify_MainPage //主页面绘制
        mouse_feedback_main //鼠标反馈
Others:
各地区名称序号:
	M市1
		任城区2		
			古槐社区3
				益民小区4
				北门小区5
			仙营社区6
				光明小区7
				桂园小区8
		高新区9
			南池社区10
				南池小区11
				丽景小区12
            北湖社区13
				风韵荷都14
				恒大名都15
*******************************************/
#include "admod.h"
#include "choice.h"
#include "common.h"
#include "gettime.h"

/*********************************
Function: admin_modify()
Description: 数据修改主控制函数 
Calls:  pop_window1 //地点与时间弹窗
        modify_MainPage //主页面绘制
Called by: main()
Return:	8 返回管理员主界面
********************************/
int admin_modify(void)
{ //数据修改主函数

    int key;
    char area;

    //选择区域弹窗
    Bar1(0, 0, 1024, 768, 0xa794);
    if (pop_window1(&key, &area))//调用弹窗1
    {
        return 8;   //点击取消则返回管理员主界面
    }   

    Bar1(0, 0, 1024, 768, 0xa794);

    //显示主页面
    modify_MainPage(&key, &area);

    return 8;
}

/*********************************
Function: pop_window1()
Description: 操作选择区域和时间的两个弹窗
Calls:  choose_district //地点选择菜单
        choose_date     //时间选择
Called by: admin_modify()
Return:	0 返回admin_modify
        1 返回管理员主界面
********************************/
int pop_window1(int *key, char *area)
{ //选择区域和时间的两个弹窗

	int year,month,day,today;
	gett(&year, &month, &day);
	today = findday(year, month, day);
    Bar1(248, 168, 752, 482, 0);
    Bar1(250, 170, 750, 480, 0x8edf); //弹窗底色

    prt_hz24d(380, 200, "请选择您要修改的地区", 0, "HZK\\Hzk24h");

    Bar1(348, 413, 452, 457, 0x4b32);
    Bar1(350, 415, 450, 455, 0x8ff2);
    prt_hz24d(376, 423, "确认", 0, "HZK\\Hzk24h"); //确认键
    Bar1(548, 413, 652, 457, 0x4b32);
    Bar1(550, 415, 650, 455, 0x8ff2);
    prt_hz24d(576, 423, "取消", 0, "HZK\\Hzk24h"); //取消键

    //打开区域选择弹窗
    if (choose_district(265, 255, area)) //点击确定，进入下一弹窗
    {
        Bar1(248, 168, 752, 482, 0);
        Bar1(250, 170, 750, 480, 0x8edf); //弹窗底色
        prt_hz24d(380, 200, "请选择您要修改的日期", 0, "HZK\\Hzk24h");
        Bar1(348, 413, 452, 457, 0x4b32);
        Bar1(350, 415, 450, 455, 0x8ff2);
        prt_hz24d(376, 423, "确认", 0, "HZK\\Hzk24h"); //确认键
        Bar1(548, 413, 652, 457, 0x4b32);
        Bar1(550, 415, 650, 455, 0x8ff2);
        prt_hz24d(576, 423, "取消", 0, "HZK\\Hzk24h"); //取消键

        //打开时间选择窗口
        if (choose_date(345, 255, key))
        {
        	if (*key > today) //判断日期是否合法
    		{
        		Bar1(0, 0, 1024, 768, 0x9efc);
        		prt_hz16_size(420, 300, 2, 2, "输入数据有误", 0, "HZK\\Hzk16s");
        		delay(2000);
        		return 8;
    		}
    		else
    		return 0;
		}
            
        else    //取消选择时间，返回地点选择弹窗
            pop_window1(key, area);
    }
    else
        return 1; //回到管理员主界面
}

/*********************************
Function: modify_MainPage()
Description: 修改数据功能主页面
Calls:  pop_window2     //输入修改数据弹窗
        click_Data_Block  //点击数据框高亮
Called by: admin_modify()
Table Accessed: i.DAT   (选中地区的数据文件)
********************************/
void modify_MainPage(int *key, char *area)
{ //修改数据功能主页面

    int flg = 0, datKey = -1;
    int block_flg = 1;
    char filename[8];
    const char t[4] = {".DAT"};
    SAVEDAY *d = NULL;
    FILE *fp;

    filename[0] = *area;
    filename[1] = '\0';
    strcat(filename, t);
    filename[6] = '\0';
    
    if ((d = (SAVEDAY *)malloc(sizeof(SAVEDAY))) == NULL)
    {//为结构体分配内存

        delay(3000);
        exit(1); //分配空间不足，退出程序
    }
    if ((fp = fopen(filename, "rb+")) == NULL)
    {//打开文件
        put_asc16_size(185 + 150 + 80 + 80, 600, 2, 2, filename, 0x0000);
        delay(3000);
        exit(1); //打开失败，退出程序
    }
    
    //移至选中的日期
    fseek(fp, (*key) * sizeof(SAVEDAY), SEEK_SET);
    
    //将数据读进结构体
    fread(d, sizeof(SAVEDAY), 1, fp);
    
    //表格
    Line3(0, 98, 1024, 98, 2, 0);
    Line3(0, 198, 1024, 198, 2, 0);
    Line3(0, 298, 1024, 298, 2, 0);
    Line3(0, 398, 1024, 398, 2, 0);
    Line3(0, 498, 1024, 498, 2, 0);
    Line3(0, 598, 1024, 598, 2, 0);
    Line3(512, 0, 512, 598, 2, 0); //竖线
    Bar1(0, 666, 100, 768, 0x5b4f);
    Bar1(0, 668, 98, 768, 0x37dc);
    prt_hz24d(25, 706, "返回", 0, "HZK\\Hzk24h");
    Bar1(924, 666, 1024, 768, 0x5b4f);
    Bar1(926, 668, 1024, 768, 0x37dc);
    prt_hz24d(951, 706, "退出", 0, "HZK\\Hzk24h");
    Bar1(410, 666, 614, 768, 0x5b4f);
    Bar1(412, 668, 612, 768, 65523);
    prt_hz24d(462, 706, "修改数据", 0, "HZK\\Hzk24h");

    prt_hz24d(160, 50, "当日确诊", 0, "HZK\\Hzk24h");
    put_asc16_size(160, 50 + 100, 2, 2, d->infestor, 0x0000);
    prt_hz24d(160, 250, "当日治愈", 0, "HZK\\Hzk24h");
    put_asc16_size(160, 250 + 100, 2, 2, d->heal, 0x0000);
    prt_hz24d(160, 450, "当日死亡", 0, "HZK\\Hzk24h");
    put_asc16_size(160, 450 + 100, 2, 2, d->death, 0x0000);
    prt_hz24d(512 + 160, 50, "累计确诊", 0, "HZK\\Hzk24h");
    put_asc16_size(512 + 160, 50 + 100, 2, 2, d->allinf, 0x0000);
    prt_hz24d(512 + 160, 250, "累计治愈", 0, "HZK\\Hzk24h");
    put_asc16_size(512 + 160, 250 + 100, 2, 2, d->allhea, 0x0000);
    prt_hz24d(512 + 160, 450, "累计死亡", 0, "HZK\\Hzk24h");
    put_asc16_size(512 + 160, 450 + 100, 2, 2, d->alldea, 0x0000);
    
    Mouse_Init();
    while (1)
    {
        MouseShow(&mouse);
        if (flg == 0 && MouseIn(926, 668, 1024, 768)) //退出框反馈
        {
            MouseOff(&mouse);
            Bar1(926, 668, 1024, 768, 14137);
            prt_hz24d(951, 706, "退出", 0x0000, "HZK\\Hzk24h");
            MouseOn(mouse);
            flg = 1;
        }
        if (flg == 0 && MouseIn(0, 668, 98, 768)) //返回框反馈
        {
            MouseOff(&mouse);
            Bar1(0, 668, 98, 768, 14137);
            prt_hz24d(25, 706, "返回", 0x0000, "HZK\\Hzk24h");
            MouseOn(mouse);
            flg = 1;
        }
        if (flg == 0 && MouseIn(412, 668, 612, 768)) //修改数据键反馈
        {
            MouseOff(&mouse);
            Bar1(412, 668, 612, 768, 65184);
            prt_hz24d(462, 706, "修改数据", 0, "HZK\\Hzk24h");
            MouseOn(mouse);
            flg = 1;
        }
        else if (flg == 1 && !(MouseIn(926, 668, 1024, 768)) 
                           && !(MouseIn(0, 668, 98, 768)) 
                           && !(MouseIn(412, 668, 612, 768)))
        {
            MouseOff(&mouse);
            Bar1(926, 668, 1024, 768, 0x37dc);
            Bar1(0, 668, 98, 768, 0x37dc);
            Bar1(412, 668, 612, 768, 65523);
            prt_hz24d(462, 706, "修改数据", 0, "HZK\\Hzk24h");
            prt_hz24d(951, 706, "退出", 0x0000, "HZK\\Hzk24h");
            prt_hz24d(25, 706, "返回", 0x0000, "HZK\\Hzk24h");
            MouseOn(mouse);
            flg = 0;
        }
        
        //点击"修改数据"
        else if (MousePress(412, 668, 612, 768) && datKey != -1)
        {
            block_flg = 0;
            MouseOff(&mouse);
            pop_window2(datKey, d, area);
            
            Bar1(0, 0, 1024, 768, 0xa794);
            modify_MainPage(key, area); //重新打开界面
            MouseOn(mouse);

            block_flg = 1;
        }

        else if (MousePress(926, 668, 1024, 768)) //点击退出
        {
            CloseSVGA();
            delay(1000);
            exit(1);
        }

        else if (MousePress(0, 668, 98, 768)) //点击返回
        {
            if (fclose(fp) != 0) //关闭文件
            {
                printf("\nError in closing file .");
                delay(3000);
                exit(1);
            }
            free(d);
            return;
        }
        if (block_flg) //点击数据块反馈
            click_Data_Block(&datKey);
    }
}

/*********************************
Function: pop_window2()
Description: 输入修改数据弹窗
Calls:  modify_database //修改数据
Called by: modify_MainPage()
********************************/
void pop_window2(int datKey, SAVEDAY *d, char *area)
{ //输入数据弹窗
    char modify_number[5 + 1] = "\0";
    int flg = 0;

    Bar1(248, 168, 752, 482, 0);
    Bar1(250, 170, 750, 480, 0x8edf); //弹窗底色

    prt_hz24d(390, 200, "请输入修改后数据", 0, "HZK\\Hzk24h");
    Bar1(348, 413, 452, 457, 0x4b32);
    Bar1(350, 415, 450, 455, 0x8ff2);
    prt_hz24d(376, 423, "确认", 0, "HZK\\Hzk24h"); //确认键
    Bar1(548, 413, 652, 457, 0x4b32);
    Bar1(550, 415, 650, 455, 0x8ff2);
    prt_hz24d(576, 423, "取消", 0, "HZK\\Hzk24h"); //取消键

    Bar1(424, 258, 559, 292, 0);
    Bar1(426, 260, 557, 290, 0xffff); //输入框

    Mouse_Init();
    while (1)
    {
        MouseShow(&mouse);

        if (flg == 0 && MouseIn(350, 415, 450, 455)) //确认框反馈
        {
            MouseOff(&mouse);
            Bar2(350, 415, 450, 455, 800);
            prt_hz24d(376, 423, "确认", 0, "HZK\\Hzk24h"); //确认键
            MouseOn(mouse);
            flg = 1;
        }

        else if (flg == 0 && MouseIn(550, 415, 650, 455)) //取消框反馈
        {
            MouseOff(&mouse);
            Bar2(550, 415, 650, 455, 800);
            prt_hz24d(576, 423, "取消", 0, "HZK\\Hzk24h"); //取消
            MouseOn(mouse);
            flg = 1;
        }

        else if (flg == 1 && !(MouseIn(350, 415, 450, 455)) && !(MouseIn(550, 415, 650, 455)))
        {
            MouseOff(&mouse);
            Bar1(350, 415, 450, 455, 0x8ff2);
            prt_hz24d(376, 423, "确认", 0, "HZK\\Hzk24h"); //确认键
            Bar1(550, 415, 650, 455, 0x8ff2);
            prt_hz24d(576, 423, "取消", 0, "HZK\\Hzk24h"); //取消键
            MouseOn(mouse);
            
            flg = 0;
        }

        else if (MousePress(550, 415, 650, 455)) //点击取消键
        {
            return;
        }

        else if (MousePress(350, 415, 450, 455)) //点击确定键
        {
            modify_database(d, area);//将结构体的数据写入文件
            return;
        }

        if (MousePress(426, 260, 557, 290)) //点击输入框
        {
            Bar1(426, 260, 557, 290, 0xffff);
            MouseOff(&mouse);
            Getinfo(430, 260, modify_number, 5); //得到数据
            if (datKey == 1)
                strcpy(d->infestor, modify_number);
            if (datKey == 2)
                strcpy(d->heal, modify_number);
            if (datKey == 3)
                strcpy(d->death, modify_number);
            MouseOn(mouse);
        }
    }
}

/*********************************
Function: click_Data_Block()
Description: 点击高亮选择区域块
********************************/
void click_Data_Block(int *datKey)
{                                   //点击高亮选择区域块
                                    //点击数据块
    if (MousePress(0, 0, 510, 196)) //点击“当日确诊”
    {
        Unhighlight();
        Bar2(0, 0, 510, 196, 7327);
        *datKey = 1;
    }

    else if (MousePress(0, 200, 510, 396)) //点击“当日治愈”
    {
        Unhighlight();
        Bar2(0, 200, 510, 396, 7327);
        *datKey = 2;
    }

    else if (MousePress(0, 400, 510, 596)) //点击“当日死亡”
    {
        Unhighlight();
        Bar2(0, 400, 510, 596, 7327);
        *datKey = 3;
    }
}

/*********************************
Function: Unhighlight()
Description: 取消数据块高亮
********************************/
void Unhighlight(void)
{ //取消数据块高亮

    Bar2(0, 0, 510, 196, 0xa794);
    Bar2(0, 200, 510, 396, 0xa794);
    Bar2(0, 400, 510, 596, 0xa794);
    Bar2(514, 2, 1024, 196, 0xa794);
    Bar2(514, 200, 1024, 396, 0xa794);
    Bar2(514, 400, 1024, 596, 0xa794);
}

/*********************************
Function: mouse_feedback_main()
Description: 鼠标反馈
********************************/
void mouse_feedback_main(void)
{ //鼠标反馈
    int flg = 0;

    if (flg == 0 && MouseIn(926, 668, 1024, 768)) //退出框反馈
    {
        MouseOff(&mouse);
        Bar1(926, 668, 1024, 768, 14137);
        prt_hz24d(951, 706, "退出", 0x0000, "HZK\\Hzk24h");
        MouseOn(mouse);
        flg = 1;
    }
    if (flg == 0 && MouseIn(0, 668, 98, 768)) //返回框反馈
    {
        MouseOff(&mouse);
        Bar1(0, 668, 98, 768, 14137);
        prt_hz24d(25, 706, "返回", 0x0000, "HZK\\Hzk24h");
        MouseOn(mouse);
        flg = 1;
    }
    if (flg == 0 && MouseIn(412, 668, 612, 768)) //修改数据键反馈
    {
        MouseOff(&mouse);
        Bar1(412, 668, 612, 768, 65184);
        prt_hz24d(462, 706, "修改数据", 0, "HZK\\Hzk24h");
        MouseOn(mouse);
        flg = 1;
    }
    else if (flg == 1 && !(MouseIn(926, 668, 1024, 768)) 
                    && !(MouseIn(0, 668, 98, 768)) 
                    && !(MouseIn(412, 668, 612, 768)))
    {
        MouseOff(&mouse);
        Bar1(926, 668, 1024, 768, 0x37dc);
        Bar1(0, 668, 98, 768, 0x37dc);
        Bar1(412, 668, 612, 768, 65523);
        prt_hz24d(462, 706, "修改数据", 0, "HZK\\Hzk24h");
        prt_hz24d(951, 706, "退出", 0x0000, "HZK\\Hzk24h");
        prt_hz24d(25, 706, "返回", 0x0000, "HZK\\Hzk24h");
        MouseOn(mouse);
        flg = 0;
    }
}
