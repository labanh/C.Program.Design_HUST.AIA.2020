/*************************
该文件用于新用户注册
**************************/
#include "common.h"
#include "lgstate.h"
#include "register.h"

int register_user(void) //注册界面
{
    int flag = 0; //反馈标志变量
    char state = 1;
    char username[12 + 1] = {'\0'}; //username
    char key1[12 + 1] = {'\0'};     //password
    char key2[12 + 1] = {'\0'};     //ensure password
    char id[18 + 1] = {'\0'};       //IDnumber
    Bar1(0, 0, 1024, 768, 0x9eef);  //重设界面

    //标题
    prt_hz16_size(285, 150, 5, 5, "新型冠状病毒", 0xffe0, "HZK\\Hzk16s");
    prt_hz16_size(285, 250, 5, 5, "疫情通报系统", 0xffe0, "HZK\\Hzk16s");

    /*交互界面*/
    //退出键
    Bar1(900, 5, 1024, 55, 0x7bef); //退出框阴影
    Bar1(895, 0, 1019, 50, 59004);  //退出框实体
    prt_hz24(935, 12, "退出", 0x0000, "HZK\\Hzk24h");

    //返回键
    Bar1(5, 5, 127, 53, 0x7bef); //0x7bef灰色
    Bar1(0, 0, 124, 50, 59004);
    prt_hz24(38, 13, "返回", 0x0000, "HZK\\Hzk24h");

    Bar1(374, 423, 661, 451, 0);
    Bar1(376, 425, 659, 449, 0xffff); //账号框

    Bar1(374, 487, 661, 515, 0);
    Bar1(376, 489, 659, 513, 0xffff); //密码框

    Bar1(374, 551, 661, 579, 0);
    Bar1(376, 553, 659, 577, 0xffff); //确认密码框

    Bar1(374, 551 + 64, 661, 579 + 64, 0);
    Bar1(376, 553 + 64, 659, 577 + 64, 0xffff); //身份证框

    Bar1(361, 614 + 100, 429, 648 + 100, 0x7bef);
    Bar1(356, 609 + 100, 424, 643 + 100, 0xffff); //确认框

    Bar1(561, 614 + 100, 629, 648 + 100, 0x7bef);
    Bar1(556, 609 + 100, 624, 643 + 100, 0xffff); //取消框

    prt_hz24(307, 425, "账号：", 0, "HZK\\Hzk24h");
    prt_hz24(307, 489, "密码：", 0, "HZK\\Hzk24h");
    prt_hz24(259, 553, "确认密码：", 0, "HZK\\Hzk24h");
    prt_hz24(259, 553 + 64, "身份证：", 0, "HZK\\Hzk24h");
    prt_hz24(366, 614 + 100, "确认", 0, "HZK\\Hzk24h");
    prt_hz24(566, 614 + 100, "取消", 0, "HZK\\Hzk24h");

    Mouse_Init(); //鼠标初始化
    while (1)
    {
        char key_0 = 0;           //按下注册键后的状态，成功1，账号未输入2，密码未输入3，密码未确认4，身份证未输入5
        char key_1 = 0;           //按下注册键后的状态，账号，重名0，未重名1
        char key_2 = 0;           //按下注册键后的状态，密码格式，0表示长度不合乎要求，1表示合乎要求
        char key_3 = 0;           //按下注册键后的状态，两次密码，0表示不相同，1表示相同
        char key_4 = 0;           //按下注册键后的状态，身份证号码格式
                                  //0表示长度不合乎要求，1表示内容不合乎要求，2表示合乎要求
        
        MouseShow(&mouse);        //鼠标循环
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
        if (flag == 0 && MouseIn(366, 614 + 100, 414, 638 + 100)) //确认框反馈
        {
            MouseOff(&mouse);
            Bar1(356, 609 + 100, 424, 643 + 100, 0xeeee);
            prt_hz24d(366, 614 + 100, "确认", 0, "HZK\\Hzk24h");
            MouseOn(mouse);
            flag = 1;
        }
        if (flag == 0 && MouseIn(566, 614 + 100, 614, 638 + 100)) //取消框反馈
        {
            MouseOff(&mouse);
            Bar1(556, 609 + 100, 624, 643 + 100, 0xeeee);
            prt_hz24d(566, 614 + 100, "取消", 0, "HZK\\Hzk24h");
            MouseOn(mouse);
            flag = 1;
        }

        else if (flag == 1 && !(MouseIn(900, 0, 1024, 50)) && !(MouseIn(0, 0, 124, 50)) && !(MouseIn(366, 614 + 100, 414, 638 + 100)) && !(MouseIn(566, 614 + 100, 614, 638 + 100)))
        {
            MouseOff(&mouse);
            Bar1(895, 0, 1019, 50, 59004);
            Bar1(356, 609 + 100, 424, 643 + 100, 0xffff);
            Bar1(556, 609 + 100, 624, 643 + 100, 0xffff);
            Bar1(0, 0, 124, 50, 59004);
            prt_hz24d(38, 13, "返回", 0, "HZK\\Hzk24h");
            prt_hz24d(935, 12, "退出", 0, "HZK\\Hzk24h");
            prt_hz24d(366, 614 + 100, "确认", 0, "HZK\\Hzk24h");
            prt_hz24d(566, 614 + 100, "取消", 0, "HZK\\Hzk24h");
            MouseOn(mouse);
            flag = 0;
        }
        else if (MousePress(378, 425, 659, 449)) //输入账号
        {
            prt_hz24d(700, 454, "（回车键结束输入）", 0, "HZK\\Hzk24h");
            MouseOff(&mouse);
            Bar1(378, 425, 659, 449, 0xffff);
            Getinfo(380, 427, username, 12); //gets.h
            MouseOn(mouse);
            Bar1(670, 425, 670 + 200, 425 + 28, 0x9eef);
        }
        else if (MousePress(378, 489, 659, 513)) //输入密码
        {
            MouseOff(&mouse);
            Bar1(378, 489, 659, 513, 0xffff);
            Getcode(380, 491, key1, 12);
            MouseOn(mouse);
            Bar1(670, 425 + 64, 670 + 200, 425 + 28 + 64, 0x9eef);
        }
        else if (MousePress(378, 553, 659, 577)) //重新输入密码
        {
            MouseOff(&mouse);
            Bar1(378, 553, 659, 577, 0xffff);
            Getcode(380, 555, key2, 12);
            MouseOn(mouse);
            Bar1(670, 425 + 64 * 2, 670 + 200, 425 + 28 + 64 * 2, 0x9eef);
        }
        else if (MousePress(378, 553 + 64, 659, 577 + 64)) //输入身份证
        {
            MouseOff(&mouse);
            Bar1(378, 553 + 64, 659, 577 + 64, 0xffff);
            Getinfo(380, 555 + 64, id, 18);
            MouseOn(mouse);
            Bar1(670, 425 + 64 * 3, 670 + 200, 425 + 28 + 64 * 3, 0x9eef);
        }
        if (MousePress(366, 614 + 100, 414, 638 + 100)) //点击确认键
        {
            state = 1;
            /*判断是否输入完全*/
            key_0 = complete_register(username[0], key1[0], key2[0], id[0]); //成功1，账号未输入2，密码未输入3，密码未确认4，身份证未输入5
            switch (key_0)
            {
            case 1:
                break;
            case 2:
                prt_hz24(670, 425, "账号未输入", 0, "HZK\\Hzk24h");
                state = 0;
                break;
            case 3:
                prt_hz24(670, 489, "密码未输入", 0, "HZK\\Hzk24h");
                state = 0;
                break;
            case 4:
                prt_hz24(670, 553, "请确认密码", 0, "HZK\\Hzk24h");
                state = 0;
                break;
            case 5:
                prt_hz24(670, 553 + 64, "身份证号码未输入", 0, "HZK\\Hzk24h");
                state = 0;
                break;
            default:
                prt_hz24(670, 553, "错误", 0, "HZK\\Hzk24h");
                break;
            }
            /*判断是否重名*/
            if (key_0 == 1)
            {
                key_1 = judge_same_name(username); //0表示重名，1表示不重名
                if (key_1 == 0)
                {
                    prt_hz24(670, 553, "用户名已被使用", 0, "HZK\\Hzk24h");
                    state = 0;
                }
            }
            /*判断密码格式*/
            if (key_1 == 1)
            {
                key_2 = judge_password(key1); //0表示长度不合乎要求，1表示合乎要求
                if (key_2 == 0)
                {
                    prt_hz24(670, 553, "密码过短", 0, "HZK\\Hzk24h");
                    state = 0;
                }
            }
            /*判断两次密码是否相同*/
            if (key_2 == 1)
            {
                key_3 = compare_password(key1, key2); //0表示不相同，1表示相同
                if (key_3 == 0)
                {
                    prt_hz24(670, 553, "密码不一致", 0, "HZK\\Hzk24h");
                    state = 0;
                }
            }
            /*判断身份证号码格式*/
            if (key_3 == 1)
            {
                key_4 = judge_IDnumber(id); //0表示长度不合乎要求，1表示内容不合乎要求，2表示合乎要求
                if (key_4 == 0)
                {
                    prt_hz24(670, 553 + 64, "长度有误", 0, "HZK\\Hzk24h");
                    state = 0;
                }
                else if (key_4 == 1)
                {
                    prt_hz24(670, 553 + 64, "内容有误", 0, "HZK\\Hzk24h");
                    state = 0;
                }
            }

            if (state == 1)
            {
                wr_user_inf(username, key1, id);
                prt_hz24(670, 553, "注册成功", 0, "HZK\\Hzk24h");
                delay(1000);
                return 1;
            }
        }

        if (MousePress(566, 614, 614, 638)) //点击取消键
        {
            return 1;
        }
        if (MousePress(900, 0, 1024, 50)) //点击退出
        {
            return -1;
        }
        if (MousePress(0, 0, 124, 50)) //点击返回
        {
            return 1;
        }
    }
}
