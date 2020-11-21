/*******************************************
FileName: aduser.h
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
#ifndef ADUSER.H
#define ADUSER.H

int aduser(void);
int aduser_menu(int *choose1);
void aduserdraw(int *choose1);
void aduserbutton(int *flag,int *choose1,int n);
int user_ice(void);
int no_iced(void);
void button1(int *flag);
void button3(int *flag);
int put_User(int *choose1);
void put_run(char s,int i);

#endif
