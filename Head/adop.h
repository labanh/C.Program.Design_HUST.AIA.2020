/*******************************************
FileName: adop.c
Author:   刘子恒 
Date：    2020/10/27
Description: 该文件主要用于管理员选择操作界面 
Others: 无
Function List: 
        admin_menu() 选择操作菜单函数 
		admindraw()  画图函数 
		admindraw2() 画图函数 
		adminbutton()按钮反馈函数 
********************************************/
#ifndef _ADOP_H
#define _ADOP_H

int admin_menu(void); 
void admindraw(void);
void admindraw2(void);
void admin_button(int *flag);



#endif
