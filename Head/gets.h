#ifndef GETS_H
#define GETS_H

#define ENTER   0x1c0d

void show_gb(int x,int y);
/*画光标函数*/ 

void Getinfo(int x1,int y1,char *pm,int num);//num为最大值
/*输入用户名，日期等无需隐藏的信息*/

void Getcode(int x1,int y1,char *code,int num);
/*输入密码等需要隐藏的信息*/


#endif



