/*******************************************
FileName: draw.h
Author:   韩海若
Date：    2020/10/28
Description: 该程序文件用于绘制可视化界面的建筑
             和排行中的条形图
Function List: 
        void draw_floor1(int x, int y); //绘制 visual_basic 中的建筑
        void draw_floor2(int x, int y);
        void draw_floor3(int x, int y);
        void draw_axis(int x, int y); //坐标轴
        void draw_column(int x, int y, int len); //条形图
********************************************/
#ifndef	_DRAW_H
#define	_DRAW_H

void draw_floor1(int x, int y);
void draw_floor2(int x, int y);
void draw_floor3(int x, int y);
void draw_axis(int x, int y);
void draw_column(int x, int y, int len);

#endif