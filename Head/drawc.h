/*******************************************
FileName: drawc.h
Author:   刘子恒 
Date：    2020/10/16
Description: 该文件主要用于绘制折线图 
Others: 无
Function List: 
        drawchart(); 绘制折线图函数 
 		readata();	 读取数据函数 
 		areafunc();	 地区编号转换函数 
 		giveweight();改变权重函数 
 		findday();	 寻找对应日期数据函数 
********************************************/
#ifndef _DRAWC_H_
#define _DRAWC_H_

void drawchart(CHARTDATA *data,int areakey,int count);

void readata(CHARTDATA *data,int areakey,int count);

void areafunc(int areakey,char area[]);

void giveweight(int *areakey,float *x);

int findday(int year,int month,int day);

#endif


