/*******************************************
FileName: showinfo.h
Author:   韩海若
Date：    2020/10/28
Description: 该程序文件用于实现疫情数据排行图
Others: 无
Function List: 
        int showinfo_main(void); //参数初始化, 调用其他函数绘图
        void drawbar(int key); //绘制选择键
        void bubble_Sort(int arr[], int eq_loc[], int len); //冒泡排序
        void swap(int *a, int *b); //交换两数
********************************************/
#ifndef _SHOWINFO_H_
#define _SHOWINFO_H_

int showinfo_main(void);
void drawbar(int key);
void bubble_Sort(int arr[], int eq_loc[], int len);
void swap(int *a, int *b);

#endif
