/**********************************************
FileName: admin.c
Author:   韩海若
Date：    2020/10/29
Description: 该文件主要用于管理员登录注册功能 
Function List: 
        login_user()   //用户登录函数 
***********************************************/
#include "admin.h"
#include "common.h"
#include "lgstate.h"

/*********************************
Function: login_admin()
Description: 管理员登录函数 
Called by: main()
Return:	8 -> 进入管理员主界面
        0 —> 返回欢迎界面
********************************/
int login_admin(void)
{
    int flag = 0, key = 0; //flag 鼠标反馈 key  判断密码是否正确
    char code[20] = "";     //储存密码并进行比对

    Bar1(0, 0, 1024, 768, 0x9eef); //初始化界面

    //绘制退出返回键
    Bar1(900, 5, 1024, 55, 0x7bef);
    Bar1(895, 0, 1019, 50, 59004);
    prt_hz24(935, 12, "退出", 0x0000, "HZK\\Hzk24h");
    Bar1(5, 5, 127, 53, 0x7bef);
    Bar1(0, 0, 124, 50, 59004);
    prt_hz24(38, 13, "返回", 0x0000, "HZK\\Hzk24h");

    //标题
    prt_hz16_size(285, 150, 5, 5, "新型冠状病毒", 0xffe0, "HZK\\Hzk16s");
    prt_hz16_size(285, 250, 5, 5, "疫情通报系统", 0xffe0, "HZK\\Hzk16s");
    prt_hz16_size(404, 450, 2, 2, "输入管理员密码", 0x5091, "HZK\\Hzk16s");

    //密码框
    Bar1(382, 500, 682, 530, 0);
    Bar1(384, 502, 680, 528, 0xffff);

    //确认框
    Bar1(477, 585, 577, 635, 0);
    Bar1(472, 580, 572, 630, 0xffff);
    prt_hz24d(320, 500, "密码：", 0, "HZK\\Hzk24h");
    prt_hz24d(497, 592, "确认", 0, "HZK\\Hzk24h");

    Mouse_Init();
    while (1)
    {
        MouseShow(&mouse);
        if (flag == 0 && MouseIn(895, 0, 1019, 50)) //退出框反馈
        {
            MouseOff(&mouse);
            Bar1(895, 0, 1019, 50, 56603);
            prt_hz24d(935, 12, "退出", 0x0000, "HZK\\Hzk24h");
            MouseOn(mouse);
            flag = 1;
        }
        if (flag == 0 && MouseIn(0, 0, 124, 50)) //返回框反馈
        {
            MouseOff(&mouse);
            Bar1(0, 0, 124, 50, 56603);
            prt_hz24d(38, 13, "返回", 0x0000, "HZK\\Hzk24h");
            MouseOn(mouse);
            flag = 1;
        }
        if (flag == 0 && MouseIn(472, 580, 572, 630)) //确认键反馈
        {
            MouseOff(&mouse);
            Bar1(472, 580, 572, 630, 57083);
            prt_hz24d(497, 592, "确认", 0, "HZK\\Hzk24h");
            MouseOn(mouse);
            flag = 1;
        }

        else if (flag == 1 && !(MouseIn(0, 0, 124, 50)) 
                            && !(MouseIn(895, 0, 1019, 50)) 
                            && !(MouseIn(472, 580, 572, 630)))
        {
            MouseOff(&mouse);
            Bar1(895, 0, 1019, 50, 59004);
            Bar1(0, 0, 124, 50, 59004);
            Bar1(472, 580, 572, 630, 0xffff);

            prt_hz24d(497, 592, "确认", 0, "HZK\\Hzk24h");
            prt_hz24d(38, 13, "返回", 0x0000, "HZK\\Hzk24h");
            prt_hz24d(935, 12, "退出", 0x0000, "HZK\\Hzk24h");

            MouseOn(mouse);
            flag = 0;
        }
        else if (MousePress(384, 502, 680, 528)) //点击密码输入框
        {
            MouseOff(&mouse);
            Getcode(384, 502, code, 10);
            MouseOn(mouse);
        }
        if (MousePress(472, 580, 572, 630)) //点击确认键
        {
            if (code[0] == '\0')
            {
                prt_hz24d(450, 664, "请输入密码！", 0, "HZK\\Hzk24h");
                delay(1000);
                Bar1(450, 664, 660, 688, 0x9eef);
            }
            else
            {
                key = admin_password(code);
                if (key == 1)
                {
                    prt_hz24d(480, 664, "登录成功！", 0, "HZK\\Hzk24h");
                    delay(1000);
                    return 8; //进入管理员主菜单界面
                }
                if (key != 1)
                {
                    prt_hz24d(450, 664, "密码错误！", 0, "HZK\\Hzk24h");
                    delay(1000);
                    Bar1(450, 664, 560, 688, 0x9eef);
                }
            }
        }
        if (MousePress(0, 0, 150, 55)) //点击返回
        {
            return 0;
        }
        else if (MousePress(874, 0, 1024, 55)) //点击退出
        {
            CloseSVGA();
            delay(1000);
            exit(1);
        }
    }
}