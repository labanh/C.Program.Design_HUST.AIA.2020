/*******************************************
FileName: admod.h
Author:   韩海若
Date：    2020/10/29
Description: 该程序文件用于管理员的数据修改
Function List: 
        login_user()   //用户登录函数 
*******************************************/
#ifndef _ADMOD_H
#define _ADMOD_H

#include "data.h"

int admin_modify(void);
void modify_page(void);
void Unhighlight(void);
int pop_window1(int *key,char *area);

void click_Data_Block(int *datakey);
void mouse_feedback_main(void);
void modify_MainPage(int *key,char *area);
void pop_window2(int datakey,SAVEDAY *d,char *area);

#endif
