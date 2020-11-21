/*******************************************
FileName: visual.h
Author:   韩海若
Date：    2020/10/28
Description: 该程序文件用于实现疫情风险等级可视化
Others: 无
Function List: 
        int visual page()   //底层界面绘制
        void visual_basic() //可视化区域风险表示
        int risk_level()    //判断风险等级
********************************************/
#ifndef _VISUAL_H_
#define _VISUAL_H_

#include"common.h"
#include "login.h"  //用于“返回”“注销”操作返回登录界面

//界面绘制，返回值提供给main()用于跳转下一界面
int visual_page(void);

//可视化区域绘制
void visual_basic(void);

//根据相应数据判断风险并用不同颜色显示
int risk_level(int cases);

#endif
