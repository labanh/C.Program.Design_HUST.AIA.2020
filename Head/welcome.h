/**********************************************
FileName: welcome.h
Author:   韩海若
Date:     2020/10/28
Description:该程序文件用于绘制欢迎界面, 界面尺寸 1024x768
            背景色(浅绿)0x9eef, 可进入用户或管理员登录界面
            (login.c), 返回值:
                1    ->用户登录
                2    ->管理员登录
               -1    ->退出
Others: 无
Function list: 
        welcome()  绘制欢迎界面         
***********************************************/
#ifndef WELCOME_H
#define WELCOME_H

int welcome(void);

#endif
