/*******************************************
FileName: visual.c
Author:   韩海若
Date：    2020/10/28
Description: 该程序文件用于实现疫情风险等级可视化
Others: 无
Function List: 
        int visual page()   //底层界面绘制
        void visual_basic() //可视化区域风险表示
        int risk_level()    //判断风险等级
********************************************/
#include "common.h"
#include "dayinfo.h"
#include "draw.h"
#include "visual.h"

/*****************************
Function: int visual_page(void)
Description: 可视化背景界面绘制
Calls:     void visual_basic()
Called by: main()
Table Accessed: areanow.DAT
Table Updated:  areanow.DAT
Input:  无
Output: 无 
Return: 1   -> 返回
        6   -> 通报界面
        7   -> 查询界面
       12   -> 注销
******************************/
int visual_page(void)
{
    int flg = 0;
    int choose = -1;
    Bar1(0, 0, 1024, 768, 0x9eef); //主窗口

    //退出键
    Bar1(900, 5, 1024, 55, 0x7bef); //退出框阴影
    Bar1(895, 0, 1019, 50, 59004);  //退出框实体
    prt_hz24(935, 12, "退出", 0x0000, "HZK\\Hzk24k");

    //返回键
    Bar1(5, 5, 129, 55, 0x7bef); //0x7bef灰色
    Bar1(0, 0, 124, 50, 59004);
    prt_hz24(38, 13, "返回", 0x0000, "HZK\\Hzk24k");

    //跳转选择控制台
    Bar1(282, 5, 766, 55, 0x7bef); //灰色阴影
    Bar1(277, 0, 761, 50, 0x0000); //黑色底色
    Bar1(280, 3, 438, 47, 63422);  //注销
    Bar1(441, 3, 600, 47, 63422);  //通报
    Bar1(603, 3, 758, 47, 63422);  //查询

    //标题
    prt_hz24(335, 13, "排行", 0x0000, "HZK\\Hzk24k");
    prt_hz24(470, 13, "疫情通报", 0x0000, "HZK\\Hzk24k");
    prt_hz24(630, 13, "数据查询", 0x0000, "HZK\\Hzk24k");
    prt_hz16_size(280, 100, 5, 5, "风险等级地图", 0xffe0, "HZK\\Hzk16s");

    visual_basic(); //绘制区域基本框架

    Mouse_Init();
    while (1)
    {
        MouseShow(&mouse);
        if (flg == 0 && MouseIn(895, 0, 1019, 50)) //退出框反馈
        {
            MouseOff(&mouse);
            Bar1(895, 0, 1019, 50, 56603);
            prt_hz24d(935, 12, "退出", 0, "HZK\\Hzk24k");
            MouseOn(mouse);
            flg = 1;
        }
        else if (flg == 0 && MouseIn(0, 0, 124, 50)) //返回框反馈
        {
            MouseOff(&mouse);
            Bar1(0, 0, 124, 50, 56603);
            prt_hz24d(38, 13, "返回", 0, "HZK\\Hzk24k");
            MouseOn(mouse);
            flg = 1;
        }
        else if (flg == 0 && MouseIn(280, 3, 438, 47)) //注销框反馈
        {
            MouseOff(&mouse);
            Bar2(280, 3, 438, 47, 7327);
            MouseOn(mouse);
            flg = 1;
        }
        else if (flg == 0 && MouseIn(441, 3, 600, 47)) //通报框反馈
        {
            MouseOff(&mouse);
            Bar2(441, 3, 600, 47, 7327);
            MouseOn(mouse);
            flg = 1;
        }
        if (flg == 0 && MouseIn(603, 3, 758, 47)) //查询框反馈
        {
            MouseOff(&mouse);
            Bar2(603, 3, 758, 47, 7327);
            MouseOn(mouse);
            flg = 1;
        }
        else if (flg == 1 && MouseIn(277, 0, 761, 50) 
                            && !(MouseIn(280, 3, 438, 47)) 
                            && !(MouseIn(441, 3, 600, 47)) 
                            && !(MouseIn(603, 3, 758, 47)) 
                            && !(MouseIn(805, 140, 865, 180)))
        {
            MouseOff(&mouse);
            Bar2(280, 3, 438, 47, 63422); //注销
            Bar2(441, 3, 600, 47, 63422); //通报
            Bar2(603, 3, 758, 47, 63422); //查询
            MouseOn(mouse);
            flg = 0;
        }
        else if (flg == 1 && !(MouseIn(277, 0, 761, 50)) 
                           && !(MouseIn(805, 140, 865, 180)) 
                           && !(MouseIn(0, 0, 124, 50)) 
                           && !(MouseIn(895, 0, 1019, 50)))
        {
            //还原界面
            MouseOff(&mouse);
            Bar2(280, 3, 438, 47, 63422);     //注销
            Bar2(441, 3, 600, 47, 63422);     //通报
            Bar2(603, 3, 758, 47, 63422);     //查询
            Bar1(895, 0, 1019, 50, 59004);    //退出
            Bar1(0, 0, 124, 50, 59004);       //返回
            prt_hz24(38, 13, "返回", 0x0000, "HZK\\Hzk24k");
            prt_hz24(935, 12, "退出", 0x0000, "HZK\\Hzk24k");
            MouseOn(mouse);
            flg = 0;
        }
        if (MousePress(895, 0, 1019, 50)) //点击退出
        {
            CloseSVGA();
            delay(1000);
            exit(1);
        }
        else if (MousePress(0, 0, 124, 50)) //点击返回
        {
            return 1;
        }
        else if (MousePress(280, 3, 438, 47)) //点击注销
        {
            return 12;
        }
        else if (MousePress(603, 3, 758, 47)) //点击查询
        {
            if (choose == -1)
            {
                prt_hz24(810, 150, "您未选中区域", 0x0000, "HZK\\Hzk24k");
                delay(1000);
                Bar1(810, 150, 1000, 200, 0x9eef);
            }
            else
            {
                return 7;
            }
        }
        else if (MousePress(441, 3, 600, 47)) //点击通报
        {
            if (choose == 0)
            {
                return 6;
            }
            else if (choose == 1)
            {
                Bar1(810, 150, 1000, 200, 0x9eef);
                prt_hz24(810, 150, "该区域无法通报", 0x0000, "HZK\\Hzk24k");
                delay(1000);
                Bar1(810, 150, 1000, 200, 0x9eef);
            }
            else if (choose == -1)
            {
                prt_hz24(810, 150, "您未选中区域", 0x0000, "HZK\\Hzk24k");
                delay(1000);
                Bar1(810, 150, 1000, 200, 0x9eef);
            }
        }
        /******************
        判断条件由小区->社区->区->市
        优先级由高到低
        可避免重叠部分的错误
        ******************/
        if (MousePress(105, 320, 245, 480)) //益民小区
        {
            Bar1(805, 140, 805 + 200, 140 + 45, 0x9eef);
            prt_hz24(810, 150, "已选中益民小区", 0x0000, "HZK\\Hzk24k");
            wr_area(0);
            choose = 0;
            continue;
        }
        else if (MousePress(280, 320, 410, 475)) //北门小区
        {
            Bar1(805, 140, 805 + 200, 140 + 45, 0x9eef);
            prt_hz24(810, 150, "已选中北门小区", 0x0000, "HZK\\Hzk24k");
            wr_area(1);
            choose = 0;
            continue;
        }
        else if (MousePress(105, 560, 245, 710)) //光明小区
        {
            Bar1(805, 140, 805 + 200, 140 + 45, 0x9eef);
            prt_hz24(810, 150, "已选中光明小区", 0x0000, "HZK\\Hzk24k");
            wr_area(2);
            choose = 0;
            continue;
        }
        else if (MousePress(280, 560, 410, 710)) //桂园小区
        {
            Bar1(805, 140, 805 + 200, 140 + 45, 0x9eef);
            prt_hz24(810, 150, "已选中桂园小区", 0x0000, "HZK\\Hzk24k");
            wr_area(3);
            choose = 0;
            continue;
        }
        else if (MousePress(555, 320, 695, 480)) //南池小区
        {
            Bar1(805, 140, 805 + 200, 140 + 45, 0x9eef);
            prt_hz24(810, 150, "已选中南池小区", 0x0000, "HZK\\Hzk24k");
            wr_area(4);
            choose = 0;
            continue;
        }
        else if (MousePress(740, 320, 920, 480)) //丽景小区
        {
            Bar1(805, 140, 805 + 200, 140 + 45, 0x9eef);
            prt_hz24(810, 150, "已选中丽景小区", 0x0000, "HZK\\Hzk24k");
            wr_area(5);
            choose = 0;
            continue;
        }
        else if (MousePress(555, 560, 695, 710)) //风韵荷都
        {
            Bar1(805, 140, 805 + 200, 140 + 45, 0x9eef);
            prt_hz24(810, 150, "已选中风韵荷都", 0x0000, "HZK\\Hzk24k");
            wr_area(6);
            choose = 0;
            continue;
        }
        else if (MousePress(740, 560, 900, 710)) //恒大名都
        {
            Bar1(805, 140, 805 + 200, 140 + 45, 0x9eef);
            prt_hz24(810, 150, "已选中恒大名都", 0x0000, "HZK\\Hzk24k");
            wr_area(7);
            choose = 0;
            continue;
        }
        else if (MousePress(90, 290, 420, 500) 
                    && !MousePress(105, 320, 245, 480) 
                    && !MousePress(280, 320, 410, 475)) //古槐社区
        {
            Bar1(805, 140, 805 + 200, 140 + 45, 0x9eef);
            prt_hz24(810, 150, "已选中古槐社区", 0x0000, "HZK\\Hzk24k");
            wr_area(8);
            choose = 1;
            continue;
        }
        else if (MousePress(90, 530, 420, 720) 
                    && !MousePress(105, 560, 245, 710) 
                    && !MousePress(280, 560, 410, 710)) //仙营社区
        {
            Bar1(805, 140, 805 + 200, 140 + 45, 0x9eef);
            prt_hz24(810, 150, "已选中仙营社区", 0x0000, "HZK\\Hzk24k");
            wr_area(9);
            choose = 1;
            continue;
        }
        else if (MousePress(540, 290, 930, 500) 
                    && !MousePress(555, 320, 695, 480) 
                    && !MousePress(740, 320, 920, 480)) //南池社区
        {
            Bar1(805, 140, 805 + 200, 140 + 45, 0x9eef);
            prt_hz24(810, 150, "已选中南池社区", 0x0000, "HZK\\Hzk24k");
            wr_area(10);
            choose = 1;
            continue;
        }
        else if (MousePress(540, 530, 930, 720) 
                    && !MousePress(555, 560, 695, 710) 
                    && !MousePress(740, 560, 900, 710)) //北湖社区
        {
            Bar1(805, 140, 805 + 200, 140 + 45, 0x9eef);
            prt_hz24(810, 150, "已选中北湖社区", 0x0000, "HZK\\Hzk24k");
            wr_area(11);
            choose = 1;
            continue;
        }
        else if (MousePress(50, 260, 460, 740) 
                    && !MousePress(90, 290, 420, 500) 
                    && !MousePress(90, 530, 420, 720)) //任城区
        {
            Bar1(805, 140, 805 + 200, 140 + 45, 0x9eef);
            prt_hz24(810, 150, "已选中任城区", 0x0000, "HZK\\Hzk24k");
            wr_area(12);
            choose = 1;
            continue;
        }
        else if (MousePress(495, 260, 960, 740) 
                    && !MousePress(540, 290, 930, 500) 
                    && !MousePress(540, 530, 930, 720)) //高新区
        {
            Bar1(805, 140, 805 + 200, 140 + 45, 0x9eef);
            prt_hz24(810, 150, "已选中高新区", 0x0000, "HZK\\Hzk24k");
            wr_area(13);
            choose = 1;
            continue;
        }
        else if (MousePress(2, 240, 1022, 766) 
                    && !MousePress(495, 260, 960, 740) 
                    && !MousePress(50, 260, 460, 740)) //市
        {
            Bar1(805, 140, 805 + 200, 140 + 45, 0x9eef);
            prt_hz24(810, 150, "已选中市", 0x0000, "HZK\\Hzk24k");
            wr_area(14);
            choose = 1;
            continue;
        }
    }
}
/*****************************
Function: void visual_basic(void)
Description: 可视化背景界面绘制
Calls:     risk_level()
           draw_floor1()
Called by: visual_page()
Input:  无
Output: 无 
Return: 1   -> 返回
        6   -> 通报界面
        7   -> 查询界面
       12   -> 注销
******************************/
void visual_basic(void)
{
    //把每个地区的数据存在数组里
    int data[15] = {0};
    int temp1, temp2, temp3, temp4 = 10;
    int i = 0;
    for (i = 14; i >= 0; i--)
    {
        countareacases(i, &temp4, &temp1, &temp3, &temp2);
        data[14 - i] = temp2;
    }

    Bar1(0, 237, 1024, 768, 0x0000);              //黑边框，主体范围
    Bar1(2, 240, 1022, 766, risk_level(data[0])); //最外围(市级)(2,240,1022,766)

    Bar1(47, 257, 463, 743, 0x0000);
    Bar1(50, 260, 460, 740, risk_level(data[2])); //左侧任城区 50,260,460,740

    //画两个区之间的马路
    Bar1(465, 240, 485, 768, 0);
    for (i = 0; i < 20; i++)
    {
        Line3(475, 242 + 25 * i, 475, 242 + 25 * i + 10, 2, 65184);
    }

    Bar1(492, 257, 963, 743, 0x0000);
    Bar1(495, 260, 960, 740, risk_level(data[1])); //右侧高新区 495,260,960,740

    Bar1(87, 287, 423, 503, 0x0000);
    Bar1(90, 290, 420, 500, risk_level(data[6])); //左侧古槐社区 90,290,420,500

    Bar1(87, 527, 423, 723, 0x0000);
    Bar1(90, 530, 420, 720, risk_level(data[5])); //左侧仙营社区 90,530,420,720

    //画上下社区之间的马路
    Bar1(0, 505, 1024, 525, 0);
    for (i = 0; i < 46; i++)
    {
        Line3(3 + 25 * i, 515, 3 + 25 * i + 10, 515, 2, 65184);
    }

    Bar1(537, 287, 933, 503, 0x0000);
    Bar1(540, 290, 930, 500, risk_level(data[4]));  //右侧南池社区 540,290,930,500

    Bar1(537, 527, 933, 723, 0x0000);
    Bar1(540, 530, 930, 720, risk_level(data[3]));  //右侧北湖社区 540,530,930,720

    Bar1(102, 317, 248, 483, 0x0000);
    Bar1(105, 320, 245, 480, risk_level(data[14])); //左侧益民小区 105,320,245,480
    draw_floor1(120, 360);

    Bar1(277, 317, 413, 478, 0x0000);
    Bar1(280, 320, 410, 475, risk_level(data[13])); //左侧北门小区 280,320,410,475
    draw_floor2(310, 360);

    //画左侧小区之间的马路
    Bar1(250, 240, 270, 766, 0);
    for (i = 0; i < 46; i++)
    {
        Line3(260, 245 + 25 * i, 260, 245 + 25 * i + 10, 2, 65184);
    }

    Bar1(102, 557, 248, 713, 0x0000);
    Bar1(105, 560, 245, 710, risk_level(data[12])); //左侧光明小区 105,560,245,710
    draw_floor3(140, 600);

    Bar1(277, 557, 413, 713, 0x0000);
    Bar1(280, 560, 410, 710, risk_level(data[11])); //左侧桂园小区 280,560,410,710
    draw_floor1(285, 600);

    Bar1(552, 317, 698, 483, 0x0000);
    Bar1(555, 320, 695, 480, risk_level(data[10])); //右侧南池小区 555,320,695,480
    draw_floor3(590, 360);

    Bar1(737, 317, 903, 483, 0x0000);
    Bar1(740, 320, 900, 480, risk_level(data[9])); //右侧丽景小区 740,320,920,480
    draw_floor1(760, 360);

    //画右侧小区之间的马路
    Bar1(710, 240, 730, 766, 0);
    for (i = 0; i < 46; i++)
    {
        Line3(720, 245 + 25 * i, 720, 245 + 25 * i + 10, 2, 65184);
    }

    Bar1(552, 557, 698, 713, 0x0000);
    Bar1(555, 560, 695, 710, risk_level(data[8])); //右侧风韵荷都 555,560,695,710
    draw_floor2(590, 600);

    Bar1(737, 557, 903, 713, 0x0000);
    Bar1(740, 560, 900, 710, risk_level(data[7])); //右侧恒大名都 740,560,900,710
    draw_floor3(780, 600);
}
/********************
Function: int risk_level(int cases)
Description: 判断风险等级函数
Calls:  无
Called by: visual_basic()
Input:  int cases 为对应地区确诊人数
Output: 无 
Return: 不同风险对应的颜色RGB值
Others:
    *高风险*地区的分级标准为累计确诊病例    *超过2例*
    *中高风险*地区的分级标准为累计确诊病例  *2例*
    *中风险*地区的分级标准为累计确诊病例    *1例*
    *低风险*地区的分级标准为累计确诊病例    *无病例*
**********************/
int risk_level(int cases)
{
    if (cases == 0)
    {
        return 32736; //低风险绿色
    }
    else if (cases == 1)
    {
        return 65184; //中风险黄色
    }
    else if (cases == 2)
    {
        return 64800; //中高风险橙色
    }
    else if (cases > 2)
    {
        return 64526; //高风险红色
    }
    return 0;
}
