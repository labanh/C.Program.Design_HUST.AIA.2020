/*******************************************
FileName: login.c
Author:   韩海若
Date：    2020/10/28
Description: 该程序文件用于用户登录 
Others: 无
Function List: 
        login_user()   //用户登录函数 
********************************************/
#include "common.h"
#include "lgstate.h"
#include "login.h"

/*********************************
Function: login_user()
Description: 用户登录函数 
Calls:  wr_user        //将登录的账号写入文件
        judge_userfrozen //判断用户是否冻结
        right_password  //判断密码是否正确
Called by: main()
Table Accessed: userinfo.DAT
Table Updated:  usernow.DAT
Return:	3 -> 进入注册界面
		5 -> 登录成功
        4 -> 忘记密码
       -1 -> 退出
        0 —> 返回
********************************/
int login_user(void)
{
    //初始化
    int flag = 0;
    int state = 1;
    char username[12 + 1] = "\0";
    char key[12 + 1] = "\0";

    Bar1(0, 0, 1024, 768, 0x9eef);

    //退出返回键
    Bar1(900, 5, 1024, 55, 0x7bef); //退出框阴影
    Bar1(895, 0, 1019, 50, 59004);  //退出框实体
    prt_hz24(935, 12, "退出", 0x0000, "HZK\\Hzk24h");
    Bar1(5, 5, 127, 53, 0x7bef);
    Bar1(0, 0, 124, 50, 59004); //返回键
    prt_hz24(38, 13, "返回", 0x0000, "HZK\\Hzk24h");

    //标题
    prt_hz16_size(285, 150, 5, 5, "新型冠状病毒", 0xffe0, "HZK\\Hzk16s");
    prt_hz16_size(285, 250, 5, 5, "疫情通报系统", 0xffe0, "HZK\\Hzk16s");

    //账号密码框
    Bar1(374, 420, 659, 449, 0);
    Bar1(376, 422, 657, 447, 0xffff);
    Bar1(374, 484, 659, 513, 0);
    Bar1(376, 486, 657, 511, 0xffff);
    
    //登录注册键
    Bar1(405, 560, 473, 594, 0x7bef); //阴影
    Bar1(400, 555, 468, 589, 0xffff); //实体
    Bar1(545, 560, 613, 594, 0x7bef); //阴影
    Bar1(540, 555, 608, 589, 0xffff); //实体
    
    //忘记密码键
    Bar1(700, 484 + 76, 815, 513 + 76, 0x7bef); //阴影
    Bar1(695, 479 + 76, 810, 508 + 76, 0xffff); //实体

    prt_hz24d(307, 423, "账号", 0, "HZK\\Hzk24h");
    prt_hz24d(307, 487, "密码", 0, "HZK\\Hzk24h");
    prt_hz24d(410, 560, "登录", 0, "HZK\\Hzk24h");
    prt_hz24d(550, 560, "注册", 0, "HZK\\Hzk24h");
    prt_hz24d(705, 484 + 76, "忘记密码", 0, "HZK\\Hzk24h");
    
    Mouse_Init();
    while (1)
    {
        char key_0 = 0; //按下登录键后的状态
                        //1表示全部输入，2表示账号未输入，3表示密码未输入
                        
        char key_1 = 2; //按下登录键后的状态
                        //0表示已注册，1表示尚未注册
                        
        char key_2 = 0; //按下登录键后的状态，账户密码匹配
        char key_3 = 0; //0表示不正确，1表示正确
        
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
        if (flag == 0 && MouseIn(400, 555, 468, 589)) //登录键反馈
        {
            MouseOff(&mouse);
            Bar1(405, 560, 473, 594, 0x7bef);
            Bar1(400, 555, 468, 589, 57083);
            prt_hz24d(410, 560, "登录", 0, "HZK\\Hzk24h");
            MouseOn(mouse);
            flag = 1;
        }
        if (flag == 0 && MouseIn(540, 555, 608, 589)) //注册键反馈
        {
            MouseOff(&mouse);
            Bar1(545, 560, 613, 594, 0x7bef);
            Bar1(540, 555, 608, 589, 57083); //注册框
            prt_hz24d(550, 560, "注册", 0, "HZK\\Hzk24h");
            MouseOn(mouse);
            flag = 1;
        }
        if (flag == 0 && MouseIn(695, 479 + 76, 810, 508 + 76)) //忘记密码键反馈
        {
            MouseOff(&mouse);
            Bar1(700, 484 + 76, 815, 513 + 76, 0x7bef);
            Bar1(695, 479 + 76, 810, 508 + 76, 57083); //忘记密码框
            prt_hz24d(705, 484 + 76, "忘记密码", 0, "HZK\\Hzk24h");
            MouseOn(mouse);
            flag = 1;
        }
        else if (flag == 1 && !(MouseIn(895, 0, 1019, 50)) 
                            && !(MouseIn(540, 555, 608, 589)) 
                            && !(MouseIn(400, 555, 468, 589)) 
                            && !(MouseIn(0, 0, 124, 50)) 
                            && !(MouseIn(695, 479 + 76, 810, 508 + 76)))
        {
            MouseOff(&mouse);
            Bar1(895, 0, 1019, 50, 59004);
            Bar1(0, 0, 124, 50, 59004);
            Bar1(400, 555, 468, 589, 0xffff);
            Bar1(540, 555, 608, 589, 0xffff);
            Bar1(695, 479 + 76, 810, 508 + 76, 0xffff);
            prt_hz24d(935, 12, "退出", 0x0000, "HZK\\Hzk24h");
            prt_hz24d(38, 13, "返回", 0x0000, "HZK\\Hzk24h");
            prt_hz24d(410, 560, "登录", 0, "HZK\\Hzk24h");
            prt_hz24d(550, 560, "注册", 0, "HZK\\Hzk24h");
            prt_hz24d(705, 484 + 76, "忘记密码", 0, "HZK\\Hzk24h");
            MouseOn(mouse);
            flag = 0;
        }
        else if (MousePress(376, 422, 657, 447)) //点击账号框
        {
            prt_hz24d(700, 454, "（回车键结束输入）", 0, "HZK\\Hzk24h");
            MouseOff(&mouse);
            Bar1(376, 422, 657, 447, 0xffff);
            Getinfo(380, 424, username, 9); //得到账号
            MouseOn(mouse);
            Bar1(700, 454, 910, 454 + 24, 0x9eef);
        }
        else if (MousePress(376, 486, 657, 511)) //点击密码框
        {
            MouseOff(&mouse);
            Bar1(376, 486, 657, 511, 0xffff);
            Getcode(380, 488, key, 9); //得到密码
            MouseOn(mouse);
            Bar1(700, 486, 900, 486 + 28, 0x9eef);
        }
        else if (MousePress(540, 555, 608, 589)) //点击注册
        {
            return 3;
        }
        if (MousePress(400, 555, 468, 589)) //登录确认键
        {
            /*判断是否输入完全*/
            state = 1;
            key_0 = complete_login(username[0], key[0]);   //1表示全部输入
                                                            //2表示账号未输入
                                                            //3表示密码未输入
            {
                if (key_0 == 2)
                {
                    prt_hz24d(700, 410, "帐户未输入", 0, "HZK\\Hzk24h");
                    state = 0;
                }
                else if (key_0 == 3)
                {
                    prt_hz24d(700, 490, "密码未输入", 0, "HZK\\Hzk24h");
                    state = 0;
                }
            }
            
            /*判断登录账号是否已经注册*/
            if (key_0 == 1)
            {
                key_1 = judge_same_name(username); //0表示已注册，1表示尚未注册
                if (key_1 == 1)
                {
                    prt_hz24d(650, 660, "帐户未注册", 0, "HZK\\Hzk24h");
                    delay(1000);
                    Bar1(650, 660, 850, 660 + 35, 0x9eef);
                    state = 0;
                }
            }
            
            /*判断账号密码是否匹配*/
            if (key_1 == 0) //若已经注册，则看账户密码是否匹配
            {
                key_2 = right_password(username, key); //0表示不正确，1表示正确
                if (key_2 == 0)
                {
                    prt_hz24d(650, 660, "密码不正确", 0, "HZK\\Hzk24h");
                    delay(1000);
                    Bar1(650, 660, 850, 660 + 35, 0x9eef);
                    state = 0;
                }
            }
            if (key_2 == 1)
            {
                key_3 = judge_userfrozen(username);
                if (key_3 == 1)
                {
                    prt_hz24d(650, 660, "帐户已冻结", 0, "HZK\\Hzk24h");
                    delay(500);
                    Bar1(650, 660, 850, 660 + 35, 0x9eef);
                    state = 0;
                }
            }
            if (state == 1) //将登录的账号写入文件
            {
                wr_user(username);
                return 5; //进入系统
            }
        }
        if (MousePress(695, 479 + 76, 810, 508 + 76)) //点击忘记密码
        {
            return 4;
        }
        if (MousePress(895, 0, 1019, 50)) //点击退出
        {
            return -1;
        }
        else if (MousePress(0, 0, 124, 50)) //点击返回
        {
            return 0;
        }
    }
}