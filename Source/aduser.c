/*******************************************
FileName: aduser.c
Author:   刘子恒 
Date：    2020/10/26
Description: 该文件主要用于用户管理功能 
Others: 无
Function List: 
        aduser();       用户管理主函数 
        aduser_menu();  用户管理主界面 
        aduserdraw();   界面翻页函数 
 		aduserbutton(); 绘制按钮 
 		user_ice();		冻结用户 
 		no_iced();      解冻用户 
 		button1();	    按钮反馈 
 		button3();	    按钮反馈 
 		put_User();	    打印用户数据 
 		put_run();      打印用户是否可通报 
********************************************/
#include "aduser.h"
#include "common.h"
#include "lgstate.h"
/*****************************
Function: int admin_menu(void)
Description: 选择操作菜单
Calls:     aduser_menu() 
           user_ice()
           no_iced()
Called by: main()
Table Accessed: 无
Table Updated:  无
Input:  无
Output: 无 
Return: 8  -> 返回管理员页面 
******************************/
int aduser(void)
{
    int choose = 0;
    int choose1 = 0;
    while (choose != -1)
    {
        choose = aduser_menu(&choose1);
        switch (choose)
        {
        case 1:
            user_ice(); //冻结用户函数
            break;
        case 3:
            no_iced(); //解冻用户函数
            break;
        case -1:
            return 8;
            //返回
        case -2:
            CloseSVGA(); //退出系统
            delay(1000);
            exit(0);
        case -3:
            break; //控制上一页和下一页
        }
    }
}
/*****************************
Function: int aduser_menu(int *choose1)
Description: 用户管理主界面
Calls:     aduserdraw()
           aduserbutton()
Called by: admin_menu()
Table Accessed: UserInfo.dat
Table Updated:  无
Input:  *choose1
Output: 无 
Return: 1  -> 冻结用户 
		3  -> 解冻用户 
		-1  -> 返回管理员页面 
		-2  -> 退出程序 
		-3  -> 控制翻页 
******************************/
int aduser_menu(int *choose1)
{
    int choose = 0;
    int flag = 0;
    int long q = 0;
    int m = 0;
    int n = 0;
    int u = 0;
    FILE *fp = NULL;
    if ((fp = fopen("UserInfo.dat", "rb+")) == NULL) //读取文件
    {
        CloseSVGA();
        printf("Unable to open UserInfo.dat!\n");
        getch();
        exit(0);
    }
    fseek(fp, 0, 2);
    q = ftell(fp);
    m = q / sizeof(USER); //m为总用户数量
    n = m / 5;            //n为页数
    u = m % 5;            //u为最后一页的用户数量
    if (u != 0)
    {
        n = n + 1;
    }
    fclose(fp);
    aduserdraw(choose1); //绘制页面
    Mouse_Init();
    while (choose != -1)
    {
        MouseShow(&mouse);
        aduserbutton(&flag, choose1, n);
        if (MousePress(156, 668, 356, 768)) //冻结用户
        {
            return 1;
        }
        if (MousePress(668, 668, 868, 768)) //解冻用户
        {
            return 3;
        }
        if (MousePress(0, 668, 98, 768)) //返回
        {
            return -1;
        }
        if (MousePress(926, 668, 1024, 768)) //退出
        {
            return -2;
        }
        if (*choose1 == 0 && MousePress(425, 533, 599, 633)) //初始界面点击下一页
        {
            *choose1 = *choose1 + 1;
            return -3;
        }
        if (*choose1 == n - 1 && MousePress(425, 533, 599, 633)) //最后一页界面点击上一页
        {
            *choose1 = *choose1 - 1;
            return -3;
        }
        if (*choose1 > 0 && MousePress(562, 533, 736, 633) && (*choose1 != n - 1)) //非第一页后点击下一页
        {
            *choose1 = *choose1 + 1;
            return -3;
        }
        if (*choose1 > 0 && MousePress(288, 533, 462, 633) && (*choose1 != n - 1)) //非第一页后点击上一页
        {
            *choose1 = *choose1 - 1;
            return -3;
        }
    }
    return 0;
}
/*****************************
Function: void aduserdraw(int *choose1)
Description: 绘制界面 
Calls:     put_User()
Called by: aduser_menu()
Table Accessed: UserInfo.dat
Table Updated:  无
Input:  *choose1
Output: 无 
Return: 无 
******************************/
void aduserdraw(int *choose1)
{
    FILE *fp = NULL;
    int long q = 0;
    int m = 0;
    int n = 0;
    int u = 0;
    if ((fp = fopen("UserInfo.dat", "rb+")) == NULL)
    {
        CloseSVGA();
        printf("Unable to open UserInfo.dat!\n");
        getch();
        exit(0);
    }
    fseek(fp, 0, 2);
    q = ftell(fp);
    m = q / sizeof(USER);
    n = m / 5;
    u = m % 5;
    if (u != 0)
    {
        n = n + 1;
    }
    fclose(fp);
    Bar1(0, 0, 1024, 768, 0x875a);
    Line3(0, 98, 1024, 98, 2, 0);
    Line3(0, 198, 1024, 198, 2, 0);
    Line3(0, 298, 1024, 298, 2, 0);
    Line3(0, 398, 1024, 398, 2, 0);
    Line3(0, 498, 1024, 498, 2, 0);
    Bar1(0, 666, 100, 768, 0x5d75);
    Bar1(0, 668, 98, 768, 0xb7b1);
    prt_hz24d(25, 706, "返回", 0, "HZK\\Hzk24h");
    Bar1(924, 666, 1024, 768, 0x5d75);
    Bar1(926, 668, 1024, 768, 0xb7b1);
    prt_hz24d(951, 706, "退出", 0, "HZK\\Hzk24h");
    Bar1(154, 666, 358, 768, 0x4b32);
    Bar1(156, 668, 356, 768, 0xa794);
    prt_hz24d(208, 706, "冻结用户", 0, "HZK\\Hzk24h");
    Bar1(666, 666, 870, 768, 0x4b32);
    Bar1(668, 668, 868, 768, 0xa794);
    prt_hz24d(720, 706, "解冻用户", 0, "HZK\\Hzk24h");
    put_User(choose1); //绘制用户
    if (*choose1 == 0)
    {
        Bar1(250, 510, 750, 650, 0x875a);
        Bar1(423, 531, 601, 635, 0);
        Bar1(425, 533, 599, 633, 0x37dc);
        prt_hz24d(476, 571, "下一页", 0, "HZK\\Hzk24h");
    }
    if (*choose1 > 0 && (*choose1 != n - 1))
    {
        Bar1(250, 510, 750, 650, 0x875a);
        Bar1(286, 531, 464, 635, 0);
        Bar1(288, 533, 462, 633, 0x37dc);
        prt_hz24d(339, 571, "上一页", 0, "HZK\\Hzk24h");
        Bar1(560, 531, 738, 635, 0);
        Bar1(562, 533, 736, 633, 0x37dc);
        prt_hz24d(613, 571, "下一页", 0, "HZK\\Hzk24h");
    }
    if (*choose1 == n - 1)
    {
        Bar1(250, 510, 750, 650, 0x875a);
        Bar1(423, 531, 601, 635, 0);
        Bar1(425, 533, 599, 633, 0x37dc);
        prt_hz24d(476, 571, "上一页", 0, "HZK\\Hzk24h");
    }
}
/*****************************
Function: void aduserbutton(int *flag,int *choose1,int n)
Description: 绘制按钮 
Calls:     无 
Called by: aduser_menu()
Table Accessed: 无
Table Updated:  无
Input:  *flag,*choose1,n 
Output: 无 
Return: 无 
******************************/
void aduserbutton(int *flag, int *choose1, int n)
{
    if (*flag == 0 && MouseIn(0, 668, 98, 768))
    {
        MouseOff(&mouse);
        Bar1(0, 668, 98, 768, 0x1639);
        prt_hz24d(25, 706, "返回", 0, "HZK\\Hzk24h");
        MouseOn(mouse);
        *flag = -1;
    }
    if (*flag == 0 && MouseIn(926, 668, 1024, 768))
    {
        MouseOff(&mouse);
        Bar1(926, 668, 1024, 768, 0x1639);
        prt_hz24d(951, 706, "退出", 0, "HZK\\Hzk24h");
        MouseOn(mouse);
        *flag = -2;
    }
    if (*flag == 0 && MouseIn(156, 668, 356, 768))
    {
        MouseOff(&mouse);
        Bar1(156, 668, 356, 768, 0xb9d7);
        prt_hz24d(208, 706, "冻结用户", 0, "HZK\\Hzk24h");
        MouseOn(mouse);
        *flag = -3;
    }
    if (*flag == 0 && MouseIn(668, 668, 868, 768))
    {
        MouseOff(&mouse);
        Bar1(668, 668, 868, 768, 0xb9d7);
        prt_hz24d(720, 706, "解冻用户", 0, "HZK\\Hzk24h");
        MouseOn(mouse);
        *flag = -5;
    }
    if (*choose1 == 0 && (*flag == 0) && MouseIn(425, 533, 599, 633))
    {
        MouseOff(&mouse);
        Bar1(425, 533, 599, 633, 0xdf70);
        prt_hz24d(476, 571, "下一页", 0, "HZK\\Hzk24h");
        MouseOn(mouse);
        *flag = 1;
    }
    if (*choose1 == n - 1 && (*flag == 0) && MouseIn(425, 533, 599, 633))
    {
        MouseOff(&mouse);
        Bar1(425, 533, 599, 633, 0xdf70);
        prt_hz24d(476, 571, "上一页", 0, "HZK\\Hzk24h");
        MouseOn(mouse);
        *flag = 4;
    }
    if (*choose1 > 0 && (*flag == 0) && MouseIn(288, 533, 462, 633) && (*choose1 != n - 1))
    {
        MouseOff(&mouse);
        Bar1(288, 533, 462, 633, 0xdf70);
        prt_hz24d(339, 571, "上一页", 0, "HZK\\Hzk24h");
        MouseOn(mouse);
        *flag = 2;
    }
    if (*choose1 > 0 && (*flag == 0) && MouseIn(562, 533, 736, 633) && (*choose1 != n - 1))
    {
        MouseOff(&mouse);
        Bar1(562, 533, 736, 633, 0xdf70);
        prt_hz24d(613, 571, "下一页", 0, "HZK\\Hzk24h");
        MouseOn(mouse);
        *flag = 3;
    }
    else if (*flag == -1 && !(MouseIn(0, 668, 98, 768)))
    {
        MouseOff(&mouse);
        Bar1(0, 668, 98, 768, 0xb7b1);
        prt_hz24d(25, 706, "返回", 0, "HZK\\Hzk24h");
        MouseOn(mouse);
        *flag = 0;
    }
    else if (*flag == -2 && !(MouseIn(926, 668, 1024, 768)))
    {
        MouseOff(&mouse);
        Bar1(926, 668, 1024, 768, 0xb7b1);
        prt_hz24d(951, 706, "退出", 0, "HZK\\Hzk24h");
        MouseOn(mouse);
        *flag = 0;
    }
    else if (*flag == -3 && !(MouseIn(156, 668, 356, 768)))
    {
        MouseOff(&mouse);
        Bar1(156, 668, 356, 768, 0xa794);
        prt_hz24d(208, 706, "冻结用户", 0, "HZK\\Hzk24h");
        MouseOn(mouse);
        *flag = 0;
    }
    else if (*flag == -5 && !(MouseIn(668, 668, 868, 768)))
    {
        MouseOff(&mouse);
        Bar1(668, 668, 868, 768, 0xa794);
        prt_hz24d(720, 706, "解冻用户", 0, "HZK\\Hzk24h");
        MouseOn(mouse);
        *flag = 0;
    }
    else if (*choose1 == 0 && (*flag == 1) && !(MouseIn(425, 533, 599, 633)))
    {
        MouseOff(&mouse);
        Bar1(425, 533, 599, 633, 0x37dc);
        prt_hz24d(476, 571, "下一页", 0, "HZK\\Hzk24h");
        MouseOn(mouse);
        *flag = 0;
    }
    else if (*choose1 == n - 1 && (*flag == 4) && !(MouseIn(425, 533, 599, 633)))
    {
        MouseOff(&mouse);
        Bar1(425, 533, 599, 633, 0x37dc);
        prt_hz24d(476, 571, "上一页", 0, "HZK\\Hzk24h");
        MouseOn(mouse);
        *flag = 0;
    }
    else if (*choose1 > 0 && (*flag == 2) && !(MouseIn(288, 533, 462, 633)) && (*choose1 != n - 1))
    {
        MouseOff(&mouse);
        Bar1(288, 533, 462, 633, 0x37dc);
        prt_hz24d(339, 571, "上一页", 0, "HZK\\Hzk24h");
        MouseOn(mouse);
        *flag = 0;
    }
    else if (*choose1 > 0 && (*flag == 3) && !(MouseIn(562, 533, 736, 633)) && (*choose1 != n - 1))
    {
        MouseOff(&mouse);
        Bar1(562, 533, 736, 633, 0x37dc);
        prt_hz24d(613, 571, "下一页", 0, "HZK\\Hzk24h");
        MouseOn(mouse);
        *flag = 0;
    }
}
/*****************************
Function: int user_ice(void)
Description: 冻结用户 
Calls:     user_freeze() 
Called by: aduser_menu()
Table Accessed: 无
Table Updated:  无
Input:  无
Output: 无 
Return: 1->返回用户管理主函数 
******************************/
int user_ice(void)
{
    char name[12 + 1] = "";
    int choose = 0;
    int flag = 0;
    int key;
    MouseOff(&mouse);
    Bar1(298, 198, 702, 402, 0);
    Bar1(300, 200, 700, 400, 0x8edf);
    prt_hz24d(356, 228, "请输入您要冻结的用户账号", 0, "HZK\\Hzk24h");
    Bar1(402, 258, 598, 312, 0);
    Bar1(404, 260, 596, 310, 0xffff); //输入框
    Bar1(348, 333, 452, 377, 0x4b32);
    Bar1(350, 335, 450, 375, 0x8ff2);
    prt_hz24d(376, 343, "确认", 0, "HZK\\Hzk24h"); //确认键
    Bar1(548, 333, 652, 377, 0x4b32);
    Bar1(550, 335, 650, 375, 0x8ff2);
    prt_hz24d(576, 343, "取消", 0, "HZK\\Hzk24h"); //取消
    Mouse_Init();
    while (choose != -1)
    {
        MouseShow(&mouse);
        button1(&flag);
        if (MousePress(404, 260, 596, 310))
        {
            MouseOff(&mouse);
            Getinfo(404, 260, name, 12);
            MouseOn(mouse);
        }
        if (MousePress(350, 335, 450, 375))
        {
            choose = -1;
        }
        if (MousePress(550, 335, 650, 375))
        {

            return 1;
        }
    }
    key = user_freeze(name);
    if (key == 1)
    {
        Bar1(400, 250, 600, 350, 0x8edf);
        Bar1(403, 253, 597, 347, 0x327d);
        Bar1(405, 255, 595, 345, 0x8edf);
        prt_hz24d(452, 283, "冻结成功", 0, "HZK\\Hzk24h");
        delay(1500);
        return 1;
    }
    if (key == 0)
    {
        Bar1(300, 200, 700, 400, 0x8edf);
        Bar1(303, 203, 697, 397, 0x327d);
        Bar1(305, 205, 695, 395, 0x8edf);
        prt_hz24d(416, 252, "该用户已被冻结", 0, "HZK\\Hzk24h");
        prt_hz24d(440, 323, "请重新输入", 0, "HZK\\Hzk24h");
        delay(1500);
        return 1;
    }
    if (key == 2)
    {
        Bar1(300, 200, 700, 400, 0x8edf);
        Bar1(303, 203, 697, 397, 0x327d);
        Bar1(305, 205, 695, 395, 0x8edf);
        prt_hz24d(428, 252, "未找到该用户", 0, "HZK\\Hzk24h");
        prt_hz24d(440, 323, "请重新输入", 0, "HZK\\Hzk24h");
        delay(1500);
        return 1;
    }
    return 0;
}

/*****************************
Function: void button1(int *flag)
Description: 按钮反馈 
Calls:     无 
Called by: aduser_menu()
Table Accessed: 无
Table Updated:  无
Input:  *flag 
Output: 无 
Return: 无
******************************/
void button1(int *flag)
{
    if (*flag == 0 && MouseIn(350, 335, 450, 375))
    {
        MouseOff(&mouse);
        Bar1(348, 333, 452, 377, 0xf0a0);
        Bar1(350, 335, 450, 375, 0x1dbe);
        prt_hz24d(376, 343, "确认", 0, "HZK\\Hzk24h");
        MouseOn(mouse);
        *flag = 1;
    }
    if (*flag == 0 && MouseIn(550, 335, 650, 375))
    {
        MouseOff(&mouse);
        Bar1(548, 333, 652, 377, 0xf0a0);
        Bar1(550, 335, 650, 375, 0x1dbe);
        prt_hz24d(576, 343, "取消", 0, "HZK\\Hzk24h");
        MouseOn(mouse);
        *flag = 2;
    }
    else if (*flag == 1 && !(MouseIn(350, 335, 450, 375)))
    {
        MouseOff(&mouse);
        Bar1(348, 333, 452, 377, 0x4b32);
        Bar1(350, 335, 450, 375, 0x8ff2);
        prt_hz24d(376, 343, "确认", 0, "HZK\\Hzk24h");
        MouseOn(mouse);
        *flag = 0;
    }
    else if (*flag == 2 && !(MouseIn(550, 335, 650, 375)))
    {
        MouseOff(&mouse);
        Bar1(548, 333, 652, 377, 0x4b32);
        Bar1(550, 335, 650, 375, 0x8ff2); //重新选择
        prt_hz24d(576, 343, "取消", 0, "HZK\\Hzk24h");
        MouseOn(mouse);
        *flag = 0;
    }
}
/*****************************
Function: int no_iced(void)
Description:解冻用户 
Calls:     int no_iced(void)() 
Called by: aduser_menu()
Table Accessed: 无
Table Updated:  无
Input:  无
Output: 无 
Return: 1->返回用户管理主函数 
******************************/
int no_iced(void)
{
    char name[12 + 1] = "";
    int choose = 0;
    int flag = 0;
    char key;

    MouseOff(&mouse);
    Bar1(298, 198, 702, 402, 0);
    Bar1(300, 200, 700, 400, 0x8edf);
    prt_hz24d(356, 235, "请输入您要解冻的用户账号", 0, "HZK\\Hzk24h");
    Bar1(402, 278, 598, 317, 0);
    Bar1(404, 280, 596, 315, 0xffff); //输入框
    Bar1(348, 348, 452, 387, 0x4b32);
    Bar1(350, 350, 450, 385, 0x8ff2); //确认
    prt_hz24d(376, 355, "确认", 0, "HZK\\Hzk24h");
    Bar1(548, 348, 652, 387, 0x4b32);
    Bar1(550, 350, 650, 385, 0x8ff2); //取消
    prt_hz24d(576, 355, "取消", 0, "HZK\\Hzk24h");
    Mouse_Init();
    while (choose != -1)
    {
        MouseShow(&mouse);
        button3(&flag);
        if (MousePress(404, 280, 596, 315))
        {
            MouseOff(&mouse);
            Getinfo(404, 280, name, 12);
            MouseOn(mouse);
        }
        if (MousePress(350, 350, 450, 385))
        {
            choose = -1;
        }
        if (MousePress(550, 350, 650, 385))
        {
            return 1;
        }
    }
    key = user_unfreeze(name);
    if (key == 1)
    {
        Bar1(400, 250, 600, 350, 0x8edf);
        Bar1(403, 253, 597, 347, 0x327d);
        Bar1(405, 255, 595, 345, 0x8edf);
        prt_hz24d(452, 283, "解冻成功", 0, "HZK\\Hzk24h"); //有个bug
        delay(1500);
        return 1;
    }
    if (key == 0)
    {
        Bar1(300, 200, 700, 400, 0x8edf);
        Bar1(303, 203, 697, 397, 0x327d);
        Bar1(305, 205, 695, 395, 0x8edf);
        prt_hz24d(416, 252, "该用户未被冻结", 0, "HZK\\Hzk24h");
        prt_hz24d(440, 323, "请重新输入", 0, "HZK\\Hzk24h");
        delay(1500);
        return 1;
    }
    if (key == 2)
    {
        Bar1(300, 200, 700, 400, 0x8edf);
        Bar1(303, 203, 697, 397, 0x327d);
        Bar1(305, 205, 695, 395, 0x8edf);
        prt_hz24d(428, 252, "未找到该用户", 0, "HZK\\Hzk24h");
        prt_hz24d(440, 323, "请重新输入", 0, "HZK\\Hzk24h");
        delay(1500);
        return 1;
    }
    return 0;
}
/*****************************
Function: void button3(int *flag)
Description: 按钮反馈 
Calls:     无 
Called by: aduser_menu()
Table Accessed: 无
Table Updated:  无
Input:  *flag 
Output: 无 
Return: 无
******************************/
void button3(int *flag)
{
    if (*flag == 0 && MouseIn(350, 350, 450, 385))
    {
        MouseOff(&mouse);
        Bar1(348, 348, 452, 387, 0xf0a0);
        Bar1(350, 350, 450, 385, 0x1dbe);
        prt_hz24d(376, 355, "确认", 0, "HZK\\Hzk24h");
        MouseOn(mouse);
        *flag = 1;
    }
    if (*flag == 0 && MouseIn(550, 350, 650, 385))
    {
        MouseOff(&mouse);
        Bar1(548, 348, 652, 387, 0xf0a0);
        Bar1(550, 350, 650, 385, 0x1dbe);
        prt_hz24d(576, 355, "取消", 0, "HZK\\Hzk24h");
        MouseOn(mouse);
        *flag = 2;
    }
    else if (*flag == 1 && !(MouseIn(350, 350, 450, 385)))
    {
        MouseOff(&mouse);
        Bar1(348, 348, 452, 387, 0x4b32);
        Bar1(350, 350, 450, 385, 0x8ff2);
        prt_hz24d(376, 355, "确认", 0, "HZK\\Hzk24h");
        MouseOn(mouse);
        *flag = 0;
    }
    else if (*flag == 2 && !(MouseIn(550, 350, 650, 385)))
    {
        MouseOff(&mouse);
        Bar1(548, 348, 652, 387, 0x4b32);
        Bar1(550, 350, 650, 385, 0x8ff2);
        prt_hz24d(576, 355, "取消", 0, "HZK\\Hzk24h");
        MouseOn(mouse);
        *flag = 0;
    }
}
/*****************************
Function: int put_User(int *choose1)
Description:打印用户信息 
Calls:     put_run()
Called by: aduserdraw()
Table Accessed: UserInfo.dat
Table Updated:  无
Input:  *flag 
Output: 无 
Return: -1
******************************/
int put_User(int *choose1)
{
    FILE *fp = NULL;

    USER *e = NULL;
    //	char s[13]="";
    int i = 0, page, u, count, length;
    //	char ordernum[5];
    if ((fp = fopen("UserInfo.dat", "rb+")) == NULL)
    {
        CloseSVGA();
        printf("Unable to open UserInfo.dat!\n");
        getch();
        exit(0);
    }
    if ((e = (USER *)malloc(sizeof(USER))) == NULL)
    {

        delay(3000);
        exit(1); //分配空间不足，退出程序
    }

    fseek(fp, 0, SEEK_END);

    length = ftell(fp) / sizeof(USER);
    page = length / 5;
    u = length % 5;

    if (page == 0 || (page - *choose1) == 0)
        count = u;
    else
        count = 5;

    fseek(fp, 0, SEEK_SET);
    for (i = 0; i < count; i++)
    {
        fseek(fp, (i + 5 * (*choose1)) * sizeof(USER), SEEK_SET);
        fread(e, sizeof(USER), 1, fp);

        prt_hz16_asc16_size(10, 20 + 100 * i, 2, 2, e->UserName, 0, "HZK\\Hzk16k");

        prt_hz16_asc16_size(160 + 40, 20 + 100 * (i), 2, 2, e->password, 0, "HZK\\Hzk16k");
        prt_hz16_asc16_size(300 + 40, 20 + 100 * (i), 2, 2, e->IDnumber, 0, "HZK\\Hzk16k");
        put_run(e->UserState, i);
    }
    fclose(fp);
    return -1;
}
/*****************************
Function: void put_run(char s,int i) 
Description:判断用户是否冻结 
Calls:     无 
Called by: put_User()
Table Accessed: 无 
Table Updated:  无
Input:  *flag 
Output: s , i; 
Return: 无
******************************/
void put_run(char s, int i)
{
    if (s == '1')
    {
        prt_hz24d(910, 20 + 100 * (i), "可通报", 0, "HZK\\Hzk24h");
    }
    if (s == '2')
    {
        prt_hz24d(910, 20 + 100 * (i), "冻结", 0, "HZK\\Hzk24h");
    }
}